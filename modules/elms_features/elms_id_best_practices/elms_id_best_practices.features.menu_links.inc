<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function elms_id_best_practices_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-usermenu:course_resources
  $menu_links['menu-usermenu:course_resources'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'course_resources',
    'router_path' => 'course_resources',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all Course Resources',
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
