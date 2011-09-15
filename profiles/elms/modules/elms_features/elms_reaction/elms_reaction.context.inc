<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_reaction_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_reaction-content-list';
  $context->description = 'Position blocks on the page for a reaction to content';
  $context->tag = 'ELMS Reaction';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        'version' => 'version',
      ),
      'options' => array(
        'node_form' => 0,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-course_reaction_list-block_1' => array(
          'module' => 'views',
          'delta' => 'course_reaction_list-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Reaction');
  t('Position blocks on the page for a reaction to content');
  $export['elms_reaction-content-list'] = $context;

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
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Reaction');
  t('Provide navigation if primary links are in use');
  $export['elms_reaction-navigation'] = $context;

  return $export;
}
