<?php

/**
 * Implementation of hook_strongarm().
 */
function elms_terms_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_term';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '1',
    'revision_information' => '6',
    'author' => '5',
    'options' => '7',
    'menu' => '-4',
    'book' => '3',
    'path' => '8',
    'og_nodeapi' => '-2',
    'print' => '9',
    'workflow' => '4',
    'locations' => '0',
    'spaces_preset' => '10',
    'purl' => '-1',
    'themes' => '2',
  );
  $export['content_extra_weights_term'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_term';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_term'] = $strongarm;

  return $export;
}
