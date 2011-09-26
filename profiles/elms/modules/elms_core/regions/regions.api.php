<?php

/**
 * @file
 * Hooks provided by Regions.
 
 */

/**

  * When defining blocks in regions you can use $block['regions_allow_html_title']
  * This will render the block's title with $block->title instead of $block->subject
  * Subject is sanitized where as title is not
  * the most common use-case is pictures / images in place of titles.

 * Add regions to be created
 *
 * Allows other modules to define regions
 *
 */
function hook_define_regions() {
  //this could also be module_name if you want to be consistent
  $regions['my_region_1'] = array(
    //required: name of the module invoking this
    'project' => 'module_name',
	//optional: css file name in the project folder, no leading slash
	'css' => 'style.css',
	//optional: js file name in the project folder, no leading slash
	'js' => 'script.js'
  );
  //you can define as many regions as you want though including only 1 is more modular
  $regions['my_region_2'] = array(
    'project' => 'module_name', 
	'css' => 'style.css',
	'js' => 'script.js'
  );
  return $regions;
}
