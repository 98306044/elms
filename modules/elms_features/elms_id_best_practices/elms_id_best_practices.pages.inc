<?php

/**
 * Display Syllabus Page
 */
function _elms_id_best_practices_page_syllabus() {
  //get the group
  $group = og_get_group_context();
  return variable_get('elms_id_bp_syllabus', '');
}

/**
 * Display Help Page
 */
function _elms_id_best_practices_page_help() {
  //get the group
  $group = og_get_group_context();
  return variable_get('elms_id_bp_help', '');
}


/**
 * Settings form for book feature.
 */

function elms_id_best_practices_settings() {
	//create directory just in-case of first load
  $dir = file_create_path(file_directory_path() .'/syllabi');
  file_check_directory($dir,  1);
  $form = array();
	$form['elms_id_bp_syllabus'] = array(
	  '#default_value' => variable_get('elms_id_bp_syllabus', ''),
    '#description' => t('Upload your syllabus'),
    '#type' => 'file',
		'#size' => '10',
    '#title' => t('Syllabus'),
  );
	$form['elms_id_bp_help'] = array(
    '#default_value' => variable_get('elms_id_bp_help', 'Course Help'),
    '#description' => t('Text to display on the help page'),
    '#rows' => '3',
    '#cols' => '60',
    '#input_format' => '2',
    '#type' => 'textarea',
    '#title' => t('Help Page'),
  );
	//render a select list based on a list of all available resources
	$result = db_query("SELECT nid,title FROM {node} WHERE type='course_resource'");
	$options = array();
	while ($val = db_fetch_array($result)) {
		$options[$val['nid']] = $val['title'];
	}
	$form['elms_id_bp_resources'] = array(
    '#default_value' => variable_get('elms_id_bp_resources', array()),
    '#description' => t('Select the resources you would like to display from the list of available ones'),
    '#type' => 'select',
		'#multiple' => TRUE,
    '#title' => t('Resource List'),
		'#options' => $options,
  );
	//needs to be added for WYSIWYG to work correctly
 // $form['format'] = filter_form('2');
	//needs to be added so that we can successfully submit files
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  return system_settings_form($form);
}

//validate the form values
function elms_id_best_practices_settings_validate($form, &$form_state) {
    $form_state['storage']['elms_id_bp_syllabus'] = '';
    //create the theme logo area and validate its size
    $dir = file_create_path(file_directory_path() .'/syllabi');
    $is_writable = file_check_directory($dir, 1);
    if ($is_writable) {
      $validators = array(
        'file_validate_size' => array(20 * 1024),
        'file_validate_extensions' => array('pdf'),
      );
      if ($file = file_save_upload('elms_id_bp_syllabus', $validators, $dir)) {
        $form_state['storage']['elms_id_bp_syllabus'] = str_replace(' ', '%20', $file->filepath);
      }
    }
}
