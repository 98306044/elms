$(document).ready(function(){
  //block 1 is the default for an open
  $('#elms_region_right .elms_region_1 .elms_region_block_content').css('display','block');
  //when clicking the title, bring it to the front
  $('#elms_region_right .elms_region_block_title').click(function(){
	//hide all block content
	$('#elms_region_right .elms_region_block_content').css('display','none');
	//show this one
	$(this).parent().children('.elms_region_block_content').css('display','block');
	//only expand based on clicking block titles, never collapse
	if ($('#elms_region_right .elms_region_toggle').hasClass('elms_region_toggle_closed')) {
	  $('#elms_region_right .elms_region_toggle').addClass('elms_region_toggle_open');
	  $('#elms_region_right .elms_region_toggle').removeClass('elms_region_toggle_closed');
	  $('#elms_region_right').animate({right:'0'}, 500);
	}
  });
  //collapse based on toggle
  $('#elms_region_right .elms_region_toggle').click(function(){
	//additional logic is to account for menu being opened by clicking a block title
	if ($(this).hasClass('elms_region_toggle_closed')) {
	  $(this).addClass('elms_region_toggle_open');
	  $(this).removeClass('elms_region_toggle_closed');
	  $('#elms_region_right').animate({right:'0'}, 500);
	}
	else {
	  $(this).addClass('elms_region_toggle_closed');
	  $(this).removeClass('elms_region_toggle_open');
	  $('#elms_region_right').animate({right:'-200'}, 500);
	}
  });
});