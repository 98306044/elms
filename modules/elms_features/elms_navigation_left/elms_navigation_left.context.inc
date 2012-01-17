<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_navigation_left_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_core-nav-left';
  $context->description = 'Left side menu items';
  $context->tag = 'ELMS Core';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'elms_navigation_left-2' => array(
          'module' => 'elms_navigation_left',
          'delta' => 2,
          'region' => 'regions_elms_navigation_left',
          'weight' => 0,
        ),
        'elms_navigation_left-1' => array(
          'module' => 'elms_navigation_left',
          'delta' => 1,
          'region' => 'regions_elms_navigation_left',
          'weight' => 1,
        ),
        'elms_navigation_left-0' => array(
          'module' => 'elms_navigation_left',
          'delta' => 0,
          'region' => 'regions_elms_navigation_left',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Core');
  t('Left side menu items');
  $export['elms_core-nav-left'] = $context;

  return $export;
}
