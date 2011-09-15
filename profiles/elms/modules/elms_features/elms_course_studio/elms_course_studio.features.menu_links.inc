<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function elms_course_studio_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-course-studio:node/add/studio-submission
  $menu_links['menu-course-studio:node/add/studio-submission'] = array(
    'menu_name' => 'menu-course-studio',
    'link_path' => 'node/add/studio-submission',
    'router_path' => 'node/add/studio-submission',
    'link_title' => 'Create Submission',
    'options' => array(
      'attributes' => array(
        'title' => 'Create Studio Submission',
      ),
      'menu_icon' => array(
        'enable' => 0,
        'path' => 'profiles/elms_content/modules/elms_core/elms_appbar/images/placeholder.png',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: menu-course-studio:studio/my
  $menu_links['menu-course-studio:studio/my'] = array(
    'menu_name' => 'menu-course-studio',
    'link_path' => 'studio/my',
    'router_path' => 'studio',
    'link_title' => 'My Studio',
    'options' => array(
      'attributes' => array(
        'title' => 'My Studio Submissions',
      ),
      'menu_icon' => array(
        'enable' => 0,
        'path' => 'profiles/elms/modules/elms_core/elms_appbar/images/placeholder.png',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: menu-course-studio:studio/view
  $menu_links['menu-course-studio:studio/view'] = array(
    'menu_name' => 'menu-course-studio',
    'link_path' => 'studio/view',
    'router_path' => 'studio/view',
    'link_title' => 'View Studio',
    'options' => array(
      'attributes' => array(
        'title' => 'View all Studio Submissions',
      ),
      'menu_icon' => array(
        'enable' => 0,
        'path' => 'profiles/elms/modules/elms_core/elms_appbar/images/placeholder.png',
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
  t('Create Submission');
  t('My Studio');
  t('View Studio');


  return $menu_links;
}
