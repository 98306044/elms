<?php

/**
 * @todo
 * -
 * -
 * -
 */

!function_exists('profiler_v2') ? require_once('libraries/profiler/profiler.inc') : FALSE;
profiler_v2('elms');

/**
 * Implementation of hook_install().
 */
function elms_install() {
  //run the accessible content builder
  //include_once('modules/contrib/accessible_content/accessible_content.admin.inc');
  drupal_set_message(l(t('Click to install Accessibility Test'),'admin/settings/accessible_content/create_tests'));
  //accessible_content_admin_update_tests_form_submit();
  _elms_role_query();
  // Remove default input filter formats
  db_query("DELETE FROM {filters} WHERE fid <> 0");
  db_query("DELETE FROM {filter_formats} WHERE format <> 0");
  //delete book content type
  db_query("DELETE FROM {node_type} WHERE type='book'");
  //apply elms default filters
  _elms_filters_query();
  _elms_filter_formats_query();
  //apply defaults for better formats
  _elms_better_formats_defaults_query();
  //wysiwyg defaults
  _elms_wysiwyg_query();
  //add profile fields
  _elms_profile_fields_query();
  //contact form for the default helpdesk
  _elms_contact_query();
  _elms_contact_fields_query();
  //set default workflow states, in the future workflow states will be exportable via Features
  _elms_workflow_query();
  // Create user picture directory
  $picture_path = file_create_path(variable_get('user_picture_path', 'pictures'));
  file_check_directory($picture_path, 1, 'user_picture_path');
  
  //Rebuild key tables/caches
  drupal_flush_all_caches();
  //disable all DB blocks
  db_query("UPDATE {blocks} SET status = 0, region = ''");
  db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'garland');
  //set module weights accordingly
  
  // In Aegir install processes, we need to init strongarm manually as a
  // separate page load isn't available to do this for us.
  if (function_exists('strongarm_init')) {
    strongarm_init();
  }

  // Revert key components that are overridden by others on install.
  // Note that this comes after all other processes have run, as some cache
  // clears/rebuilds actually set variables or other settings that would count
  // as overrides. See `og_node_type()`.
  /*
  $revert = array(
    'elms_course' => array('user_role', 'user_permission', 'variable', 'filter'),
  );
  features_revert($revert);*/  
}

/**
 * Helper function to install roles with RID defaults.
 */
function _elms_profile_fields_query() {
  db_query("INSERT INTO {profile_fields} VALUES ('1', 'First Name', 'profile_first_name', '', 'Personal', '', 'textfield', '-10', '0', '0', '4', '0', ''), ('2', 'Last Name', 'profile_last_name', '', 'Personal', '', 'textfield', '-9', '0', '0', '4', '0', '')");
}

/**
 * Helper function to install roles with RID defaults.
 */
function _elms_role_query() {
  db_query("INSERT INTO {role} VALUES ('6', 'instructional designer'), ('4', 'instructor'), ('9', 'staff'), ('10', 'student'), ('8', 'teaching assistant');");	
}
/**
 * Helper function to install workflow states.
 */
function _elms_workflow_query() {
  $ary = array (
  'wid' => '1',
  'name' => 'Status',
  'tab_roles' => 'author,3,6',
  'options' => 
  serialize(array (
    'comment_log_node' => 1,
    'comment_log_tab' => 1,
    'name_as_title' => 1,
  )),
  );
  drupal_write_record('workflows', $ary);
  //insert the content type association
  db_query("INSERT INTO {workflow_type_map} VALUES ('accessibility_guideline', '0'), ('accessibility_test', '0'), ('blog', '0'), ('course', '0'), ('course_event', '0'), ('feed_reader', '0'), ('feed_user_import', '0'), ('folder', '0'), ('link', '0'), ('page', '0'), ('promo', '0'), ('reaction', '0'), ('studio_submission', '0'), ('version', '1')");
  //define the workflow states
  db_query("INSERT INTO {workflow_states} VALUES ('2', '1', '(creation)', '-50', '1', '1'), ('3', '1', 'Development Sandbox', '0', '0', '1'), ('4', '1', 'Inactive', '1', '0', '0'), ('5', '1', 'Active Offering', '2', '0', '1'), ('6', '1', 'Archived Offering', '3', '0', '1'), ('7', '1', 'Course Promo', '4', '0', '1'), ('8', '1', 'Master', '8', '0', '0'), ('9', '1', 'Staging', '0', '0', '0'), ('10', '1', 'Master Version', '1', '0', '1')");
  //define allowed workflow state transitions
  db_query("INSERT INTO {workflow_transitions} VALUES ('1', '2', '3', 'author,3,6'), ('3', '3', '7', 'author,3,6'), ('6', '5', '3', 'author,3,6'), ('8', '5', '6', 'author,3,6'), ('9', '7', '3', 'author,3,6'), ('14', '3', '5', 'author,3,6'), ('15', '6', '5', 'author,3,6'), ('17', '3', '10', 'author,3,6'), ('18', '10', '3', 'author,3,6'), ('19', '6', '3', 'author,3,6')");
}

/**
 * Helper function to install default contact form.
 */
function _elms_contact_query() {
  db_query("INSERT INTO {contact} VALUES ('1','Helpdesk', '%s', 'Thank you for contacting the e-Learning Institute Helpdesk.  We will contact you within 24 hours during normal business hours or 48 hours during off-peak times.', '0', '1')", variable_get('site_mail', ''));
}

/**
 * Helper function to install default contact fields.
 */
function _elms_contact_fields_query() {
  $ary = array (
  'field_name' => 'name',
  'field_type' => 'textfield',
  'settings' => 
  serialize(array (
    'title' => 'Your name',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '2',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'mail',
  'field_type' => 'textfield',
  'settings' => 
  serialize(array (
    'title' => 'Your e-mail address',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '3',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'subject',
  'field_type' => 'textfield',
  'settings' => 
  serialize(array (
    'title' => 'Subject',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '4',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'cid',
  'field_type' => 'value',
  'settings' => 
  serialize(array (
    'title' => NULL,
  )),
  'required' => '0',
  'enabled' => '1',
  'weight' => '7',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'message',
  'field_type' => 'textarea',
  'settings' => 
  serialize(array (
    'title' => 'Message',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '5',
  'core' => '1',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'field_issue_type',
  'field_type' => 'select',
  'settings' => 
  serialize(array (
    'multiple' => false,
    'title' => 'Type of Question',
    'prefix' => '',
    'suffix' => '',
    'num_value' => '0',
    'description' => 'Please classify your question to help us better understand the issue you are having.',
    'options' => 
    array (
      'general' => 'General
',
      'instructor' => 'For Instructor
',
      'technical' => 'Technical
',
    ),
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '0',
  'core' => '0',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'field_roles',
  'field_type' => 'textfield',
  'settings' => 
  serialize(array (
    'title' => 'Roles',
    'description' => '',
    'prefix' => '',
    'suffix' => '',
    'maxlength' => 255,
    'field_prefix' => '',
    'field_suffix' => '',
  )),
  'required' => '0',
  'enabled' => '1',
  'weight' => '1',
  'core' => '0',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
  $ary = array (
  'field_name' => 'field_tech_details',
  'field_type' => 'textarea',
  'settings' => 
  serialize(array (
    'description' => 'The following are technical support details that will also be sent to the helpdesk',
    'title' => 'Technical Details',
    'rows' => '14',
    'cols' => '',
  )),
  'required' => '1',
  'enabled' => '1',
  'weight' => '6',
  'core' => '0',
  'field_group' => '',
  );
  drupal_write_record('contact_fields', $ary);
}

/**
 * Helper function to install default wysiwyg settings.
 */
function _elms_wysiwyg_query() {
  $tmp_ary = array (
  'default' => 1,
  'user_choose' => 0,
  'show_toggle' => 0,
  'theme' => 'advanced',
  'language' => 'en',
  'buttons' => 
  array (
    'default' => 
    array (
      'Bold' => 1,
      'Italic' => 1,
      'Underline' => 1,
      'BulletedList' => 1,
      'NumberedList' => 1,
      'Link' => 1,
      'Scayt' => 1,
    ),
  ),
  'toolbar_loc' => 'top',
  'toolbar_align' => 'left',
  'path_loc' => 'none',
  'resizing' => 1,
  'verify_html' => 1,
  'preformatted' => 0,
  'convert_fonts_to_spans' => 1,
  'remove_linebreaks' => 0,
  'apply_source_formatting' => 0,
  'paste_auto_cleanup_on_paste' => 1,
  'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
  'css_setting' => 'none',
  'css_path' => '',
  'css_classes' => '',
);
$ary = array('format' => '1', 'editor' => 'ckeditor', 'settings' => serialize($tmp_ary));
drupal_write_record('wysiwyg', $ary);

$tmp_ary = array (
  'default' => 1,
  'user_choose' => 0,
  'show_toggle' => 1,
  'theme' => 'advanced',
  'language' => 'en',
  'buttons' => 
  array (
    'default' => 
    array (
      'Bold' => 1,
      'Italic' => 1,
      'Underline' => 1,
      'JustifyLeft' => 1,
      'JustifyCenter' => 1,
      'JustifyRight' => 1,
      'BulletedList' => 1,
      'NumberedList' => 1,
      'Outdent' => 1,
      'Indent' => 1,
      'Link' => 1,
      'Image' => 1,
      'Superscript' => 1,
      'Subscript' => 1,
      'RemoveFormat' => 1,
      'FontSize' => 1,
      'Styles' => 1,
      'Table' => 1,
      'Scayt' => 1,
    ),
    'elimedia' => 
    array (
      'elimedia' => 1,
    ),
    'imce' => 
    array (
      'imce' => 1,
    ),
    'drupal_path' => 
    array (
      'Link' => 1,
    ),
  ),
  'toolbar_loc' => 'top',
  'toolbar_align' => 'left',
  'path_loc' => 'bottom',
  'resizing' => 1,
  'verify_html' => 0,
  'preformatted' => 0,
  'convert_fonts_to_spans' => 1,
  'remove_linebreaks' => 0,
  'apply_source_formatting' => 0,
  'paste_auto_cleanup_on_paste' => 1,
  'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
  'css_setting' => 'none',
  'css_path' => '',
  'css_classes' => '',
);
$ary = array('format' => '2', 'editor' => 'ckeditor', 'settings' => serialize($tmp_ary));
drupal_write_record('wysiwyg', $ary);

$tmp_ary = array (
  'default' => 1,
  'user_choose' => 0,
  'show_toggle' => 0,
  'theme' => 'advanced',
  'language' => 'en',
  'buttons' => 
  array (
    'default' => 
    array (
      'Bold' => 1,
      'Italic' => 1,
      'BulletedList' => 1,
      'NumberedList' => 1,
    ),
  ),
  'toolbar_loc' => 'top',
  'toolbar_align' => 'left',
  'path_loc' => 'bottom',
  'resizing' => 1,
  'verify_html' => 1,
  'preformatted' => 0,
  'convert_fonts_to_spans' => 1,
  'remove_linebreaks' => 1,
  'apply_source_formatting' => 0,
  'paste_auto_cleanup_on_paste' => 1,
  'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
  'css_setting' => 'none',
  'css_path' => '',
  'css_classes' => '',
);
$ary = array('format' => '4', 'editor' => 'ckeditor', 'settings' => serialize($tmp_ary));
drupal_write_record('wysiwyg', $ary);
}

/**
 * Helper function to install default filter formats.
 */
function _elms_filter_formats_query() {
  db_query("INSERT INTO {filter_formats} VALUES ('1', 'Comment Filter', ',1,2,3,6,4,9,10,8,', '1'), ('2', 'Content Filter', ',3,6,4,', '1'), ('4', 'Course Event', ',6,4,', '1')");
}

/**
 * Helper function to set the defaults defined by better formats module.
 */
function _elms_better_formats_defaults_query() {
  db_query("INSERT INTO {better_formats_defaults} VALUES ('1', 'block', '0', '1', '25'), ('1', 'comment', '1', '1', '0'), ('1', 'comment/accessibility_guideline', '1', '2', '0'), ('1', 'comment/accessibility_test', '1', '2', '0'), ('1', 'comment/blog', '1', '2', '0'), ('1', 'comment/course', '0', '2', '0'), ('1', 'comment/course_event', '0', '2', '0'), ('1', 'comment/feed_reader', '1', '2', '0'), ('1', 'comment/feed_user_import', '1', '2', '0'), ('1', 'comment/folder', '1', '2', '0'), ('1', 'comment/link', '1', '2', '0'), ('1', 'comment/offering', '0', '2', '0'), ('1', 'comment/page', '0', '2', '0'), ('1', 'comment/promo', '0', '2', '0'), ('1', 'comment/reaction', '1', '2', '0'), ('1', 'comment/studio_submission', '1', '2', '0'), ('1', 'comment/version', '0', '2', '0'), ('1', 'node', '0', '1', '0'), ('1', 'node/accessibility_guideline', '0', '2', '0'), ('1', 'node/accessibility_test', '0', '2', '0'), ('1', 'node/blog', '0', '2', '0'), ('1', 'node/course', '0', '2', '0'), ('1', 'node/course_event', '0', '2', '0'), ('1', 'node/feed_reader', '0', '2', '0'), ('1', 'node/feed_user_import', '0', '2', '0'), ('1', 'node/folder', '0', '2', '0'), ('1', 'node/link', '0', '2', '0'), ('1', 'node/offering', '0', '2', '0'), ('1', 'node/page', '0', '2', '0'), ('1', 'node/promo', '0', '2', '0'), ('1', 'node/reaction', '0', '2', '0'), ('1', 'node/studio_submission', '0', '2', '0'), ('1', 'node/version', '0', '2', '0'), ('2', 'block', '0', '1', '25'), ('2', 'comment', '1', '1', '0'), ('2', 'comment/accessibility_guideline', '1', '2', '0'), ('2', 'comment/accessibility_test', '1', '2', '0'), ('2', 'comment/blog', '1', '2', '0'), ('2', 'comment/course', '0', '2', '0'), ('2', 'comment/course_event', '0', '2', '0'), ('2', 'comment/feed_reader', '1', '2', '0'), ('2', 'comment/feed_user_import', '1', '2', '0'), ('2', 'comment/folder', '1', '2', '0'), ('2', 'comment/link', '1', '2', '0'), ('2', 'comment/offering', '0', '2', '0'), ('2', 'comment/page', '0', '2', '0'), ('2', 'comment/promo', '0', '2', '0'), ('2', 'comment/reaction', '1', '2', '0'), ('2', 'comment/studio_submission', '1', '2', '0'), ('2', 'comment/version', '0', '2', '0'), ('2', 'node', '0', '1', '0'), ('2', 'node/accessibility_guideline', '0', '2', '0'), ('2', 'node/accessibility_test', '0', '2', '0'), ('2', 'node/blog', '0', '2', '0'), ('2', 'node/course', '0', '2', '0'), ('2', 'node/course_event', '0', '2', '0'), ('2', 'node/feed_reader', '0', '2', '0'), ('2', 'node/feed_user_import', '0', '2', '0'), ('2', 'node/folder', '0', '2', '0'), ('2', 'node/link', '0', '2', '0'), ('2', 'node/offering', '0', '2', '0'), ('2', 'node/page', '0', '2', '0'), ('2', 'node/promo', '0', '2', '0'), ('2', 'node/reaction', '0', '2', '0'), ('2', 'node/studio_submission', '0', '2', '0'), ('2', 'node/version', '0', '2', '0'), ('3', 'block', '2', '1', '25'), ('3', 'comment', '1', '1', '0'), ('3', 'comment/accessibility_guideline', '1', '2', '0'), ('3', 'comment/accessibility_test', '1', '2', '0'), ('3', 'comment/blog', '1', '2', '0'), ('3', 'comment/course', '0', '2', '0'), ('3', 'comment/course_event', '0', '2', '0'), ('3', 'comment/feed_reader', '1', '2', '0'), ('3', 'comment/feed_user_import', '1', '2', '0'), ('3', 'comment/folder', '1', '2', '0'), ('3', 'comment/link', '1', '2', '0'), ('3', 'comment/offering', '0', '2', '0'), ('3', 'comment/page', '0', '2', '0'), ('3', 'comment/promo', '0', '2', '0'), ('3', 'comment/reaction', '1', '2', '0'), ('3', 'comment/studio_submission', '1', '2', '0'), ('3', 'comment/version', '0', '2', '0'), ('3', 'node', '2', '1', '0'), ('3', 'node/accessibility_guideline', '2', '2', '0'), ('3', 'node/accessibility_test', '2', '2', '0'), ('3', 'node/blog', '2', '2', '0'), ('3', 'node/course', '2', '2', '0'), ('3', 'node/course_event', '0', '2', '0'), ('3', 'node/feed_reader', '2', '2', '0'), ('3', 'node/feed_user_import', '2', '2', '0'), ('3', 'node/folder', '2', '2', '0'), ('3', 'node/link', '0', '2', '0'), ('3', 'node/offering', '2', '2', '0'), ('3', 'node/page', '2', '2', '0'), ('3', 'node/promo', '2', '2', '0'), ('3', 'node/reaction', '0', '2', '0'), ('3', 'node/studio_submission', '2', '2', '0'), ('3', 'node/version', '2', '2', '0'), ('4', 'block', '2', '1', '25'), ('4', 'comment', '1', '1', '25'), ('4', 'comment/accessibility_guideline', '1', '2', '25'), ('4', 'comment/accessibility_test', '1', '2', '25'), ('4', 'comment/blog', '1', '2', '25'), ('4', 'comment/course', '0', '2', '25'), ('4', 'comment/course_event', '0', '2', '25'), ('4', 'comment/feed_reader', '1', '2', '25'), ('4', 'comment/feed_user_import', '1', '2', '25'), ('4', 'comment/folder', '1', '2', '25'), ('4', 'comment/link', '1', '2', '25'), ('4', 'comment/offering', '0', '2', '25'), ('4', 'comment/page', '0', '2', '25'), ('4', 'comment/promo', '0', '2', '25'), ('4', 'comment/reaction', '1', '2', '25'), ('4', 'comment/studio_submission', '1', '2', '25'), ('4', 'comment/version', '0', '2', '25'), ('4', 'node', '2', '1', '25'), ('4', 'node/accessibility_guideline', '2', '2', '25'), ('4', 'node/accessibility_test', '2', '2', '25'), ('4', 'node/blog', '2', '2', '25'), ('4', 'node/course', '2', '2', '25'), ('4', 'node/course_event', '0', '2', '25'), ('4', 'node/feed_reader', '2', '2', '25'), ('4', 'node/feed_user_import', '2', '2', '25'), ('4', 'node/folder', '2', '2', '25'), ('4', 'node/link', '0', '2', '25'), ('4', 'node/offering', '2', '2', '25'), ('4', 'node/page', '2', '2', '25'), ('4', 'node/promo', '2', '2', '25'), ('4', 'node/reaction', '0', '2', '25'), ('4', 'node/studio_submission', '2', '2', '25'), ('4', 'node/version', '2', '2', '25'), ('6', 'block', '2', '1', '25'), ('6', 'comment', '1', '1', '25'), ('6', 'comment/accessibility_guideline', '1', '2', '25'), ('6', 'comment/accessibility_test', '1', '2', '25'), ('6', 'comment/blog', '1', '2', '25'), ('6', 'comment/course', '0', '2', '25'), ('6', 'comment/course_event', '0', '2', '25'), ('6', 'comment/feed_reader', '1', '2', '25'), ('6', 'comment/feed_user_import', '1', '2', '25'), ('6', 'comment/folder', '1', '2', '25'), ('6', 'comment/link', '1', '2', '25'), ('6', 'comment/offering', '0', '2', '25'), ('6', 'comment/page', '0', '2', '25'), ('6', 'comment/promo', '0', '2', '25'), ('6', 'comment/reaction', '1', '2', '25'), ('6', 'comment/studio_submission', '1', '2', '25'), ('6', 'comment/version', '0', '2', '25'), ('6', 'node', '2', '1', '25'), ('6', 'node/accessibility_guideline', '2', '2', '25'), ('6', 'node/accessibility_test', '2', '2', '25'), ('6', 'node/blog', '2', '2', '25'), ('6', 'node/course', '2', '2', '25'), ('6', 'node/course_event', '0', '2', '25'), ('6', 'node/feed_reader', '2', '2', '25'), ('6', 'node/feed_user_import', '2', '2', '25'), ('6', 'node/folder', '2', '2', '25'), ('6', 'node/link', '0', '2', '25'), ('6', 'node/offering', '2', '2', '25'), ('6', 'node/page', '2', '2', '25'), ('6', 'node/promo', '2', '2', '25'), ('6', 'node/reaction', '0', '2', '25'), ('6', 'node/studio_submission', '2', '2', '25'), ('6', 'node/version', '2', '2', '25'), ('7', 'block', '0', '1', '25'), ('7', 'comment', '1', '1', '25'), ('7', 'node', '0', '1', '25'), ('8', 'block', '0', '1', '25'), ('8', 'comment', '0', '1', '25'), ('8', 'comment/accessibility_guideline', '0', '2', '25'), ('8', 'comment/accessibility_test', '0', '2', '25'), ('8', 'comment/blog', '0', '2', '25'), ('8', 'comment/course', '0', '2', '25'), ('8', 'comment/course_event', '0', '2', '25'), ('8', 'comment/feed_reader', '0', '2', '25'), ('8', 'comment/feed_user_import', '0', '2', '25'), ('8', 'comment/folder', '0', '2', '25'), ('8', 'comment/link', '0', '2', '25'), ('8', 'comment/offering', '0', '2', '25'), ('8', 'comment/page', '0', '2', '25'), ('8', 'comment/promo', '0', '2', '25'), ('8', 'comment/reaction', '0', '2', '25'), ('8', 'comment/studio_submission', '0', '2', '25'), ('8', 'comment/version', '0', '2', '25'), ('8', 'node', '0', '1', '25'), ('8', 'node/accessibility_guideline', '0', '2', '25'), ('8', 'node/accessibility_test', '0', '2', '25'), ('8', 'node/blog', '0', '2', '25'), ('8', 'node/course', '0', '2', '25'), ('8', 'node/course_event', '0', '2', '25'), ('8', 'node/feed_reader', '0', '2', '25'), ('8', 'node/feed_user_import', '0', '2', '25'), ('8', 'node/folder', '0', '2', '25'), ('8', 'node/link', '0', '2', '25'), ('8', 'node/offering', '0', '2', '25'), ('8', 'node/page', '0', '2', '25'), ('8', 'node/promo', '0', '2', '25'), ('8', 'node/reaction', '0', '2', '25'), ('8', 'node/studio_submission', '0', '2', '25'), ('8', 'node/version', '0', '2', '25'), ('10', 'block', '0', '1', '25'), ('10', 'comment', '0', '1', '25'), ('10', 'comment/accessibility_guideline', '0', '2', '25'), ('10', 'comment/accessibility_test', '0', '2', '25'), ('10', 'comment/blog', '0', '2', '25'), ('10', 'comment/course', '0', '2', '25'), ('10', 'comment/course_event', '0', '2', '25'), ('10', 'comment/feed_reader', '0', '2', '25'), ('10', 'comment/feed_user_import', '0', '2', '25'), ('10', 'comment/folder', '0', '2', '25'), ('10', 'comment/link', '0', '2', '25'), ('10', 'comment/offering', '0', '2', '25'), ('10', 'comment/page', '0', '2', '25'), ('10', 'comment/promo', '0', '2', '25'), ('10', 'comment/reaction', '0', '2', '25'), ('10', 'comment/studio_submission', '0', '2', '25'), ('10', 'comment/version', '0', '2', '25'), ('10', 'node', '0', '1', '25'), ('10', 'node/accessibility_guideline', '0', '2', '25'), ('10', 'node/accessibility_test', '0', '2', '25'), ('10', 'node/blog', '0', '2', '25'), ('10', 'node/course', '0', '2', '25'), ('10', 'node/course_event', '0', '2', '25'), ('10', 'node/feed_reader', '0', '2', '25'), ('10', 'node/feed_user_import', '0', '2', '25'), ('10', 'node/folder', '0', '2', '25'), ('10', 'node/link', '0', '2', '25'), ('10', 'node/offering', '0', '2', '25'), ('10', 'node/page', '0', '2', '25'), ('10', 'node/promo', '0', '2', '25'), ('10', 'node/reaction', '0', '2', '25'), ('10', 'node/studio_submission', '0', '2', '25'), ('10', 'node/version', '0', '2', '25')");	
}

/**
 * Helper function to install default filters.
 */
function _elms_filters_query() {
  db_query("INSERT INTO {filters} VALUES ('40', '1', 'filter', '2', '0'), ('37', '1', 'filter', '0', '1'), ('38', '1', 'filter', '1', '2'), ('36', '1', 'filter', '3', '10'), ('39', '1', 'pathologic', '0', '10'), ('67', '2', 'wysiwyg_filter', '0', '-10'), ('62', '2', 'ckeditor_link', '0', '-9'), ('64', '2', 'lightbox2', '0', '-8'), ('63', '2', 'filter', '3', '-7'), ('66', '2', 'filter', '2', '-6'), ('65', '2', 'filter', '1', '-5'), ('45', '4', 'filter', '2', '0'), ('42', '4', 'filter', '0', '1'), ('43', '4', 'filter', '1', '2'), ('41', '4', 'filter', '3', '10'), ('44', '4', 'pathologic', '0', '10'), ('69', '6', 'filter', '1', '2')");
}