<?php
/**
 * @file
 * Batch processing and heavy lifting associated with export
 */

/**
 * Helper function to start the HTML rendering job
 */
function _html_export_job_page() {
  $form = array();
  $path_provders = module_invoke_all('html_export_add_path_provider');
  // allow projects to alter list
  drupal_alter('html_export_add_path_provider', $path_provders);
  // convert providers to options array
  foreach ($path_provders as $key => $provider) {
    $options[$key] = t($provider['title']);
  }
  // build the form
  $form['path_selector'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Path selectors'),
    '#description' => t('Select paths to combine in formulating a list of paths in which to use for export.'),
    '#options' => $options,
    '#required' => TRUE,
  );
  $form['html_export_dom_remove'] = array(
    '#type' => 'textfield',
    '#title' => t('Advanced dom removal'),
    '#description' => t("Supply a css style selector to target the removal of. This is especially useful for removing things like the admin toolbar, tabs, or other elements you don't want to have exported. Split selectors with a comma."),
    '#default_value' => variable_get('html_export_dom_remove', ''),
  );
	$form['anonymous'] = array(
		'#type' => 'checkbox',
		'#default_value' => TRUE,
		'#title' => t('Render as anonymous'),
		'#description' => t('Render pages via an external request so that they are treated as anonymous.'),
	);
  // enable ability to export as if you are another user
  if (module_exists('masquerade')) {
    if (masquerade_access('autocomplete')) {
      $markup_value .= t('Enter the username to masquerade as.');
      $form['masquerade_user_field'] = array(
        '#type' => 'textfield',
        '#title' => t('EXPERIMENTAL: Masquerade for export'),
        '#description' => t('Select a user account to masquerade as during this export. This allows you to render to file as if you were a different user. This has known page rendering conflicts with certain projects, anonymous is recommended for an accurate export.'),
        '#size' => '18',
        '#default_value' => '',
        '#autocomplete_path' => 'masquerade/autocomplete',
        '#required' => FALSE,
      );
    }
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Render as html'),
  );
  return $form;
}

/**
 * Submit handler for HTML rendering job
 */
function _html_export_job_page_submit($form, &$form_state) {
  // invoke the hooks that will provide us with a list of paths
  $path_provders = module_invoke_all('html_export_add_path_provider');
  // allow projects to alter list
  drupal_alter('html_export_add_path_provider', $path_provders);
  // use the selector from the previous form as to what paths to gather
  $paths = array();
  $uid = NULL;
  $selectors = $form_state['values']['path_selector'];
  foreach ($selectors as $selector) {
    // only submit arg if its set to avoid notices
    if (isset($path_provders[$selector]['arg'])) {
      $tmp = call_user_func_array($path_provders[$selector]['callback'], array($path_provders[$selector]['arg']));
    }
    else {
      $tmp = call_user_func_array($path_provders[$selector]['callback'], array());
    }
    $paths = array_merge($paths, $tmp);
    // make sure all paths are numeric as spec won't be
    sort($paths);
  }
  // bring along advanced dom removal on publish, accounting for multiple
  $dom_remove = explode(',', $form_state['values']['html_export_dom_remove']);
	// see if checkbox for anonymous was set
  if (!empty($form_state['values']['anonymous'])) {
		$uid = 0;
	}
	else {
		// see if masquerade was enabled and used
		if (!empty($form_state['values']['masquerade_user_field'])) {
			// convert name we were passed to uid
			$masq_user = user_load(array('name' => $form_state['values']['masquerade_user_field']));
			if (isset($masq_user->uid)) {
				$uid = $masq_user->uid;
			}
		}
	}
  
  html_export_process_job($paths, 'export'. time(), $dom_remove, $uid);
}

/**
 * Initialize batch job
 */
function html_export_process_job($paths, $export_folder, $dom_remove = NULL, $uid = NULL) {
  $GLOBALS['html_export_active'] = TRUE;
  $anonymous = FALSE;
	if ($uid != NULL) {
    masquerade_switch_user($uid);
  }
	elseif ($uid == 0) {
		$anonymous = TRUE;
	}
  // create a folders
  $dir = file_create_path(file_directory_path() . '/html_export');
  file_check_directory($dir, 1);
  // make the directory path for this export (just timestamp)
  $export_path = $dir .'/'. $export_folder;
  file_check_directory(file_create_path($export_path), 1);
  // render pages and deep copy directories
  $batch = array(
    'operations' => array(
      array('html_export_render_pages', array($paths, $export_path, $dom_remove, $anonymous)),
      array('html_export_copy_all_resources', array($export_path)),
      array('html_export_cleanup', array($export_path, $uid)),
      ),
    'finished' => 'html_export_finished',
    'title' => t('Processing html export'),
    'init_message' => t('HTML export is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('HTML export has encountered an error.'),
    'file' => drupal_get_path('module', 'html_export') . '/html_export.pages.inc',
  );
  batch_set($batch);
  batch_process('html_export');
}

/**
 * Batch Operation Callback to render all pages
 */
function html_export_render_pages($paths, $export_path, $dom_remove, $anonymous, &$context) {
  // first run
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($paths);
    $context['results']['paths'] = array();
    $context['results']['copy_list'] = array();
  }
  // process limit amount of records
  $count = 0;
  while ($count<HTML_EXPORT_PROCESS_LIMIT && $context['sandbox']['progress'] < $context['sandbox']['max']) {
    $active = $context['sandbox']['progress'];
		$context['message'] = t('Now processing %path', array('%path' => drupal_get_path_alias($paths[$active])));
		// Store some result for post-processing in the finished callback.
    $context['results']['paths'][] = $paths[$active];
    if ($anonymous) {
			$root = $_SERVER['HTTP_ORIGIN'] . base_path();
			if (variable_get('clean_url', 0)) {
				$http = drupal_http_request($root . $paths[$active]);
			}
			else {
				$http = drupal_http_request($root .'index.php?q='. $paths[$active]);
			}
			// store http data object in variable for processing
			$data = $http->data;
		}
		else {
			menu_set_active_item($paths[$active]);
			$menu_item = menu_get_item($paths[$active]);
			menu_set_item(NULL, $menu_item);
			// squelch any and all messages at this time
			$tmpmsg = drupal_get_messages();
			// issue all calls by making things active
			// get object to then be able to activate menu
			$result = menu_execute_active_handler($paths[$active]);
			if (strpos($paths[$active], 'node') !== FALSE) {
				$obj = menu_get_object('node', 1, $paths[$active]);
				if (isset($obj->book)) {
					menu_tree_all_data($obj->book['menu_name'], $obj->book);
				}
				else if(isset($obj->menu)) {
					menu_tree_all_data($obj->menu['menu_name'], $obj->menu);
				}
			}
			// render page
			$data = theme('page', $result);
		}
		// locate all the resources used to make this page and copy them
    _html_export_copy_resources($data, $export_path, $context);
    // allow projects to process page data
    drupal_alter('html_export_data', $data, $paths, $active, $dom_remove);
    // prepare to save file by creating folders for path
    $tmp = split('/', $paths[$active]);
    $folder_path = '';
    // build path leading up to the current one
    foreach ($tmp as $folder) {
      $folder_path .= '/'. $folder;
      $tmppath = file_create_path($export_path . $folder_path);
      // ensure we can write there
      file_check_directory($tmppath, 1);
    }
    // open a writable file at that location
    if ($file = fopen($export_path .'/'. $paths[$active] .'/index.html' , 'w')) {
      fwrite($file, $data);
      fclose($file);
    }
    // Update our progress information.
    $context['sandbox']['progress']++;
		$count++;
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Batch Operation Callback to copy all resources
 */
function html_export_copy_all_resources($export_path, &$context) {
  // first run
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['active_copy_id'] = 0;
    $context['results']['files'] = array();
    $context['sandbox']['max'] = count($context['results']['copy_list']);
  }
  // process limit amount of records
  $count = 0;
  $active_copy_id = $context['sandbox']['active_copy_id'];
  while ($count<HTML_EXPORT_FILE_PROCESS_LIMIT && $active_copy_id < $context['sandbox']['max']) {
    _html_export_copy_file($context['results']['copy_list'][$active_copy_id], $export_path, $context);
    // Update our progress information.
    $context['message'] = t('Now copying %file', array('%file' => $context['results']['copy_list'][$active_copy_id]));
    $active_copy_id++;
    $count++;
    $context['sandbox']['progress']++;
    $context['sandbox']['active_copy_id'] = $active_copy_id;
  }
  $tmpmsg = drupal_get_messages();
  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Batch Operation Callback to clean up before finished
 */
function html_export_cleanup($export_path, $uid, &$context) {
  dpm($context);
	// unmasquerade if we are done
  if ($uid != NULL) {
    masquerade_switch_back();
  }
  // compress it all up if we can
  if (html_export_compress_directory($export_path, $context)) {
    $message = l(t('Click to download export'), $export_path .'.gz', array('absolute' => TRUE, 'purl' => array('disabled' => TRUE)));
  }
  else {
    $message = l(t('Click to locate export'), $export_path, array('absolute' => TRUE, 'purl' => array('disabled' => TRUE)));
  }
  drupal_set_message(filter_xss($message));
  $GLOBALS['html_export_active'] = FALSE;
}

/**
 * Helper function to deep copy all resource files
 */
function _html_export_copy_resources($data, $export_path, &$context) {
  // Create a DOM object
  $html_obj = new simple_html_dom();
  $copy_list = array();
  // Load HTML from a string
  $html_obj->load($data);
  $resources = array('link', 'img', 'script', 'a', 'object');
  // repair paths for these resources
  foreach ($resources as $find) {
    // find the selectors in the document
    $objs = $html_obj->find($find);
    // account for ability to find multiple objects
    foreach ($objs as $obj) {
      // account for internal href resources, cut arguments
      if (isset($obj->href) && strpos($obj->href, 'http://') === FALSE && strpos($obj->href, 'https://') === FALSE && strpos($obj->href, '.') !== FALSE && !in_array($obj->href, $copy_list)) {
          $href = explode('?', $obj->href);
          $copy_list[$href[0]] = $href[0];
      }
      // account for internal src resources, cut arguments
      if (isset($obj->src) && strpos($obj->src, 'http://') === FALSE && strpos($obj->src, 'https://') === FALSE && strpos($obj->src, '.') !== FALSE && !in_array($obj->href, $copy_list)) {
        $src = explode('?', $obj->src);
        $copy_list[$src[0]] = $src[0];
      }
    }
  }
  sort($copy_list);
  // assets to copy, need to filter out base path
  foreach ($copy_list as $key => $file) {
    // only replace first occurance as this will be base path
    $pos = strpos($file, base_path());
    if ($pos !== FALSE) {
      $context['results']['copy_list'][$key] = substr_replace($file, '', $pos, drupal_strlen(base_path()));
    }
  }
  return $copy_list;
}

/**
 * Helper function to deep copy all resource files
 */
function _html_export_copy_file($source, $export_path, &$context) {
  // Simple copy for a file
  if (is_file($source)) {
    // split to build the folder structure
    $tmp = explode('/', $source);
    array_pop($tmp);
    $folder_path = '';
    $deepcopy = implode('/', $tmp);
    // build path leading up to the current one
    foreach ($tmp as $folder) {
      $folder_path .= '/'. $folder;
      $tmppath = file_create_path($export_path . $folder_path);
      // ensure we can write there
      file_check_directory($tmppath, 1);
    }
    // deep copy in each directory assembled previously ignoring files and devel
    if (strpos($deepcopy, file_directory_path()) === FALSE && strpos($deepcopy, drupal_get_path('module', 'devel')) === FALSE) {
      _html_export_deep_file_copy($deepcopy, $export_path . $folder_path, $context);
    }
    $context['results']['files'][$source] = $source;
    return copy($source, $export_path .'/'. $source);
  }
}

/**
 * Helper function to deep copy all resource files
 */
function _html_export_deep_file_copy($source, $dest, &$context) {
  // Simple copy for a file
  if (is_file($source)) {
    $context['results']['files'][$source] = $source;
    return copy($source, $dest);
  }
  // Make destination directory
  if (!is_dir($dest)) {
    mkdir($dest);
  }
  // Loop through the folder
  $dir = dir($source);
  while (false !== $entry = $dir->read()) {
    // skip over all the files types that make no sense in an export
    if ($entry == '.' || $entry == '..' || $entry == '.DS_Store' || $entry == '.htaccess' || $entry == '.project' || $entry == 'Thumbs.db' || $entry == '_notes' || strpos($entry, '.engine') != 0 || strpos($entry, '.php') != 0 || strpos($entry, '.inc') != 0 || strpos($entry, '.include') != 0 || strpos($entry, '.info') != 0 || strpos($entry, '.txt') != 0 || strpos($entry, '.ini') != 0 || strpos($entry, '.po') != 0 || strpos($entry, '.install') != 0 || strpos($entry, '.module') != 0 || strpos($entry, '.html') != 0 || strpos($entry, '.htm') != 0 || strpos($entry, '.test') != 0) {
      continue;
    }
    // Deep copy directories, ignore the html_export ones
    if ($dest !== "$source/$entry" && strpos($source, 'html_export') == 0 ) {
      _html_export_deep_file_copy("$source/$entry", "$dest/$entry", $context);
    }
  }
  // Clean up
  $dir->close();
  return TRUE;
}

/**
 * Batch 'finished' callback
 */
function html_export_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    $message = t('Export created %count html pages and %files files.', array('%count' => count($results['paths']), '%files' => count($results['files'])));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
  drupal_set_message($message);
}