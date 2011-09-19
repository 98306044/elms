<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function elms_promo_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "input_formats" && $api == "input_formats") {
    return array("version" => 1);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function elms_promo_node_info() {
  $items = array(
    'promo' => array(
      'name' => t('Promotional'),
      'module' => 'features',
      'description' => t('Only use this for the front facing aspect to the ELMS distribution.'),
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
