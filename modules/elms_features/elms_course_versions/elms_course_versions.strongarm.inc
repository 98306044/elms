<?php

/**
 * Implementation of hook_strongarm().
 */
function elms_course_versions_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_version';
  $strongarm->value = 0;
  $export['comment_anonymous_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_version';
  $strongarm->value = '3';
  $export['comment_controls_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_version';
  $strongarm->value = '4';
  $export['comment_default_mode_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_version';
  $strongarm->value = '1';
  $export['comment_default_order_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_version';
  $strongarm->value = '50';
  $export['comment_default_per_page_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_version';
  $strongarm->value = '0';
  $export['comment_form_location_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_version';
  $strongarm->value = '1';
  $export['comment_preview_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_version';
  $strongarm->value = '0';
  $export['comment_subject_field_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_version';
  $strongarm->value = '0';
  $export['comment_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_version';
  $strongarm->value = array(
    'og_user_roles_default_role' => '5',
    'title' => '-4',
    'revision_information' => '12',
    'author' => '13',
    'options' => '14',
    'menu' => '6',
    'book' => '11',
    'path' => '16',
    'og_description' => '-3',
    'og_selective' => '7',
    'og_register' => '10',
    'og_directory' => '8',
    'print' => '15',
    'workflow' => '-1',
    'og_private' => '9',
    'spaces_preset' => '17',
    'purl' => '-2',
    'themes' => '2',
  );
  $export['content_extra_weights_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_version';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_version'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_version';
  $strongarm->value = '0';
  $export['upload_version'] = $strongarm;

  return $export;
}
