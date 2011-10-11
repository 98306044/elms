<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_course_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_course-landing-page';
  $context->description = 'This is to get the blocks onto the page for the course landing pages';
  $context->tag = 'ELMS Course';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'course' => 'course',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-course_promo-block_1' => array(
          'module' => 'views',
          'delta' => 'course_promo-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
        'views-courses-block_1' => array(
          'module' => 'views',
          'delta' => 'courses-block_1',
          'region' => 'content',
          'weight' => 1,
        ),
        'views-courses-block_3' => array(
          'module' => 'views',
          'delta' => 'courses-block_3',
          'region' => 'right',
          'weight' => 0,
        ),
        'views-courses-block_4' => array(
          'module' => 'views',
          'delta' => 'courses-block_4',
          'region' => 'right',
          'weight' => 1,
        ),
        'views-baddb6f656d85554896d66c27169b3ec' => array(
          'module' => 'views',
          'delta' => 'baddb6f656d85554896d66c27169b3ec',
          'region' => 'right',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Course');
  t('This is to get the blocks onto the page for the course landing pages');
  $export['elms_course-landing-page'] = $context;

  return $export;
}
