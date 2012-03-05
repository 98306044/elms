<?php

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
		'#options' => $options,
		'#required' => TRUE,
	);
	$form['html_export_dom_remove'] = array(
	  '#type' => 'textfield',
		'#title' => t('Advanced dom removal'),
		'#description' => t("Supply a css style selector to target the removal of. This is especially useful for removing things like the admin toolbar, tabs, or other elements you don't want to have exported. Split selectors with a comma."),
		'#default_value' => variable_get('html_export_dom_remove', ''),
	);
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Render to html'),
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
	// @todo: select the specific provider selected in the pervious form and run its callback
	// need to document the API too
	$paths = array();
	$selectors = $form_state['values']['path_selector'];
	foreach ($selectors as $selector) {
		$tmp = call_user_func_array($path_provders[$selector]['callback'], array());
		$paths = array_merge($paths, $tmp);
	}
	// bring along advanced dom removal on publish, accounting for multiple
	$dom_remove = explode(',', $form_state['values']['html_export_dom_remove']);
	
  // create a folders
  $dir = file_create_path(file_directory_path() . '/html_export');
  file_check_directory($dir, 1);
  // make the directory path for this export (just timestamp)
  $export_path = $dir .'/export'. time();
  file_check_directory(file_create_path($export_path), 1);
  // process the records in the batch
  $base = str_replace('index.php', '', $_SERVER['PATH_TRANSLATED']);
	// render pages and deep copy directories
	// @todo: more intelligent selection
  $batch = array(
    'operations' => array(
      array('_html_export_copy_files', array($base .'sites', $export_path . '/sites')),
      array('_html_export_copy_files', array($base .'modules', $export_path . '/modules')),
      array('_html_export_copy_files', array($base .'themes', $export_path . '/themes')),
      array('_html_export_copy_files', array($base .'misc', $export_path . '/misc')),
		  array('_html_export_copy_files', array($base .'profiles', $export_path . '/profiles')),
			array('html_export_render_pages', array($paths, $export_path, $dom_remove)),
      ),
    'finished' => 'html_export_finished',
    'title' => t('Processing HTML Export'),
    'init_message' => t('HTML Export is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('HTML Export has encountered an error.'),
    'file' => drupal_get_path('module', 'html_export') . '/html_export.pages.inc',
  );
  batch_set($batch);
  batch_process('html_export');
}

/**
 * Batch Operation Callback
 */
function html_export_render_pages($paths, $export_path, $dom_remove, &$context) {
	$GLOBALS['html_export_active'] = TRUE;
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_path'] = 0;
    $context['sandbox']['max'] = count($paths);
		$context['results'][] = $export_path;
  }
  // process limit amount of records
	$count = 0;
  $active_path_count = $context['sandbox']['current_path'];
  while ($count<HTML_EXPORT_PROCESS_LIMIT && $active_path_count < $context['sandbox']['max']) {
    // squelch any and all messages at this time
    $tmpmsg = drupal_get_messages();
    // issue all calls
    $return = menu_execute_active_handler($paths[$active_path_count]);
		// @todo: need to activate a menu or collapse/expand is inaccurate
		// menu_tree_all_data();
    // render as a page
    $data = theme('page', $return);
		// allow projects to process page data
    drupal_alter('html_export_data', $data, $paths, $active_path_count, $dom_remove);
    // prepare to save file by creating folders for path
    $tmp = split('/', $paths[$active_path_count]);
    $folder_path = '';
    // build path leading up to the current one
    foreach ($tmp as $folder) {
      $folder_path .= '/'. $folder;
      $tmppath = file_create_path($export_path . $folder_path);
      // ensure we can write there
      file_check_directory($tmppath, 1);
    }
    // open a writable file at that location
    if ($file = fopen($export_path .'/'. $paths[$active_path_count] .'/index.html' , 'w')) {
      fwrite($file, $data);
      fclose($file);
    }
    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_path'] = $active_path_count;
    $context['message'] = t('Now processing %path', array('%path' => drupal_get_path_alias($paths[$active_path_count])));
		$count++;
    $active_path_count++;
		// Store some result for post-processing in the finished callback.
    $context['results'][] = drupal_get_path_alias($paths[$active_path_count]);
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Helper function to deep copy all resource files
 */
function _html_export_copy_files($source, $dest, &$context) {
  // Simple copy for a file
  if (is_file($source)) {
    return copy($source, $dest);
  }
  // Make destination directory
  if (!is_dir($dest)) {
    mkdir($dest);
  }
  // Loop through the folder
  $dir = dir($source);
  while (false !== $entry = $dir->read()) {
    //if this is the files folder then skip the pointers, the html_export directory (server == dead), and .htaccess files
    //if not then Skip pointers to folders, .DS_Store, *.php, and .htaccess
    if ($entry == '.' || $entry == '..' || $entry == 'README.txt' || $entry == 'LICENSE.txt' || $entry == '.DS_Store' || $entry == '.htaccess' || $entry == 'Thumbs.db' || strpos($entry,'.engine') != 0 || strpos($entry,'.php') != 0 || strpos($entry,'.inc') != 0 || strpos($entry,'.include') != 0 || strpos($entry,'.info') != 0 || strpos($entry,'.install') != 0 || strpos($entry,'.module') != 0){
      continue;
    }
    // Deep copy directories, ignore the html_export ones
    if ($dest !== "$source/$entry" && strpos($source,'html_export') == 0 ) {
      _html_export_copy_files("$source/$entry", "$dest/$entry", $context);
    }
  }
  // Clean up
  $dir->close();
  return true;
}

/**
 * Batch 'finished' callback
 */
function html_export_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    $message = (count($results)-1) .' html pages created. <a href="'. url($results[0], array('absolute' => TRUE, 'purl' => array('disabled' => TRUE))) .'">Click to access export</a>';
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
	$GLOBALS['html_export_active'] = FALSE;
  drupal_set_message($message);
}