ELMS Distribution Alpha 5
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

ELMS ICMS Alpha 5 is built on top of the Pressflow Distribution.  Pressflow is a performance optimized version of Drupal CMS.  It is very close to production ready as Alpha 5 should be the last release that will be marked Alpha.  The features of this system are still being ironed out as discussions progress.  Modules and Libraries used as part of this distribution are licensed according to their local LICENSE / README files.  If you are interested in joining efforts in development please email elms@psu.edu.

------------
UPGRADE PATH
------------
If you were running Alpha 4 there is no upgrade path to Alpha 5.  Clear out Alpha 4's files and install this release as a fresh install.  There should be an upgrade path from Alpha 5 to Beta 1 but upgrades won't be formally supported until we are in the Beta phase of releases.

------------
INSTALLATION
------------
*Download the ELMS ICMS Alpha 5 distribution from http://drupal.psu.edu/fserver
*Unzip and go to the install.php page from a web-browser as you normally would when installing Drupal
*Select the ELMS radio bubble and run through the typical Drupal installation
*You are now running ELMS ICMS Alpha 5, enjoy making courses!

------------
TROUBLESHOOTING INSTALLATION / SETUP
------------
PHP 5.3
-- Make sure you have error reporting turned off during installation

PHP 5.2
-- There may be a lot of errors after install though it has installed correctly so turning error reporting off is recommended for 5.2 as well

PHP lower then 5.2
-- Unsupported because of date module though you can activate the date 5.2 emulation module and it should work

Solving Drupal White screen of Death
*Try setting the following settings in included .htaccess file:
  php_value memory_limit 128M
* if that doesn't work, remove the php_value part and see if it works otherwise you'll need to change it in the php.ini

Annoying MYSQL max packet error
*run the following command in mysql console: "set global max_allowed_packet = 10 * 1024 * 1024;"
* This error is caused mostly in localhost installs or shared environments and is caused by all the caching of views going on

------------
Known issues
------------
*There are still some admin UIs that need to be built out and more visual user management
*The Studio, Reactions and Schedule Features have not been fully implemented.  The Course Content feature is mostly feature complete at this time.
* There are settings pages for all features but only the Course Content settings page has been partially implemented.  These should be finished for the next release
