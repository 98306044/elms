<?php

/**
 * Implementation of hook_input_formats().
 */
function elms_input_formats_input_formats() {
  $input_formats = array();

  $input_format = new stdClass;
  $input_format->api_version = 1;
  $input_format->name = 'Comment Filter';
  $input_format->roles = array(
    1 => 'anonymous user',
    2 => 'authenticated user',
    3 => 'administrator',
    6 => 'instructional designer',
    4 => 'instructor',
    9 => 'staff',
    10 => 'student',
    8 => 'teaching assistant',
  );
  $input_format->cache = TRUE;
  $input_format->settings = array(
    // Settings for: filter module
    'filter' => array(
      // Filter HTML tags
      'filter_html' => 1,
    ),
  );
  $input_format->filters = array(
    'filter' => array(
      // Delta => Weight for: URL filter
      '2' => '0',
      // Delta => Weight for: HTML filter
      '0' => '1',
      // Delta => Weight for: Line break converter
      '1' => '2',
      // Delta => Weight for: HTML corrector
      '3' => '10',
    ),
  );
  $input_format->machine = 'comment_filter';
  $input_formats['comment_filter'] = $input_format;

  $input_format = new stdClass;
  $input_format->api_version = 1;
  $input_format->name = 'Content Filter';
  $input_format->roles = array(
    3 => 'administrator',
    6 => 'instructional designer',
    4 => 'instructor',
  );
  $input_format->cache = TRUE;
  $input_format->settings = array(
    // Settings for: filter module
    'filter' => array(
      // Maximum link text length
      'filter_url_length' => '72',
    ),
  );
  $input_format->filters = array(
    'ckeditor_link' => array(
      // Delta => Weight for: CKEditor Link Filter
      '0' => '-9',
    ),
    'lightbox2' => array(
      // Delta => Weight for: Lightbox filter
      '0' => '-8',
    ),
    'filter' => array(
      // Delta => Weight for: HTML corrector
      '3' => '-7',
      // Delta => Weight for: URL filter
      '2' => '-6',
      // Delta => Weight for: Line break converter
      '1' => '-5',
    ),
  );
  $input_format->machine = 'content_filter';
  $input_formats['content_filter'] = $input_format;

  $input_format = new stdClass;
  $input_format->api_version = 1;
  $input_format->name = 'Course Event';
  $input_format->roles = array(
    6 => 'instructional designer',
    4 => 'instructor',
  );
  $input_format->cache = TRUE;
  $input_format->settings = array(
    // Settings for: filter module
    'filter' => array(
      // Filter HTML tags
      'filter_html' => '1',
      // Allowed HTML tags
      'allowed_html' => '<a> <em> <strong> <cite> <code> <ul> <ol> <li> <dl> <dt> <dd>',
      // Display HTML help
      'filter_html_help' => 1,
      // Spam link deterrent
      'filter_html_nofollow' => 0,
    ),
  );
  $input_format->filters = array(
    'filter' => array(
      // Delta => Weight for: URL filter
      '2' => '0',
      // Delta => Weight for: HTML filter
      '0' => '1',
      // Delta => Weight for: Line break converter
      '1' => '2',
      // Delta => Weight for: HTML corrector
      '3' => '10',
    ),
  );
  $input_format->machine = 'course_event';
  $input_formats['course_event'] = $input_format;

  $input_format = new stdClass;
  $input_format->api_version = 1;
  $input_format->name = 'PHP code';
  $input_format->roles = array();
  $input_format->cache = FALSE;
  $input_format->settings = array(
  );
  $input_format->filters = array(
    'php' => array(
      // Delta => Weight for: PHP evaluator
      '0' => '0',
    ),
  );
  $input_format->machine = 'php_code';
  $input_formats['php_code'] = $input_format;

  return $input_formats;

}
