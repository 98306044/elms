<?php

/**
 * Implementation of hook_content_default_fields().
 */
function elms_course_versions_content_default_fields() {
  $fields = array();

  // Exported field: field_campus
  $fields['version-field_campus'] = array(
    'field_name' => 'field_campus',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '20',
      'parent' => 'group_section_info',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'oz|Abington Campus
aa|Altoona Campus
br|Beaver Campus
bk|Berks Campus
de|Brandywine Campus
dn|Dickinson School of Law
ds|Dubois Campus
fe|Fayette Campus
xs|Foreign Studies Program
mk|Greater Allegheny Campus
hn|Hazleton Campus
an|Lehigh Valley Campus
hy|Milton S. Hershey Medical Center
ma|Mont Alto Campus
nk|New Kensington Campus
bd|Penn State Erie, The Behrend College
kp|Penn State Great Valley
cl|Penn State Harrisburg, The Capital College
sl|Schuylkill Campus
sv|Shenango Campus
up|University Park
wb|Wilkes-Barre Campus
wd|World Campus
ws|Worthington Scranton Campus
yk|York Campus',
    'allowed_values_php' => '',
    'widget' => array(
      'multistep' => '6',
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Campus',
      'weight' => '20',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_course_ref
  $fields['version-field_course_ref'] = array(
    'field_name' => 'field_course_ref',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '-4',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'course' => 'course',
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'course_event' => 0,
      'folder' => 0,
      'link' => 0,
      'page' => 0,
      'promo' => 0,
      'version' => 0,
      'reaction' => FALSE,
      'studio_submission' => FALSE,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => '20',
      'multistep' => '1',
      'default_value' => array(
        '0' => array(
          'nid' => '',
        ),
      ),
      'default_value_php' => NULL,
      'node_link' => array(
        'teaser' => 0,
        'full' => 0,
        'title' => 'Course Version',
        'hover_title' => '',
        'destination' => 'default',
      ),
      'fallback' => 'select',
      'edit_fallback' => 0,
      'label' => 'Course',
      'weight' => '-5',
      'description' => '',
      'type' => 'nodereference_url',
      'module' => 'nodereference_url',
    ),
  );

  // Exported field: field_finals_monday
  $fields['version-field_finals_monday'] = array(
    'field_name' => 'field_finals_monday',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '17',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'date',
    'required' => '1',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
    ),
    'timezone_db' => 'America/New_York',
    'tz_handling' => 'none',
    'todate' => '',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'schedule_date',
    'widget' => array(
      'default_value' => 'blank',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'D, d/m/Y - g:ia',
      'input_format_custom' => '',
      'increment' => '1',
      'text_parts' => array(),
      'year_range' => '-1:+3',
      'label_position' => 'above',
      'label' => 'Finals',
      'weight' => '17',
      'description' => 'The Monday of the week that finals start',
      'type' => 'date_popup',
      'module' => 'date',
    ),
  );

  // Exported field: field_forming_week_structure
  $fields['version-field_forming_week_structure'] = array(
    'field_name' => 'field_forming_week_structure',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '20',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'define_structure|Define Structure below
none|Don\'t create events, only create containers
prototype|Build from Prototype Lesson / Course',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'define_structure',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Forming Week Structure',
      'weight' => '20',
      'description' => 'How do you want weeks to be populated in schedule creation? You can either define a structure below, not build one, or build based on a prototype lesson (requires that a course structure exist)',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_instructional_template
  $fields['version-field_instructional_template'] = array(
    'field_name' => 'field_instructional_template',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '8',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => 'return _elms_instructional_templates_get_instructional_template();',
    'widget' => array(
      'multistep' => '2',
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Instructional Template',
      'weight' => '-1',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_lesson_count
  $fields['version-field_lesson_count'] = array(
    'field_name' => 'field_lesson_count',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '9',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '1
2
3
4
5
6
7
8
9
10
11
12
13
14
15',
    'allowed_values_php' => '',
    'widget' => array(
      'multistep' => '2',
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Lessons',
      'weight' => 0,
      'description' => 'How many lessons would you like to start with?',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_num_topics
  $fields['version-field_num_topics'] = array(
    'field_name' => 'field_num_topics',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '19',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '2
3
4
5
6
7
8',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '3',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Number of Topics',
      'weight' => '19',
      'description' => 'How many topics would you like to build out? This will be used to spread the weeks of instruction evenly. You can always add or remove topics after creation.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_schedule_source
  $fields['version-field_schedule_source'] = array(
    'field_name' => 'field_schedule_source',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '15',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'registrar|Registrar
manual|Manual Entry',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => 'registrar',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Schedule Source',
      'weight' => '15',
      'description' => 'Connect to the registrar or use manual date entry to build schedule.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_schedule_to_build
  $fields['version-field_schedule_to_build'] = array(
    'field_name' => 'field_schedule_to_build',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '14',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'week|Week Based Schedule
topic|Topic Based Schedule',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'week',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Schedule to Build',
      'weight' => '14',
      'description' => 'Select if you would like to build a new schedule from scratch or use a template.  In the case of rebuilding a schedule you can either rebuild the dates or the entire schedule. <strong>WARNING: Rebuilding the entire schedule will delete your current schedule!</strong>',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_scoring_method
  $fields['version-field_scoring_method'] = array(
    'field_name' => 'field_scoring_method',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '12',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'points|Points
percentage|Percentages',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 'points',
        ),
      ),
      'default_value_php' => NULL,
      'multistep' => '3',
      'label' => 'Scoring Method',
      'weight' => '3',
      'description' => 'This will base all Event Score values on either points or percentages.  Points is the default and this value won\'t be used unless you decide to add points to events.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_section_number
  $fields['version-field_section_number'] = array(
    'field_name' => 'field_section_number',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '21',
      'parent' => 'group_section_info',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '3',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '3',
      'multistep' => '6',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_section_number][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Section Number',
      'weight' => '21',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_section_semester
  $fields['version-field_section_semester'] = array(
    'field_name' => 'field_section_semester',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '18',
      'parent' => 'group_section_info',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'fa|Fall
sp|Spring
su|Summer
su1|Summer 1
su2|Summer 2',
    'allowed_values_php' => '',
    'widget' => array(
      'multistep' => '6',
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Section Semester',
      'weight' => '18',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_section_year
  $fields['version-field_section_year'] = array(
    'field_name' => 'field_section_year',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '19',
      'parent' => 'group_section_info',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '201112|201112
201213|201213
201314|201314
201415|201415
201516|201516
201617|201617
201718|201718',
    'allowed_values_php' => '',
    'widget' => array(
      'multistep' => '6',
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Year',
      'weight' => '19',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_semester
  $fields['version-field_semester'] = array(
    'field_name' => 'field_semester',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '22',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'fall|Fall
spring|Spring
summer|Summer
summer1|Summer 1
summer2|Summer 2',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Semester',
      'weight' => '22',
      'description' => 'What semester is this course space being developed for?',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_start_date
  $fields['version-field_start_date'] = array(
    'field_name' => 'field_start_date',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '16',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'date',
    'required' => '1',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
    ),
    'timezone_db' => 'America/New_York',
    'tz_handling' => 'none',
    'todate' => '',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'schedule_date',
    'widget' => array(
      'default_value' => 'blank',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'D, m/d/Y - g:ia',
      'input_format_custom' => '',
      'increment' => '1',
      'text_parts' => array(),
      'year_range' => '-1:+3',
      'label_position' => 'above',
      'label' => 'Start',
      'weight' => '16',
      'description' => 'The first Monday of the semester.',
      'type' => 'date_popup',
      'module' => 'date',
    ),
  );

  // Exported field: field_top_level_name
  $fields['version-field_top_level_name'] = array(
    'field_name' => 'field_top_level_name',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '18',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'module|Module
unit|Unit',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => 'unit',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Top Level Name',
      'weight' => '18',
      'description' => 'The name of the largest structural item in the schedule for Topic Based outlines / schedules.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_week_structure
  $fields['version-field_week_structure'] = array(
    'field_name' => 'field_week_structure',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '21',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '1',
    'module' => 'text',
    'active' => '1',
    'text_processing' => 0,
    'max_length' => '',
    'allowed_values' => 'activity|Activity
assessment|Assessment
assignment|Assignment
discussion|Discussion
lecture|Lecture
reading|Reading',
    'allowed_values_php' => '',
    'widget' => array(
      'size' => '20',
      'autocomplete_match' => 'starts_with',
      'autocomplete_case' => '1',
      'i18n_flddata' => 0,
      'default_value' => NULL,
      'default_value_php' => 'return array(
  0 => array(\'value\' => \'reading\'),
  1 => array(\'value\' => \'reading\'),
  2 => array(\'value\' => \'activity\'),
  3 => array(\'value\' => \'assessment\'));',
      'label' => 'Week Structure',
      'weight' => '21',
      'description' => 'Select the default structure for your weeks. Allowed values are Activity, Assessment, Assignment, Discussion, Lecture, Reading',
      'type' => 'autocomplete_widgets_allowvals',
      'module' => 'autocomplete_widgets',
    ),
  );

  // Exported field: field_year
  $fields['version-field_year'] = array(
    'field_name' => 'field_year',
    'type_name' => 'version',
    'display_settings' => array(
      'weight' => '23',
      'parent' => 'group_schedule',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '11|2011
12|2012
13|2013
14|2014
15|2015
16|2016
17|2017',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Year',
      'weight' => '23',
      'description' => 'The year this course will be offered.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Campus');
  t('Course');
  t('Finals');
  t('Forming Week Structure');
  t('Instructional Template');
  t('Lessons');
  t('Number of Topics');
  t('Schedule Source');
  t('Schedule to Build');
  t('Scoring Method');
  t('Section Number');
  t('Section Semester');
  t('Semester');
  t('Start');
  t('Top Level Name');
  t('Week Structure');
  t('Year');

  return $fields;
}
