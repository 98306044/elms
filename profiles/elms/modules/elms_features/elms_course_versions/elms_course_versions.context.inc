<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_course_versions_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_course_versions-features';
  $context->description = 'Display the block navigation for the enabled Features';
  $context->tag = 'ELMS Course Versions';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        'version' => 'version',
      ),
      'options' => array(
        'node_form' => 0,
      ),
    ),
    'context_var' => array(
      'values' => array(
        'theme_%theme_settings|toggle_primary_links:0' => 'theme_%theme_settings|toggle_primary_links:0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-features' => array(
          'module' => 'menu',
          'delta' => 'features',
          'region' => 'left',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display the block navigation for the enabled Features');
  t('ELMS Course Versions');
  $export['elms_course_versions-features'] = $context;

  return $export;
}
