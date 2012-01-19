<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_course_studio_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_studio-navigation-content-type';
  $context->description = 'Course Studio navigation while viewing a submission';
  $context->tag = 'ELMS Studio';
  $context->conditions = array(
    'context_var' => array(
      'values' => array(
        'theme_%theme_settings|toggle_primary_links:1' => 'theme_%theme_settings|toggle_primary_links:1',
        'theme_%theme_settings|toggle_secondary_links:0' => 'theme_%theme_settings|toggle_secondary_links:0',
      ),
    ),
    'node' => array(
      'values' => array(
        'studio_submission' => 'studio_submission',
      ),
      'options' => array(
        'node_form' => '1',
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
    'menu' => 'studio',
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Course Studio navigation while viewing a submission');
  t('ELMS Studio');
  $export['elms_studio-navigation-content-type'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_studio-navigation-view';
  $context->description = 'Course Studio navigation while on views';
  $context->tag = 'ELMS Studio';
  $context->conditions = array(
    'context_var' => array(
      'values' => array(
        'theme_%theme_settings|toggle_primary_links:1' => 'theme_%theme_settings|toggle_primary_links:1',
        'theme_%theme_settings|toggle_secondary_links:0' => 'theme_%theme_settings|toggle_secondary_links:0',
      ),
    ),
    'views' => array(
      'values' => array(
        'course_studio:page_1' => 'course_studio:page_1',
        'course_studio:page_2' => 'course_studio:page_2',
        'course_studio:page_3' => 'course_studio:page_3',
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
    'menu' => 'studio',
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Course Studio navigation while on views');
  t('ELMS Studio');
  $export['elms_studio-navigation-view'] = $context;

  return $export;
}