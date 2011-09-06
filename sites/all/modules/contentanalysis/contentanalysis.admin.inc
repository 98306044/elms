<?php
// $Id: contentanalysis.admin.inc,v 1.1.2.4 2010/06/01 21:23:39 tomdude48 Exp $
/**
 * @file * Admin include file. 
*/

/** 
 * Displays the form for the standard settings tab.
 * 
 * @return array 
 * A structured array for use with Forms API. 
*/ 
 function contentanalysis_admin_settings() {
  $params = array(
    'title' => t('Default analyzers'),
    'description' => t('Select the analyzers you want enabled by default.'),
  );
  $form['contentanalysis_default_analyzers'] = contentanalysis_get_analyzer_form_element($params);

  $form['contentanalysis_analyzerchecklist'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable analyzer checklist report'),
    '#default_value' => variable_get('contentanalysis_analyzerchecklist', 1)  
  ); 
  
  $form['contentanalysis_node_edit_form_collapsed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collapse the content analysis fieldset on the node edit form'),
    '#default_value' => variable_get('contentanalysis_node_edit_form_collapsed', 0)  
  );  

  $options = array(    
    'both' => t('Display both dialog and inline reports.'),
    'dialog' => t('Display dialog report only.'),
    'inline' => t('Display inline reports only.'),
    'multibutton' => t('Provide buttons to enable the user to select report options.'),
  );
  
  $form['contentanalysis_node_report_display'] = array(    
    '#type' => 'radios',    
    '#title' => t('Node edit report style'), 
    '#options' => $options,
    '#default_value' => variable_get('contentanalysis_node_report_display', 'both'),     
    '#description' => t('Select the style of report you would like when launching from the node edit form. Dialog is the standard modal report. Inline inserts recommendations directly into the node edit form.')     
  );     
  
  $form['contentanalysis_node_parse_options'] = array(      
    '#type' => 'fieldset',      
    '#title' => t('Node parsing options'),      
    '#collapsible' => TRUE,      
    '#collapsed' => TRUE,    
  );   
  $form['contentanalysis_node_parse_options']['contentanalysis_node_parse_nodetitle_prepend'] = array(    
    '#type' => 'checkbox',    
    '#title' => t('Prepend node title to body'),    
    '#default_value' => variable_get('contentanalysis_node_parse_nodetitle_prepend', 1),     
    '#description' => t('Most Drupal sites format node views by putting the node title as a page header above the node body. If your site is formatted this way, check this box. If node titles are not used as headers, uncheck the option.')     
  );   
  $form['contentanalysis_node_parse_options']['contentanalysis_node_parse_nodetitle_tags'] = array(    
    '#type' => 'textfield',    
    '#title' => t('Node title tags'),    
    '#default_value' => variable_get('contentanalysis_node_parse_nodetitle_tags', '<h2>[node_title]</h2>'),     
    '#description' => t('If your node title is included on node views, include any formating tags it is enclosed within. Default is &lt;h2&gt;[node_title]&lt;/h2&gt;')     
  );  
  
  $form['contentanalysis_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => $a . t('Advanced'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );  
  $form['contentanalysis_advanced']['contentanalysis_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Host'), 
    '#description' => t('Use this field to enter an alternative url for the content analysis api ajax calls.'),
    '#default_value' => variable_get('contentanalysis_host', ''), 
  );
  
  /*
  $form['contentanalysis_display'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Analysis box display options',
    '#description' => t('Controls where the analysis messages display on node edit forms.'),
    '#options' => array(
      'sections' => t('On each content section'),
      'main' => t('On content optmizer fieldset'),
    ),
    '#default_value' => variable_get('contentanalysis_display',array('sections','main')),
  );

  $form['contentanalysis_analyze_on_start'] = array(
    '#type' => 'checkbox',
    '#title' => 'Auto-analyze on edit',
    '#description' => t('Turns on if you want content to be automatically analyzed when node is edited.'),
    '#default_value' => variable_get('contentanalysis_analyze_on_start','0'),
  );

  if(module_exists('setags')) {
    $form['contentanalysis_include_setags'] = array(
    '#type' => 'checkbox',
    '#title' => 'Include search engine tags.',
    '#description' => t('Will add tags from the search engine tags module on analysis.'),
    '#default_value' => variable_get('contentanalysis_include_setags','0'),
   );
  }
*/  
  //Add the system buttons to the form
  $form = system_settings_form($form);  

  
  //Overide the theme function back to our own one
  return $form;
}