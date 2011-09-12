<?php 
// helper function for group theme settings
function _elms_spaces_theme_form($form_state, $feature = NULL) {
  //create directories just in-case of first load
  $dir = file_create_path(file_directory_path() .'/theme_logos');
  file_check_directory($dir,  1);
  $dir = file_create_path(file_directory_path() .'/theme_favicons');
  file_check_directory($dir,  1);
  $group = og_get_group_context();
  // Merge the saved variables and their default values
  $settings = variable_get('theme_'. $group->og_theme .'_settings',array());
  $form = array();
  //add in the theme selection form
  if ($theme_form = system_theme_select_form(t('Changing the theme will reload the settings below.'), isset($form_state['values']['theme']) ? $form_state['values']['theme'] : $group->og_theme, 2)) {
    $theme_form['themes']['#weight'] = -8;
	$theme_form['themes']['#collapsed'] = 1;
	$theme_form['themes']['#title'] = 'Change Course version Theme';
	unset($theme_form['themes']['rubik']);
    unset($theme_form['themes']['theme']['#options']['rubik']);
    unset($theme_form['themes']['']);
    unset($theme_form['themes']['theme']['#options']['']);
    $form += $theme_form;
  }
  //site logo
  $form['logo'] = array(
  '#type' => 'fieldset',
  '#title' => t('Site Logo'),
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
  );
  $form['logo']['default_logo'] = array(
  '#type' => 'select',
  '#title' => t('Use..'),
  '#options' => array(1 => 'Default Logo', 0 => 'Upload / File Path'),
  '#default_value' => $settings['default_logo'],
  );
  $form['logo']['logo_path'] = array(
  '#type' => 'textfield',
  '#size' => '40',
  '#title' => t("File Path"),
  '#required' => FALSE,
  '#default_value' => $settings['logo_path'],
  );
  $form['logo']['logo_upload'] = array(
  '#type' => 'file',
  '#size' => '10',
  '#title' => t("Upload"),
  '#description' => 'The logo typically is in the top left corner of the theme',
  '#required' => FALSE,
  );
  //favorite's icon
  $form['icon'] = array(
  '#type' => 'fieldset',
  '#title' => t('Shortcut Icon'),
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
  );
  $form['icon']['default_favicon'] = array(
  '#type' => 'select',
  '#title' => t('Use..'),
  '#options' => array(1 => 'Default Icon', 0 => 'Upload / File Path'),
  '#default_value' => $settings['default_favicon'],
  );
  $form['icon']['favicon_path'] = array(
  '#type' => 'textfield',
  '#size' => '40',
  '#title' => t("File Path"),
  '#required' => FALSE,
  '#default_value' => $settings['favicon_path'],
  );
  $form['icon']['favicon_upload'] = array(
  '#type' => 'file',
  '#size' => '10',
  '#title' => t("Upload"),
  '#description' => 'The icon you see in the left corner of the link bar.  This is usually a 16x16 icon to represent the course version. File size must be less then 1M',
  '#required' => FALSE,
  );
  //font selection
  $options = array(
  'none' => '- Use CSS Default -',
  'georgia' => 'Georgia, serif',
  'palatino' => '"Palatino Linotype", "Book Antiqua", Palatino, serif',
  'times' => '"Times New Roman", Times, serif',
  'arial' => 'Arial, Helvetica, sans-serif',
  'arialblack' => 'Arial Black, Gadget, sans-serif',
  'comic' => '"Comic Sans MS", cursive, sans-serif',
  'impact' => 'Impact, Charcoal, sans-serif',
  'lucidasans' => '"Lucida Sans Unicode", "Lucida Grande", sans-serif',
  'tahoma' => 'Tahoma, Geneva, sans-serif',
  'trebuchet' => '"Trebuchet MS", Helvetica, sans-serif',
  'verdana' => 'Verdana, Geneva, sans-serif',
  'courier' => '"Courier New", Courier, monospace',
  'lucidaconsole' => '"Lucida Console", Monaco, monospace',
  );
  $form['font_contatiner'] = array(
  '#type' => 'fieldset',
  '#title' => t('Font / Style'),
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
  );
  $form['font_contatiner']['font'] = array(
  '#type' => 'select',
  '#options' => $options,
  '#title' => t("Font"),
  '#description' => 'Select a font for all content in the course version.  Leaving default will use whatever your theme has indicated.',
  '#required' => TRUE,
  '#default_value' => $settings['font'],
  );
  $form['font_contatiner']['extra_css_use'] = array(
  '#type' => 'select',
  '#title' => t('Use..'),
  '#options' => array(0 => 'Theme CSS Only', 1 => 'Upload / File Path'),
  '#default_value' => $settings['extra_css_use'],
  );
  $form['font_contatiner']['extra_css_path'] = array(
  '#type' => 'textfield',
  '#size' => '40',
  '#title' => t("File Path"),
  '#required' => FALSE,
  '#default_value' => $settings['extra_css_path'],
  );
  $form['font_contatiner']['extra_css_upload'] = array(
  '#type' => 'file',
  '#size' => '10',
  '#title' => t("Upload CSS File"),
  '#description' => 'Upload your own CSS file for use in this course version',
  '#required' => FALSE,
  );
  if ($group->og_theme == 'chamfer') {
    drupal_add_js(drupal_get_path('theme', 'chamfer') .'/js/settings.js', 'theme');
      if (module_exists('jquery_colorpicker')) {
        drupal_add_js(drupal_get_path('theme','chamfer') .'/js/jquery_colorpicker.js','theme');
    }
  /*
   * The default values for the theme variables. Make sure $defaults exactly
   * matches the $defaults in the template.php file.
   */
  $color_array = array(
   'default' => 'Default',
   'mudbrown' => 'Mud Brown',
   'silver' => 'Silver',
   'formalgreen' => 'Formal Green',
   'black' => 'Space Opera Black',
   'custom' => 'Custom',
  );
  $defaults = array(
  'chamfer_borders' => 1,
  'chamfer_bgimage' => 0,
  'chamfer_top_logo' => 1, //0,1 or 2 for off, clear or solid
  'chamfer_top_link' => '',
  'chamfer_bottom_logo' => 1, //0,1 or 2 for off, clear or solid
  'chamfer_bottom_link' => '',
  'chamfer_color_template' => 'default',
  'chamfer_color_primary' => '000000',
  'chamfer_color_secondary' => '000000',
  'chamfer_color_header1' => '0099FF',
  'chamfer_color_header2' => '00CCFF',
  'chamfer_color_text' => '666666',
  'chamfer_color_link' => '0099FF',
  'chamfer_color_blocks' => 'E7E7E7',
  'chamfer_color_blockstyle_link' => '6D6D6D',
  'chamfer_color_blockstyle_bgcolor' => 'df5c5c',
  'chamfer_color_blockstyle_linkhover' => 'FFFFFF',
  'chamfer_color_footer_text' => 'FFFFFF',
  'chamfer_color_footer_link' => '00CCFF',
  );

  $form['logo'] = array(
  '#type' => 'fieldset',
  '#title' => t('Site Banner'),
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
  );
  $form['logo']['default_logo'] = array(
  '#type' => 'select',
  '#title' => t('Use..'),
  '#options' => array(1 => 'Default Banner', 0 => 'Upload / Path Below'),
  '#default_value' => $settings['default_logo'],
  );
  $form['logo']['logo_path'] = array(
  '#type' => 'textfield',
  '#size' => '40',
  '#title' => t("File Path"),
  '#required' => FALSE,
  '#default_value' => $settings['logo_path'],
  );
  $form['logo']['logo_upload'] = array(
  '#type' => 'file',
  '#size' => '10',
  '#title' => t("Upload"),
  '#description' => 'In Chamfer this will take the place of the site-banner (correct dimensions are 950px by 108px). File size must be less then 2M',
  '#required' => FALSE,
  );
  // Create the form widgets using Forms API
  $form['chamfer_color_template'] = array(
    '#type' => 'select',
    '#title' => t('Chamfer Template'),
  '#description' => t('Use this color template'),
  '#options' => $color_array,
    '#default_value' => $settings['chamfer_color_template'],
  );
  if (module_exists('jquery_colorpicker')) {
    $fieldtype = 'colorpicker';
  }
  else {
    $fieldtype = 'textfield';
  }
  //page colors
  $form['page'] = array(
    '#type' => 'fieldset',
  '#title' => t('Chamfer Page Settings'),
  '#description' => t("Change page related colors"),
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
  );
  $form['page']['chamfer_bgimage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Background Image'),
  '#description' => t('Whether or not to show the background image'),
    '#default_value' => $settings['chamfer_bgimage'],
  );
  $form['page']['chamfer_borders'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include Borders'),
  '#description' => t('Whether or not there should be a 10px border'),
    '#default_value' => $settings['chamfer_borders'],
  );
  $form['page']['chamfer_color_primary'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,
    '#title' => t('Background'),
  '#description' => t('Color of the background'),
    '#default_value' => $settings['chamfer_color_primary'],
  );
  $form['page']['chamfer_color_secondary'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Secondary Background'),
  '#description' => t('Color of the Inner background, the border and header / footer'),
    '#default_value' => $settings['chamfer_color_secondary'],
  );
  //header
  $form['header'] = array(
    '#type' => 'fieldset',
  '#title' => t('Chamfer Header Settings'),
  '#description' => t('Change items in the header'),
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
  );
  $form['header']['chamfer_top_logo'] = array(
    '#type' => 'select',
    '#title' => t('Show Top Logo'),
  '#description' => t('Display the logo at the top left of the interface'),
  '#options' => array(0 => 'No', 1 => 'Logo 1', 2 => 'Logo 2'),
    '#default_value' => $settings['chamfer_top_logo'],
  );
  $form['header']['chamfer_top_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Top Logo Link'),
  '#description' => t('The link the logo should go to when clicked, leave blank for none'),
    '#default_value' => $settings['chamfer_top_link'],
  );
  $form['header']['chamfer_color_header1'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Site Title'),
  '#description' => t('Color of the site title'),
    '#default_value' => $settings['chamfer_color_header1'],
  );
  $form['header']['chamfer_color_header2'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Site Slogan'),
  '#description' => t('Color of the site slogan'),
    '#default_value' => $settings['chamfer_color_header2'],
  );
  //content
  $form['content'] = array(
    '#type' => 'fieldset',
  '#title' => t('Chamfer Content Settings'),
  '#description' => t("Change content related colors"),
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
  );
  $form['content']['chamfer_color_text'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Text'),
  '#description' => t('Body of content text'),
    '#default_value' => $settings['chamfer_color_text'],
  );
  $form['content']['chamfer_color_link'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Links'),
  '#description' => t('Color of content links'),
    '#default_value' => $settings['chamfer_color_link'],
  );
  $form['content']['chamfer_color_blocks'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Block background'),
  '#description' => t('Background color of the block regions in the content'),
    '#default_value' => $settings['chamfer_color_blocks'],
  );
  $form['content']['chamfer_color_blockstyle_link'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Special Style Link'),
  '#description' => t('The special block style link color'),
    '#default_value' => $settings['chamfer_color_blockstyle_link'],
  );
  $form['content']['chamfer_color_blockstyle_linkhover'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Special Style Hovered link'),
  '#description' => t('The special block style hovered link color'),
    '#default_value' => $settings['chamfer_color_blockstyle_linkhover'],
  );
  $form['content']['chamfer_color_blockstyle_bgcolor'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Special Style Background'),
  '#description' => t('Hover color for special block style'),
    '#default_value' => $settings['chamfer_color_blockstyle_bgcolor'],
  );
  $block_options = array();
  $result = db_query("SELECT bid,module,delta FROM {blocks} WHERE theme='chamfer' AND status=1 AND (region='left' OR region='right') ORDER BY weight");
  while ($val = db_fetch_array($result)) {
    $blocks = call_user_func_array($val['module'] .'_block', array('list'));
    $block_options[$val['bid']] = $blocks[$val['delta']]['info'];
  }
  $form['content']['chamfer_color_specialblock'] = array(
    '#type' => 'select',  
  '#title' => t('Special Style Background'),
  '#multiple' => TRUE,
  '#description' => t('Which blocks should have the special styling?'),
  '#options' => $block_options,
    '#default_value' => $settings['chamfer_color_specialblock'],
  );
  $form['content']['chamfer_taxonomy'] = array(
    '#type' => 'select',  
  '#title' => t('Taxonomy'),
  '#description' => t('Display taxonomy with node?'),
  '#options' => array(0 => 'No', 1 => 'Yes'),
    '#default_value' => $settings['chamfer_taxonomy'],
  );
  //footer
  $form['footer'] = array(
    '#type' => 'fieldset',
  '#title' => t('Chamfer Footer Settings'),
  '#description' => t('Change items in the footer'),
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
  );
  $form['footer']['chamfer_bottom_logo'] = array(
    '#type' => 'select',
    '#title' => t('Show Bottom Logo'),
  '#description' => t('Display the logo at the top left of the interface'),
  '#options' => array(0 => 'No', 1 => 'Logo 1', 2 => 'Logo 2'),
    '#default_value' => $settings['chamfer_bottom_logo'],
  );
  $form['footer']['chamfer_bottom_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Bottom Logo Link'),
  '#description' => t('The link the logo should go to when clicked, leave blank for none'),
    '#default_value' => $settings['chamfer_bottom_link'],
  );
  $form['footer']['chamfer_color_footer_text'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Footer text'),
  '#description' => t('Color of the footer text'),
    '#default_value' => $settings['chamfer_color_footer_text'],
  );
  $form['footer']['chamfer_color_footer_links'] = array(
    '#type' => $fieldtype,
  '#size' => 6,
  '#maxlength' => 6,    
  '#title' => t('Footer links'),
  '#description' => t('Color of the footer links'),
  '#default_value' => $settings['chamfer_color_footer_links'],
  );
  }
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Apply Theme Settings'),
    '#weight' => 10,
    '#submit' => array('_elms_spaces_theme_form_submit'),
  );
  
  $form['theme_settings'] = array(
  '#type' => 'fieldset',
  '#title' => t('Other Settings'),
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
  );
  //support for logo
  $form['theme_settings']['toggle_logo'] = array(
  '#type' => 'checkbox',
  '#title' => t("Logo"),
  '#description' => "Display the logo uploaded in this theme",
  '#default_value' => $settings['toggle_logo'],
  );
  //support for site name
  $form['theme_settings']['toggle_name'] = array(
  '#type' => 'checkbox',
  '#title' => t("Course Name"),
  '#description' => "Display the Course Name if the theme if it supports it",
  '#default_value' => $settings['toggle_name'],
  );
  //support for site slogan
  $form['theme_settings']['toggle_slogan'] = array(
  '#type' => 'checkbox',
  '#title' => t("Course Title"),
  '#description' => "Display the Course Title if the theme supports it",
  '#default_value' => $settings['toggle_slogan'],
  );
  $form['theme_settings']['toggle_primary_links'] = array(
  '#type' => 'checkbox',
  '#title' => t("Primary Links"),
  '#description' => "Include primary links if the theme supports them. This will also remove the block displaying course features that are enabled",
  '#default_value' => $settings['toggle_primary_links'],
  );
  $form['theme_settings']['toggle_secondary_links'] = array(
  '#type' => 'checkbox',
  '#title' => t("Secondary Links"),
  '#description' => "Include secondary links if the theme supports them",
  '#default_value' => $settings['toggle_secondary_links'],
  );
  
  return $form;
}
//validate
function _elms_spaces_theme_form_validate($form, &$form_state) {
	$form_state['storage']['logo'] = '';
	$form_state['storage']['favicon'] = '';
    $dir = file_create_path(file_directory_path() .'/theme_logos');
    $is_writable = file_check_directory($dir,  1);
    if ($is_writable) {
      $validators = array(
        'file_validate_is_image' => array(),
        'file_validate_size' => array(2000 * 1024),
      );
      if ($file = file_save_upload('logo_upload', $validators, $dir)) {
        $form_state['storage']['logo'] = str_replace(' ','%20',$file->filepath);
	  }
    }
    $dir = file_create_path(file_directory_path() .'/theme_favicons');
    $is_writable = file_check_directory($dir,  1);
    if ($is_writable) {
      $validators = array(
        'file_validate_is_image' => array(),
        '_outline_designer_validate_image_resolution' => array('16x16'),
        'file_validate_size' => array(1000 * 1024),
      );
      if ($file = file_save_upload('favicon_upload', $validators, $dir)) {
		$form_state['storage']['favicon'] = str_replace(' ','%20',$file->filepath);
      }
	}
	//custom css
	$dir = file_create_path(file_directory_path() .'/theme_custom_css');
    $is_writable = file_check_directory($dir,  1);
    if ($is_writable) {
      $validators = array(
        'file_validate_size' => array(2 * 1024),
		'file_validate_extensions' => array('css'),
      );
      if ($file = file_save_upload('extra_css_upload', $validators, $dir)) {
		$form_state['storage']['css'] = str_replace(' ','%20',$file->filepath);
      }
	}
}

//theme settings submit
function _elms_spaces_theme_form_submit($form, &$form_state) {
  //store values in related group
  $version = og_get_group_context();
  $theme = $form_state['values']['theme'];
  $space = spaces_load('og', $version->nid, TRUE);
  if ($space && $theme == $version->og_theme) {
    $theme_array = variable_get('theme_'. $theme .'_settings',array());
    foreach($form_state['values'] as $key => $val) {
      //filter out fields we don't care about
      switch ($key) {
      case 'preset_generate':
      case 'op':
      case 'submit':
      case 'form_build_id':
      case 'form_token':
      case 'form_id': 
	  case 'theme':
	  break;
      default:
      $theme_array[$key] = $val;
      break;
      }
    }
	//if a theme logo / banner was uploaded, throw it in
	//automatic chamfer / garland / pushbutton resizing since we know those have certain requirements
	if ($form_state['storage']['logo'] != '') {
      $theme_array['logo_path'] = $form_state['storage']['logo'];
      if ($theme == 'chamfer') {
        $theme_array['logo_path'] = file_directory_path() .'/imagecache/chamfer-banner'. str_replace(file_directory_path(),'',$theme_array['logo_path']);
      }
      elseif ($theme == 'pushbutton' || $theme == 'garland') {
        $theme_array['logo_path'] = file_directory_path() .'/imagecache/logo'. str_replace(file_directory_path(),'',$theme_array['logo_path']);
      }
    }
	//if favicon was uploaded, store the file path
	if ($form_state['storage']['favicon'] != '') {
		$theme_array['favicon_path'] = $form_state['storage']['favicon'];
	}
	//if CSS was uploaded, store the file path
	if ($form_state['storage']['css'] != '') {
	  $theme_array['extra_css_path'] = $form_state['storage']['css'];
	}
    $space->controllers->variable->set('theme_'. $theme .'_settings',$theme_array);
  }
  else {
    $version->theme = $theme;
    node_save($version); 
  }
  $ary = $_GET;
  $ary['set'] = rand(10,100);
  unset($ary['q']);
  drupal_goto(drupal_get_path_alias($_GET['q']),$ary);
}
