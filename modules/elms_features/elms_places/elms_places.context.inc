<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_places_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_place-nav-right';
  $context->description = 'Right hand menu integration with Places';
  $context->tag = 'ELMS Place';
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
        'views-course_place_list-block_1' => array(
          'module' => 'views',
          'delta' => 'course_place_list-block_1',
          'region' => 'regions_elms_navigation_right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Place');
  t('Right hand menu integration with Places');
  $export['elms_place-nav-right'] = $context;

  return $export;
}