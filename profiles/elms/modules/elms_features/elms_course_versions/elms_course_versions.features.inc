<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function elms_course_versions_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function elms_course_versions_imagecache_default_presets() {
  $items = array(
    'chamfer-banner' => array(
      'presetname' => 'chamfer-banner',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '950',
            'height' => '108',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function elms_course_versions_node_info() {
  $items = array(
    'version' => array(
      'name' => t('Version'),
      'module' => 'features',
      'description' => t('A version of a course either for new development, to be offered to students, or for promotional purposes.'),
      'has_title' => '1',
      'title_label' => t('Version Name'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function elms_course_versions_views_api() {
  return array(
    'api' => '2',
  );
}
