<?php

/**
 * Redirect to the book root for this course
 */
function _elms_content_root() {
  //get the group
  $group = og_get_group_context();
  //if we find a group node, take them to the book's first page
  if (isset($group->book_nid)) {
		$root = node_load($group->book_nid);
		//account for an empty book though that would cause issues
		if ($next = book_next($root->book)) {
		  drupal_goto($next['href']);
		}
		else {
      drupal_goto('node/'. $group->book_nid);
		}
  }
  //if it didn't find anything do nothing cause something went wrong
  return 1;
}


/**
 * Settings form for book feature.
 */
function elms_content_settings() {
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
    '#default_value' => variable_get('elms_print_options', 'print'),
  );
  return system_settings_form($form);
}