<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_reaction_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_reaction-navigation';
  $context->description = 'Provide navigation if primary links are in use';
  $context->tag = 'ELMS Reaction';
  $context->conditions = array(
    'context_var' => array(
      'values' => array(
        'theme_%theme_settings|toggle_primary_links:1' => 'theme_%theme_settings|toggle_primary_links:1',
        'theme_%theme_settings|toggle_secondary_links:0' => 'theme_%theme_settings|toggle_secondary_links:0',
      ),
    ),
    'views' => array(
      'values' => array(
        'course_reaction_list:page_1' => 'course_reaction_list:page_1',
        'course_reaction_list:page_2' => 'course_reaction_list:page_2',
        'course_reaction_list:page_3' => 'course_reaction_list:page_3',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-elms-reactions' => array(
          'module' => 'menu',
          'delta' => 'menu-elms-reactions',
          'region' => 'left',
          'weight' => 0,
        ),
      ),
    ),
    'menu' => 'reactions',
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Reaction');
  t('Provide navigation if primary links are in use');
  $export['elms_reaction-navigation'] = $context;

  return $export;
}
