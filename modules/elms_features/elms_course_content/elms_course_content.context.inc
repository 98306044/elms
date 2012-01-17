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
    'bookroot' => array(
      'values' => array(
        'folder' => 'folder',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
    'views' => array(
      'values' => array(
        'course_content_bookmarks' => 'course_content_bookmarks',
        'course_content_bookmarks:page' => 'course_content_bookmarks:page',
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
          'weight' => 0,
        ),
      ),
    ),
    'menu' => 'course_content',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Course Content blocks that enable navigation');
  t('ELMS Content');
  $export['elms_content-navigation'] = $context;

  return $export;
}
