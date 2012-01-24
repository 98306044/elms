<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function elms_navigation_left_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elms-system:node/add/parent
  $menu_links['menu-elms-system:node/add/parent'] = array(
    'menu_name' => 'menu-elms-system',
    'link_path' => 'node/add/parent',
    'router_path' => 'node/add/parent',
    'link_title' => 'Add Course',
    'options' => array(
      'purl' => 'disabled',
      'attributes' => array(
        'title' => 'Add Course',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: menu-elms-system:node/add/site
  $menu_links['menu-elms-system:node/add/site'] = array(
    'menu_name' => 'menu-elms-system',
    'link_path' => 'node/add/site',
    'router_path' => 'node/add/site',
    'link_title' => 'Create Sandbox',
    'options' => array(
      'purl' => 'disabled',
      'attributes' => array(
        'title' => 'Create Sandbox',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: menu-elms-system:system_stats
  $menu_links['menu-elms-system:system_stats'] = array(
    'menu_name' => 'menu-elms-system',
    'link_path' => 'system_stats',
    'router_path' => 'system_stats',
    'link_title' => 'System Stats',
    'options' => array(
      'purl' => 'disabled',
      'attributes' => array(
        'title' => 'System Stats',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add Course');
  t('Create Sandbox');
  t('System Stats');


  return $menu_links;
}
