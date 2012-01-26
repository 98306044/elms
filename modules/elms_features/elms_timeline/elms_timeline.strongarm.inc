<?php

/**
 * Implementation of hook_strongarm().
 */
function elms_timeline_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_timeline_item';
  $strongarm->value = array(
    'title' => '12',
    'body_field' => '19',
    'revision_information' => '24',
    'author' => '23',
    'options' => '25',
    'menu' => '15',
    'book' => '21',
    'path' => '26',
    'og_nodeapi' => '16',
    'print' => '27',
    'workflow' => '22',
    'locations' => '18',
    'spaces_preset' => '28',
    'purl' => '17',
    'themes' => '20',
  );
  $export['content_extra_weights_timeline_item'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_timeline_item';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_timeline_item'] = $strongarm;
	
	$strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_timeline_item';
  $strongarm->value = 'group_post_standard';
  $export['og_content_type_usage_timeline_item'] = $strongarm;

  return $export;
}
