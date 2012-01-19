<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function elms_course_resources_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-usermenu:course_applications
  $menu_links['menu-usermenu:course_applications'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'course_applications',
    'router_path' => 'course_applications',
    'link_title' => 'Applications',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all Course Applications',
      ),
      'purl' => 'disabled',
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Applications');


  return $menu_links;
}
