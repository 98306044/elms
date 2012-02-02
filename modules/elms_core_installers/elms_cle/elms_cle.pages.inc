<?php

/**
 * Redirect to the book root for this course
 */
function _elms_cle_home() {
  drupal_goto('studio/view');
  return 1;
}
