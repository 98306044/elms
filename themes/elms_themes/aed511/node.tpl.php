<div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
    <div class="page_heading"><?php print $title; ?></div>
	<div class="content"><?php print $content; ?></div>
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
</div>