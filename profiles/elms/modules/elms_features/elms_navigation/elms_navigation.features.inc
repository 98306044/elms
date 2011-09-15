<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function elms_navigation_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function elms_navigation_imagecache_default_presets() {
  $items = array(
    'appbar_user_icon' => array(
      'presetname' => 'appbar_user_icon',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '25',
            'height' => '25',
          ),
        ),
      ),
    ),
  );
  return $items;
}
