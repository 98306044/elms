(function($) {

/* Maintain a list of active editors on the page */
var instances = new Object; 

/**
 * Attach this editor to a target element.
 *
 * See Drupal.wysiwyg.editor.attach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.attach.codemirror = function(context, params, settings) {
  var textArea = document.getElementById(params.field);
  if (textArea) {
    instances[params.field] = CodeMirror.fromTextArea(textArea, settings);
  }
  
  if (params.resizable) {
    jQuery('.CodeMirror-scroll').css({
	  'height'	   : 'auto',
	  'overflow-y' : 'hidden',
	  'overflow-x' : 'auto'
	});
  }
};

/**
 * Detach a single or all editors.
 *
 * See Drupal.wysiwyg.editor.detach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.detach.codemirror = function(context, params) {
  instances[params.field].toTextArea();
  delete instances[params.field];
};

})(jQuery);