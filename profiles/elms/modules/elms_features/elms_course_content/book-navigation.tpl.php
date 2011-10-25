<?php
  //find 1 level from the top
  if(arg(0) == 'node') {
  $nid = arg(1);
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
  <?php 
  //check for highest level, print table of contents if this is the case
  if ($tree && $book_id == $nid) {
    print _elms_course_content_toc($book_id);
  }
  if ($has_links): ?>
    <div class="page-links clear-block">
      <?php if ($prev_url && $prev_url != url('node/'. $book_id)) { ?>
        <a href="<?php print $prev_url; ?>" class="elms_page_previous" title="<?php print t('Go to previous page'); ?>"><?php print t('< Previous Page') ?></a>
      <?php }else{ ?>
        <div class="elms_page_previous"></div>
      <?php } ?>
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