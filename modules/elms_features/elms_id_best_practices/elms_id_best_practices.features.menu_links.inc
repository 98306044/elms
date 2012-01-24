<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function elms_id_best_practices_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-usermenu:elms_resources
  $menu_links['menu-usermenu:elms_resources'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'elms_resources',
    'router_path' => 'elms_resources',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all ELMS Resources',
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Resources');


  return $menu_links;
}
