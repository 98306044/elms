$(document).ready(function(){
  //establish the default state for the nav which is closed
  $('#regions_elms_nav_left .regions_pre_block_container').addClass('regions_toggle_closed');
  //when clicking the title, bring it to the front
  $('#regions_elms_nav_left .regions_pre_block_container').click(function(){
    //open this region if clicked on a tab, close if you do
	if ($('#regions_elms_nav_left .regions_pre_block_container').hasClass('regions_toggle_closed')) {
	  $('#regions_elms_nav_left .regions_pre_block_container').addClass('regions_toggle_open');
	  $('#regions_elms_nav_left .regions_pre_block_container').removeClass('regions_toggle_closed');
	  $('#regions_elms_nav_left').animate({left:'0'}, 500);
	}
	else {
	  $('#regions_elms_nav_left .regions_pre_block_container').addClass('regions_toggle_closed');
	  $('#regions_elms_nav_left .regions_pre_block_container').removeClass('regions_toggle_open');
	  $('#regions_elms_nav_left').animate({left:'-200'}, 500);
	}
  });
  //collapse based on toggle
  $('#regions_elms_nav_left .regions_toggle').click(function(){
	//additional logic is to account for menu being opened by clicking a block title
	if ($(this).hasClass('regions_toggle_closed')) {
	  $(this).addClass('regions_toggle_open');
	  $(this).removeClass('regions_toggle_closed');
	  $('#regions_elms_nav_left').animate({left:'0'}, 500);
	}
	else {
	  $(this).addClass('regions_toggle_closed');
	  $(this).removeClass('regions_toggle_open');
	  $('#regions_elms_nav_left').animate({left:'-200'}, 500);
	}
  });
});