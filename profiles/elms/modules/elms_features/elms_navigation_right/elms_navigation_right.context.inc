<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_navigation_right_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_core-nav_right';
  $context->description = 'Right hand social navigation and integration';
  $context->tag = 'ELMS Core';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'blog' => 'blog',
        'page' => 'page',
        'studio_submission' => 'studio_submission',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-course_reaction_list-block_1' => array(
          'module' => 'views',
          'delta' => 'course_reaction_list-block_1',
          'region' => 'regions_elms_navigation_right',
          'weight' => 0,
        ),
        'views-ece8583737f1c7a4e7b30a5a1ec9678b' => array(
          'module' => 'views',
          'delta' => 'ece8583737f1c7a4e7b30a5a1ec9678b',
          'region' => 'regions_elms_navigation_right',
          'weight' => 1,
        ),
        'views-3ba823cec964d8d329159a07015deca8' => array(
          'module' => 'views',
          'delta' => '3ba823cec964d8d329159a07015deca8',
          'region' => 'regions_elms_navigation_right',
          'weight' => 2,
        ),
        'views-e184cf5e3750b61341cbed374fda8361' => array(
          'module' => 'views',
          'delta' => 'e184cf5e3750b61341cbed374fda8361',
          'region' => 'regions_elms_navigation_right',
          'weight' => 3,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Core');
  t('Right hand social navigation and integration');
  $export['elms_core-nav_right'] = $context;

  return $export;
}
