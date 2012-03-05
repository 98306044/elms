<?php
/**
 * Implementation of hook_settings().
 */
function _html_export_settings() {
  $form['html_export_dom_remove'] = array(
	  '#type' => 'textfield',
		'#title' => t('Default dom removal'),
		'#description' => t("Supply a css style selector to target the removal of. This is especially useful for removing things like the admin toolbar, tabs, or other elements you don't want to have exported. Split selectors with a comma."),
		'#default_value' => variable_get('html_export_dom_remove', ''),
	);
	return system_settings_form($form);
}
