<?php

/**
 * Implementation of page callback for settings.
 */
function hidden_nodes_setting_page() {
  $form = array();
  foreach (node_get_types() as $type_data) {
    $types[$type_data->type] = $type_data->name;
  }
  $form['hidden_nodes_types'] = array(
    '#type' => 'select',
    '#options' => $types,
    '#title' => t('Types to hide'),
    '#description' => t("Select the types that are allowed to be hidden from users that don't have permission to view hidden content."),
    '#default_value' => variable_get('hidden_nodes_types', array()),
    '#multiple' => TRUE,
  );
  $form['hidden_nodes_show_message'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display message'),
    '#description' => t("Display a message to users who can view hidden nodes that it is hidden."),
    '#default_value' => variable_get('hidden_nodes_show_message', 1),
  );
  return system_settings_form($form);
}