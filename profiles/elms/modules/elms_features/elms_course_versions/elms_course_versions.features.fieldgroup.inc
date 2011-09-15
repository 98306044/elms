<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function elms_course_versions_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_basic
  $groups['version-group_basic'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_basic',
    'label' => 'Basic Information',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
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
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'no_style',
          'exclude' => 1,
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
        'label' => 'hidden',
      ),
      'multistep' => array(
        'step' => '1',
        'block' => 1,
      ),
    ),
    'weight' => '-5',
    'fields' => array(),
  );

  // Exported group: group_content
  $groups['version-group_content'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_content',
    'label' => 'Content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
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
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 1,
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
      'multistep' => array(
        'step' => '2',
        'block' => 1,
      ),
    ),
    'weight' => '2',
    'fields' => array(),
  );

  // Exported group: group_enrollment_management
  $groups['version-group_enrollment_management'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_enrollment_management',
    'label' => 'Enrollment Management',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
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
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 1,
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
      'multistep' => array(
        'step' => '6',
        'block' => 1,
      ),
    ),
    'weight' => '19',
    'fields' => array(),
  );

  // Exported group: group_instructional_flow
  $groups['version-group_instructional_flow'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_instructional_flow',
    'label' => 'Content Outline',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => 'You can start with a blank course outline or duplicate an existing one from another course.',
      ),
      'display' => array(
        'description' => 'You can start with a blank course outline or duplicate an existing one from another course.',
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'no_style',
          'exclude' => 1,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 1,
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
      'multistep' => array(
        'step' => '2',
        'block' => 0,
      ),
    ),
    'weight' => '5',
    'fields' => array(),
  );

  // Exported group: group_schedule
  $groups['version-group_schedule'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_schedule',
    'label' => 'Schedule',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => 'Use the Schedule Builder to communicate course pacing',
      ),
      'display' => array(
        'description' => 'Use the Schedule Builder to communicate course pacing',
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'no_style',
          'exclude' => 1,
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
      'multistep' => array(
        'step' => '3',
        'block' => 0,
      ),
    ),
    'weight' => '13',
    'fields' => array(
      '0' => 'field_schedule_to_build',
      '1' => 'field_schedule_source',
      '2' => 'field_start_date',
      '3' => 'field_finals_monday',
      '4' => 'field_top_level_name',
      '5' => 'field_num_topics',
      '6' => 'field_forming_week_structure',
      '7' => 'field_week_structure',
      '8' => 'field_semester',
      '9' => 'field_year',
    ),
  );

  // Exported group: group_schedule_step
  $groups['version-group_schedule_step'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_schedule_step',
    'label' => 'Schedule',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
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
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 1,
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
      'multistep' => array(
        'step' => '3',
        'block' => 1,
      ),
    ),
    'weight' => '10',
    'fields' => array(),
  );

  // Exported group: group_section_info
  $groups['version-group_section_info'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_section_info',
    'label' => 'Section Info',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
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
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 1,
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
      'multistep' => array(
        'step' => '5',
        'block' => 1,
      ),
    ),
    'weight' => '18',
    'fields' => array(
      '0' => 'field_section_semester',
      '1' => 'field_section_year',
      '2' => 'field_campus',
      '3' => 'field_section_number',
    ),
  );

  // Exported group: group_theme
  $groups['version-group_theme'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_theme',
    'label' => 'Design',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
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
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 1,
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
      'multistep' => array(
        'step' => '4',
        'block' => 1,
      ),
    ),
    'weight' => '15',
    'fields' => array(),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Basic Information');
  t('Content');
  t('Content Outline');
  t('Design');
  t('Enrollment Management');
  t('Schedule');
  t('Section Info');

  return $groups;
}
