// JavaScript Document
$(document).ready(function(){
  $('label[for=edit-field-navigation-value-dropdown]').prepend('<div id="dropdown-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-dropdownactiveleft]').prepend('<div id="dropdownactiveleft-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-dropdownleft]').prepend('<div id="dropdownleft-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-left]').prepend('<div id="left-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-activeleftleft]').prepend('<div id="activeleftleft-image" class="navstyle-image" />');
  $('label[for=edit-field-navigation-value-leftactiveright]').prepend('<div id="leftactiveright-image" class="navstyle-image" />');

  $('body.node-type-version .form-radios').parent().css('float','left').css('width','96%');
  $('#edit-field-footer-0-value-wrapper').css('float','left').css('width','96%');
  //$('body.page-node .column-side').destroy();
});