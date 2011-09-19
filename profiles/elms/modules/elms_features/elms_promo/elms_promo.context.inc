<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_promo_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_promo-promo-site';
  $context->description = 'This context is used to manage blocks on the promotional site';
  $context->tag = 'ELMS Promo';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'promo' => 'promo',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-promo' => array(
          'module' => 'menu',
          'delta' => 'menu-promo',
          'region' => 'right',
          'weight' => 0,
        ),
        'block-1' => array(
          'module' => 'block',
          'delta' => 1,
          'region' => 'right',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Promo');
  t('This context is used to manage blocks on the promotional site');
  $export['elms_promo-promo-site'] = $context;

  return $export;
}
