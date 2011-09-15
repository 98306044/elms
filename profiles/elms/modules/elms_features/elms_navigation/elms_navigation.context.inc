<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_navigation_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_core-navigation';
  $context->description = 'The path of blocks helping keep in scope where you are in ELMS driven by the Appbar';
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
        'elms_helper-4' => array(
          'module' => 'elms_helper',
          'delta' => 4,
          'region' => 'appbar',
          'weight' => 0,
        ),
        'menu_block-1' => array(
          'module' => 'menu_block',
          'delta' => 1,
          'region' => 'appbar',
          'weight' => 1,
        ),
        'menu_block-4' => array(
          'module' => 'menu_block',
          'delta' => 4,
          'region' => 'appbar',
          'weight' => 2,
        ),
        'menu_block-6' => array(
          'module' => 'menu_block',
          'delta' => 6,
          'region' => 'appbar',
          'weight' => 3,
        ),
        'menu_block-5' => array(
          'module' => 'menu_block',
          'delta' => 5,
          'region' => 'appbar',
          'weight' => 4,
        ),
        'menu_block-3' => array(
          'module' => 'menu_block',
          'delta' => 3,
          'region' => 'appbar',
          'weight' => 5,
        ),
        'masquerade-0' => array(
          'module' => 'masquerade',
          'delta' => 0,
          'region' => 'appbar',
          'weight' => 6,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Core');
  t('The path of blocks helping keep in scope where you are in ELMS driven by the Appbar');
  $export['elms_core-navigation'] = $context;

  return $export;
}
