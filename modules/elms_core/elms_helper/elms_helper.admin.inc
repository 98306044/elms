<?php

/**
 * Menu callback; displays a module's settings page.
 */
function elms_helper_settings_overview() {
  // Check database setup if necessary
  if (function_exists('db_check_setup') && empty($_POST)) {
    db_check_setup();
  }

  $item = menu_get_item('admin/elms');
  $content = system_admin_menu_block($item);

  $output = theme('admin_block_content', $content);

  return $output;
}