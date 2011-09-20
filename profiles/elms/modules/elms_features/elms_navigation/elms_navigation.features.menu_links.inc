<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function elms_navigation_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-usermenu:<front>
  $menu_links['menu-usermenu:<front>'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => '[user-name]',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(
        'title' => '',
        'class' => 'menu_icon menu-16500',
      ),
      'menu_icon' => array(
        'enable' => 1,
        'path' => 'sites/default/files/menu_icons/menu_icon_16500.png',
        'imagecache_preset' => 'appbar_user_icon',
      ),
      'purl' => 'disabled',
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '1',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: menu-usermenu:bookmarks
  $menu_links['menu-usermenu:bookmarks'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'bookmarks',
    'router_path' => 'bookmarks',
    'link_title' => 'My Bookmarks',
    'options' => array(
      'purl' => 'disabled',
      'attributes' => array(
        'title' => 'My Bookmarks',
        'class' => 'menu_icon menu-16504',
      ),
      'menu_icon' => array(
        'enable' => 1,
        'path' => 'sites/default/files/menu_icons/menu_icon_16504.png',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
    'parent_path' => 'user/1',
  );
  // Exported menu link: menu-usermenu:courses
  $menu_links['menu-usermenu:courses'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'courses',
    'router_path' => 'courses',
    'link_title' => 'View All Courses',
    'options' => array(
      'attributes' => array(
        'title' => 'View a list of all courses',
        'class' => 'menu_icon menu-1526',
      ),
      'menu_icon' => array(
        'enable' => 1,
        'path' => 'profiles/elms_content/modules/elms_features/elms_navigation/images/placeholder.png',
      ),
      'purl' => 'disabled',
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
    'parent_path' => 'courses',
  );
  // Exported menu link: menu-usermenu:courses/my
  $menu_links['menu-usermenu:courses/my'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'courses/my',
    'router_path' => 'courses',
    'link_title' => 'My Courses',
    'options' => array(
      'purl' => 'disabled',
      'attributes' => array(
        'title' => 'My Courses',
        'class' => 'menu_icon menu-16495',
      ),
      'menu_icon' => array(
        'enable' => 1,
        'path' => 'sites/default/files/menu_icons/menu_icon_16495.png',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
    'parent_path' => 'user/1',
  );
  // Exported menu link: menu-usermenu:logout
  $menu_links['menu-usermenu:logout'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'logout',
    'router_path' => 'logout',
    'link_title' => 'Logout',
    'options' => array(
      'purl' => 'disabled',
      'attributes' => array(
        'title' => 'Logout of ELMS',
        'class' => 'menu_icon menu-16499',
      ),
      'menu_icon' => array(
        'enable' => 1,
        'path' => 'sites/default/files/menu_icons/menu_icon_16499.png',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
    'parent_path' => 'user/1',
  );
  // Exported menu link: menu-usermenu:node/add/course
  $menu_links['menu-usermenu:node/add/course'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'node/add/course',
    'router_path' => 'node/add/course',
    'link_title' => 'Add Course Space',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a Course Space to the system',
        'class' => 'menu_icon menu-16566',
      ),
      'menu_icon' => array(
        'enable' => 1,
        'path' => 'sites/default/files/menu_icons/menu_icon_16566.png',
      ),
      'purl' => 'disabled',
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
    'parent_path' => 'courses',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add Course Space');
  t('Logout');
  t('My Bookmarks');
  t('My Courses');
  t('View All Courses');
  t('[user-name]');


  return $menu_links;
}
