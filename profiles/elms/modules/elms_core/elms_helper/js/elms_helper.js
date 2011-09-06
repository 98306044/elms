// $Id$

Drupal.behaviors.appbar = function (context) {
  if (context == document) {
    $('body').addClass('with-appbar');
    if (Drupal.settings.appbar.use_alerts) {
      var interval = setInterval("appbar_refresh();", Drupal.settings.appbar.delay);
    }
  }
  //Make sure we can run context.find().
  var ctxt = $(context);
  appbar_tn();
  ctxt.find('#appbar_container').show();
  ctxt.find('#appbar_alerts').click(function() {
    var $list = $('#appbar_alerts_list');
    var $bar = $('#appbar_messages');
    if ($bar.css('background-image') == 'url("'+ Drupal.settings.appbar.open_path +'")') {
      $bar.css('background-image', 'url("'+ Drupal.settings.appbar.close_path +'")');
    }
    else {
      $bar.css('background-image', 'url("'+ Drupal.settings.appbar.open_path +'")');
    }
    $list.toggle();
    if ($list.is(':visible')) {
      $list.load(Drupal.settings.appbar.base_path +'appbar/refresh/list');
      $('#appbar_count').html('0');
    }
  });
  if ($.fn.hoverIntent) {
    ctxt.find('.appbar-block-hover').hoverIntent(appbarHoverOn, appbarHoverOff);
  }
  else {  
    ctxt.find('.appbar-block-hover').hover(appbarHoverOn, appbarHoverOff);
  }
  ctxt.find('.appbar-block-popup .appbar-block-title').click(function(e) {
    e.preventDefault();
    var content = $(this).prev('.appbar-block-content');
    var visible = content.slideToggle('fast').attr('display');
    if (visible != 'none') {
      $('.appbar-block-content:visible').not(content).hide();
    }
  });
  ctxt.find('.appbar-block-popup .appbar-minimize').click(function(e) {
    e.preventDefault();
    $(this).parent().parent().slideToggle('fast');
  });
  $('.appbar-block:first').addClass('first');
  $('.appbar-block:last').addClass('last');
  ctxt.find('.appbar-block-controls').hover(
    function() {$('.appbar-block-configure').show(); },
    function() { $('.appbar-block-configure').hide(); }
  );
}