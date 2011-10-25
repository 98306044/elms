$(document).ready(function(){
  //allow user menu to slide into focus
  $('#regions_block_elms_navigation_top_2 .regions_block_title').click(function(){
    $('#regions_block_elms_navigation_top_2 .regions_block_content').slideToggle('fast', 'linear');
  });
  //scaling capabilities
  $('#regions_block_elms_navigation_top_3 .elms_zoom_in').click(function(){
    if (Drupal.settings.elms_navigation_top.factor <= 1.5) {
      Drupal.settings.elms_navigation_top.factor = Drupal.settings.elms_navigation_top.factor + 0.1;
      $('body').css('zoom', Drupal.settings.elms_navigation_top.factor).css('-moz-transform', 'scale('+ Drupal.settings.elms_navigation_top.factor +')');
    }
  });
  $('#regions_block_elms_navigation_top_3 .elms_zoom_out').click(function(){
    if (Drupal.settings.elms_navigation_top.factor >= 0.9) {
      Drupal.settings.elms_navigation_top.factor = Drupal.settings.elms_navigation_top.factor - 0.1;
      $('body').css('zoom', Drupal.settings.elms_navigation_top.factor).css('-moz-transform', 'scale('+ Drupal.settings.elms_navigation_top.factor +')');
    }
  });
  $('#regions_block_elms_navigation_top_3 .elms_zoom_reset').click(function(){
	  Drupal.settings.elms_navigation_top.factor = 1;
	  $('body').css('zoom', Drupal.settings.elms_navigation_top.factor).css('-moz-transform', 'scale('+ Drupal.settings.elms_navigation_top.factor +')');
  });
});