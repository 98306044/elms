<?php

/**
 * Implementation of hook_content_default_fields().
 */
function elms_reference_links_content_default_fields() {
  $fields = array();

  // Exported field: field_related_content_ref
  $fields['content_links-field_related_content_ref'] = array(
    'field_name' => 'field_related_content_ref',
    'type_name' => 'content_links',
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
      'accessibility_guideline' => 0,
      'accessibility_test' => 0,
      'blog' => 0,
      'content_links' => 0,
      'course_event' => 0,
      'course_resource' => 0,
      'course' => 0,
      'version' => 0,
      'link' => 0,
      'place' => 0,
      'poll' => 0,
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
        'title' => 'Associate External Links',
        'hover_title' => 'Associate External Links',
        'destination' => 'node',
      ),
      'fallback' => 'autocomplete',
      'edit_fallback' => 0,
      'label' => 'Related Content',
      'weight' => '-3',
      'description' => '',
      'type' => 'nodereference_url',
      'module' => 'nodereference_url',
    ),
  );

  // Exported field: field_related_links
  $fields['content_links-field_related_links'] = array(
    'field_name' => 'field_related_links',
    'type_name' => 'content_links',
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
    'type' => 'link',
    'required' => '1',
    'multiple' => '1',
    'module' => 'link',
    'active' => '1',
    'attributes' => array(
      'target' => '_blank',
      'rel' => 'nofollow',
      'class' => '',
      'title' => '',
    ),
    'display' => array(
      'url_cutoff' => '80',
    ),
    'url' => 0,
    'title' => 'required',
    'title_value' => '',
    'enable_tokens' => 0,
    'validate_url' => 1,
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'title' => '',
          'url' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Related Links',
      'weight' => '-4',
      'description' => '',
      'type' => 'link',
      'module' => 'link',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Related Content');
  t('Related Links');

  return $fields;
}