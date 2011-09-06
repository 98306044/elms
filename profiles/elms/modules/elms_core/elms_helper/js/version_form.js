// JavaScript Document
$(document).ready(function(){
  $('label[for=edit-field-navigation-value-dropdown]').prepend('<div id="dropdown-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-dropdownactiveleft]').prepend('<div id="dropdownactiveleft-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-dropdownleft]').prepend('<div id="dropdownleft-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-left]').prepend('<div id="left-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-activeleftleft]').prepend('<div id="activeleftleft-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-leftactiveright]').prepend('<div id="leftactiveright-image" class="navstyle-image" />');

  //stick the multistep to the left column to float as the user scrolls
  var elTop = $('#block-multistep-version').offset().top+20;
  var sticky_width = $('#block-multistep-version').width();
  $(window).scroll(function() {
    var windowTop = $(window).scrollTop();
    if (windowTop > elTop) {
      $('#block-multistep-version').addClass('sticky');
	  $('#block-multistep-version').width(sticky_width);
	}
    else {
      $('#block-multistep-version').removeClass('sticky');
    }
  });
  //block
  if ($('#multistep-version-1').attr('id') == 'multistep-version-1') {
	var output = '<div align="center" class="multistep-buttons">';
	if ($('#edit-previous').attr('id') == 'edit-previous') {
      output += '<input type="button" id="previous-multistep" name="Previous" value="Previous" class="form-submit"/>';
	}
	if ($('#edit-next').attr('id') == 'edit-next') {
      output += '<input type="button" id="next-multistep" name="next" class="form-submit"/>';
	}
	if ($('#edit-done').attr('id') == 'edit-done') {
      output += '<input type="button" id="done-multistep" name="build" class="form-submit"/>';
	}
	output += '</div>';
	$('#multistep-version-1').parent().parent().append(output);
	$('#done-multistep').val($('#edit-done').val());
	$('#next-multistep').val($('#edit-next').val());
  }
  $('#next-multistep').click(function(){
    $('#edit-next').click();
  });
  $('#previous-multistep').click(function(){
    $('#edit-previous').click();
  });
  $('#done-multistep').click(function(){
    $('#edit-done').click();
  });
  $('body.node-type-version .form-radios').parent().css('float','left').css('width','96%');
  $('#edit-field-footer-0-value-wrapper').css('float','left').css('width','96%');
  //$('body.page-node .column-side').destroy();
});