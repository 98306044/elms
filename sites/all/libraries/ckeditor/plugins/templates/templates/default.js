/*
Copyright (c) 2003-2010, CKSource - Frederico Knabben. All rights reserved.
For licensing, see LICENSE.html or http://ckeditor.com/license
*/
var template_html = [];
template_html['assignment'] = '<div class="id-assignment"><div class="id-icon-info"></div><h2 class="id-header">Assignment / Activity / Quiz</h2><div class="id-directions">Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...</div></div><br/>';
template_html['collapsed'] = '<fieldset class="collapsible collapsed id-collapse"><legend class="id-collapse-text">Collapse</legend><div class="id-collapse-body">Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...</div></fieldset><br/><br/>';
template_html['collapsible'] = '<fieldset class="collapsible id-collapse"><legend class="id-collapse-text">Collapsible</legend><div class="id-collapse-body">Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...</div></fieldset><br/><br/>';
template_html['fact'] = '<div class="id-fact"><div class="id-icon-info"></div><h2 class="id-header">Fact / Note</h2><div class="id-directions">Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...</div></div><br/>';
template_html['ipsum'] = 'Lorem ipsum dolor sit amet, elit fusce erat, arcu pretium et ultricies velit, parturient faucibus sit dignissim varius, dui nibh ut tellus mauris dolor. Cursus vulputate erat dolore arcu sit egestas, suspendilacus vel in fringilla elit. Fusce tempus ante congue faucibus odio sed, gravida eu libero, elit gravida pede a id varius tempus. Aut massa vel sagittis sed vel donec, et eros. Amet nunc vivamus, gravida suspendisse integer vivamus ligula. Ultrices sociosqu ornare duis, eget tempor quisque.<br/><br/>Vestibulum ut est, wisi velit, nulla sollicitudin morbi. Fermentum non wisi. Magna nec id sit consectetuer vel, montes mauris, scelerisque erat purus etiam nisl erat. Sit ut pulvinar quisque quisque. A ante, odio pharetra urna suspendisse nascetur metus. Dignissim dui nullam adipiscing amet, tincidunt tincidunt turpis. Duis a ipsum aliquam purus orci, in nec vel libero fusce, imperdiet quisque sem, in ac aenean ut, ac dolor scelerisque nibh nam.<br/><br/>Sapien vestibulum turpis, commodo arcu tortor massa faucibus molestie. Litora suspendisse etiam a tortor in. Ultricies fringilla. Hac vulputate donec auctor. Viverra at ultrices et mattis volutpat, aenean interdum nec. Condimentum a et amet quia, mi feugiat in suscipit, aliquet parhendrerit fames hymenaeos vel, quam bibendum et massa donec nunc.<br/>';
template_html['objectives'] = '<div class="id-objectives"><div class="id-objectives-header"><h2>Objectives</h2></div><table class="id-objectives-table"><tbody><tr class="id-row"><td class="id-col1">1</td><td>Review Syllabus</td></tr><tr class="id-row"><td class="id-col1">2</td><td>Read Course E-Text Chapter</td></tr><tr class="id-row"><td class="id-col1">3</td><td>Complete Quiz</td></tr></tbody></table></div><br/>';
template_html['quote'] = '<blockquote class="id-blockquote"><div class="id-blockquote2">Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...</div></blockquote><br/>';
template_html['readings'] = '<div class="id-readings"><h2 class="id-header">Readings</h2><ul><li>Reading 1</li><li>Reading 2</li><li>Reading 3</li></ul></div><br/>';
template_html['steps'] = '<div class="id-stepstocompletion"><div class="id-stepstocompletion-header"><h2>Steps to Completion</h2></div><table class="id-stepstocompletion-table"><th class="id-col1 id-colheading">Step</th><th class="id-col2 id-colheading">Activity</th><th class="id-col3 id-colheading">Directions</th><tr class="id-row"><td class="id-col1">1</td><td>Review Syllabus</td><td><a href="https://cms.psu.edu/">See Angel</a></td></tr><tr class="id-row"><td class="id-col1">2</td><td>Read Course E-Text Chapter</td><td>See Orientation Above</td></tr><tr class="id-row"><td class="id-col1">3</td><td>Complete Quiz</td><td>Download Quiz Directions</td></tr></table></div><br/>';

CKEDITOR.addTemplates('default',{imagesPath:CKEDITOR.getUrl(CKEDITOR.plugins.getPath('templates')+'templates/images/'),templates:[{
  title:'Assignment / Activity / Quiz',
  image:'assignment.png',
  description:'Use this for directing students to pay attention to assignments, activities, and quizes',
  html: template_html['assignment']
  },{
  title:'Collapsed',
  image:'collapsed.png',
  description:'Create a region that can be collapsed and is collapsed by default',
  html: template_html['collapsed']
  },{
  title:'Collapsible',
  image:'collapsible.png',
  description:'Create a region that can be collapsed but is open by default',
  html: template_html['collapsible']
  },{
  title:'Fact / Note',
  image:'fact.png',
  description:'Use this for any facts or notes that you want to stand out from the rest of the material',
  html:template_html['fact']
  },{
  title:'Filler Text (Ipsum)',
  image:'ipsum.png',
  description:'Use this text for laying out a page without content',
  html: template_html['ipsum']
  },{
  title:'Landing Page',
  image:'landingpage.png',
  description:'This is a sample module / unit / lesson landing page',
  html: template_html['ipsum'] + template_html['readings'] + template_html['steps']
  },{
  title:'Objectives',
  image:'objectives.png',
  description:'A table of lesson objectives',
  html: template_html['objectives']
  },{
  title:'Quote',
  image:'quote.png',
  description:'Use this for directing students to pay attention to assignments, activities, and quizes',
  html: template_html['quote']
  },{
  title:'Readings',
  image:'readings.png',
  description:'Use this for communicating Reading lists to students',
  html: template_html['readings']
  },{
  title:'Steps to Completion',
  image:'steps.png',
  description:'Use this for communicating Steps to Completion as well as lesson objectives',
  html:template_html['steps']
  }
  ]});