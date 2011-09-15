<?php

/**
 * Implementation of hook_content_default_fields().
 */
function elms_promo_content_default_fields() {
  $fields = array();

  // Exported field: field_redirect
  $fields['promo-field_redirect'] = array(
    'field_name' => 'field_redirect',
    'type_name' => 'promo',
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
    'type' => 'cck_redirection',
    'required' => '0',
    'multiple' => '0',
    'module' => 'cck_redirection',
    'active' => '1',
    'widget' => array(
      'redirect_type' => '0',
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Redirect',
      'weight' => '-1',
      'description' => '',
      'type' => 'cck_redirection',
      'module' => 'cck_redirection',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Redirect');

  return $fields;
}
