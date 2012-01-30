<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
<title><?php print $head_title ?></title>
<?php print $head ?><?php print $styles ?><?php print $scripts ?>
<script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
</head>
<body>
<div id="skip-nav" class="offscreen">
  <a href="#main-content"><?php print t('Skip to main content'); ?></a>
</div>
<div id="container">
  <div id="elearningmain">
    <div id="header">
      <div id="banner"> <img src="<?php print $base_path . $directory; ?>/images/larch65_3_r1_c1.gif" alt="course banner" title="course banner" width="1024" height="76" border="0" usemap="#map2"/>

      </div>
      <div id="imagebar"></div>
      <div id="header-nice-menu"><?php print $header; ?></div>
    </div>
    <div id="maincontainer">
      <div id="sidebar-left">
        <div id="leftcontainer">
          <div id="menu"> <?php print $left; ?> </div>
        </div>
        <div id="rightcontainer">
        <a name="main-content"></a>
          <div id="content">
            <?php 
			print $breadcrumb;
			if(!isset($node->nid)){
				print '<h1>' . $title . '</h1>';
			}
			?>
            <?php print $messages; ?> <?php print $tabs; ?> <?php print $content; ?>
          </div>
        </div>
      </div>
    </div>
    <div class="clear"></div>
    <div id="endcontainer"></div>
    <div class="clear"></div>
    <div id="footer"> <?php print $footer_message . $footer; ?> </div>
  </div>
</div>
<?php print $closure; ?>
</body>
</html>
