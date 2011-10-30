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
        'weight' => '11',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'description' => '',
        '5' => array(
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
      ),
    ),
    'weight' => '11',
    'fields' => array(
      '0' => 'field_description',
      '1' => 'field_course_promotion',
      '2' => 'field_prerequisites',
      '3' => 'field_listing_only',
      '4' => 'field_course_link',
    ),
  );

  // Exported group: group_documentation
  $groups['course-group_documentation'] = array(
    'group_type' => 'standard',
    'type_name' => 'course',
    'group_name' => 'group_documentation',
    'label' => 'Documentation',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => 'Add files either to facilitate communication with faculty or students.',
      ),
      'display' => array(
        'weight' => '9',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'description' => '',
        '5' => array(
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
      ),
    ),
    'weight' => '9',
    'fields' => array(
      '0' => 'field_sample_materials',
      '1' => 'field_faculty_resources',
    ),
  );

  // Exported group: group_requirements
  $groups['course-group_requirements'] = array(
    'group_type' => 'standard',
    'type_name' => 'course',
    'group_name' => 'group_requirements',
    'label' => 'Technical Requirements',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => 'List the technical requirements so that they can be checked against the user prior to them taking the course.  This can offset headaches that would arise after course launch.',
      ),
      'display' => array(
        'weight' => '10',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'description' => '',
        '5' => array(
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
      ),
    ),
    'weight' => '10',
    'fields' => array(
      '0' => 'field_supported_browsers',
      '1' => 'field_required_plugins',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional Settings');
  t('Documentation');
  t('Technical Requirements');

  return $groups;
}
