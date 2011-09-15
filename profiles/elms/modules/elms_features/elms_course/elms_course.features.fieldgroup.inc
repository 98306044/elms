<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function elms_course_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_additional_settings
  $groups['course-group_additional_settings'] = array(
    'group_type' => 'standard',
    'type_name' => 'course',
    'group_name' => 'group_additional_settings',
    'label' => 'Additional Settings',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '11',
    'fields' => array(
      '0' => 'field_course_title',
      '1' => 'field_description',
      '2' => 'field_course_promotion',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional Settings');

  return $groups;
}
