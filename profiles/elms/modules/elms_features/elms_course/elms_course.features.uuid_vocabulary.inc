<?php

/**
 * Implementation of hook_uuid_features_default_vocabularies().
 */
function elms_course_uuid_features_default_vocabularies() {
  $vocabularies = array();

  $vocabularies[] = array(
    'uuid' => '661d3c52-df9f-11e0-9008-005056807d81',
    'name' => 'Academic Unit',
    'description' => 'Academic Unit that is offering this course',
    'help' => 'Choose the Academic Unit offering this course',
    'relations' => '1',
    'multiple' => '0',
    'required' => '1',
    'tags' => '0',
    'module' => 'features_academicunit',
    'weight' => '0',
    'nodes' => array(
      'course' => 'course',
    ),
  );
  return $vocabularies;
}
