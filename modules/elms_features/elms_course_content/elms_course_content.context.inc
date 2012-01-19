<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_course_content_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_content-navigation';
  $context->description = 'Course Content blocks that enable navigation';
  $context->tag = 'ELMS Content';
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
        'elms_course_content-0' => array(
          'module' => 'elms_course_content',
          'delta' => 0,
          'region' => 'left',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Course Content blocks that enable navigation');
  t('ELMS Content');
  $export['elms_content-navigation'] = $context;

  return $export;
}
