<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_course_studio_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_studio-navigation';
  $context->description = 'Course Studio navigation';
  $context->tag = 'ELMS Studio';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'studio_submission' => 'studio_submission',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'views' => array(
      'values' => array(
        'course_studio:page_1' => 'course_studio:page_1',
        'course_studio:page_2' => 'course_studio:page_2',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-course-studio' => array(
          'module' => 'menu',
          'delta' => 'menu-course-studio',
          'region' => 'left',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Course Studio navigation');
  t('ELMS Studio');
  $export['elms_studio-navigation'] = $context;

  return $export;
}
