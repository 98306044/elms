<?php

/**
 * Implementation of hook_menu_default_menu_custom().
 */
function elms_course_studio_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-course-studio
  $menus['menu-course-studio'] = array(
    'menu_name' => 'menu-course-studio',
    'title' => 'Studio',
    'description' => 'This will contain all menu items pertaining to the submission of content in the course studio',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Studio');
  t('This will contain all menu items pertaining to the submission of content in the course studio');


  return $menus;
}
