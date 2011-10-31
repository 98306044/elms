/*********************************************************************************************************/
/**
 * elimedia plugin for CKEditor 3.x (Author: Lajox ; Email: lajox@19www.com)
 * version:	 1.0
 * Released: On 2009-12-11
 * Download: http://code.google.com/p/lajox
 */
/*********************************************************************************************************/

CKEDITOR.plugins.add('elimedia_webcam',   
  {    
    requires: ['dialog'],
	lang : ['en'], 
    init:function(a) { 
	var b="elimedia_webcam";
	var c=a.addCommand(b,new CKEDITOR.dialogCommand(b));
		c.modes={wysiwyg:1,source:0};
		c.canUndo=false;
	a.ui.addButton("elimedia_webcam",{
					label:a.lang.elimedia_webcam.title,
					command:b,
					icon:this.path+"elimedia_webcam.png"
	});
	CKEDITOR.dialog.add(b,this.path+"dialogs/elimedia_webcam.js")}
});