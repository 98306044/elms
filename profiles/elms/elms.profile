<?php

/**
 * @todo
 * -
 * -
 * -
 */

!function_exists('profiler_v2') ? require_once('libraries/profiler/profiler.inc') : FALSE;
profiler_v2('elms');

/**
 * Implementation of hook_profile_task_list().
 */
function elms_profile_task_list() {
  $tasks['install-elms-modules'] = st('Install ELMS Modules');
  $tasks['set-elms-defaults'] = st('Set ELMS Defaults');
  return $tasks;
}

/**
 * Implementation of hook_profile_tasks().
 */
function elms_profile_tasks(&$task, $url) {
  // We are running a batch task for this profile so basically do nothing and return page
  if (in_array($task, array('install-elms-modules', 'set-elms-defaults'))) {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }
  if ($task == 'install-elms') {
	$modules = _elms_modules();
    $files = module_rebuild_cache();
    // Create batch
    foreach ($modules as $module) {
      $batch['operations'][] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }    
    $batch['finished'] = '_elms_profile_batch_finished';
    $batch['title'] = st('Installing @drupal', array('@drupal' => drupal_install_profile_name()));
    $batch['error_message'] = st('The installation has encountered an error.');

    // Start a batch, switch to 'install-elms-modules' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'install-elms-modules');
    batch_set($batch);
    batch_process($url, $url);
    // Just for cli installs. We'll never reach here on interactive installs.
    return;
  }
  
  if ($task == 'set-elms-defaults') {
	  $batch['title'] = st('Configuring @drupal', array('@drupal' => drupal_install_profile_name()));
    $batch['operations'][] = array('_elms_configure', array());
    $batch['operations'][] = array('_elms_configure_check', array());
    $batch['finished'] = '_elms_configure_finished';
    variable_set('install_task', 'set-elms-defaults');
    batch_set($batch);
    batch_process($url, $url);
    // Jut for cli installs. We'll never reach here on interactive installs.
    return;
  }
  
  return $output;
}

/**
 * Finished callback for the modules install batch.
 *
 * Advance installer task to language import.
 */
function _elms_profile_batch_finished($success, $results) {
  variable_set('install_task', 'install-elms-modules');
}

/**
 * Finish configuration batch
 * 
 * @todo Handle error condition
 */
function _elms_configure_finished($success, $results) {
  variable_set('elms_install', 1);
  // Get out of this batch and let the installer continue.
  variable_set('install_task', 'finished');
}

/**
 * Configuration. First stage.
 */
function _elms_configure() {
  // Remove default input filter formats
  $result = db_query("SELECT * FROM {filter_formats} WHERE name IN ('%s', '%s')", 'Filtered HTML', 'Full HTML');
  while ($row = db_fetch_object($result)) {
    db_query("DELETE FROM {filter_formats} WHERE format = %d", $row->format);
    db_query("DELETE FROM {filters} WHERE format = %d", $row->format);
  }
  // Create user picture directory
  $picture_path = file_create_path(variable_get('user_picture_path', 'pictures'));
  file_check_directory($picture_path, 1, 'user_picture_path');
}

/**
 * Configuration. Second stage.
 */
function _elms_configure_check() {
  // This isn't actually necessary as there are no node_access() entries,
  // but we run it to prevent the "rebuild node access" message from being
  // shown on install.
  node_access_rebuild();

  // Rebuild key tables/caches
  drupal_flush_all_caches();

  // Set default theme. This must happen after drupal_flush_all_caches(), which
  // will run system_theme_data() without detecting themes in the install
  // profile directory.
  _openatrium_system_theme_data();
  db_query("UPDATE {blocks} SET status = 0, region = ''"); // disable all DB blocks
  db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'garland');

  // In Aegir install processes, we need to init strongarm manually as a
  // separate page load isn't available to do this for us.
  if (function_exists('strongarm_init')) {
    strongarm_init();
  }

  // Revert key components that are overridden by others on install.
  // Note that this comes after all other processes have run, as some cache
  // clears/rebuilds actually set variables or other settings that would count
  // as overrides. See `og_node_type()`.
  /*
  $revert = array(
    'elms_course' => array('user_role', 'user_permission', 'variable', 'filter'),
  );
  features_revert($revert);*/
}

function _elms_modules() {
  return array(
  'elms_helper',
  'elms_course',
  'elms_course_versions',
  'elms_navigation_right',
  'elms_navigation_left',
  'elms_navigation_top',
  'elms_roles',
  'elms_course_content',
  'elms_course_studio',
  'elms_reaction',
  'elms_schedule',
  'elms_helpdesk',
  'elms_course_content_export',
  'elms_export_html',
  'elms_data_out'
  );
}