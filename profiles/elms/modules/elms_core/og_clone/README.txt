ELMS: OG Clone - Clone groups and all associated content / settings
Copyright (C) 2011  The Pennsylvania State University

Bryan Ollendyke
bto108@psu.edu

Keith D. Bailey
kdb163@psu.edu

12 Borland
University Park, PA 16802

Needs a patch to work correctly if you are using purl / spaces

Go to line 148 of spaces/spaces_og/plugins/space_og.inc and replace 

spaces_load('og', current($node->og_groups))->activate();

with the following:

//PATCH to work with elms / og_clone
if (arg(0) != 'og_clone') {
  spaces_load('og', current($node->og_groups))->activate();
}

This is currently a known issue with spaces where they activate whenever a node is loaded.  This is great except for the use-case of loading a node in order to copy / clone it to a new location.  In creating the node it will indefinitely be tied to the original group that created it unless this patch is applied.