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
    'node' => array(
      'values' => array(
        'folder' => 'folder',
        'link' => 'link',
        'page' => 'page',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'views' => array(
      'values' => array(
        'course_content_root_node:page_1' => 'course_content_root_node:page_1',
        'og_ghp_course_content_root_node' => 'og_ghp_course_content_root_node',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'elms_helper-2' => array(
          'module' => 'elms_helper',
          'delta' => 2,
          'region' => 'left',
          'weight' => 0,
        ),
        'elms_helper-0' => array(
          'module' => 'elms_helper',
          'delta' => 0,
          'region' => 'left',
          'weight' => 1,
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
