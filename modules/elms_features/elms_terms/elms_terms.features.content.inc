<?php

/**
 * Implementation of hook_content_default_fields().
 */
function elms_terms_content_default_fields() {
  $fields = array();

  // Exported field: field_term_content_ref
  $fields['term-field_term_content_ref'] = array(
    'field_name' => 'field_term_content_ref',
    'type_name' => 'term',
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
    'multiple' => '1',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'folder' => 'folder',
      'page' => 'page',
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'blog' => 0,
      'course_event' => 0,
      'course' => 0,
      'version' => 0,
      'link' => 0,
      'place' => 0,
      'promo' => 0,
      'reaction' => 0,
      'feed_reader' => 0,
      'studio_submission' => 0,
      'term' => 0,
      'timeline_item' => 0,
      'feed_user_import' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'node_link' => array(
        'teaser' => 0,
        'full' => 1,
        'title' => 'Associate a Term',
        'hover_title' => 'Associate a Term',
        'destination' => 'default',
      ),
      'fallback' => 'leave_blank',
      'edit_fallback' => 0,
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_term_content_ref][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'autocomplete_match' => 'contains',
      'size' => '60',
      'label' => 'Content Reference',
      'weight' => '-3',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Content Reference');

  return $fields;
}
