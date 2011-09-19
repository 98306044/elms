<?php

/**
 * Implementation of hook_conditional_fields_default_fields().
 */
function elms_course_versions_conditional_fields_default_fields() {
$items = array();
$items[] = array (
  'control_field_name' => 'field_forming_week_structure',
  'field_name' => 'field_week_structure',
  'type' => 'version',
  'trigger_values' => 
  array (
    'define_structure' => 'define_structure',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_source',
  'field_name' => 'field_finals_monday',
  'type' => 'version',
  'trigger_values' => 
  array (
    'manual' => 'manual',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_source',
  'field_name' => 'field_semester',
  'type' => 'version',
  'trigger_values' => 
  array (
    'registrar' => 'registrar',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_source',
  'field_name' => 'field_start_date',
  'type' => 'version',
  'trigger_values' => 
  array (
    'manual' => 'manual',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_source',
  'field_name' => 'field_year',
  'type' => 'version',
  'trigger_values' => 
  array (
    'registrar' => 'registrar',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_to_build',
  'field_name' => 'field_finals_monday',
  'type' => 'version',
  'trigger_values' => 
  array (
    'week' => 'week',
    'topic' => 'topic',
    'rebuild' => 'rebuild',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_to_build',
  'field_name' => 'field_forming_week_structure',
  'type' => 'version',
  'trigger_values' => 
  array (
    'week' => 'week',
    'topic' => 'topic',
    'rebuild_schedule' => 'rebuild_schedule',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_to_build',
  'field_name' => 'field_num_topics',
  'type' => 'version',
  'trigger_values' => 
  array (
    'topic' => 'topic',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_to_build',
  'field_name' => 'field_schedule_source',
  'type' => 'version',
  'trigger_values' => 
  array (
    'week' => 'week',
    'topic' => 'topic',
    'rebuild' => 'rebuild',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_to_build',
  'field_name' => 'field_semester',
  'type' => 'version',
  'trigger_values' => 
  array (
    'week' => 'week',
    'topic' => 'topic',
    'rebuild' => 'rebuild',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_to_build',
  'field_name' => 'field_start_date',
  'type' => 'version',
  'trigger_values' => 
  array (
    'week' => 'week',
    'topic' => 'topic',
    'rebuild' => 'rebuild',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_to_build',
  'field_name' => 'field_top_level_name',
  'type' => 'version',
  'trigger_values' => 
  array (
    'topic' => 'topic',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_to_build',
  'field_name' => 'field_week_structure',
  'type' => 'version',
  'trigger_values' => 
  array (
    'week' => 'week',
    'topic' => 'topic',
    'rebuild_schedule' => 'rebuild_schedule',
  ),
);
$items[] = array (
  'control_field_name' => 'field_schedule_to_build',
  'field_name' => 'field_year',
  'type' => 'version',
  'trigger_values' => 
  array (
    'week' => 'week',
    'topic' => 'topic',
    'rebuild' => 'rebuild',
  ),
);
return $items;
}
