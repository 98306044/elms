<?php

/**
 * Implementation of hook_input_formats().
 */
function elms_promo_input_formats() {
  $input_formats = array();

  $input_format = new stdClass;
  $input_format->api_version = 1;
  $input_format->name = 'promopages';
  $input_format->roles = array(
    3 => 'administrator',
  );
  $input_format->cache = TRUE;
  $input_format->settings = array(
  );
  $input_format->filters = array(
    'filter' => array(
      // Delta => Weight for: Line break converter
      '1' => '2',
    ),
  );
  $input_format->machine = 'promopages';
  $input_formats['promopages'] = $input_format;

  return $input_formats;

}
