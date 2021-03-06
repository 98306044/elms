<?php
// $Id: views-view-fields.tpl.php,v 1.6 2008/09/24 22:48:21 merlinofchaos Exp $
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
 $has_end = false;
foreach ($fields as $id => $field) {
  $style = '';
  switch ($id) {
    case 'field_color_value':
      $color = strtolower($field->content);
      if ($color != '#ffffff' && $color != '') {
        $style = 'style="background-color:'. $color .';"';
      }
    break;
    case 'field_event_name_value':
      $title = $field->content;
    break;
    case 'field_task_link_url':
      $url = $field->content;
    break;
    case 'field_score_value_value':
      $points = $field->content .' '. _elms_schedule_score_format();
    break;
    case 'nid':
      $nid = $field->content;
      $tmpnid = $field->content;
    break;
    case 'nid_1':
      $ref_nid = $field->content;
    break;
    case 'field_due_date_value':
      $date = $field->content;
    break;
    case 'field_due_time_value':
      $time = $field->content;
    break;
    case 'field_date_mod_text_value':
      $mod_text = $field->content;
    break;
    case 'field_end_date_value':
      $date.= '<span class="schedule_spacer">-</span>' . $field->content;
      $has_end = true;
    break;
    case 'field_detail_text_value':
      $details = $field->content;
    break;
    case 'ops':
      $flag = $field->content;
    break;
    case 'field_event_type_value':
      $event_type = $field->content;
      //nothing's set so just display the field to change the icon
      if ($event_type == '') {
        $event_type.= '<img width="24px" height="24px" class="schedule_event_type" src="'. base_path() . drupal_get_path('module','elms_schedule') .'/images/types/blank.png" alt="blank" title="blank"/>';
        $event_icon = '';
      }
      else {
        $event_icon = strtolower($event_type);
        $event_type= '<img width="24px" height="24px" class="schedule_event_type" src="'. base_path() . drupal_get_path('module','elms_schedule') .'/images/types/'. $event_icon .'.png" alt="'. $event_type .'" title="'. $event_type .'"/>';
      }
    break;
  }
}
$depth = -1;
//calculate depth
while (isset($tmpnid) && $tmpnid != 0) {
    $last_nid = $tmpnid;
    $tmpnid = db_result(db_query("SELECT value FROM {draggableviews_structure} WHERE delta=1 AND view_name='elms_schedule' AND nid=%d", $last_nid));
    $depth++;
}
//make it a link if we have to but ref node takes priority over an external link
if (isset($ref_nid) && $ref_nid != '') {
  $title = l($title, 'node/'. $ref_nid, array('html' => true, 'attributes' => array('alt' => $title, 'title' => $title)));
}
elseif (isset($url) && $url != '') {
  $title = l($title, $url, array('html' => true, 'attributes' => array('alt' => $title,'title' => $title)));
}

//alter date if needed for due-dates
if (!$has_end) {
  if (isset($mod_text) && $mod_text != '') {
    $date = $mod_text .' '. $date;
  }
  if (isset($time) && $time != '') {
    $date = $date .' at '. $time; 
  }
}
?>
<?php if (isset($points)): ?>
  <div class="schedule_points"><?php print $points; ?></div>
<?php endif; ?>
<div class="schedule_task_wrapper">
  <?php print $event_type; ?>
  <div class="schedule_task event_type_<?php print $event_icon;?> schedule_depth_<?php print $depth;?> schedule_check_<?php print $nid; ?>_row" <?php print $style; ?>>
    <div class="schedule_checkbox_wrapper">
      <div class="schedule_flag"><?php print $flag; ?></div>
      <input class="schedule_checkbox" type="checkbox" id="schedule_check_<?php print $nid; ?>"/>
    </div>
    <div class="schedule_content_wrapper">
    <h<?php print ($depth+2); ?> class="schedule_title"><?php print $title; ?>
    <?php print '</h'. ($depth+2) .'>'; ?>
    <?php if (isset($details)): ?>
    <div class="schedule_details"><?php print $details; ?></div>
    <?php endif; ?>
    </div>
    <?php if (isset($date)): ?>
      <div class="schedule_due_date"><?php print $date; ?></div>
      <?php endif; ?>
  </div>
</div>