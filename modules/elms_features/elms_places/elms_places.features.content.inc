<?php

/**
 * Implementation of hook_content_default_fields().
 */
function elms_places_content_default_fields() {
  $fields = array();

  // Exported field: field_location_content_ref
  $fields['place-field_location_content_ref'] = array(
    'field_name' => 'field_location_content_ref',
    'type_name' => 'place',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
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
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'folder' => 'folder',
      'page' => 'page',
      'studio_submission' => 'studio_submission',
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'blog' => 0,
      'elms_event' => 0,
      'course' => 0,
      'site' => 0,
      'link' => 0,
      'place' => 0,
      'promo' => 0,
      'reaction' => 0,
      'feed_reader' => 0,
      'feed_user_import' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'node_link' => array(
        'teaser' => 0,
        'full' => 1,
        'title' => 'Associate a Place to this Content',
        'hover_title' => 'Associate a Place to this Content',
        'destination' => 'node',
      ),
      'fallback' => 'leave_blank',
      'edit_fallback' => 0,
      'label' => 'Content Reference',
      'weight' => '-4',
      'description' => '',
      'type' => 'nodereference_url',
      'module' => 'nodereference_url',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Content Reference');

  return $fields;
}
