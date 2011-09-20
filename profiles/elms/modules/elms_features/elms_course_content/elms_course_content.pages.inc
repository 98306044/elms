<?php


/**
 * Settings form for book feature.
 */
function elms_course_content_settings() {
  $form = array();
  $form['elms_print_options'] = array(
    '#key_type_toggled' => '1',
    '#required' => '1',
    '#description' => t('What formats should students be able to print the course content in?'),
    '#multiple_toggle' => '1',
    '#type' => 'select',
    '#title' => t('Print Options'),
    '#options' => array(
      'print' => t('Print Page Only'),
	  'print_lesson' => t('Print Lesson or Page'),
	  'print_course' => t('Print Course, Lesson or Page'),
      'none' => t('Can not print'),
    ),
    '#default_value' => variable_get('elms_print_options','print'),
  );
  $form['content'] = array(
    '#title' => t('Content Outline'),
	'#type' => 'fieldset',
	'#collapsed' => true,
	'#collapsible' => true,
  );
  $form['content']['elms_content_outline'] = array(
    '#description' => t('Select a content outline to work from.  This is not required to create a course but can help with rapid prototyping.'),
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => _elms_course_content_get_instructional_template(),
    '#multiple_toggle' => '1',
    '#title' => t('Content Outline'),
  );
  $form['content']['elms_content_lessons'] = array(
    '#description' => t('How many lessons would you like to start with?'),
    '#type' => 'select',
    '#options' => array(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15),
    '#title' => t('Lessons'),
  );
  
  $form['site_footer'] = array(
    '#default_value' => variable_get('site_footer','2011 Copyright PSU'),
    '#description' => t('This will be the footer for your course in ELMS'),
    '#rows' => '3',
    '#cols' => '60',
    '#input_format' => '2',
    '#type' => 'textarea',
    '#title' => t('Footer'),
  );
  $form['format'] = filter_form('2');
  return system_settings_form($form);
}