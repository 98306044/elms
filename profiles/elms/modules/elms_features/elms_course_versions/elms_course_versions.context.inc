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

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_course_versions-multistep-left';
  $context->description = 'Make sure that the multistep form appears on themes that support left block nav, which is the majority of drupal themes';
  $context->tag = 'ELMS Course Versions';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        'version' => 'version',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'multistep-version' => array(
          'module' => 'multistep',
          'delta' => 'version',
          'region' => 'left',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Course Versions');
  t('Make sure that the multistep form appears on themes that support left block nav, which is the majority of drupal themes');
  $export['elms_course_versions-multistep-left'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_course_versions-multistep-right';
  $context->description = 'Enable multistep block when creating a course version before the theme is set';
  $context->tag = 'ELMS Course Versions';
  $context->conditions = array(
    'context_condition_theme' => array(
      'values' => array(
        'cube' => 'cube',
      ),
    ),
    'node' => array(
      'values' => array(
        'version' => 'version',
      ),
      'options' => array(
        'node_form' => '2',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'multistep-version' => array(
          'module' => 'multistep',
          'delta' => 'version',
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Course Versions');
  t('Enable multistep block when creating a course version before the theme is set');
  $export['elms_course_versions-multistep-right'] = $context;

  return $export;
}
