<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function elms_course_ctools_plugin_api() {
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
function elms_course_imagecache_default_presets() {
  $items = array(
    'course_promo' => array(
      'presetname' => 'course_promo',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '600',
            'height' => '340',
          ),
        ),
      ),
    ),
    'course_promo_listing' => array(
      'presetname' => 'course_promo_listing',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '150',
            'height' => '150',
            'upscale' => 0,
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
function elms_course_node_info() {
  $items = array(
    'course' => array(
      'name' => t('Course Space'),
      'module' => 'features',
      'description' => t('Use this to setup a course name space to group instances'),
      'has_title' => '1',
      'title_label' => t('Title'),
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
function elms_course_views_api() {
  return array(
    'api' => '2',
  );
}
