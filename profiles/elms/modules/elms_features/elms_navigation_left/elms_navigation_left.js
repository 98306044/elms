$(document).ready(function(){
  //establish the default state for the nav which is closed
  $('#regions_elms_navigation_left .regions_pre_block_container').addClass('regions_toggle_closed');
  //when clicking the title, bring it to the front
  $('#regions_elms_navigation_left .regions_pre_block_container').click(function(){
    //open this region if clicked on a tab, close if you do
    if ($('#regions_elms_navigation_left .regions_pre_block_container').hasClass('regions_toggle_closed')) {
      $('#regions_elms_navigation_left .regions_pre_block_container').addClass('regions_toggle_open');
      $('#regions_elms_navigation_left .regions_pre_block_container').removeClass('regions_toggle_closed');
      $('#regions_elms_navigation_left').animate({left:'0'}, 'fast');
    }
    else {
      $('#regions_elms_navigation_left .regions_pre_block_container').addClass('regions_toggle_closed');
      $('#regions_elms_navigation_left .regions_pre_block_container').removeClass('regions_toggle_open');
      $('#regions_elms_navigation_left').animate({left:'-180'}, 'fast');
    }
  });
});