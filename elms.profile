<?php

/**
 * Implementation of hook_profile_details().
 */
function elms_profile_details() {
  return array(
    'name' => 'ELMS',
    'description' => '<img src="profiles/elms/images/elms.png" alt="ELMS wordart" title="ELMS wordart" /> e-Learning Instructional Content Management System',
  );
}

/**
 * Helper to parse info file for module set management().
 */
function _elms_get_module_group($core_part = 'all') {
	$filepath = "./profiles/elms/elms.info";
  $infofile = file_get_contents($filepath);
  $info_setup = elms_parse_info_file($infofile);
	//if nothing was supplied, return all modules in list
	if ($core_part == 'all') {
		$tmp = array();
		//flatten the array into a single list
		foreach ($info_setup['dependencies'] as $key => $array) {
			$tmp = array_merge($tmp, $info_setup['dependencies'][$key]);
		}
		return $tmp;
	}
	else {
    return $info_setup['dependencies'][$core_part];
	}
}
/**
 * Implementation of hook_profile_modules().
 */
function elms_profile_modules() {
  $modules = _elms_get_module_group('core');
	//print_r($modules);
	//exit;
  // If language is not English we add the 'elms_translate' module the first
  // To get some modules installed properly we need to have translations loaded
  // We also use it to check connectivity with the translation server on hook_requirements()
  if (_elms_language_selected()) {
    // We need locale before l10n_update because it adds fields to locale tables
    $modules[] = 'locale';
    //$modules[] = 'l10n_update';
    //$modules[] = 'elms_translate';
  }

  return $modules;
}

/**
 * Returns an array list of elms features (and supporting) modules.
 */
function _elms_core_modules() {
	return _elms_get_module_group('elms_core');
}

/**
 * Implementation of hook_profile_task_list().
 */
function elms_profile_task_list() {
  if (_elms_language_selected()) {
    $tasks['elms-install-translation-batch'] = st('Download and import translation');
  }
  $tasks['elms-install-modules-batch'] = st('Install Profile modules');
  $tasks['elms-install-configure-batch'] = st('Configure Defaults');
  return $tasks;
}

/**
 * Implementation of hook_profile_tasks().
 */
function elms_profile_tasks(&$task, $url) {
  global $profile, $install_locale;
  
  // Just in case some of the future tasks adds some output
  $output = '';

  // Download and install translation if needed
  if ($task == 'profile') {
    // Rebuild the language list.
    // When running through the CLI, the static language list will be empty
    // unless we repopulate it from the ,newly available, database.
    language_list('name', TRUE);

    if (_elms_language_selected() && module_exists('elms_translate')) {
      module_load_install('elms_translate');
      if ($batch = elms_translate_create_batch($install_locale, 'install')) {
        $batch['finished'] = '_elms_translate_batch_finished';
        // Remove temporary variables and set install task
        variable_del('install_locale_batch_components');
        variable_set('install_task', 'elms-install-translation-batch');
        batch_set($batch);
        batch_process($url, $url);
        // Jut for cli installs. We'll never reach here on interactive installs.
        return;
      }
    }
    // If we reach here, means no language install, move on to the next task
    $task = 'elms-install-modules';
  }

  // We are running a batch task for this profile so basically do nothing and return page
  if (in_array($task, array('elms-install-modules-batch', 'elms-install-translation-batch', 'elms-install-configure-batch'))) {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }
  
  // Install some more modules and maybe localization helpers too
  if ($task == 'elms-install-modules') {
    $modules = _elms_core_modules();
    $files = module_rebuild_cache();
    // Create batch
    foreach ($modules as $module) {
      $batch['operations'][] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }    
    $batch['finished'] = '_elms_profile_batch_finished';
    $batch['title'] = st('Installing @drupal', array('@drupal' => drupal_install_profile_name()));
    $batch['error_message'] = st('The installation has encountered an error.');

    // Start a batch, switch to 'elms-install-modules-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'elms-install-modules-batch');
    batch_set($batch);
    batch_process($url, $url);
    // Jut for cli installs. We'll never reach here on interactive installs.
    return;
  }

  // Run additional configuration tasks
  // @todo Review all the cache/rebuild options at the end, some of them may not be needed
  // @todo Review for localization, the time zone cannot be set that way either
  if ($task == 'elms-install-configure') {
    $batch['title'] = st('Configuring @drupal', array('@drupal' => drupal_install_profile_name()));
    $batch['operations'][] = array('_elms_installer_configure', array());
    $batch['operations'][] = array('_elms_installer_configure_check', array());
    $batch['finished'] = '_elms_installer_configure_finished';
    variable_set('install_task', 'elms-install-configure-batch');
    batch_set($batch);
    batch_process($url, $url);
    // Jut for cli installs. We'll never reach here on interactive installs.
    return;
  }  

  return $output;
}

/**
 * Check whether we are installing in a language other than English
 */
function _elms_language_selected() {
  global $install_locale;
  return !empty($install_locale) && ($install_locale != 'en');
}

/**
 * Configuration. First stage.
 */
function _elms_installer_configure() {
  global $install_locale;

  // Disable the english locale if using a different default locale.
  if (!empty($install_locale) && ($install_locale != 'en')) {
    db_query("DELETE FROM {languages} WHERE language = 'en'");
  }

  // Remove default input filter formats
  $result = db_query("SELECT * FROM {filter_formats} WHERE name IN ('%s', '%s')", 'Filtered HTML', 'Full HTML');
  while ($row = db_fetch_object($result)) {
    db_query("DELETE FROM {filter_formats} WHERE format = %d", $row->format);
    db_query("DELETE FROM {filters} WHERE format = %d", $row->format);
  }

  // Create user picture directory
  $picture_path = file_create_path(variable_get('user_picture_path', 'pictures'));
  file_check_directory($picture_path, 1, 'user_picture_path');

  // Set time zone
  // @TODO: This is not sufficient. We either need to display a message or
  // derive a default date API location.
  $tz_offset = date('Z');
  variable_set('date_default_timezone', $tz_offset);
}

/**
 * Configuration. Second stage.
 */
function _elms_installer_configure_check() {
	//final clean up stuff
  _elms_role_query();
  //delete book content type
  db_query("DELETE FROM {node_type} WHERE type='book'");
  //apply elms default filters
  _elms_filters_query();
  _elms_filter_formats_query();
  //apply defaults for better formats
  _elms_better_formats_defaults_query();
  //wysiwyg defaults
  _elms_wysiwyg_query();
  //add profile fields
  _elms_profile_fields_query();
  //contact form for the default helpdesk
  _elms_contact_query();
  _elms_contact_fields_query();
  //set default workflow states, in the future workflow states will be exportable via Features
  _elms_workflow_query();
	//create default vocab and terms
	_elms_vocab_query();
  // This isn't actually necessary as there are no node_access() entries,
  // but we run it to prevent the "rebuild node access" message from being
  // shown on install.
  node_access_rebuild();

  // Rebuild key tables/caches
  drupal_flush_all_caches();

  // Set default theme. This must happen after drupal_flush_all_caches(), which
  // will run system_theme_data() without detecting themes in the install
  // profile directory.
  _elms_system_theme_data();
	// disable all DB blocks
  db_query("UPDATE {blocks} SET status = 0, region = ''");
	// activate all themes first
  db_query("UPDATE {system} SET status = 1 WHERE type = 'theme'");
	// disable some core themes
  db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'garland');
	db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'minnelli');
	db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'marvin');
	db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'chameleon');
	// disable system themes by default
	db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'tao');
	db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'rubik');
  variable_set('theme_default', 'cube');
  //try rebuilding caches prior to system load
	drupal_rebuild_theme_registry();
	menu_rebuild();
  // In Aegir install processes, we need to init strongarm manually as a
  // separate page load isn't available to do this for us.
  if (function_exists('strongarm_init')) {
    strongarm_init();
  }

  // Revert key components that are overridden by others on install.
  // Note that this comes after all other processes have run, as some cache
  // clears/rebuilds actually set variables or other settings that would count
  // as overrides. See `og_node_type()`.
  $revert = array(
	  //revert core architecture
	  'elms_course' => array('content', 'fieldgroup'),
		'elms_course_versions' => array('content', 'fieldgroup'),
		//revert default features
	  'elms_course_content' => array('content'),
		'elms_course_resources' => array('content'),
		'elms_id_best_practices' => array('views'),
		//revert data passers
		'elms_course_content_export' => array('content', 'fieldgroup'),
		'elms_course_content_import' => array('content', 'fieldgroup'),
		//revert nav
	  'elms_navigation_top' => array('menu_links', 'menu_custom'),
		'elms_navigation_left' => array('menu_links', 'menu_custom'),
  );
	features_revert($revert);
}

/**
 * Finish configuration batch
 * 
 * @todo Handle error condition
 */
function _elms_installer_configure_finished($success, $results) {
  variable_set('elms_install', 1);
  // Get out of this batch and let the installer continue. If loaded translation,
  // we skip the locale remaining batch and move on to the next.
  // However, if we didn't make it with the translation file, or they downloaded
  // an unsupported language, we let the standard locale do its work.
  if (variable_get('elms_translate_done', 0)) {
    variable_set('install_task', 'finished');
  }
  else {
    variable_set('install_task', 'profile-finished');
  } 
}

/**
 * Finished callback for the modules install batch.
 *
 * Advance installer task to language import.
 */
function _elms_profile_batch_finished($success, $results) {
  variable_set('install_task', 'elms-install-configure');
}

/**
 * Finished callback for the first locale import batch.
 *
 * Advance installer task to the configure screen.
 */
function _elms_translate_batch_finished($success, $results) {
  include_once 'includes/locale.inc';
  // Let the installer now we've already imported locales
  variable_set('elms_translate_done', 1);
  variable_set('install_task', 'elms-install-modules');
  _locale_batch_language_finished($success, $results);
}

/**
 * Alter some forms implementing hooks in system module namespace
 * This is a trick for hooks to get called, otherwise we cannot alter forms
 */

/**
 * @TODO: This might be impolite/too aggressive. We should at least check that
 * other install profiles are not present to ensure we don't collide with a
 * similar form alter in their profile.
 *
 * Set ELMS as default install profile.
 */
function system_form_install_select_profile_form_alter(&$form, $form_state) {
  foreach($form['profile'] as $key => $element) {
    $form['profile'][$key]['#value'] = 'elms';
  }
}

/**
 * Set English as default language.
 * 
 * If no language selected, the installation crashes. I guess English should be the default 
 * but it isn't in the default install. @todo research, core bug?
 */
function system_form_install_select_locale_form_alter(&$form, $form_state) {
  $form['locale']['en']['#value'] = 'en';
}

/**
 * Alter the install profile configuration form and provide timezone location options.
 */
function system_form_install_configure_form_alter(&$form, $form_state) {
  $form['site_information']['site_name']['#default_value'] = 'ELMS';
  $form['site_information']['site_mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];

  if (function_exists('date_timezone_names') && function_exists('date_timezone_update_site')) {
    $form['server_settings']['date_default_timezone']['#access'] = FALSE;
    $form['server_settings']['#element_validate'] = array('date_timezone_update_site');
    $form['server_settings']['date_default_timezone_name'] = array(
      '#type' => 'select',
      '#title' => t('Default time zone'),
      '#default_value' => NULL,
      '#options' => date_timezone_names(FALSE, TRUE),
      '#description' => t('Select the default site time zone. If in doubt, choose the timezone that is closest to your location which has the same rules for daylight saving time.'),
      '#required' => TRUE,
    );
  }
}

/**
 * Reimplementation of system_theme_data(). The core function's static cache
 * is populated during install prior to active install profile awareness.
 * This workaround makes enabling themes in profiles/[profile]/themes possible.
 */
function _elms_system_theme_data() {
  global $profile;
  $profile = 'elms';

  $themes = drupal_system_listing('\.info$', 'themes');
  $engines = drupal_system_listing('\.engine$', 'themes/engines');

  $defaults = system_theme_default();

  $sub_themes = array();
  foreach ($themes as $key => $theme) {
    $themes[$key]->info = drupal_parse_info_file($theme->filename) + $defaults;

    if (!empty($themes[$key]->info['base theme'])) {
      $sub_themes[] = $key;
    }

    $engine = $themes[$key]->info['engine'];
    if (isset($engines[$engine])) {
      $themes[$key]->owner = $engines[$engine]->filename;
      $themes[$key]->prefix = $engines[$engine]->name;
      $themes[$key]->template = TRUE;
    }

    // Give the stylesheets proper path information.
    $pathed_stylesheets = array();
    foreach ($themes[$key]->info['stylesheets'] as $media => $stylesheets) {
      foreach ($stylesheets as $stylesheet) {
        $pathed_stylesheets[$media][$stylesheet] = dirname($themes[$key]->filename) .'/'. $stylesheet;
      }
    }
    $themes[$key]->info['stylesheets'] = $pathed_stylesheets;

    // Give the scripts proper path information.
    $scripts = array();
    foreach ($themes[$key]->info['scripts'] as $script) {
      $scripts[$script] = dirname($themes[$key]->filename) .'/'. $script;
    }
    $themes[$key]->info['scripts'] = $scripts;

    // Give the screenshot proper path information.
    if (!empty($themes[$key]->info['screenshot'])) {
      $themes[$key]->info['screenshot'] = dirname($themes[$key]->filename) .'/'. $themes[$key]->info['screenshot'];
    }
  }

  foreach ($sub_themes as $key) {
    $themes[$key]->base_themes = system_find_base_themes($themes, $key);
    // Don't proceed if there was a problem with the root base theme.
    if (!current($themes[$key]->base_themes)) {
      continue;
    }
    $base_key = key($themes[$key]->base_themes);
    foreach (array_keys($themes[$key]->base_themes) as $base_theme) {
      $themes[$base_theme]->sub_themes[$key] = $themes[$key]->info['name'];
    }
    // Copy the 'owner' and 'engine' over if the top level theme uses a
    // theme engine.
    if (isset($themes[$base_key]->owner)) {
      if (isset($themes[$base_key]->info['engine'])) {
        $themes[$key]->info['engine'] = $themes[$base_key]->info['engine'];
        $themes[$key]->owner = $themes[$base_key]->owner;
        $themes[$key]->prefix = $themes[$base_key]->prefix;
      }
      else {
        $themes[$key]->prefix = $key;
      }
    }
  }

  // Extract current files from database.
  system_get_files_database($themes, 'theme');
  db_query("DELETE FROM {system} WHERE type = 'theme'");
  foreach ($themes as $theme) {
    $theme->owner = !isset($theme->owner) ? '' : $theme->owner;
    db_query("INSERT INTO {system} (name, owner, info, type, filename, status, throttle, bootstrap) VALUES ('%s', '%s', '%s', '%s', '%s', %d, %d, %d)", $theme->name, $theme->owner, serialize($theme->info), 'theme', $theme->filename, isset($theme->status) ? $theme->status : 0, 0, 0);
  }
}

/**
 * Copy of drupal_parse_info_file() but must be passed a string rather than a
 * file path to read from.
 */
function elms_parse_info_file($data) {
  if (!$data) {
    return FALSE;
  }

  $constants = get_defined_constants();
  if (preg_match_all('
    @^\s*                           # Start at the beginning of a line, ignoring leading whitespace
    ((?:
      [^=;\[\]]|                    # Key names cannot contain equal signs, semi-colons or square brackets,
      \[[^\[\]]*\]                  # unless they are balanced and not nested
    )+?)
    \s*=\s*                         # Key/value pairs are separated by equal signs (ignoring white-space)
    (?:
      ("(?:[^"]|(?<=\\\\)")*")|     # Double-quoted string, which may contain slash-escaped quotes/slashes
      (\'(?:[^\']|(?<=\\\\)\')*\')| # Single-quoted string, which may contain slash-escaped quotes/slashes
      ([^\r\n]*?)                   # Non-quoted string
    )\s*$                           # Stop at the next end of a line, ignoring trailing whitespace
    @msx', $data, $matches, PREG_SET_ORDER)) {
    $info = array();
    foreach ($matches as $match) {
      // Fetch the key and value string
      $i = 0;
      foreach (array('key', 'value1', 'value2', 'value3') as $var) {
        $$var = isset($match[++$i]) ? $match[$i] : '';
      }
      $value = stripslashes(substr($value1, 1, -1)) . stripslashes(substr($value2, 1, -1)) . $value3;

      // Parse array syntax
      $keys = preg_split('/\]?\[/', rtrim($key, ']'));
      $last = array_pop($keys);
      $parent = &$info;

      // Create nested arrays
      foreach ($keys as $key) {
        if ($key == '') {
          $key = count($parent);
        }
        if (!isset($parent[$key]) || !is_array($parent[$key])) {
          $parent[$key] = array();
        }
        $parent = &$parent[$key];
      }

      // Handle PHP constants
      if (defined($value)) {
        $value = constant($value);
      }

      // Insert actual value
      if ($last == '') {
        $last = count($parent);
      }
      $parent[$last] = $value;
    }
    return $info;
  }
  return FALSE;
}

/**
 * Helper function to install roles with RID defaults.
 */
function _elms_profile_fields_query() {
  db_query("INSERT INTO {profile_fields} VALUES ('1', 'First Name', 'profile_first_name', '', 'Personal', '', 'textfield', '-10', '0', '0', '4', '0', ''), ('2', 'Last Name', 'profile_last_name', '', 'Personal', '', 'textfield', '-9', '0', '0', '4', '0', '')");
}

/**
 * Helper function to install roles with RID defaults.
 */
function _elms_role_query() {
  db_query("INSERT INTO {role} VALUES ('6', 'instructional designer'), ('4', 'instructor'), ('9', 'staff'), ('10', 'student'), ('8', 'teaching assistant');");	
}
/**
 * Helper function to install workflow states.
 */
function _elms_workflow_query() {
  $ary = array (
  'wid' => '1',
  'name' => 'Status',
  'tab_roles' => 'author,3,6',
  'options' => 
  serialize(array (
    'comment_log_node' => 1,
    'comment_log_tab' => 1,
    'name_as_title' => 1,
  )),
  );
  drupal_write_record('workflows', $ary);
  //insert the content type association
  db_query("INSERT INTO {workflow_type_map} VALUES ('accessibility_guideline', '0'), ('accessibility_test', '0'), ('blog', '0'), ('course', '0'), ('course_event', '0'), ('feed_reader', '0'), ('feed_user_import', '0'), ('folder', '0'), ('link', '0'), ('page', '0'), ('promo', '0'), ('reaction', '0'), ('studio_submission', '0'), ('version', '1')");
  //define the workflow states
  db_query("INSERT INTO {workflow_states} VALUES ('2', '1', '(creation)', '-50', '1', '1'), ('3', '1', 'Development Sandbox', '0', '0', '1'), ('4', '1', 'Inactive', '1', '0', '0'), ('5', '1', 'Active Offering', '2', '0', '1'), ('6', '1', 'Archived Offering', '3', '0', '1'), ('7', '1', 'Course Promo', '4', '0', '1'), ('8', '1', 'Master', '8', '0', '0'), ('9', '1', 'Staging', '0', '0', '0'), ('10', '1', 'Master Version', '1', '0', '1')");
  //define allowed workflow state transitions
  db_query("INSERT INTO {workflow_transitions} VALUES ('1', '2', '3', 'author,3,6'), ('3', '3', '7', 'author,3,6'), ('6', '5', '3', 'author,3,6'), ('8', '5', '6', 'author,3,6'), ('9', '7', '3', 'author,3,6'), ('14', '3', '5', 'author,3,6'), ('15', '6', '5', 'author,3,6'), ('17', '3', '10', 'author,3,6'), ('18', '10', '3', 'author,3,6'), ('19', '6', '3', 'author,3,6')");
}

/**
 * Helper function to install default contact form.
 */
function _elms_contact_query() {
  db_query("INSERT INTO {contact} VALUES ('1','Helpdesk', '%s', 'Thank you for contacting the e-Learning Institute Helpdesk.  We will contact you within 24 hours during normal business hours or 48 hours during off-peak times.', '0', '1')", variable_get('site_mail', ''));
}

/**
 * Helper function to install default contact fields.
 */
function _elms_contact_fields_query() {
  $ary = array (
  'field_name' => 'name',
  'field_type' => 'textfield',
  'settings' => 
  serialize(array (
    'title' => 'Your name',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '2',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'mail',
  'field_type' => 'textfield',
  'settings' => 
  serialize(array (
    'title' => 'Your e-mail address',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '3',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'subject',
  'field_type' => 'textfield',
  'settings' => 
  serialize(array (
    'title' => 'Subject',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '4',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'cid',
  'field_type' => 'value',
  'settings' => 
  serialize(array (
    'title' => NULL,
  )),
  'required' => '0',
  'enabled' => '1',
  'weight' => '7',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'message',
  'field_type' => 'textarea',
  'settings' => 
  serialize(array (
    'title' => 'Message',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '5',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'field_issue_type',
  'field_type' => 'select',
  'settings' => 
  serialize(array (
    'multiple' => false,
    'title' => 'Type of Question',
    'prefix' => '',
    'suffix' => '',
    'num_value' => '0',
    'description' => 'Please classify your question to help us better understand the issue you are having.',
    'options' => 
    array (
      'general' => 'General
',
      'instructor' => 'For Instructor
',
      'technical' => 'Technical
',
    ),
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '0',
  'core' => '0',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'field_roles',
  'field_type' => 'textfield',
  'settings' => 
  serialize(array (
    'title' => 'Roles',
    'description' => '',
    'prefix' => '',
    'suffix' => '',
    'maxlength' => 255,
    'field_prefix' => '',
    'field_suffix' => '',
  )),
  'required' => '0',
  'enabled' => '1',
  'weight' => '1',
  'core' => '0',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'field_tech_details',
  'field_type' => 'textarea',
  'settings' => 
  serialize(array (
    'description' => 'The following are technical support details that will also be sent to the helpdesk',
    'title' => 'Technical Details',
    'rows' => '14',
    'cols' => '',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '6',
  'core' => '0',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
}

/**
 * Helper function to install default wysiwyg settings.
 */
function _elms_wysiwyg_query() {
  $tmp_ary = array (
  'default' => 1,
  'user_choose' => 0,
  'show_toggle' => 0,
  'theme' => 'advanced',
  'language' => 'en',
  'buttons' => 
  array (
    'default' => 
    array (
      'Bold' => 1,
      'Italic' => 1,
      'Underline' => 1,
      'BulletedList' => 1,
      'NumberedList' => 1,
      'Link' => 1,
      'Scayt' => 1,
    ),
  ),
  'toolbar_loc' => 'top',
  'toolbar_align' => 'left',
  'path_loc' => 'none',
  'resizing' => 1,
  'verify_html' => 1,
  'preformatted' => 0,
  'convert_fonts_to_spans' => 1,
  'remove_linebreaks' => 0,
  'apply_source_formatting' => 0,
  'paste_auto_cleanup_on_paste' => 1,
  'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
  'css_setting' => 'none',
  'css_path' => '',
  'css_classes' => '',
);
$ary = array('format' => '1', 'editor' => 'ckeditor', 'settings' => serialize($tmp_ary));
drupal_write_record('wysiwyg', $ary);

$tmp_ary = array (
  'default' => 1,
  'user_choose' => 0,
  'show_toggle' => 1,
  'theme' => 'advanced',
  'language' => 'en',
  'buttons' => 
  array (
    'default' => 
    array (
      'Bold' => 1,
      'Italic' => 1,
      'Underline' => 1,
      'JustifyLeft' => 1,
      'JustifyCenter' => 1,
      'JustifyRight' => 1,
      'BulletedList' => 1,
      'NumberedList' => 1,
      'Outdent' => 1,
      'Indent' => 1,
      'Link' => 1,
      'Image' => 1,
      'Superscript' => 1,
      'Subscript' => 1,
      'RemoveFormat' => 1,
      'FontSize' => 1,
      'Styles' => 1,
      'Table' => 1,
      'Scayt' => 1,
    ),
    'elimedia' => 
    array (
      'elimedia' => 1,
    ),
    'imce' => 
    array (
      'imce' => 1,
    ),
    'drupal_path' => 
    array (
      'Link' => 1,
    ),
  ),
  'toolbar_loc' => 'top',
  'toolbar_align' => 'left',
  'path_loc' => 'bottom',
  'resizing' => 1,
  'verify_html' => 0,
  'preformatted' => 0,
  'convert_fonts_to_spans' => 1,
  'remove_linebreaks' => 0,
  'apply_source_formatting' => 0,
  'paste_auto_cleanup_on_paste' => 1,
  'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
  'css_setting' => 'none',
  'css_path' => '',
  'css_classes' => '',
);
$ary = array('format' => '2', 'editor' => 'ckeditor', 'settings' => serialize($tmp_ary));
drupal_write_record('wysiwyg', $ary);

$tmp_ary = array (
  'default' => 1,
  'user_choose' => 0,
  'show_toggle' => 0,
  'theme' => 'advanced',
  'language' => 'en',
  'buttons' => 
  array (
    'default' => 
    array (
      'Bold' => 1,
      'Italic' => 1,
      'BulletedList' => 1,
      'NumberedList' => 1,
    ),
  ),
  'toolbar_loc' => 'top',
  'toolbar_align' => 'left',
  'path_loc' => 'bottom',
  'resizing' => 1,
  'verify_html' => 1,
  'preformatted' => 0,
  'convert_fonts_to_spans' => 1,
  'remove_linebreaks' => 1,
  'apply_source_formatting' => 0,
  'paste_auto_cleanup_on_paste' => 1,
  'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
  'css_setting' => 'none',
  'css_path' => '',
  'css_classes' => '',
);
$ary = array('format' => '4', 'editor' => 'ckeditor', 'settings' => serialize($tmp_ary));
drupal_write_record('wysiwyg', $ary);
}

/**
 * Helper function to install default filter formats.
 */
function _elms_filter_formats_query() {
  db_query("INSERT INTO {filter_formats} VALUES ('1', 'Comment Filter', ',1,2,3,6,4,9,10,8,', '1'), ('2', 'Content Filter', ',3,6,4,', '1'), ('4', 'Course Event', ',6,4,', '1')");
}

/**
 * Helper function to set the defaults defined by better formats module.
 */
function _elms_better_formats_defaults_query() {
  db_query("INSERT INTO {better_formats_defaults} VALUES ('1', 'block', '0', '1', '25'), ('1', 'comment', '1', '1', '0'), ('1', 'comment/accessibility_guideline', '1', '2', '0'), ('1', 'comment/accessibility_test', '1', '2', '0'), ('1', 'comment/blog', '1', '2', '0'), ('1', 'comment/course', '0', '2', '0'), ('1', 'comment/course_event', '0', '2', '0'), ('1', 'comment/feed_reader', '1', '2', '0'), ('1', 'comment/feed_user_import', '1', '2', '0'), ('1', 'comment/folder', '1', '2', '0'), ('1', 'comment/link', '1', '2', '0'), ('1', 'comment/offering', '0', '2', '0'), ('1', 'comment/page', '0', '2', '0'), ('1', 'comment/promo', '0', '2', '0'), ('1', 'comment/reaction', '1', '2', '0'), ('1', 'comment/studio_submission', '1', '2', '0'), ('1', 'comment/version', '0', '2', '0'), ('1', 'node', '0', '1', '0'), ('1', 'node/accessibility_guideline', '0', '2', '0'), ('1', 'node/accessibility_test', '0', '2', '0'), ('1', 'node/blog', '0', '2', '0'), ('1', 'node/course', '0', '2', '0'), ('1', 'node/course_event', '0', '2', '0'), ('1', 'node/feed_reader', '0', '2', '0'), ('1', 'node/feed_user_import', '0', '2', '0'), ('1', 'node/folder', '0', '2', '0'), ('1', 'node/link', '0', '2', '0'), ('1', 'node/offering', '0', '2', '0'), ('1', 'node/page', '0', '2', '0'), ('1', 'node/promo', '0', '2', '0'), ('1', 'node/reaction', '0', '2', '0'), ('1', 'node/studio_submission', '0', '2', '0'), ('1', 'node/version', '0', '2', '0'), ('2', 'block', '0', '1', '25'), ('2', 'comment', '1', '1', '0'), ('2', 'comment/accessibility_guideline', '1', '2', '0'), ('2', 'comment/accessibility_test', '1', '2', '0'), ('2', 'comment/blog', '1', '2', '0'), ('2', 'comment/course', '0', '2', '0'), ('2', 'comment/course_event', '0', '2', '0'), ('2', 'comment/feed_reader', '1', '2', '0'), ('2', 'comment/feed_user_import', '1', '2', '0'), ('2', 'comment/folder', '1', '2', '0'), ('2', 'comment/link', '1', '2', '0'), ('2', 'comment/offering', '0', '2', '0'), ('2', 'comment/page', '0', '2', '0'), ('2', 'comment/promo', '0', '2', '0'), ('2', 'comment/reaction', '1', '2', '0'), ('2', 'comment/studio_submission', '1', '2', '0'), ('2', 'comment/version', '0', '2', '0'), ('2', 'node', '0', '1', '0'), ('2', 'node/accessibility_guideline', '0', '2', '0'), ('2', 'node/accessibility_test', '0', '2', '0'), ('2', 'node/blog', '0', '2', '0'), ('2', 'node/course', '0', '2', '0'), ('2', 'node/course_event', '0', '2', '0'), ('2', 'node/feed_reader', '0', '2', '0'), ('2', 'node/feed_user_import', '0', '2', '0'), ('2', 'node/folder', '0', '2', '0'), ('2', 'node/link', '0', '2', '0'), ('2', 'node/offering', '0', '2', '0'), ('2', 'node/page', '0', '2', '0'), ('2', 'node/promo', '0', '2', '0'), ('2', 'node/reaction', '0', '2', '0'), ('2', 'node/studio_submission', '0', '2', '0'), ('2', 'node/version', '0', '2', '0'), ('3', 'block', '2', '1', '25'), ('3', 'comment', '1', '1', '0'), ('3', 'comment/accessibility_guideline', '1', '2', '0'), ('3', 'comment/accessibility_test', '1', '2', '0'), ('3', 'comment/blog', '1', '2', '0'), ('3', 'comment/course', '0', '2', '0'), ('3', 'comment/course_event', '0', '2', '0'), ('3', 'comment/feed_reader', '1', '2', '0'), ('3', 'comment/feed_user_import', '1', '2', '0'), ('3', 'comment/folder', '1', '2', '0'), ('3', 'comment/link', '1', '2', '0'), ('3', 'comment/offering', '0', '2', '0'), ('3', 'comment/page', '0', '2', '0'), ('3', 'comment/promo', '0', '2', '0'), ('3', 'comment/reaction', '1', '2', '0'), ('3', 'comment/studio_submission', '1', '2', '0'), ('3', 'comment/version', '0', '2', '0'), ('3', 'node', '2', '1', '0'), ('3', 'node/accessibility_guideline', '2', '2', '0'), ('3', 'node/accessibility_test', '2', '2', '0'), ('3', 'node/blog', '2', '2', '0'), ('3', 'node/course', '2', '2', '0'), ('3', 'node/course_event', '0', '2', '0'), ('3', 'node/feed_reader', '2', '2', '0'), ('3', 'node/feed_user_import', '2', '2', '0'), ('3', 'node/folder', '2', '2', '0'), ('3', 'node/link', '0', '2', '0'), ('3', 'node/offering', '2', '2', '0'), ('3', 'node/page', '2', '2', '0'), ('3', 'node/promo', '2', '2', '0'), ('3', 'node/reaction', '0', '2', '0'), ('3', 'node/studio_submission', '2', '2', '0'), ('3', 'node/version', '2', '2', '0'), ('4', 'block', '2', '1', '25'), ('4', 'comment', '1', '1', '25'), ('4', 'comment/accessibility_guideline', '1', '2', '25'), ('4', 'comment/accessibility_test', '1', '2', '25'), ('4', 'comment/blog', '1', '2', '25'), ('4', 'comment/course', '0', '2', '25'), ('4', 'comment/course_event', '0', '2', '25'), ('4', 'comment/feed_reader', '1', '2', '25'), ('4', 'comment/feed_user_import', '1', '2', '25'), ('4', 'comment/folder', '1', '2', '25'), ('4', 'comment/link', '1', '2', '25'), ('4', 'comment/offering', '0', '2', '25'), ('4', 'comment/page', '0', '2', '25'), ('4', 'comment/promo', '0', '2', '25'), ('4', 'comment/reaction', '1', '2', '25'), ('4', 'comment/studio_submission', '1', '2', '25'), ('4', 'comment/version', '0', '2', '25'), ('4', 'node', '2', '1', '25'), ('4', 'node/accessibility_guideline', '2', '2', '25'), ('4', 'node/accessibility_test', '2', '2', '25'), ('4', 'node/blog', '2', '2', '25'), ('4', 'node/course', '2', '2', '25'), ('4', 'node/course_event', '0', '2', '25'), ('4', 'node/feed_reader', '2', '2', '25'), ('4', 'node/feed_user_import', '2', '2', '25'), ('4', 'node/folder', '2', '2', '25'), ('4', 'node/link', '0', '2', '25'), ('4', 'node/offering', '2', '2', '25'), ('4', 'node/page', '2', '2', '25'), ('4', 'node/promo', '2', '2', '25'), ('4', 'node/reaction', '0', '2', '25'), ('4', 'node/studio_submission', '2', '2', '25'), ('4', 'node/version', '2', '2', '25'), ('6', 'block', '2', '1', '25'), ('6', 'comment', '1', '1', '25'), ('6', 'comment/accessibility_guideline', '1', '2', '25'), ('6', 'comment/accessibility_test', '1', '2', '25'), ('6', 'comment/blog', '1', '2', '25'), ('6', 'comment/course', '0', '2', '25'), ('6', 'comment/course_event', '0', '2', '25'), ('6', 'comment/feed_reader', '1', '2', '25'), ('6', 'comment/feed_user_import', '1', '2', '25'), ('6', 'comment/folder', '1', '2', '25'), ('6', 'comment/link', '1', '2', '25'), ('6', 'comment/offering', '0', '2', '25'), ('6', 'comment/page', '0', '2', '25'), ('6', 'comment/promo', '0', '2', '25'), ('6', 'comment/reaction', '1', '2', '25'), ('6', 'comment/studio_submission', '1', '2', '25'), ('6', 'comment/version', '0', '2', '25'), ('6', 'node', '2', '1', '25'), ('6', 'node/accessibility_guideline', '2', '2', '25'), ('6', 'node/accessibility_test', '2', '2', '25'), ('6', 'node/blog', '2', '2', '25'), ('6', 'node/course', '2', '2', '25'), ('6', 'node/course_event', '0', '2', '25'), ('6', 'node/feed_reader', '2', '2', '25'), ('6', 'node/feed_user_import', '2', '2', '25'), ('6', 'node/folder', '2', '2', '25'), ('6', 'node/link', '0', '2', '25'), ('6', 'node/offering', '2', '2', '25'), ('6', 'node/page', '2', '2', '25'), ('6', 'node/promo', '2', '2', '25'), ('6', 'node/reaction', '0', '2', '25'), ('6', 'node/studio_submission', '2', '2', '25'), ('6', 'node/version', '2', '2', '25'), ('7', 'block', '0', '1', '25'), ('7', 'comment', '1', '1', '25'), ('7', 'node', '0', '1', '25'), ('8', 'block', '0', '1', '25'), ('8', 'comment', '0', '1', '25'), ('8', 'comment/accessibility_guideline', '0', '2', '25'), ('8', 'comment/accessibility_test', '0', '2', '25'), ('8', 'comment/blog', '0', '2', '25'), ('8', 'comment/course', '0', '2', '25'), ('8', 'comment/course_event', '0', '2', '25'), ('8', 'comment/feed_reader', '0', '2', '25'), ('8', 'comment/feed_user_import', '0', '2', '25'), ('8', 'comment/folder', '0', '2', '25'), ('8', 'comment/link', '0', '2', '25'), ('8', 'comment/offering', '0', '2', '25'), ('8', 'comment/page', '0', '2', '25'), ('8', 'comment/promo', '0', '2', '25'), ('8', 'comment/reaction', '0', '2', '25'), ('8', 'comment/studio_submission', '0', '2', '25'), ('8', 'comment/version', '0', '2', '25'), ('8', 'node', '0', '1', '25'), ('8', 'node/accessibility_guideline', '0', '2', '25'), ('8', 'node/accessibility_test', '0', '2', '25'), ('8', 'node/blog', '0', '2', '25'), ('8', 'node/course', '0', '2', '25'), ('8', 'node/course_event', '0', '2', '25'), ('8', 'node/feed_reader', '0', '2', '25'), ('8', 'node/feed_user_import', '0', '2', '25'), ('8', 'node/folder', '0', '2', '25'), ('8', 'node/link', '0', '2', '25'), ('8', 'node/offering', '0', '2', '25'), ('8', 'node/page', '0', '2', '25'), ('8', 'node/promo', '0', '2', '25'), ('8', 'node/reaction', '0', '2', '25'), ('8', 'node/studio_submission', '0', '2', '25'), ('8', 'node/version', '0', '2', '25'), ('10', 'block', '0', '1', '25'), ('10', 'comment', '0', '1', '25'), ('10', 'comment/accessibility_guideline', '0', '2', '25'), ('10', 'comment/accessibility_test', '0', '2', '25'), ('10', 'comment/blog', '0', '2', '25'), ('10', 'comment/course', '0', '2', '25'), ('10', 'comment/course_event', '0', '2', '25'), ('10', 'comment/feed_reader', '0', '2', '25'), ('10', 'comment/feed_user_import', '0', '2', '25'), ('10', 'comment/folder', '0', '2', '25'), ('10', 'comment/link', '0', '2', '25'), ('10', 'comment/offering', '0', '2', '25'), ('10', 'comment/page', '0', '2', '25'), ('10', 'comment/promo', '0', '2', '25'), ('10', 'comment/reaction', '0', '2', '25'), ('10', 'comment/studio_submission', '0', '2', '25'), ('10', 'comment/version', '0', '2', '25'), ('10', 'node', '0', '1', '25'), ('10', 'node/accessibility_guideline', '0', '2', '25'), ('10', 'node/accessibility_test', '0', '2', '25'), ('10', 'node/blog', '0', '2', '25'), ('10', 'node/course', '0', '2', '25'), ('10', 'node/course_event', '0', '2', '25'), ('10', 'node/feed_reader', '0', '2', '25'), ('10', 'node/feed_user_import', '0', '2', '25'), ('10', 'node/folder', '0', '2', '25'), ('10', 'node/link', '0', '2', '25'), ('10', 'node/offering', '0', '2', '25'), ('10', 'node/page', '0', '2', '25'), ('10', 'node/promo', '0', '2', '25'), ('10', 'node/reaction', '0', '2', '25'), ('10', 'node/studio_submission', '0', '2', '25'), ('10', 'node/version', '0', '2', '25')");	
}

/**
 * Helper function to install default filters.
 */
function _elms_filters_query() {
  db_query("INSERT INTO {filters} VALUES ('40', '1', 'filter', '2', '0'), ('37', '1', 'filter', '0', '1'), ('38', '1', 'filter', '1', '2'), ('36', '1', 'filter', '3', '10'), ('39', '1', 'pathologic', '0', '10'), ('67', '2', 'wysiwyg_filter', '0', '-10'), ('62', '2', 'ckeditor_link', '0', '-9'), ('64', '2', 'lightbox2', '0', '-8'), ('63', '2', 'filter', '3', '-7'), ('66', '2', 'filter', '2', '-6'), ('65', '2', 'filter', '1', '-5'), ('45', '4', 'filter', '2', '0'), ('42', '4', 'filter', '0', '1'), ('43', '4', 'filter', '1', '2'), ('41', '4', 'filter', '3', '10'), ('44', '4', 'pathologic', '0', '10'), ('69', '6', 'filter', '1', '2')");
}

/**
 * Helper function to install default vocabulary.
 */
function _elms_vocab_query() {
	//create vocab as first item
  db_query("INSERT INTO {vocabulary} VALUES ('1', 'Academic Unit', 'Academic Unit that is offering this course', 'Choose the Academic Unit offering this course', '1', '0', '0', '1', '0', 'features_academicunit', '0')");
	//populate hierarchy
	db_query("INSERT INTO {vocabulary_node_types} VALUES ('1', 'course')");
	//populate terms
	db_query("INSERT INTO {term_data} VALUES ('1', '1', 'Department 1', '', '0'), ('2', '1', 'Department 4', '', '1'), ('3', '1', 'Department 3', '', '2'), ('4', '1', 'Department 4', '', '3')");
	//populate hierarchy
	db_query("INSERT INTO {term_hierarchy} VALUES ('1', '0'), ('2', '0'), ('3', '0'), ('4', '0')");
}