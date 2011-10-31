/*********************************************************************************************************/
/**
 * elimedia plugin for CKEditor 3.x (Author: Lajox ; Email: lajox@19www.com)
 * version:	 1.0
 * Released: On 2009-12-11
 * Download: http://code.google.com/p/lajox
 */
/*********************************************************************************************************/

CKEDITOR.plugins.add('elimedia',   
  {    
    requires: ['dialog'],
		lang : ['en'], 
    init:function(a) { 
	var b="elimedia";
	var c=a.addCommand(b,new CKEDITOR.dialogCommand(b));
		c.modes={wysiwyg:1,source:0};
		c.canUndo=false;
	a.ui.addButton("elimedia",{
					label:a.lang.elimedia.title,
					command:b,
					icon:this.path+"elimedia.png"
	});
	CKEDITOR.dialog.add(b,this.path+"dialogs/elimedia.js")}
});