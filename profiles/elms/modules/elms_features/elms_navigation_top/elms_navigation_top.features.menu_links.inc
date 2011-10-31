<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function elms_navigation_top_menu_default_menu_links() {
  $menu_links = array();

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
    'weight' => '-45',
  );
  // Exported menu link: menu-usermenu:my_reactions
  $menu_links['menu-usermenu:my_reactions'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'my_reactions',
    'router_path' => 'my_reactions',
    'link_title' => 'My Reactions',
    'options' => array(
      'attributes' => array(
        'title' => 'All reactions across courses',
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
  // Exported menu link: menu-usermenu:my_studio
  $menu_links['menu-usermenu:my_studio'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'my_studio',
    'router_path' => 'my_studio',
    'link_title' => 'My Studio',
    'options' => array(
      'attributes' => array(
        'title' => 'All my studio submissions',
      ),
      'purl' => 'disabled',
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: menu-usermenu:user
  $menu_links['menu-usermenu:user'] = array(
    'menu_name' => 'menu-usermenu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My Profile',
    'options' => array(
      'purl' => 'disabled',
      'attributes' => array(
        'title' => 'Your User profile',
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
  t('Logout');
  t('My Bookmarks');
  t('My Courses');
  t('My Profile');
  t('My Reactions');
  t('My Studio');


  return $menu_links;
}
