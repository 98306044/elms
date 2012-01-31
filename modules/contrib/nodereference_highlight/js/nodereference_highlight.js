// JavaScript Document
//
Drupal.nodereference_highlight = {"text" : ""};
Drupal.nodereference_highlight.getSelected = function(){
  var t = '';
  if(window.getSelection){
    t = window.getSelection();
  }else if(document.getSelection){
    t = document.getSelection();
  }else if(document.selection){
    t = document.selection.createRange().text;
  }
  return t;
}

Drupal.nodereference_highlight.mouseup = function(e){
  var text = Drupal.nodereference_highlight.getSelected();
  if(text !=''){
		Drupal.nodereference_highlight.text = text;
		$('#nrhi_container a').each(function(){
			$(this).attr('href', $(this).attr('href') + Drupal.nodereference_highlight.text);
		});
		$("#nrhi_container").css('display', 'block').css('top', e.pageY + 10).css('left', e.pageX - 30);
  }
}

$(document).ready(function(){
  $('div.node').bind("mouseup", Drupal.nodereference_highlight.mouseup);
  $('.elms_poll_tab').click(function(){
    $('#elms_poll_list-block_1_tab').parent().click();
  });
});