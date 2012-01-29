// JavaScript Document
//
Drupal.SelectedText = {};
Drupal.SelectedText.getSelected = function(){
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

Drupal.SelectedText.mouseup = function(){
  var st = Drupal.SelectedText.getSelected();
  if(st!=''){
		var pathname = window.location.pathname;
		var path = pathname.split('/');
		var splitpath = '';
		var last_found = false;
		for (var arg in path) {
			if (last_found) {
				var nid = path[arg];
			}
			else {
				if (path[arg] == 'node') {
				  last_found = true;
			  }
				else {
				  splitpath += path[arg] +'/';
				}
			}
		}
		//ask before making the association, test only
		if (confirm("Add a poll association to selected text?")) {
		  window.location = splitpath +'node/add/poll/'+ nid +'&edit[field_poll_text_ref][0][value]='+ st;
		}
  }
}

$(document).ready(function(){
  $('div.node').bind("mouseup", Drupal.SelectedText.mouseup);
	$('.elms_poll_tab').click(function(){
	  $('#elms_poll_list-block_1_tab').parent().click();	
	});
});