// JavaScript Document
$(document).ready(function(){
  if (Drupal.settings.elms_navigation.color != null) {
    $('#appbar').css('background-color', Drupal.settings.elms_navigation.color);
  }
  $('ul.tabs.primary li').each(function() {
	$(this).addClass('leaf').appendTo('.menu-block-3 > ul');
	$(this).children('a').addClass('menu_icon menu-16776');
  });
  $('#appbar .menu-mlid-16776').remove();
  //$('ul.tabs.secondary').appendTo('.menu-block-3 > ul');
});