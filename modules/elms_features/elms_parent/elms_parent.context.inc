<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_parent_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_parent-landing-page';
  $context->description = 'This is to get the blocks onto the page for the course landing pages';
  $context->tag = 'ELMS Parent';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'parent' => 'parent',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-parent_promo-block_1' => array(
          'module' => 'views',
          'delta' => 'parent_promo-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
        'views-parents-block_1' => array(
          'module' => 'views',
          'delta' => 'parents-block_1',
          'region' => 'content',
          'weight' => 1,
        ),
        'views-parents-block_6' => array(
          'module' => 'views',
          'delta' => 'parents-block_6',
          'region' => 'content',
          'weight' => 2,
        ),
        'views-parents-block_3' => array(
          'module' => 'views',
          'delta' => 'parents-block_3',
          'region' => 'content',
          'weight' => 3,
        ),
        'views-parents-block_5' => array(
          'module' => 'views',
          'delta' => 'parents-block_5',
          'region' => 'content',
          'weight' => 4,
        ),
        'views-elms_parent_info_blocks-block_3' => array(
          'module' => 'views',
          'delta' => 'elms_parent_info_blocks-block_3',
          'region' => 'right',
          'weight' => 0,
        ),
        'views-parents-block_4' => array(
          'module' => 'views',
          'delta' => 'parents-block_4',
          'region' => 'right',
          'weight' => 1,
        ),
        'views-elms_parent_info_blocks-block_2' => array(
          'module' => 'views',
          'delta' => 'elms_parent_info_blocks-block_2',
          'region' => 'right',
          'weight' => 2,
        ),
        'views-elms_parent_info_blocks-block_1' => array(
          'module' => 'views',
          'delta' => 'elms_parent_info_blocks-block_1',
          'region' => 'right',
          'weight' => 3,
        ),
        'views-elms_parent_info_blocks-block_4' => array(
          'module' => 'views',
          'delta' => 'elms_parent_info_blocks-block_4',
          'region' => 'right',
          'weight' => 4,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Parent');
  t('This is to get the blocks onto the page for the course landing pages');
  $export['elms_parent-landing-page'] = $context;

  return $export;
}
