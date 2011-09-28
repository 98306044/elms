ELMS: OG Clone - Clone groups and all associated content / settings
Copyright (C) 2011  The Pennsylvania State University

Bryan Ollendyke
bto108@psu.edu

Keith D. Bailey
kdb163@psu.edu

12 Borland
University Park, PA 16802
=================================
Spaces Issue / Patch:
There is currently a known issue with spaces where they activate whenever a node is loaded.  
This is great except for the use-case of loading a node in order to copy / clone it to a new location.  
In creating the node it will indefinitely be tied to the original group that created it unless this patch is applied.

Setup and Installation
1.) Download and add to sites/all/modules

2.) Patch Spaces 
If you are using purl / spaces (for example, with OpenAtrium), in order for og_clone to work, 
you will need to go to line 148 of spaces/spaces_og/plugins/space_og.inc and replace: 

spaces_load('og', current($node->og_groups))->activate();

with the following:

//PATCH to work with elms / og_clone
if (arg(0) != 'og_clone') {
  spaces_load('og', current($node->og_groups))->activate();
}

3.) Enable module and adjust permission for "Clone Groups"
4.) Navigate to the group you wish to clone site-name.com/group-name and go to site-name.com/group-name/og_clone
5.) Select features from which content and from which roles you wish to clone, 
    set user who will be author of new nodes, and clone!  