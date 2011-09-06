<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function elms_reaction_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elms_reaction-content-list';
  $context->description = 'Position blocks on the page for a reaction to content';
  $context->tag = 'ELMS Reaction';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        'version' => 'version',
      ),
      'options' => array(
        'node_form' => 0,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-reaction_list-block_1' => array(
          'module' => 'views',
          'delta' => 'reaction_list-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMS Reaction');
  t('Position blocks on the page for a reaction to content');
  $export['elms_reaction-content-list'] = $context;

  return $export;
}
