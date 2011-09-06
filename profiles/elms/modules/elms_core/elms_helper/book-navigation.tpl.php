<?php 
  //find 1 level from the top
  if(arg(0) == 'node') {
  $nid = arg(1);
  $group = og_get_group_context();
  $options = _elms_helper_toc($book_id, array(), 100);
  if (isset($group->nid)) {
    array_shift($options);
    $options = array_merge(array('node/'. $group->nid => t('Home')),$options);
  }
  //find the current array item and advance the internal pointer to it
  foreach ($options as $key => $option) {
    //we're at the current node
    if ($key == 'node/'. $nid) {
      $found_current = true;
      prev($options);
    }
    //increment the pointer as long as we haven't found the current item
    if (!$found_current) {
      next($options);
    }
  }
  //now we're at the current item, grab a depth count
  $active_depth = count(explode('--', current($options)));
  //grab the next depth count
  $next_depth = count(explode('--', next($options)));
  //grab the previous depth count, accounting for the position moved ahead
  prev($options);
  $prev_depth = count(explode('--', prev($options)));
  //if active is the first child page to the previous item, remove the previous url
  if ($prev_depth < $active_depth) {
    $prev_url = false;  
  }
  //if active is the last child page in this branch and the next item is in a new branch, remove the next url
  if ($active_depth > $next_depth) {
    $next_url = false;
  }
  if ($tree || $has_links): ?>
  <br/>
  <div id="book-navigation-<?php print $book_id; ?>" class="book-navigation">
    <?php if ($has_links): ?>
    <div class="page-links clear-block">
      <?php if ($prev_url && $prev_url != url('node/'. $book_id)) { ?>
        <a href="<?php print $prev_url; ?>" class="elms_page_previous" title="<?php print t('Go to previous page'); ?>"><?php print t('< Previous Page') ?></a>
      <?php }else{ ?>
		<div class="elms_page_previous"></div>
	  <?php } ?>
      <div class="elms_quick_jump">
      <label for="elms_quick_jump">Jump to:</label> <select id="elms_quick_jump" onchange="if(this.value != '') window.location=this.value;">
	<?php
      foreach ($options as $key => $option) {
		if ($key == 'node/'. $nid) {
			print '<option value="'. base_path() . $key .'" SELECTED>'. $option .'</option>';
		}
		else{
			print '<option value="'. base_path() . $key .'">'. $option .'</option>';
		}
	}
	?>
	</select>
    </div>
      <?php if ($next_url) { ?>
        <a href="<?php print $next_url; ?>" class="elms_page_next" title="<?php print t('Go to next page'); ?>"><?php print t('Next Page >'); ?></a>
      <?php }else{ ?>
		<div class="elms_page_next"></div>
	  <?php } ?>
    </div>
    <?php endif; ?>

  </div>
<?php endif; 
  }
  ?>