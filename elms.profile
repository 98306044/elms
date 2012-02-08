<?php

define('ELMS_MAX_ALLOWED_PACKET', 10);

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
function _elms_get_core_install_data($core_part = 'all') {
	//build list of all info files
  $files = _elms_get_core_install_files();
	//if loading all we need to build all the info files
  if ($core_part == 'all') {
    $tmp = array();
    //flatten all info files into one
    foreach ($files as $key => $file) {
			$infofile = file_get_contents($files[$key]->filename);
      $info_setup = elms_parse_info_file($infofile);
			$info_setup['file'] = $files[$key]->name;
      $tmp[] = $info_setup;
    }
    return $tmp;
  }
  else {
    //return just the info from the core piece in question
    $infofile = file_get_contents($files[$core_part]->filename);
    $info_setup = elms_parse_info_file($infofile);
    return $info_setup;
  }
}
/**
 * Helper to allow for modularity in the direction the install profile shifts based on creation of new .info files
 */
function _elms_get_core_install_files() {
  $dir = "./profiles/elms/core_installers";
  $mask = '\.info$';
  $files = file_scan_directory($dir, $mask, array('.', '..', 'CVS'), 0, TRUE, 'name', 0);
  return $files;
}

/**
 * Implementation of hook_profile_modules().
 */
function elms_profile_modules() {
	//get the core installation module set
	$install_core = _elms_get_core_install_data('default');
	$modules = $install_core['dependencies'];
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
function _elms_extended_modules() {
	$req_core = _elms_get_core_install_data('extended');
  return $req_core['dependencies'];
}

/**
 * Returns an array list of modules based on the core focus selected
 */
function _elms_core_focus_modules() {
  $install_core = _elms_get_core_install_data(variable_get('install-core-installer','icms'));
	return $install_core['dependencies'];
}

/**
 * Returns an array list of add on modules to install
 */
function _elms_add_ons_modules() {
	$add_ons = variable_get('install-add-ons', array());
	$add_on_modules = array();
	//loop through to account for possible multiple options
	foreach ($add_ons as $val) {
		//if the box was checked, append it to the module lis
		if ($val != '0') {
		  $tmp = _elms_get_core_install_data($val);
		  $add_on_modules = array_merge($add_on_modules, $tmp['dependencies']);
		}
	}
	return $add_on_modules;
}

/**
 * Implementation of hook_profile_task_list().
 */
function elms_profile_task_list() {
  if (_elms_language_selected()) {
    $tasks['elms-install-translation-batch'] = st('Download and import translation');
  }
  $tasks['elms-install-modules-batch'] = st('Install ELMS');
  $tasks['elms-install-modules-2-batch'] = st('Install Core Focus');
	$tasks['elms-install-modules-3-batch'] = st('Install Add Ons');
	$tasks['elms-install-ac-batch'] = st('Configure Accessibility');
	$tasks['elms-install-configure-batch'] = st('Finalize Install');
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
  if (in_array($task, array('elms-install-modules-batch', 'elms-install-modules-2-batch', 'elms-install-modules-3-batch', 'elms-install-translation-batch', 'elms-install-ac-batch', 'elms-install-configure-batch'))) {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }
  
  // Install some more modules and maybe localization helpers too
  if ($task == 'elms-install-modules') {
    $modules = _elms_extended_modules();
    $files = module_rebuild_cache();
    // Create batch
    foreach ($modules as $module) {
      $batch['operations'][] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }
		//build directories
		$batch['operations'][] = array('_elms_build_directories', array());
    $batch['finished'] = '_elms_module_batch_1_finished';
    $batch['title'] = st('Installing @drupal Base', array('@drupal' => drupal_install_profile_name()));
    $batch['error_message'] = st('The installation has encountered an error.');

    // Start a batch, switch to 'elms-install-modules-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'elms-install-modules-batch');
    batch_set($batch);
    batch_process($url, $url);
    // Jut for cli installs. We'll never reach here on interactive installs.
    return;
  }
	// Install some more modules
  if ($task == 'elms-install-modules-2') {
    $modules = _elms_core_focus_modules();
    $files = module_rebuild_cache();
    // Create batch
    foreach ($modules as $module) {
      $batch['operations'][] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }    
    $batch['finished'] = '_elms_module_batch_2_finished';
    $batch['title'] = st('Install Core Focus');
    $batch['error_message'] = st('The installation has encountered an error.');
		
    // Start a batch, switch to 'elms-install-modules-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'elms-install-modules-2-batch');
    batch_set($batch);
    batch_process($url, $url);
    // Jut for cli installs. We'll never reach here on interactive installs.
    return;
  }
	
	// Install some more modules
  if ($task == 'elms-install-modules-3') {
    $modules = _elms_add_ons_modules();
    $files = module_rebuild_cache();
    // Create batch
		$timeline = false;
    foreach ($modules as $module) {
      $batch['operations'][] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }
    $batch['finished'] = '_elms_module_batch_3_finished';
    $batch['title'] = st('Install Add Ons');
    $batch['error_message'] = st('The installation has encountered an error.');
		
    // Start a batch, switch to 'elms-install-modules-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'elms-install-modules-3-batch');
    batch_set($batch);
    batch_process($url, $url);
    // Jut for cli installs. We'll never reach here on interactive installs.
    return;
  }
  // install accessible content node structure
  if ($task == 'elms-install-ac') {
    $batch = array(
    'title' => st('Configure Accessibility'),
    'operations' => array(
      array('accessible_content_admin_update_tests_form_operation', array()),
      array('accessible_cotnent_admin_install_guidelines_form_operation', array()),
    ),
    'finished' => '_elms_install_ac_finished',
    'file' => drupal_get_path('module', 'accessible_content') .'/accessible_content.admin.inc',
		'error_message' => st('The installation has encountered an error.'),
  );   
    // Start a batch, switch to 'elms-install-modules-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'elms-install-ac-batch');
    batch_set($batch);
    batch_process($url, $url);
    // Jut for cli installs. We'll never reach here on interactive installs.
    return;
  }
	
  // Run additional configuration tasks
  // @todo Review all the cache/rebuild options at the end, some of them may not be needed
  // @todo Review for localization, the time zone cannot be set that way either
  if ($task == 'elms-install-configure') {
		//build revert array for passing through 1 and a time
		$revert = array(
      //revert core architecture
      array('elms_parent' => array('content', 'fieldgroup', 'node', 'views', 'variable')),
      array('elms_site' => array('content', 'fieldgroup', 'node', 'views', 'variable')),
      //revert potentially enabled features
      array('elms_content' => array('content', 'flag', 'node', 'views')),
      array('elms_resources' => array('content', 'menu_links', 'node', 'variable')),
      //revert data passers
      array('elms_content_export' => array('content', 'fieldgroup')),
      array('elms_content_import' => array('content', 'fieldgroup')),
      //revert nav
      array('elms_navigation_top' => array('menu_links', 'menu_custom')),
      array('elms_navigation_left' => array('menu_links', 'menu_custom')),
			//revert optional features if they are enabled
			array('elms_places' => array('menu_links', 'menu_custom')),
			array('elms_polls' => array('menu_links', 'menu_custom')),
			array('elms_reference_links' => array('menu_links', 'menu_custom')),
			array('elms_terms' => array('menu_links', 'menu_custom')),
			array('elms_timeline' => array('menu_links', 'menu_custom')),
		  //revert core installer last as they take priority
		  array('elms_'. variable_get('install-core-installer', '') => array('variable')),
    );
    $batch['title'] = st('Finalize Install');
    $batch['operations'][] = array('_elms_installer_configure', array());
		$batch['operations'][] = array('_elms_installer_configure_cleanup', array());
		//set default workflow states, in the future workflow states will be exportable via Features
    $batch['operations'][] = array('_elms_workflow_query', array());
		//insert roles
    $batch['operations'][] = array('_elms_role_query', array());  
		//insert permissions to match
		$batch['operations'][] = array('_elms_perm_query', array());
    //apply elms default filters
    $batch['operations'][] = array('_elms_filters_query', array()); ;
    $batch['operations'][] = array('_elms_filter_formats_query', array()); 
    //apply defaults for better formats
    $batch['operations'][] = array('_elms_better_formats_defaults_query', array()); 
    //wysiwyg defaults
    $batch['operations'][] = array('_elms_wysiwyg_query', array()); 
    //add profile fields
    $batch['operations'][] = array('_elms_profile_fields_query', array()); 
    //contact form for the default helpdesk
    $batch['operations'][] = array('_elms_contact_query', array()); 
    $batch['operations'][] = array('_elms_contact_fields_query', array()); 
    //create default vocab and terms
    $batch['operations'][] = array('_elms_vocab_query', array()); 
	  $batch['operations'][] = array('node_access_rebuild', array());
	  $batch['operations'][] = array('drupal_flush_all_caches', array());
	  $batch['operations'][] = array('_elms_system_theme_data', array());
    $batch['operations'][] = array('_elms_installer_configure_system_cleanup', array());
		//check to see if we were asked to run cron
		if (variable_get('install-run_cron', 0)) {
		  $batch['operations'][] = array('_elms_installer_configure_run_cron', array());
		}
		//revert all components 1 at a time to help avoid timeout
		foreach ($revert as $feature) {
		  $batch['operations'][] = array('_elms_installer_configure_revert', array($feature));
		}
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
function _elms_installer_configure(&$context) {
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

  // Set time zone
  // @TODO: This is not sufficient. We either need to display a message or
  // derive a default date API location.
  $tz_offset = date('Z');
  variable_set('date_default_timezone', $tz_offset);
	$context['message'] = st('Set language and content filter defaults');
}


/**
 * Configuration. Second stage.
 */
function _elms_installer_configure_cleanup(&$context) {
	//set front page to site default, this way if other features strongarm it they can but the default was set at least so we don't get the stupid 'welcome to your site' page
	variable_set('site_frontpage', 'parents');
	variable_set('site_frontpage_path', 'parents');
	//setup private directory defaults
	$filename = file_directory_path() .'/'. variable_get('private_download_directory','private') .'/.htaccess';
  if (!private_download_write($filename, variable_get('private_download_htaccess',''))) {
    // failed to write htaccess file; report to log and return
    watchdog('private_download', t('Unable to write data to file: !filename', array('!filename' => $filename)), 'error');
  }	
	//accessibility cleanup if active
	if (variable_get('install-accessibility-guideline', 'wcag2aa') != 'none') {
	  $guidelines = _elms_get_guidelines();
	  //find the node created based on the spec requested
	  $guide_nid = db_result(db_query("SELECT nid FROM {node} WHERE type='%s' AND title='%s'", 'accessibility_guideline', $guidelines[variable_get('install-accessibility-guideline', 'wcag2aa')]));
	  //associate known content types to this guideline and set defaults
	  $types = node_get_types();
	  foreach ($types as $key => $type) {
	    variable_set($key .'_accessibility_guideline_nid', $guide_nid);
	    variable_set($key .'_ac_after_filter', 1);
      variable_set($key .'_ac_display_level', array(1 => 1, 2 => 2, 3 => 3));
		  //defaults laid out for site and parent but not activated by default
		  if ($key != 'site' && $key != 'parent') {
        variable_set($key .'_ac_enable', 1);
		  }
      variable_set($key .'_ac_fail', 1);
		  variable_set($key .'_ac_ignore_cms_off', 1);
	  }
	}
	db_query("DELETE FROM {node_type} WHERE type='book'");
	$context['message'] = st('Accessibility tests implemented');
}

/**
 * Configuration. Third stage.
 */
function _elms_installer_configure_system_cleanup(&$context) {
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
  // In Aegir install processes, we need to init strongarm manually as a
  // separate page load isn't available to do this for us.
  if (function_exists('strongarm_init')) {
    strongarm_init();
  }
	$context['message'] = st('Set language and content filter defaults');
}

/**
 * Configuration. Revert stage.
 */
function _elms_installer_configure_revert($feature, &$context) {
	//revert the passed features so we can keep memory limit low
	features_revert($feature);
  $context['message'] = st('Reverted %feature feature.', array('%feature' => key($feature)));
}

/**
 * Finished. Try to run cron.
 */
function _elms_installer_configure_run_cron(&$context) {
  //run cron as the last thing
	if (drupal_cron_run()) {
		$context['message'] = st('Cron run successfully');
  }
  else {
		$context['message'] = st('Cron run failed (not critical)');
  }
	
}


/**
 * Finished callback for the modules install batch.
 *
 * Advance installer task to language import.
 */
function _elms_install_ac_finished($success, $results) {
  variable_set('install_task', 'elms-install-configure');
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
function _elms_module_batch_1_finished($success, $results) {
  variable_set('install_task', 'elms-install-modules-2');
}

/**
 * Finished callback for the modules install batch.
 *
 * Advance installer task to language import.
 */
function _elms_module_batch_2_finished($success, $results) {
  variable_set('install_task', 'elms-install-modules-3');
}

/**
 * Finished callback for the modules install batch.
 *
 * Advance installer task to language import.
 */
function _elms_module_batch_3_finished($success, $results) {
  variable_set('install_task', 'elms-install-ac');
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
	//add options for core installer
	$form['core_installer'] = array(
	  '#type' => 'fieldset',
		'#title' => st('Installation Options'),
		'#collapsed' => FALSE,
		'#collapsible' => TRUE,
		'#description' => st('ELMS allows for the creation of many different kinds of systems.  These options are just to get you started off as far along as possible in meeting the goals of your organization.'),
		'#weight' => -10,
	);
	//build list of possible installer options
	$core_install_data = _elms_get_core_install_data();
	foreach ($core_install_data as $key => $install_file) {
		if ($install_file['type'] == 'installer') {
			$installers[$install_file['file']] = $install_file['name'];
		}
		if ($install_file['type'] == 'add-on') {
			$add_ons[$install_file['file']] = $install_file['name'];
		}
		if ($install_file['type'] == 'features') {
			$features[$install_file['file']] = $install_file['name'];
		}
	}
	//sort alphabetically
	asort($installers);
	asort($add_ons);
	
	$form['core_installer']['installer'] = array(
	  '#type' => 'select',
		'#options' => $installers,
		'#title' => st('Core Focus'),
		'#description' => st('What is the core mission of this ELMS instance?'),
		'#default_value' => 'icms',
		'#required' => TRUE,
	);
	$form['core_installer']['features'] = array(
	  '#type' => 'checkboxes',
		'#options' => $features,
		'#default_value' => array(),
		'#title' => st('Features'),
		'#description' => st('Features that you would like to have access to, you can always turn these on after install'),
	);
	//accessibility
	$guidelines = _elms_get_guidelines();
	$form['accessibility'] = array(
	  '#type' => 'fieldset',
		'#title' => st('Accessibility'),
		'#collapsed' => FALSE,
		'#collapsible' => TRUE,
		'#description' => st('ELMS helps your organization adhere to accessibility guidelines.'),
		'#weight' => -9,
	);
	$form['accessibility']['guideline'] = array(
	  '#type' => 'select',
		'#options' => $guidelines,
		'#title' => st('Accessibility Guideline'),
		'#description' => st('Which guideline would you like to ensure content respects?'),
		'#default_value' => 'wcag2aa',
		'#required' => TRUE,
	);
	$form['developer'] = array(
	  '#type' => 'fieldset',
		'#title' => st('Developer Settings'),
		'#collapsed' => FALSE,
		'#collapsible' => TRUE,
		'#description' => st('A listing of developer centric options.'),
		'#weight' => -9,
	);
	$form['developer']['add_ons'] = array(
	  '#type' => 'checkboxes',
		'#options' => $add_ons,
		'#default_value' => array('developer_ui'),
		'#title' => st('Optional Add-ons'),
		'#description' => st('Functionality to extend your instance'),
	);
	//alert user to their version of php
	// PHP_VERSION_ID is available as of PHP 5.2.7, if our 
// version is lower than that, then emulate it
if (!defined('PHP_VERSION_ID')) {
    $version = explode('.', PHP_VERSION);

    define('PHP_VERSION_ID', ($version[0] * 10000 + $version[1] * 100 + $version[2]));
}
	if (PHP_VERSION_ID < 50207) {
			define('PHP_MAJOR_VERSION',   $version[0]);
			define('PHP_MINOR_VERSION',   $version[1]);
			define('PHP_RELEASE_VERSION', $version[2]);
	
			// and so on, ...
	}
	//less then 5.2 is not supported
	if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 2) {
		drupal_set_message(st("You are running PHP @phpversion which is unsupported", array('@phpversion. PHP 5.2 or higher is required.' => PHP_MAJOR_VERSION .'.'. PHP_MINOR_VERSION .'.'. PHP_RELEASE_VERSION)),'error');
	}
	//5.2 allowed but not recommended
	if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION == 2) {
		drupal_set_message(st("You are running PHP @phpversion which will install successfully but we recommend that you upgrade to 5.3 or higher", array('@phpversion' => PHP_MAJOR_VERSION .'.'. PHP_MINOR_VERSION .'.'. PHP_RELEASE_VERSION)),'warning');
	}
	//5.3 and higher is acceptable still report it just cause its nice to know
	if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION > 2) {
		drupal_set_message(st("You are running PHP @phpversion which is a supported version", array('@phpversion' => PHP_MAJOR_VERSION .'.'. PHP_MINOR_VERSION .'.'. PHP_RELEASE_VERSION)));
	}
	//this is a critical step to ensuring a stable environment installation
	//max packet is an extremely common error with large platform installations and this needs to be perfect
	//attempt to calculate max allowed packet
	$result =  db_query("SHOW VARIABLES LIKE 'max_allowed_packet'");
  while ($variables = db_fetch_object($result)) {
    $current_max_packet = $variables->Value / (1024 * 1024);
  }
	$max_allowed_capable = FALSE;
	//test if current is equal to or greater then max allowed
	if ($current_max_packet >= ELMS_MAX_ALLOWED_PACKET) {
		$max_allowed_capable = TRUE;
		if ($_GET['set_map'] == 1) {
			drupal_set_message(st("The database setting `max_allowed_packet` was successfully set to @megs", array('@megs' => ELMS_MAX_ALLOWED_PACKET)));
		}
	}
	else {
		//attempt to set it higher automatically but most likely can't
		if ($_GET['set_map'] != 1) {
		  drupal_set_message(st("Database setting `max_allowed_packet` makes ELMS happy at @megs or higher. Your current setting is @urmegs. <a href='@link'>Click to attempt to fix this</a>.", array('@megs' => ELMS_MAX_ALLOWED_PACKET,'@urmegs' => $current_max_packet, '@link' => 'install.php?locale='. check_plain($_GET['locale']) .'&profile='. check_plain($_GET['profile']) .'&set_map=1')), 'error');
		db_query('SET GLOBAL max_allowed_packet=%d*1024*1024', ELMS_MAX_ALLOWED_PACKET);
		  $result =  db_query("SHOW VARIABLES LIKE 'max_allowed_packet'");
      while ($variables = db_fetch_object($result)) {
       $current_max_packet = $variables->Value / (1024 * 1024);
		  }
		}
		else {
			drupal_set_message(st("ELMS attempt to set `max_allowed_packet` @megs failed. This is most likely a permission issue. You can still install without issue but read the included README.txt for ways of solving this to prevent future problems.", array('@megs' => $current_max_packet)));
		}
	}
	$form['developer']['run_cron'] = array(
	  '#type' => 'checkbox',
		'#options' => 'Run Cron',
		'#default_value' => $max_allowed_capable,
		'#disabled' => !($max_allowed_capable),
		'#title' => st('Run Cron'),
		'#description' => st('Run cron as a final cleanup at the end of the system installation'),
	);
	//make other fieldsets collapsible for consistency
	$form['site_information']['#collapsible'] = TRUE;
  $form['site_information']['site_name']['#default_value'] = 'ELMS';
  $form['site_information']['site_mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
	$form['admin_account']['#collapsible'] = TRUE;
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];

  $form['server_settings']['#collapsible'] = TRUE;
  if (function_exists('date_timezone_names') && function_exists('date_timezone_update_site')) {
    $form['server_settings']['date_default_timezone']['#access'] = FALSE;
    $form['server_settings']['#element_validate'] = array('date_timezone_update_site');
    $form['server_settings']['date_default_timezone_name'] = array(
      '#type' => 'select',
      '#title' => st('Default time zone'),
      '#default_value' => NULL,
      '#options' => date_timezone_names(FALSE, TRUE),
      '#description' => st('Select the default site time zone. If in doubt, choose the timezone that is closest to your location which has the same rules for daylight saving time.'),
      '#required' => TRUE,
    );
  }
	$form['#submit'][] = 'elms_install_configure_form_submit';
}

/**
 * Submit handler for the installation configure form
 */
function elms_install_configure_form_submit(&$form, &$form_state) {
	//store the values selected for installer and add ons
	variable_set('install-core-installer', $form_state['values']['installer']);
	$add_ons = array_merge($form_state['values']['add_ons'], $form_state['values']['features']);
	variable_set('install-add-ons', $add_ons);
	variable_set('install-accessibility-guideline', $form_state['values']['guideline']);
	variable_set('install-run_cron', $form_state['values']['run_cron']);
}

// Create required directories, taken from Commons
function _elms_build_directories() {
  $dirs = array('user_picture_path', 'ctools', 'ctools/css', 'pictures', 'imagecache', 'imagecache/elms_navigation_top', 'css', 'js', 'private', 'spaces_theme_logos', 'spaces_theme_favicons', 'syllabi');
  
  foreach ($dirs as $dir) {
    $dir = file_directory_path() . '/' . $dir;
    file_check_directory($dir, TRUE);
  }
	// Create the js/ within the files folder.
  $jspath = file_create_path('timeline');
  file_check_directory($jspath, FILE_CREATE_DIRECTORY);
	//make timeline settings ahead of time..hehe
	$timeline_lib_path = base_path() . libraries_get_path('simile_timeline');
  // Build aggregate JS file.
  $contents = "var Timeline_ajax_url = '". $timeline_lib_path ."/timeline_ajax/simile-ajax-api.js'; ";
  $contents .= "var Timeline_urlPrefix= '". $timeline_lib_path ."/timeline_js/'; ";
  $contents .= "var Timeline_parameters='bundle=true'; ";
  // Create the JS file.
  file_save_data($contents, $jspath .'/local_variables.js', FILE_EXISTS_REPLACE);
}

/**
 * Reimplementation of system_theme_data(). The core function's static cache
 * is populated during install prior to active install profile awareness.
 * This workaround makes enabling themes in profiles/[profile]/themes possible.
 */
function _elms_system_theme_data(&$context) {
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
	$context['message'] = st('Theme cache rebuilt');
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
function _elms_profile_fields_query(&$context) {
  db_query("INSERT INTO {profile_fields} VALUES ('1', 'First Name', 'profile_first_name', '', 'Personal', '', 'textfield', '-10', '0', '0', '1', '0', ''), ('2', 'Last Name', 'profile_last_name', '', 'Personal', '', 'textfield', '-9', '0', '0', '1', '0', ''), ('3', 'Campus', 'profile_campus', 'The LDAP Campus association for this member', 'Personal', '', 'textfield', '0', '0', '0', '1', '0', ''), ('4', 'Administrative Area', 'profile_administrative_area', '', 'Personal', '', 'textfield', '0', '0', '0', '1', '0', ''), ('5', 'Title', 'profile_title', '', 'Personal', '', 'textfield', '0', '0', '0', '1', '0', '')");
	$context['message'] = st('User Profile fields installed');
}

/**
 * Helper function to install roles with RID defaults.
 */
function _elms_role_query(&$context) {
  db_query("INSERT INTO {role} VALUES ('6', 'instructional designer'), ('4', 'instructor'), ('9', 'staff'), ('10', 'student'), ('8', 'teaching assistant');");  
	$context['message'] = st('User Roles installed');
}

/**
 * Helper function to install permissions for roles
 */
function _elms_perm_query(&$context) {
	//clear anon / auth user permission defaults as we will apply our own prebuilt ones
	db_query("DELETE FROM {permission} WHERE pid>0");
	db_query("INSERT INTO {permission} VALUES ('115', '1', 'collapse format fieldset by default, collapsible format selection, view field_campus, view field_description, view field_link, view field_prerequisites, view field_reference_page, view field_required_plugins, view field_sample_materials, view field_section_number, view field_section_semester, view field_section_year, view imagecache chamfer-banner, view imagecache elms_navigation_top, access content, access print, view regions_elms_navigation_bottom region, view regions_elms_navigation_left region, view regions_elms_navigation_right region, view regions_elms_navigation_top region', '0'), ('116', '2', 'collapse format fieldset by default, collapsible format selection, access printer-friendly version, view field_campus, view field_description, view field_link, view field_prerequisites, view field_reference_page, view field_required_plugins, view field_sample_materials, view field_section_number, view field_section_semester, view field_section_year, view imagecache chamfer-banner, view imagecache elms_navigation_top, access content, access print, view regions_elms_navigation_bottom region, view regions_elms_navigation_left region, view regions_elms_navigation_right region, view regions_elms_navigation_top region', '0'), ('118', '6', 'view advanced help index, view advanced help popup, view advanced help topic, add content to books, administer book outlines, create new books, bypass redirection, access ckeditor link, access site-wide contact form, edit field_campus, edit field_description, edit field_faculty_resources, edit field_id_of_record, edit field_inst_contact_block, edit field_instructional_template, edit field_lead_faculty, edit field_lesson_count, edit field_link, edit field_link_more_info, edit field_listing_only, edit field_past_faculty, edit field_prerequisites, edit field_reference_page, edit field_required_plugins, edit field_sample_materials, edit field_section_number, edit field_section_semester, edit field_section_year, view field_faculty_resources, view field_id_of_record, view field_inst_contact_block, view field_instructional_template, view field_lead_faculty, view field_lesson_count, view field_link, view field_link_more_info, view field_listing_only, view field_past_faculty, create folder content, create link content, create page content, create referenced_page content, delete any folder content, delete any link content, delete any page content, delete any referenced_page content, delete own folder content, delete own link content, delete own page content, delete own referenced_page content, edit any folder content, edit any link content, edit any page content, edit any referenced_page content, edit own folder content, edit own link content, edit own page content, edit own referenced_page content, manage features, import elms_node_import feeds, tamper elms_node_import, download original image, masquerade as user, administer nodes, revert revisions, view revisions, administer organic groups, create url aliases, access private download directory, view og requirements dashboard, view system requirements dashboard, view users outside groups, access spaces og clone, select different theme, access user profiles, access workflow summary views, administer workflow, schedule workflow transitions', '0'), ('119', '4', 'view advanced help index, view advanced help popup, view advanced help topic, add content to books, administer book outlines, create new books, bypass redirection, access ckeditor link, access site-wide contact form, edit field_link, edit field_reference_page, view field_faculty_resources, view field_id_of_record, view field_inst_contact_block, view field_instructional_template, view field_lead_faculty, view field_lesson_count, view field_link, view field_link_more_info, view field_listing_only, view field_past_faculty, create folder content, create link content, create page content, delete any folder content, delete any link content, delete any page content, delete own folder content, delete own link content, delete own page content, edit any folder content, edit any link content, edit any page content, edit own folder content, edit own link content, edit own page content, download original image, masquerade as user, revert revisions, view revisions, create url aliases, access private download directory, view og requirements dashboard, view users outside groups, select different theme, access user profiles', '0'), ('120', '9', 'view advanced help index, view advanced help popup, view advanced help topic, add content to books, administer book outlines, create new books, bypass redirection, access ckeditor link, access site-wide contact form, edit field_campus, edit field_description, edit field_faculty_resources, edit field_id_of_record, edit field_inst_contact_block, edit field_instructional_template, edit field_lead_faculty, edit field_lesson_count, edit field_link, edit field_link_more_info, edit field_listing_only, edit field_past_faculty, edit field_prerequisites, edit field_reference_page, edit field_required_plugins, edit field_sample_materials, edit field_section_number, edit field_section_semester, edit field_section_year, view field_faculty_resources, view field_id_of_record, view field_inst_contact_block, view field_instructional_template, view field_lead_faculty, view field_lesson_count, view field_link, view field_link_more_info, view field_listing_only, view field_past_faculty, create folder content, create link content, create page content, create referenced_page content, delete any folder content, delete any link content, delete any page content, delete any referenced_page content, delete own folder content, delete own link content, delete own page content, delete own referenced_page content, edit any folder content, edit any link content, edit any page content, edit any referenced_page content, edit own folder content, edit own link content, edit own page content, edit own referenced_page content, manage features, import elms_node_import feeds, tamper elms_node_import, download original image, masquerade as user, administer nodes, revert revisions, view revisions, administer organic groups, create url aliases, access private download directory, view og requirements dashboard, view system requirements dashboard, view users outside groups, access spaces og clone, select different theme, access user profiles, access workflow summary views, administer workflow, schedule workflow transitions', '0'), ('121', '10', 'access site-wide contact form, view field_inst_contact_block, access private download directory, view users outside groups', '0'), ('122', '8', 'view advanced help index, view advanced help popup, view advanced help topic, bypass redirection, access ckeditor link, access site-wide contact form, edit field_link, edit field_reference_page, view field_faculty_resources, view field_id_of_record, view field_inst_contact_block, view field_instructional_template, view field_lead_faculty, view field_lesson_count, view field_link, view field_link_more_info, view field_listing_only, view field_past_faculty, create folder content, create link content, create page content, edit any folder content, edit any link content, edit any page content, edit own folder content, edit own link content, edit own page content, masquerade as user, create url aliases, access private download directory, view og requirements dashboard, view users outside groups, access user profiles', '0')");
  $context['message'] = st('Permissions established for roles');
}

/**
 * Helper function to install workflow states.
 */
function _elms_workflow_query(&$context) {
	//insert the workflow state name
	$options = serialize(array (
      'comment_log_node' => 1,
      'comment_log_tab' => 1,
      'name_as_title' => 1,
  ));
	db_query("INSERT INTO {workflows} VALUES('1', 'Status', 'author,3,6', '%s')", $options);
	
  //insert the content type association
  db_query("INSERT INTO {workflow_type_map} VALUES ('accessibility_guideline', '0'), ('accessibility_test', '0'), ('blog', '0'), ('parent', '0'), ('elms_event', '0'), ('feed_user_import', '0'), ('folder', '0'), ('link', '0'), ('page', '0'), ('reaction', '0'), ('studio_submission', '0'), ('site', '1')");
  //define the workflow states
  db_query("INSERT INTO {workflow_states} VALUES ('2', '1', '(creation)', '-50', '1', '1'), ('3', '1', 'Development Sandbox', '0', '0', '1'), ('4', '1', 'Inactive', '1', '0', '0'), ('5', '1', 'Active Offering', '2', '0', '1'), ('6', '1', 'Archived Offering', '3', '0', '1'), ('7', '1', 'Promo', '4', '0', '1'), ('8', '1', 'Master', '8', '0', '0'), ('9', '1', 'Staging', '0', '0', '0'), ('10', '1', 'Master', '1', '0', '1')");
  //define allowed workflow state transitions
  db_query("INSERT INTO {workflow_transitions} VALUES ('1', '2', '3', 'author,3,6'), ('3', '3', '7', 'author,3,6'), ('6', '5', '3', 'author,3,6'), ('8', '5', '6', 'author,3,6'), ('9', '7', '3', 'author,3,6'), ('14', '3', '5', 'author,3,6'), ('15', '6', '5', 'author,3,6'), ('17', '3', '10', 'author,3,6'), ('18', '10', '3', 'author,3,6'), ('19', '6', '3', 'author,3,6')");
	$context['message'] = st('Publishing Workflows installed');
}

/**
 * Helper function to install default contact form.
 */
function _elms_contact_query(&$context) {
  db_query("INSERT INTO {contact} VALUES ('1','Helpdesk', '%s', 'Thank you for contacting the Helpdesk.  We will contact you within 24 hours during normal business hours or 48 hours during off-peak times.', '0', '1')", variable_get('site_mail', ''));
	$context['message'] = st('Contact form installed');
}

/**
 * Helper function to install default contact fields.
 */
function _elms_contact_fields_query(&$context) {
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
	$context['message'] = st('Contact form built');
}

/**
 * Helper function to install default wysiwyg settings.
 */
function _elms_wysiwyg_query(&$context) {
  drupal_write_record('wysiwyg', $insert);
  $insert = array (
  'format' => '1',
  'editor' => 'ckeditor',
  'settings' => 
  serialize(array (
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
  )),
  );
  drupal_write_record('wysiwyg', $insert);
  $insert = array (
  'format' => '2',
  'editor' => 'ckeditor',
  'settings' => 
  serialize(array (
    'default' => 1,
    'user_choose' => 0,
    'show_toggle' => 0,
    'theme' => 'advanced',
    'language' => 'en',
    'buttons' => 
    array (
      'default' => 
      array (
        'BulletedList' => 1,
        'NumberedList' => 1,
        'Outdent' => 1,
        'Indent' => 1,
        'Link' => 1,
        'Image' => 1,
        'Blockquote' => 1,
        'Source' => 1,
        'RemoveFormat' => 1,
        'Format' => 1,
        'Styles' => 1,
        'Table' => 1,
        'Iframe' => 1,
        'Scayt' => 1,
      ),
      'imce' => 
      array (
        'imce' => 1,
      ),
      'templates' => 
      array (
        'Templates' => 1,
      ),
			'drupal' => 
      array (
        'node_embed' => 1,
      ),
      'elimedia' => 
      array (
        'elimedia' => 1,
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
    'convert_fonts_to_spans' => 0,
    'remove_linebreaks' => 0,
    'apply_source_formatting' => 1,
    'paste_auto_cleanup_on_paste' => 1,
    'block_formats' => 'p,h2',
    'css_setting' => 'self',
    'css_path' => '%bprofiles/elms/modules/elms_core/elms_styles/elms_styles.css',
    'css_classes' => '',
  )),
  );
  drupal_write_record('wysiwyg', $insert);
  $insert = array (
  'format' => '4',
  'editor' => 'ckeditor',
  'settings' => 
  serialize(array (
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
  )),
  );
  drupal_write_record('wysiwyg', $insert);
	$context['message'] = st('WYSIWYG Text Editor installed');
}

/**
 * Helper function to install default filter formats.
 */
function _elms_filter_formats_query(&$context) {
  db_query("INSERT INTO {filter_formats} VALUES ('1', 'Comment Filter', ',1,2,3,6,4,9,10,8,', '1'), ('2', 'Content Filter', ',3,6,4,9,11,8,', '0'), ('4', 'Event', ',3,6,4,9,11,8,', '1')");
	$context['message'] = st('Input Filters installed');
}

/**
 * Helper function to set the defaults defined by better formats module.
 */
function _elms_better_formats_defaults_query(&$context) {
	//clear better formats before running
	db_query("DELETE FROM {better_formats_defaults} WHERE rid > 0");
  db_query("INSERT INTO {better_formats_defaults} VALUES ('1', 'block', '0', '1', '25'), ('1', 'comment', '0', '1', '0'), ('1', 'comment/parent', '0', '2', '0'), ('1', 'comment/elms_resource', '0', '2', '0'), ('1', 'comment/folder', '0', '2', '0'), ('1', 'comment/page', '0', '2', '0'), ('1', 'comment/referenced_page', '0', '2', '0'), ('1', 'node', '0', '1', '0'), ('1', 'node/parent', '0', '2', '0'), ('1', 'node/elms_resource', '0', '2', '0'), ('1', 'node/folder', '0', '2', '0'), ('1', 'node/page', '0', '2', '0'), ('1', 'node/referenced_page', '0', '2', '0'), ('2', 'block', '0', '1', '25'), ('2', 'comment', '0', '1', '0'), ('2', 'comment/parent', '0', '2', '0'), ('2', 'comment/elms_resource', '0', '2', '0'), ('2', 'comment/folder', '0', '2', '0'), ('2', 'comment/page', '0', '2', '0'), ('2', 'comment/referenced_page', '0', '2', '0'), ('2', 'node', '0', '1', '0'), ('2', 'node/parent', '0', '2', '0'), ('2', 'node/elms_resource', '0', '2', '0'), ('2', 'node/folder', '0', '2', '0'), ('2', 'node/page', '0', '2', '0'), ('2', 'node/referenced_page', '0', '2', '0'), ('3', 'block', '0', '1', '25'), ('3', 'comment', '0', '1', '0'), ('3', 'comment/parent', '0', '2', '0'), ('3', 'comment/elms_resource', '0', '2', '0'), ('3', 'comment/folder', '0', '2', '0'), ('3', 'comment/page', '0', '2', '0'), ('3', 'comment/referenced_page', '0', '2', '0'), ('3', 'node', '0', '1', '0'), ('3', 'node/parent', '0', '2', '0'), ('3', 'node/elms_resource', '0', '2', '0'), ('3', 'node/folder', '0', '2', '0'), ('3', 'node/page', '0', '2', '0'), ('3', 'node/referenced_page', '0', '2', '0'), ('11', 'block', '0', '1', '25'), ('11', 'comment', '0', '1', '25'), ('11', 'comment/elms_resource', '0', '2', '25'), ('11', 'comment/folder', '0', '2', '25'), ('11', 'comment/page', '0', '2', '25'), ('11', 'comment/referenced_page', '0', '2', '25'), ('11', 'node', '0', '1', '25'), ('11', 'node/elms_resource', '0', '2', '25'), ('11', 'node/folder', '0', '2', '25'), ('11', 'node/page', '0', '2', '25'), ('11', 'node/referenced_page', '0', '2', '25')");
	$context['message'] = st('Content Formats installed');
}

/**
 * Helper function to install default filters.
 */
function _elms_filters_query(&$context) {
  db_query("INSERT INTO {filters} VALUES ('36', '1', 'filter', '3', '10'), ('39', '1', 'pathologic', '0', '10'), ('38', '1', 'filter', '1', '2'), ('37', '1', 'filter', '0', '1'), ('40', '1', 'filter', '2', '0'), ('137', '2', 'ckeditor_link', '0', '-9'), ('139', '2', 'nodereference_highlight', '0', '10'), ('138', '2', 'htmlpurifier', '1', '-7'), ('82', '4', 'filter', '2', '0'), ('80', '4', 'filter', '0', '1'), ('81', '4', 'filter', '1', '2'), ('79', '4', 'filter', '3', '10'), ('69', '6', 'filter', '1', '2'), ('136', '2', 'elms_terms', '0', '10'), ('140', '2', 'node_embed', '0', '10'), ('141', '2', 'lightbox2', '0', '-10'), ('142', '2', 'filter', '2', '-8')");
	$context['message'] = st('Input Filters established');
}

/**
 * Helper function to install default vocabulary.
 */
function _elms_vocab_query(&$context) {
	//create vocab
	db_query("INSERT INTO {vocabulary} VALUES ('1', 'Unit', 'Unit', '', '1', '0', '0', '0', '0', 'features_unit', '0')");
  db_query("INSERT INTO {vocabulary_node_types} VALUES ('1', 'parent')");
  //populate terms
  db_query("INSERT INTO {term_data} VALUES ('1', '1', 'Department 1', '', '0'), ('2', '1', 'Department 4', '', '1'), ('3', '1', 'Department 3', '', '2'), ('4', '1', 'Department 4', '', '3')");
  //populate hierarchy
  db_query("INSERT INTO {term_hierarchy} VALUES ('1', '0'), ('2', '0'), ('3', '0'), ('4', '0')");
	$context['message'] = st('Default taxonomy terms installed');
}

//helper for guidelines
function _elms_get_guidelines() {
	return array(
	  'none' => "None",
	  '508' => 'Section 508',
		'wcag1a' => 'WCAG 1.0 (A)',
		'wcag1aa' => 'WCAG 1.0 (AA)',
		'wcag1aaa' => 'WCAG 1.0 (AAA)',
		'wcag2a' => 'WCAG 2.0 (A)',
		'wcag2aa' => 'WCAG 2.0 (AA)',
		'wcag2aaa' => 'WCAG 2.0 (AAA)',
	);
}