<?php

/**
 * @file
 * Editor integration functions for codemirror.
 */

/**
 * Plugin implementation of hook_editor().
 */
function wysiwyg_codemirror_editor() {
  $editor['codemirror'] = array(
    'title' => 'CodeMirror',
    'vendor url' => 'http://codemirror.net',
    'download url' => 'http://codemirror.net',
    'library path' => wysiwyg_get_path('codemirror'),
    'libraries' => array(
      '' => array(
        'title' => 'CodeMirror',
        'files' => array(
          'lib/codemirror.js',
        ),
      ),
    ),
    'version callback' => 'wysiwyg_codemirror_version',
    'settings callback' => 'wysiwyg_codemirror_settings',
    'plugin callback' => 'wysiwyg_codemirror_plugins',
    'load callback' => 'wysiwyg_codemirror_load',
    'versions' => array(
      '2' => array(
        'js files' => array('codemirror.js'),
        'css files' => array('codemirror.css'),
      ),
    ),
  );
  return $editor;
}

/**
 * Detect editor version.
 *
 * @param $editor
 *   An array containing editor properties as returned from hook_editor().
 *
 * @return
 *   The installed editor version.
 */
function wysiwyg_codemirror_version($editor) {
  $fp = $editor['library path'] . '/README.md';
  if (!file_exists($fp)) {
    return;
  }
  $fp = fopen($fp, 'r');
  $line = fgets($fp);
  if (preg_match('@([0-9\.]+)$@', $line, $version)) {
    fclose($fp);
    return $version[1];
  }
  fclose($fp);
}

/**
 * Perform additional actions upon loading this editor.
 *
 * @param $editor
 *   A processed hook_editor() array of editor properties.
 * @param $library
 *   The internal library name (array key) to use.
 */
function wysiwyg_codemirror_load($editor, $library) {
  drupal_add_css($editor['library path'] . '/lib/codemirror.css');
  drupal_add_css($editor['library path'] . '/theme/default.css');

  drupal_add_js($editor['library path'] . '/lib/codemirror.js');
  drupal_add_js($editor['library path'] . '/mode/clike/clike.js');
  drupal_add_js($editor['library path'] . '/mode/css/css.js');
  drupal_add_js($editor['library path'] . '/mode/diff/diff.js');
  drupal_add_js($editor['library path'] . '/mode/haskell/haskell.js');
  drupal_add_js($editor['library path'] . '/mode/htmlmixed/htmlmixed.js');
  drupal_add_js($editor['library path'] . '/mode/javascript/javascript.js');
  drupal_add_js($editor['library path'] . '/mode/php/php.js');
  drupal_add_js($editor['library path'] . '/mode/stex/stex.js');
  drupal_add_js($editor['library path'] . '/mode/xml/xml.js');
}

/**
 * Return runtime editor settings for a given wysiwyg profile.
 *
 * @param $editor
 *   A processed hook_editor() array of editor properties.
 * @param $config
 *   An array containing wysiwyg editor profile settings.
 * @param $theme
 *   The name of a theme/GUI/skin to use.
 *
 * @return
 *   A settings array to be populated in
 *   Drupal.settings.wysiwyg.configs.{editor}
 */
function wysiwyg_codemirror_settings($editor, $config, $theme) {
  /* Defaults */
  $settings = array(
    'mode' 			 => 'application/x-httpd-php', 
    'indentUnit' 	 => 2,
    'indentWithTabs' => false,
    'tabMode' 		 => 'shift',
    'enterMode' 	 => 'indent',
    'electricChars'  => false,
    'lineNumbers' 	 => false, 
    'gutter' 		 => false,
    'readOnly' 		 => false,
    'matchBrackets'  => false
  );

  $all_settings = array_keys($settings);

  if (is_array($config['buttons']['default'])) {
    foreach ($config['buttons']['default'] as $key => $value) {
      if ($value) {
        if (in_array($key, $all_settings)) {
          $settings[$key] = ($value != 0);
        }
      }
    }
  }
  
  return $settings;
}

/**
 * Return internal plugins for this editor; semi-implementation of hook_wysiwyg_plugin().
 */
function wysiwyg_codemirror_plugins($editor) {
  return array(
    'default' => array(
      'buttons' => array(
        'lineNumbers' 	 => t('Line Numbers'),
        'matchBrackets'  => t('Match Brackets'),
        'electricChars'  => t('Electric Characters'),
		'indentWithTabs' => t('Indent With Tabs'),
		'gutter' 		 => t('Gutter'),
		'matchBrackets'  => t('Match Brackets')
      )
    ),
    'internal' => TRUE,
  );
}