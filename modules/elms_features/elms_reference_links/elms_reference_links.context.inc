<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_reference_links_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_reference_links-nav-right';
  $context->description = 'Right hand menu integration with Reference Links';
  $context->tag = 'ELMS Reference Links';
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
        'views-elms_related_links_list-block_1' => array(
          'module' => 'views',
          'delta' => 'elms_related_links_list-block_1',
          'region' => 'regions_elms_navigation_right',
          'weight' => NULL,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Reference Links');
  t('Right hand menu integration with Reference Links');
  $export['elms_reference_links-nav-right'] = $context;

  return $export;
}
