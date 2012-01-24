<?php

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function elms_parent_taxonomy_default_vocabularies() {
  return array(
    'academicunit' => array(
      'name' => 'Academic Unit',
      'description' => 'Academic Unit that is offering this course',
      'help' => 'Choose the Academic Unit offering this course',
      'relations' => '1',
      'hierarchy' => '1',
      'multiple' => '0',
      'required' => '1',
      'tags' => '0',
      'module' => 'features_academicunit',
      'weight' => '0',
      'nodes' => array(
        'parent' => 'parent',
      ),
    ),
  );
}
