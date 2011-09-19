<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function elms_input_formats_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "input_formats" && $api == "input_formats") {
    return array("version" => 1);
  }
}
