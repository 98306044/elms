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
  // Remove default input filter formats
  db_query("DELETE FROM {filters} WHERE format = *");
  //apply elms default filters
  _elms_filters_query();
  _elms_filter_formats_query();
  //apply defaults for better formats
  _elms_better_formats_defaults_query();
  //wysiwyg defaults
  _elms_wysiwyg_query();
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
 * Helper function to install workflow states.
 */
function _elms_workflow_query() {
  db_query("INSERT INTO {workflows} VALUES ('1', 'Status', 'author,3,6', 'a:3:{s:16:\"comment_log_node\";i:1;s:15:\"comment_log_tab\";i:1;s:13:\"name_as_title\";i:1;}')");
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
  db_query("INSERT INTO {contact} VALUES ('Helpdesk', '%s', 'Thank you for contacting the e-Learning Institute Helpdesk.  We will contact you within 24 hours during normal business hours or 48 hours during off-peak times.', '0', '1')", variable_get('site_mail', ''));
}

/**
 * Helper function to install default contact fields.
 */
function _elms_contact_fields_query() {
  db_query("INSERT INTO {contact_fields} VALUES ('name', 'textfield', 'a:1:{s:5:\"title\";s:9:\"Your name\";}', '1', '1', '2', '1', ''), ('mail', 'textfield', 'a:1:{s:5:\"title\";s:19:\"Your e-mail address\";}', '1', '1', '3', '1', ''), ('subject', 'textfield', 'a:1:{s:5:\"title\";s:7:\"Subject\";}', '1', '1', '4', '1', ''), ('cid', 'value', 'a:1:{s:5:\"title\";N;}', '0', '1', '7', '1', ''), ('message', 'textarea', 'a:1:{s:5:\"title\";s:7:\"Message\";}', '1', '1', '5', '1', ''), ('field_issue_type', 'select', 'a:7:{s:8:\"multiple\";b:0;s:5:\"title\";s:16:\"Type of Question\";s:6:\"prefix\";s:0:\"\";s:6:\"suffix\";s:0:\"\";s:9:\"num_value\";s:1:\"0\";s:11:\"description\";s:84:\"Please classify your question to help us better understand the issue you are having.\";s:7:\"options\";a:4:{s:7:\"general\";s:8:\"General\r\";s:10:\"instructor\";s:15:\"For Instructor\r\";s:9:\"technical\";s:10:\"Technical\r\";s:5:\"angel\";s:5:\"ANGEL\";}}', '1', '1', '0', '0', ''), ('field_roles', 'textfield', 'a:7:{s:5:\"title\";s:5:\"Roles\";s:11:\"description\";s:0:\"\";s:6:\"prefix\";s:0:\"\";s:6:\"suffix\";s:0:\"\";s:9:\"maxlength\";i:255;s:12:\"field_prefix\";s:0:\"\";s:12:\"field_suffix\";s:0:\"\";}', '0', '1', '1', '0', ''), ('field_tech_details', 'textarea', 'a:4:{s:11:\"description\";s:82:\"The following are technical support details that will also be sent to the helpdesk\";s:5:\"title\";s:17:\"Technical Details\";s:4:\"rows\";s:2:\"14\";s:4:\"cols\";s:0:\"\";}', '1', '1', '6', '0', '')");
}

/**
 * Helper function to install default wysiwyg settings.
 */
function _elms_wysiwyg_query() {
  db_query("INSERT INTO {wysiwyg} VALUES ('1', 'ckeditor', 'a:20:{s:7:\"default\";i:1;s:11:\"user_choose\";i:0;s:11:\"show_toggle\";i:0;s:5:\"theme\";s:8:\"advanced\";s:8:\"language\";s:2:\"en\";s:7:\"buttons\";a:1:{s:7:\"default\";a:7:{s:4:\"Bold\";i:1;s:6:\"Italic\";i:1;s:9:\"Underline\";i:1;s:12:\"BulletedList\";i:1;s:12:\"NumberedList\";i:1;s:4:\"Link\";i:1;s:5:\"Scayt\";i:1;}}s:11:\"toolbar_loc\";s:3:\"top\";s:13:\"toolbar_align\";s:4:\"left\";s:8:\"path_loc\";s:4:\"none\";s:8:\"resizing\";i:1;s:11:\"verify_html\";i:1;s:12:\"preformatted\";i:0;s:22:\"convert_fonts_to_spans\";i:1;s:17:\"remove_linebreaks\";i:0;s:23:\"apply_source_formatting\";i:0;s:27:\"paste_auto_cleanup_on_paste\";i:1;s:13:\"block_formats\";s:32:\"p,address,pre,h2,h3,h4,h5,h6,div\";s:11:\"css_setting\";s:4:\"none\";s:8:\"css_path\";s:0:\"\";s:11:\"css_classes\";s:0:\"\";}'), ('2', 'ckeditor', 'a:20:{s:7:\"default\";i:1;s:11:\"user_choose\";i:0;s:11:\"show_toggle\";i:1;s:5:\"theme\";s:8:\"advanced\";s:8:\"language\";s:2:\"en\";s:7:\"buttons\";a:4:{s:7:\"default\";a:19:{s:4:\"Bold\";i:1;s:6:\"Italic\";i:1;s:9:\"Underline\";i:1;s:11:\"JustifyLeft\";i:1;s:13:\"JustifyCenter\";i:1;s:12:\"JustifyRight\";i:1;s:12:\"BulletedList\";i:1;s:12:\"NumberedList\";i:1;s:7:\"Outdent\";i:1;s:6:\"Indent\";i:1;s:4:\"Link\";i:1;s:5:\"Image\";i:1;s:11:\"Superscript\";i:1;s:9:\"Subscript\";i:1;s:12:\"RemoveFormat\";i:1;s:8:\"FontSize\";i:1;s:6:\"Styles\";i:1;s:5:\"Table\";i:1;s:5:\"Scayt\";i:1;}s:8:\"elimedia\";a:1:{s:8:\"elimedia\";i:1;}s:4:\"imce\";a:1:{s:4:\"imce\";i:1;}s:11:\"drupal_path\";a:1:{s:4:\"Link\";i:1;}}s:11:\"toolbar_loc\";s:3:\"top\";s:13:\"toolbar_align\";s:4:\"left\";s:8:\"path_loc\";s:6:\"bottom\";s:8:\"resizing\";i:1;s:11:\"verify_html\";i:0;s:12:\"preformatted\";i:0;s:22:\"convert_fonts_to_spans\";i:1;s:17:\"remove_linebreaks\";i:0;s:23:\"apply_source_formatting\";i:0;s:27:\"paste_auto_cleanup_on_paste\";i:1;s:13:\"block_formats\";s:32:\"p,address,pre,h2,h3,h4,h5,h6,div\";s:11:\"css_setting\";s:4:\"none\";s:8:\"css_path\";s:0:\"\";s:11:\"css_classes\";s:0:\"\";}'), ('4', 'ckeditor', 'a:20:{s:7:\"default\";i:1;s:11:\"user_choose\";i:0;s:11:\"show_toggle\";i:0;s:5:\"theme\";s:8:\"advanced\";s:8:\"language\";s:2:\"en\";s:7:\"buttons\";a:1:{s:7:\"default\";a:4:{s:4:\"Bold\";i:1;s:6:\"Italic\";i:1;s:12:\"BulletedList\";i:1;s:12:\"NumberedList\";i:1;}}s:11:\"toolbar_loc\";s:3:\"top\";s:13:\"toolbar_align\";s:4:\"left\";s:8:\"path_loc\";s:6:\"bottom\";s:8:\"resizing\";i:1;s:11:\"verify_html\";i:1;s:12:\"preformatted\";i:0;s:22:\"convert_fonts_to_spans\";i:1;s:17:\"remove_linebreaks\";i:1;s:23:\"apply_source_formatting\";i:0;s:27:\"paste_auto_cleanup_on_paste\";i:1;s:13:\"block_formats\";s:32:\"p,address,pre,h2,h3,h4,h5,h6,div\";s:11:\"css_setting\";s:4:\"none\";s:8:\"css_path\";s:0:\"\";s:11:\"css_classes\";s:0:\"\";}'), ('5', '', null), ('6', 'codemirror', 'a:20:{s:7:\"default\";i:1;s:11:\"user_choose\";i:0;s:11:\"show_toggle\";i:1;s:5:\"theme\";s:8:\"advanced\";s:8:\"language\";s:2:\"en\";s:7:\"buttons\";a:1:{s:7:\"default\";a:5:{s:11:\"lineNumbers\";i:1;s:13:\"matchBrackets\";i:1;s:13:\"electricChars\";i:1;s:14:\"indentWithTabs\";i:1;s:6:\"gutter\";i:1;}}s:11:\"toolbar_loc\";s:3:\"top\";s:13:\"toolbar_align\";s:4:\"left\";s:8:\"path_loc\";s:6:\"bottom\";s:8:\"resizing\";i:1;s:11:\"verify_html\";i:0;s:12:\"preformatted\";i:0;s:22:\"convert_fonts_to_spans\";i:1;s:17:\"remove_linebreaks\";i:0;s:23:\"apply_source_formatting\";i:0;s:27:\"paste_auto_cleanup_on_paste\";i:1;s:13:\"block_formats\";s:32:\"p,address,pre,h2,h3,h4,h5,h6,div\";s:11:\"css_setting\";s:4:\"none\";s:8:\"css_path\";s:0:\"\";s:11:\"css_classes\";s:0:\"\";}'), ('7', 'ckeditor', 'a:20:{s:7:\"default\";i:1;s:11:\"user_choose\";i:0;s:11:\"show_toggle\";i:1;s:5:\"theme\";s:8:\"advanced\";s:8:\"language\";s:2:\"en\";s:7:\"buttons\";a:2:{s:7:\"default\";a:5:{s:4:\"Bold\";i:1;s:6:\"Italic\";i:1;s:9:\"Underline\";i:1;s:4:\"Link\";i:1;s:11:\"SpecialChar\";i:1;}s:11:\"drupal_path\";a:1:{s:4:\"Link\";i:1;}}s:11:\"toolbar_loc\";s:3:\"top\";s:13:\"toolbar_align\";s:4:\"left\";s:8:\"path_loc\";s:6:\"bottom\";s:8:\"resizing\";i:1;s:11:\"verify_html\";i:1;s:12:\"preformatted\";i:0;s:22:\"convert_fonts_to_spans\";i:1;s:17:\"remove_linebreaks\";i:1;s:23:\"apply_source_formatting\";i:0;s:27:\"paste_auto_cleanup_on_paste\";i:0;s:13:\"block_formats\";s:0:\"\";s:11:\"css_setting\";s:4:\"none\";s:8:\"css_path\";s:0:\"\";s:11:\"css_classes\";s:0:\"\";}')");
}

/**
 * Helper function to install default filter formats.
 */
function _elms_filter_formats_query() {
  db_query("INSERT INTO {filter_formats} VALUES ('1', 'Comment Filter', ',1,2,3,6,4,9,10,8,', '1'), ('2', 'Content Filter', ',3,6,4,', '1'), ('4', 'Course Event', ',6,4,', '1'), ('6', 'promopages', ',3,', '1')");
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