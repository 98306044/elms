<?php 
//this file exists because a lot of themes don't style the book-navigation.tpl.php file. as a result it will want to look in the modules/book folder (which we've made relative to the module at this point)
  include_once dirname(__FILE__) .'/../../book-navigation.tpl.php';