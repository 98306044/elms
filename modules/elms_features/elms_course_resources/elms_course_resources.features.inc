<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function elms_course_resources_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function elms_course_resources_node_info() {
  $items = array(
    'course_resource' => array(
      'name' => t('Course Resource'),
      'module' => 'features',
      'description' => t('Resources for communicating information about resources used in a course'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
