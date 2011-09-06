ELMS ICMS Distribution Alpha 4
Copyright (C) 2011  The Pennsylvania State University

Bryan Ollendyke
bto108@psu.edu

Keith D. Bailey
kdb163@psu.edu

12 Borland
University Park,  PA 16802

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License,  or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not,  write to the Free Software Foundation,  Inc.,
51 Franklin Street,  Fifth Floor,  Boston,  MA 02110-1301 USA.

ELMS ICMS Alpha 4 is built on top of the Drupal CMS.  It is currently not production ready but is getting very close.  The features of this system are starting to be fully ironed out as discussions progress.  Modules and Libraries used as part of this distribution are licensed according to their local LICENSE / README files.  If you are interested in joining efforts in development please email elms@psu.edu.

------------
INSTALLATION
------------
*Download the ELMS ICMS Alpha 4 distribution from https://drupal.psu.edu/
*Unzip and go to the install.php page from a web-browser as you normally would when installing Drupal
*Copy and rename /elms_icms/sites/default/default.settings.php to settings.php
*Select ELMS ICMS radio bubble and run through the typical Drupal installation
*You are now running ELMS ICMS Alpha 4, enjoy making courses!
*Some sample course versions have been created to help visualize what's possible!

------------
Known issues
------------
*The workflow for promoting Versions of Courses to Offerings / demo sites / archived spaces hasn't been worked out fully
*Some usability hiccups on different forms
*Pages 5 and 6 of the Course Version form are there for demonstration of future functionality
*Link Checker has not been implemented, a place holder link is there
*HTML Export will produce nearly perfect files but doesn't download them, a way of tar'ing / zipping them needs to be added in
*Node Import for moving books of material into ELMS has been removed for the time being until we have a clear way of doing this
*Certain pages (such as automated version creation after creating a Course Space) can take a long time and need Batch API implemented
*There are certain admin pages where Batch Jobs (Drupal displays the progress bar to do something) will throw an error. This is still being investigated
*There is no automated method of user management and getting students imported at this time, that API is being worked on either for Alpha 5 or when we move to a Beta

