<?php

/**
 * Implementation of hook_user_default_roles().
 */
function elms_roles_user_default_roles() {
  $roles = array();

  // Exported role: administrator
  $roles['administrator'] = array(
    'name' => 'administrator',
  );

  // Exported role: anonymous user
  $roles['anonymous user'] = array(
    'name' => 'anonymous user',
  );

  // Exported role: authenticated user
  $roles['authenticated user'] = array(
    'name' => 'authenticated user',
  );

  // Exported role: instructional designer
  $roles['instructional designer'] = array(
    'name' => 'instructional designer',
  );

  // Exported role: instructor
  $roles['instructor'] = array(
    'name' => 'instructor',
  );

  // Exported role: staff
  $roles['staff'] = array(
    'name' => 'staff',
  );

  // Exported role: student
  $roles['student'] = array(
    'name' => 'student',
  );

  // Exported role: teaching assistant
  $roles['teaching assistant'] = array(
    'name' => 'teaching assistant',
  );

  return $roles;
}
