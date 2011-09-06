/*********************************************************************************************************/
/**
 * elimedia plugin for CKEditor 3.x (Author: Lajox ; Email: lajox@19www.com)
 * version:	 1.0
 * Released: On 2009-12-11
 * Download: http://code.google.com/p/lajox
 */
/*********************************************************************************************************/

CKEDITOR.dialog.add("elimedia_webcam",function(e){	
	return{
		title:e.lang.elimedia_webcam.title,
		resizable : CKEDITOR.DIALOG_RESIZE_BOTH,
		minWidth:500,
		minHeight:300,
		buttons:[CKEDITOR.dialog.okButton],
		onShow:function(){ 
	
		},
		onLoad:function(){ 
			dialog = this; 
			this.setupContent();
		},
		onOk:function(){
			//if ( sInsert.length > 0 ) 
			//e.insertHtml(sInsert);
		},
		contents:[
			{	id:"info",
				name:'info',
				label:e.lang.elimedia_webcam.commonTab,
				elements:[{
				 type:'vbox',
				 padding:0,
				 children:[
					{type:'html',
					html: '<iframe src="https://elimedia.psu.edu/webcam/" id="elimedia-webcam-frame" style="width:600px;height:500px;overflow-x:hidden"></iframe>'
					}]
				}]
			}
		]
	};
});
