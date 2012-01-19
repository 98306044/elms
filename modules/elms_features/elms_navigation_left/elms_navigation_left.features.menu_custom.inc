<?php

/**
 * Implementation of hook_menu_default_menu_custom().
 */
function elms_navigation_left_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-elms-system
  $menus['menu-elms-system'] = array(
    'menu_name' => 'menu-elms-system',
    'title' => 'System',
    'description' => 'This is a list of all links to system-wide functions in ELMS.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('System');
  t('This is a list of all links to system-wide functions in ELMS.');


  return $menus;
}
