<?php

/**
 * Implementation of hook_menu_default_menu_custom().
 */
function elms_promo_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-promo
  $menus['menu-promo'] = array(
    'menu_name' => 'menu-promo',
    'title' => 'ELMS',
    'description' => 'Used for the promotional side of ELMS',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS');
  t('Used for the promotional side of ELMS');


  return $menus;
}
