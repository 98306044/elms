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
    'weight' => '8',
    'fields' => array(
      '0' => 'field_course_title',
      '1' => 'field_description',
      '2' => 'field_course_promotion',
      '3' => 'field_sample_syllabus',
      '4' => 'field_course_link',
    ),
  );

  // Exported group: group_requirements
  $groups['course-group_requirements'] = array(
    'group_type' => 'standard',
    'type_name' => 'course',
    'group_name' => 'group_requirements',
    'label' => 'Requirements',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => 'Tell students what is required in order to take this course.  General course accessibility can be defined here to tell those with special needs what to expect from this course.  This can also help offset technical requirement issues after a course launches.',
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
    'weight' => '9',
    'fields' => array(
      '0' => 'field_accessibility_rating',
      '1' => 'field_supported_browsers',
      '2' => 'field_required_plugins',
      '3' => 'field_prerequisites',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional Settings');
  t('Requirements');

  return $groups;
}
