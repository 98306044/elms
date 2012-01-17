<?php

/**
 * Implementation of hook_uuid_features_default_terms().
 */
function elms_course_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'uuid' => '661d8d88-df9f-11e0-9008-005056807d81',
    'name' => 'School of Architecture and Landscape Architecture',
    'description' => '',
    'weight' => '0',
    'uuid_vocabulary' => '661d3c52-df9f-11e0-9008-005056807d81',
  );
  $terms[] = array(
    'uuid' => '661dbb8c-df9f-11e0-9008-005056807d81',
    'name' => 'Department of Art History',
    'description' => '',
    'weight' => '1',
    'uuid_vocabulary' => '661d3c52-df9f-11e0-9008-005056807d81',
  );
  $terms[] = array(
    'uuid' => '661de4ae-df9f-11e0-9008-005056807d81',
    'name' => 'Department of Integrative Arts',
    'description' => '',
    'weight' => '2',
    'uuid_vocabulary' => '661d3c52-df9f-11e0-9008-005056807d81',
  );
  $terms[] = array(
    'uuid' => '661e0d62-df9f-11e0-9008-005056807d81',
    'name' => 'School of Music',
    'description' => '',
    'weight' => '3',
    'uuid_vocabulary' => '661d3c52-df9f-11e0-9008-005056807d81',
  );
  $terms[] = array(
    'uuid' => '661e33dc-df9f-11e0-9008-005056807d81',
    'name' => 'School of Theatre',
    'description' => '',
    'weight' => '4',
    'uuid_vocabulary' => '661d3c52-df9f-11e0-9008-005056807d81',
  );
  $terms[] = array(
    'uuid' => '661e5f92-df9f-11e0-9008-005056807d81',
    'name' => 'School of Visual Arts',
    'description' => '',
    'weight' => '5',
    'uuid_vocabulary' => '661d3c52-df9f-11e0-9008-005056807d81',
  );
  return $terms;
}
