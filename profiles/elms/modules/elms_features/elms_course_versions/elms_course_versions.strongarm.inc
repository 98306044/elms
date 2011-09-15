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
    'og_user_roles_default_role' => '21',
    'title' => '-9',
    'revision_information' => '28',
    'author' => '29',
    'options' => '30',
    'comment_settings' => '32',
    'menu' => '22',
    'book' => '27',
    'path' => '33',
    'og_description' => '-8',
    'og_selective' => '23',
    'og_register' => '26',
    'og_directory' => '24',
    'print' => '31',
    'workflow' => '11',
    'og_private' => '25',
    'spaces_preset' => '-6',
    'purl' => '-7',
    'themes' => '17',
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
