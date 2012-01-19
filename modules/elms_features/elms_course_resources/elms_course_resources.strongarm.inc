<?php

/**
 * Implementation of hook_strongarm().
 */
function elms_course_resources_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_course_resource';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '-4',
    'revision_information' => '4',
    'author' => '3',
    'options' => '5',
    'menu' => '0',
    'book' => '2',
    'path' => '7',
    'print' => '6',
    'workflow' => '1',
    'spaces_preset' => '8',
    'purl' => '-1',
    'themes' => '-2',
  );
  $export['content_extra_weights_course_resource'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_course_resource';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_course_resource'] = $strongarm;

  return $export;
}