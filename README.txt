ELMS Distribution
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

The features of this system are still being ironed out as discussions progress.

Everything in this profile is Liscensed as GPL with the following exception:
-- The Simile timeline library is BSD


If you are interested in joining efforts in development please email elms@psu.edu.

------------
UPGRADE PATH
------------
If you were running Alpha code there is no upgrade path from Alpha to Beta.  Clear out Alpha files and install this release as a fresh install.  Upgrades will be supported between versions of Beta / Release Candidate.

------------
INSTALLATION
------------
*Download the ELMS distribution from http://drupal.psu.edu/fserver
*Unzip and go to the install.php page from a web-browser as you normally would when installing Drupal
*Select the ELMS radio bubble and run through the typical Drupal installation
*Select the core focus, features and optional packages that you'd like to install with ELMS
*You are now running ELMS, enjoy making {what ever your core calls sites}!

------------
TROUBLESHOOTING INSTALLATION / SETUP
------------
PHP > 5.2
-- Unsupported because of date module though you can activate the date 5.2 emulation module and it should work.  This has been installed many times on 5.2 and 5.3 respectively.

Solving Drupal White screen of Death
*Try setting the following settings in included .htaccess file:
  php_value memory_limit 96M or set memory limit per the instructions in the "installing on 1and1"

Installing on 1and1
-- Try making an access file that allows for clean URLS
-- add a php.ini file to the root of the installation with the following in it:
allow_url_fopen = TRUE
memory_limit = 96M
post_max_size = 10M
upload_max_filesize = 10M

Annoying MYSQL max packet error
*run the following command in mysql console: "SET GLOBAL max_allowed_packet=10*1024*1024;"
* This error is caused mostly in localhost installs or shared environments and is caused by all the caching going on.
* Review this page to help resolve it http://drupal.org/node/321210

------------
Known issues
------------
*There are still some admin UIs that need to be built out and more visual user management.  Feeds can be constructed to import users without much of an issue but that is still down the road in our development.
*The Studio, Reactions and Schedule Features have not been fully implemented.  The Course Content feature is mostly feature complete at this time.