ELMS: Outline Designer - Usability improvements for rapid book outline creation
Copyright (C) 2008-2011  The Pennsylvania State University

Bryan Ollendyke
bto108@psu.edu

Keith D. Bailey
kdb163@psu.edu

12 Borland
University Park, PA 16802

REQUIREMENTS
*This module requires that you have Book enabled

OPTIONAL
*The Organic Groups add on requires og be installed
*Outline Child Pages will integrate with Book Manager or work stand alone

INSTALLATION
*Place the outline_designer directory in the correct modules folder as you would any other Drupal module
*Activate the module
*Activate the sub-modules (outline_child_pages is highly recommended though it is optional)
*Go to admin/content/book/outline_designer and configure your icons
*Go to admin/content/book/settings to enable / disable content types from outlining and set default type
*Go to admin/content/book and click "edit order and titles" to access the outline designer interface.

OPTIONAL INSTALLATION
*There is an organic groups integration helper module.  Activating it will add a "edit Books" tab to the group home page for group admins.  Group admins can now edit books owned by their group without needing the administer book privilege
*There is an outline child pages module added as of 1.3.  Outline Child Pages can add either a tab or link to nodes that have child pages, allowing you to use the outline designer to reorder JUST the children of the current node.  This can have great benefit when attempting to outline large book structures when you only want to focus on a part of the outline.  Additionally, this module can be used to give users the ability to outline book content that they own by checking that they have the new permission, and can add content to books, and have the ability to update the current node.

PERMISSIONS
The outline designer is fully compatible with the permissions designated by your Drupal site. To access outline designer:

By itself -- Requires 'admin book outlines' permission
w/ outline_designer_og -- requires admin book outlines OR that you are a group admin
w/ just outline_child_pages -- requires admin book outline OR that you are a group admin OR that you have the following three permissions combined:
** new 'outline own pages' permission
** 'add content to books' permission
** have access to update / edit the node you are currently viewing
(If you meet the three criteria you will be allowed to use the outline designer though it will still check for permissions on each action as it always does)

w/ outline_child_pages and book_manager -- requires 'add content to personal books' permission

COMPATIBILITY
No known issues
*Firefox 2+
*Safari 4+
*Chrome
*Opera 10
*IE 7/8

Major Issues
*IE 6 and lower - JS error on load and won't work