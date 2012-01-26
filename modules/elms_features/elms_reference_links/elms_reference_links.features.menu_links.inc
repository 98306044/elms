<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function elms_reference_links_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: features:resources
  $menu_links['features:resources'] = array(
    'menu_name' => 'features',
    'link_path' => 'resources',
    'router_path' => 'resources',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'A directory of external course resources',
      ),
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: menu-usermenu:my_related_links
  $menu_links['menu-usermenu:my_related_links'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'my_related_links',
    'router_path' => 'my_related_links',
    'link_title' => 'My Related Links',
    'options' => array(
      'attributes' => array(
        'title' => 'All related links across your courses',
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
  t('My Related Links');
  t('Resources');


  return $menu_links;
}
