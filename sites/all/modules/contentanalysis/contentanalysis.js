// $Id: contentanalysis.js,v 1.1.2.7 2010/11/09 21:50:14 tomdude48 Exp $

if (Drupal.jsEnabled) {
  $(document).ready(function () {
	if(Drupal.settings.contentanalysis.analyze_on_start == 1) {
//	  contentanalysis_analyze();	 
    }
  });
}


Drupal.behaviors.contentanalysisui = function () {
  if($('#modalContent div.analyzers h3.analyzer').size() > 0) {
    contentanalysis_show_analyzer_tab($('div.analyzers h3.analyzer').get(0));
    $('div.analyzers h3.analyzer').mousedown(function () {
      contentanalysis_show_analyzer_tab(this);
    }) 
    $('h3.contentanalysis-report-tab').mousedown(function () { 
      contentanalysis_show_report_tab(this);
    })
  }
}

var contentanalysisPrevAnalyzerTab;
var contentanalysisPrevReportTab;
var contentanalysisCurrentAnalyzerTab;
var contentanalysisCurrentReportTab;
var contentanalysisReportActiveTab = new Array();

var contentanalysis_back = function() {
  contentanalysis_show_analyzer_tab(contentanalysisPrevAnalyzerTab);
  //contentanalysis_show_report_tab(contentanalysisPrevReportTab);
}

var contentanalysis_show_analyzer_tab = function (theTab){
  $('div.analysis-results div.analyzer-analysis:eq(' + $('.analyzers h3.analyzer').index(theTab) + ')').children('.content-analysis-tab:first').addClass('active');
  $('div.analysis-results div.analyzer-analysis').hide();
  $('.analyzers h3.analyzer').removeClass('active');
  $(theTab).addClass('active');
  $('div.analysis-results div.analyzer-analysis:eq(' + $('.analyzers h3.analyzer').index(theTab) + ')').show();
  $('.content-analysis-results').hide();

  var id = $(theTab).attr('id');
  var e = id.split('-');
  var analyzer = e[3];
  
  if(contentanalysisReportActiveTab[analyzer]) {
    contentanalysis_show_report_tab($('#contentanalysis-report-tab-' + analyzer + '-' + contentanalysisReportActiveTab[analyzer]));
  }
  else {
    contentanalysis_show_report_tab($('#contentanalysis-report-tab-' + analyzer + '-0'));
  }
  contentanalysisPrevAnalyzerTab = contentanalysisCurrentAnalyzerTab;
  contentanalysisCurrentAnalyzerTab = theTab;  
}

var contentanalysis_show_report_tab = function (theTab){
  var id = $(theTab).attr('id');
  var e = id.split('-');
  contentanalysisReportActiveTab[e[3]] = e[4];
  $('h3.contentanalysis-report-tab').removeClass('active');  
  $(theTab).addClass('active');
  $('.contentanalysis-results-section').hide();

  var tabs = $("#contentanalysis-report-tabs-" + e[3]);
  //tabs.css('border','2px solid red');
  var pos = $("#contentanalysis-report-tabs-" + e[3]).position(); 
  var offset = $("#contentanalysis-report-tabs-" + e[3]).offset(); 
  var height = tabs.height();
  var top = (pos.top+height)+"px";
  var left = (pos.left)+"px";
  
  var sec_id = id.replace('tab', 'results');
  var result_id = sec_id.replace('-'+e[4],'')
  //$('#' + result_id).css({'top': top, 'left': left}); 
  $('#' + result_id).css('top', top); 
  //$('#' + result_id).css('border', '2px solid green'); 
  $('#' + sec_id).show();
//alert("pos.left="+pos.left+",pos.top="+pos.top+",offset.left="+offset.left+",offset.top="+offset.top);
  contentanalysisPrevReportTab = contentanalysisCurrentReportTab;
  contentanalysisCurrentReportTab = theTab; 
}

// called from inline Analyze content button
var contentanalysis_inline_analysis = function() {
  Drupal.settings.contentanalysis.display_dialog = 0;
  Drupal.settings.contentanalysis.display_inline = 1;
  //$('#contentanalysis-ininline-analysis-button').after('<span class="throbber">Loading...</span>');
  //$('#contentanalysis-ininline-analysis-button').after(Drupal.settings.contentanalysis.throbber);
  $('#contentanalysis-buttons').after('<div class="ahah-progress ahah-progress-throbber"><div class="throbber">&nbsp;</div><div class="message">' + Drupal.t('Analyzing...') + '</div></div>');
  contentanalysis_analyze();
}

// called from inline Analyze content button
var contentanalysis_dialog_analysis = function() {
  Drupal.settings.contentanalysis.display_dialog = 1;
  Drupal.settings.contentanalysis.display_inline = 0;
  contentanalysis_analyze();
}

// called from inline Analyze content button
var contentanalysis_full_analysis = function() {
  Drupal.settings.contentanalysis.display_dialog = 1;
  Drupal.settings.contentanalysis.display_inline = 1;
  contentanalysis_analyze();
}

// called from inline Analyze content button
var contentanalysis_refresh_analysis = function(analyzer) {
  Drupal.settings.contentanalysis.display_dialog = 0;
  Drupal.settings.contentanalysis.display_inline = 1;
  //$('.contentanalysis-refresh-link-' + analyzer).replaceWith('<span class="throbber">Loading...</span>');
  $('.contentanalysis-refresh-link-' + analyzer).replaceWith('<div class="ahah-progress ahah-progress-throbber"><div class="throbber">&nbsp;</div></div>');
  contentanalysis_analyze(analyzer);
}

var contentanalysis_analyze = function(analyzer_override) {
  // if TinyMCE is used, turn off and on to save body text to textarea
  var data = { 
    'nid': -1,
    'node_type': -1,
    'source': -1,
    'analyzers':-1,
    'title': -1, 
    'body': -1,
    'page_title':-1, 
    'meta_keywords':-1, 
    'meta_description':-1,
    'url': -1,
    'page': -1,
    'body_input_filter': -1,
    'hidden': -1,    
    'code': Drupal.settings.contentanalysis.code,
    'action': -1
  };
  if(analyzer_override) {
    data.action = 'refresh';
  }
  if ($('#contentanalysis-page-analyzer-form').html()) {
    data.source = 'admin-form';
    data.body = $('[name=input]').val()
    data.nid = $('[name=input_nid]').val()
    data.url = $('[name=input_url]').val()
    if(data.body == '') {
      data.body = -1;
    }
    if(data.nid == '') {
      data.nid = -1;
    }
    if(data.url == '') {
      data.url = -1;
    }    
  } else if ($('#node-form').html()) {
    data.source = 'node-edit-form';
    // Turn off TinyMCE if enabled
    if(typeof mceToggle == 'function') {
      mceToggle('edit-body', 'wysiwyg4body');
    }
    // Turn off CKEditor if any.
    var ckeditor = false;
    if ($('#cke_edit-body').html()) {
      $('#wysiwyg-toggle-edit-body').click();
      ckeditor = true;
    }

    data.title = $('#edit-title').val();
    data.body = $('#edit-body').val();
    data.nid = Drupal.settings.contentanalysis.nid
    data.node_type = Drupal.settings.contentanalysis.node_type
    data.body_input_filter = $("input[name='format']:checked").val(); 
    if($('#edit-page-title').val() != null) {
      data.page_title = $('#edit-page-title').val();
    }
    // check for deprecated nodewords format
    if($('#edit-nodewords-keywords').val() != null) {
      data.meta_keywords = $('#edit-nodewords-keywords').val();
    }
    if($('#edit-nodewords-description').val() != null) {
      data.meta_description = $('#edit-nodewords-description').val();
    }
    // newer nodewords format
    if($('#edit-nodewords-keywords-value').val() != null) {
      data.meta_keywords = $('#edit-nodewords-keywords-value').val();
    }
    if($('#edit-nodewords-description-value').val() != null) {
      data.meta_description = $('#edit-nodewords-description-value').val();
    }
    // newer, newer nodewords format
    if($('#edit-nodewords-metatags-keywords-value').val() != null) {
      data.meta_keywords = $('#edit-nodewords-metatags-keywords-value').val();
    }
    if($('#edit-nodewords-metatags-description-value').val() != null) {
      data.meta_description = $('#edit-nodewords-metatags-description-value').val();
    }
    if($('#edit-path').val() != null) {
      data.url = window.location.host + Drupal.settings.contentanalysis.base_path + $('#edit-path').val();
    }
    // Turn back on tinyMCE
    if(typeof mceToggle == 'function') {
      mceToggle('edit-body', 'wysiwyg4body');
    }	
    // Turn on CKEditor if needed.
    if (ckeditor) {
      $('#wysiwyg-toggle-edit-body').click();
    }

  } else {
    data.source = 'page-link';
    data.page = $('html').html()  
    data.url = window.location.href
  }
  if(Drupal.settings.contentanalysis.hidden != null) {
    data.hidden = Drupal.settings.contentanalysis.hidden;
  }
  
  //alert('data.nid ' + data.nid)
  var analyzers_arr = new Array();
  if(analyzer_override) {
    data.analyzers = analyzer_override;
    analyzers_arr[0] = data.analyzers; 
  }
  else if($('#contentanalysis_analyzers_override input').val() != null) {    
    data.analyzers = $('#contentanalysis_analyzers_override input').val();
    analyzers_arr[0] = data.analyzers;
  } 
  else {
    var i = 0;
    $('#contentanalysis_analyzers .form-checkbox:checked').each ( function () {  
      var expr = new RegExp(/\[[^\]]+\]/);
      analyzers_arr[i] = expr.exec($(this).attr('name'))[0].replace(']', '').replace('[','');    
      i++;
    })
    data.analyzers = analyzers_arr.join(',');
  }
  // call contentanalysis_data for enabed analyzers
  for(var i in analyzers_arr) {
    var aid = analyzers_arr[i];
    var module = Drupal.settings.contentanalysis.analyzer_modules[aid].module;
    if (eval('typeof ' + module + '_contentanalysis_data == "function"')) {
      d = eval(module + '_contentanalysis_data')(aid, data);
      for(var k in d) {
        eval('data.ao_'+aid+'_'+k+' = "'+d[k]+'";');
      }
    }
  }  
  $('#contentanalysis-buttons').hide();  
  $.ajax({
    type: 'POST',
    url: Drupal.settings.contentanalysis.analyze_callback,
    data: data,
    dataType: 'json',
    success: function(data, textStatus) {
      analyzers_arr = data.inputs['analyzers'].split(",");
      if(Drupal.settings.contentanalysis.display_dialog == 1) {
        $('#analysis-modal').append(data.main['output']);
        $('#analysis-modal .progress').remove();
        Drupal.behaviors.contentanalysisui();
      }
      // display inline if enabled
      if(Drupal.settings.contentanalysis.display_inline == 1) {
        if(data.inputs['action'] == 'refresh') {
          //if($('.contentanalysis_section_analysis').length > 0)
          //for(i in analyzers_arr) {
            aid = analyzers_arr[0];
            $('#contentanalysis-report-'+aid+'-page_title').replaceWith(data.page_title['output']);
            $('#contentanalysis-report-'+aid+'-body').replaceWith(data.body['output']);
            $('#contentanalysis-report-'+aid+'-meta_description').replaceWith(data.meta_description['output']);
            $('#contentanalysis-report-'+aid+'-meta_keywords').replaceWith(data.meta_keywords['output']);
          //}
        }
        else {
          if($('#edit-page-title-wrapper').length > 0) {
            $('#edit-page-title-wrapper > .contentanalysis_section_analysis').remove();
            $('#edit-page-title-wrapper').append(data.page_title['output']);
          } else {
            $('#edit-title-wrapper > .contentanalysis_section_analysis').remove();
            $('#edit-title-wrapper').append(data.page_title['output']);				
          }
    
          $('#edit-body-wrapper > .contentanalysis_section_analysis').remove();
          $('#edit-body-wrapper').append(data.body['output']);
          // check newer nodewords format
          if(($('#edit-nodewords-description-value-wrapper').length > 0) && data.meta_description != null) {
            $('#edit-nodewords-description-value-wrapper > .contentanalysis_section_analysis').remove();
            $('#edit-nodewords-description-value-wrapper').append(data.meta_description['output']);
          }
          
          if(($('#edit-nodewords-keywords-value-wrapper').length > 0) && data.meta_keywords != null) {
            $('#edit-nodewords-keywords-value-wrapper > .contentanalysis_section_analysis').remove();
            $('#edit-nodewords-keywords-value-wrapper').append(data.meta_keywords['output']);
          }
          // check newer, newer nodewords format
          if(($('#edit-nodewords-metatags-description-value-wrapper').length > 0) && data.meta_description != null) {
              $('#edit-nodewords-metatags-description-value-wrapper > .contentanalysis_section_analysis').remove();
              $('#edit-nodewords-metatags-description-value-wrapper').append(data.meta_description['output']);
            }
            
            if(($('#edit-nodewords-metatags-keywords-value-wrapper').length > 0) && data.meta_keywords != null) {
              $('#edit-nodewords-metatags-keywords-value-wrapper > .contentanalysis_section_analysis').remove();
              $('#edit-nodewords-metatags-keywords-value-wrapper').append(data.meta_keywords['output']);
            }
          
        }
        for(var i in analyzers_arr) {
          var aid = analyzers_arr[i];
          h = '<a href="#" class="contentanalysis-refresh-link-' + aid + '" onclick="contentanalysis_refresh_analysis(\'' + aid + '\'); return false;">';
          h += '<img src="' + Drupal.settings.contentanalysis.path_to_module + '/icons/refresh.png" alt="refresh" />';
          h += '</a>';
          $('.contentanalysis-report-' + aid + ' label').append(h);
        } 
			}      
      // call any modules post analysis hooks      
      for(var i in analyzers_arr) {
        var aid = analyzers_arr[i];        
        var module = Drupal.settings.contentanalysis.analyzer_modules[aid].module;     
        
        if (eval('typeof ' + module + '_contentanalysis_analysis_success == "function"')) {
          eval(module + '_contentanalysis_analysis_success')(aid, data);
        }
      } 
      if(typeof Drupal.behaviors.collapse == 'function') {
    	  Drupal.behaviors.collapse();  
      }
      $('.ahah-progress-throbber').remove();
      $('#contentanalysis-buttons').show();
    },
    error: function(XMLHttpRequest, textStatus, errorThrown) {
      alert("error " + errorThrown.toString());
      $('.ahah-progress-throbber').remove();
      $('#contentanalysis-buttons').show();
    }
  });
  return false;	
}
