<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function elms_course_versions_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_content
  $groups['version-group_content'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_content',
    'label' => 'Content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' => array(
        'weight' => '0',
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
    'weight' => '0',
    'fields' => array(
      '0' => 'field_instructional_template',
      '1' => 'field_lesson_count',
    ),
  );

  // Exported group: group_instructor_contact_info
  $groups['version-group_instructor_contact_info'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_instructor_contact_info',
    'label' => 'Instructor Contact Info',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsed',
        'description' => 'This provides a block for the instructor to display their contact information (such as office hours)',
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
    ),
    'weight' => '4',
    'fields' => array(
      '0' => 'field_inst_contact_block',
    ),
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
        'weight' => '1',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'no_style',
          'exclude' => 1,
        ),
        'description' => 'Use the Schedule Builder to communicate course pacing',
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
      'multistep' => array(
        'step' => '3',
        'block' => 0,
      ),
    ),
    'weight' => '1',
    'fields' => array(
      '0' => 'field_scoring_method',
      '1' => 'field_schedule_to_build',
      '2' => 'field_schedule_source',
      '3' => 'field_start_date',
      '4' => 'field_finals_monday',
      '5' => 'field_top_level_name',
      '6' => 'field_num_topics',
      '7' => 'field_forming_week_structure',
      '8' => 'field_week_structure',
      '9' => 'field_semester',
      '10' => 'field_year',
    ),
  );

  // Exported group: group_section_info
  $groups['version-group_section_info'] = array(
    'group_type' => 'standard',
    'type_name' => 'version',
    'group_name' => 'group_section_info',
    'label' => 'Section Info',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' => array(
        'weight' => '3',
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
    'weight' => '3',
    'fields' => array(
      '0' => 'field_section_semester',
      '1' => 'field_section_year',
      '2' => 'field_campus',
      '3' => 'field_section_number',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Instructor Contact Info');
  t('Schedule');
  t('Section Info');

  return $groups;
}
