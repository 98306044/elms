<?php

/**
 * Retrieve a user record from the remote db
 *
 * @param int $userid - LMS user id
 * @param string $email - LMS email address to search
 * @param string $username - LMS username
 *
 * All params are optional, but if supplied, must match existing account
 */
function remote_login_get_remote_user($userid = NULL, $email = NULL, $username = NULL) {
  $sql = "SELECT * FROM users WHERE ";
  $args = $srch = array();
  if ($username) {
    $srch[] = "username = md5('%s') ";
    $args[] = $username;
  }
  if ($email) {
    $srch[] = "useremail = '%s' ";
    $args[] = $email;
  }
  if ($userid) {
    $srch[] = "userid = %d ";
    $args[] = $userid;
  }
  if (!$username && !$email && !$userid) {
    return false;
  }
  db_set_active('remote');
  $result = db_query($sql . implode('AND ', $srch), $args);
  $row = db_fetch_array($result);
  db_set_active('default');
  return $row;
}

/**
 * Create a new user record in remote db
 */
function remote_login_create_remote_user(&$account) {
  $update = array(
    'uid' => $account->uid,
    'profile_fname' => $account->profile_fname,
    'profile_lname' => $account->profile_lname,
    'profile_position' => $account->profile_position,
    'profile_phone' => $account->profile_phone,
  );
  // check for existing LMS user first...
  if ($remote_user = remote_login_get_remote_user($account->profile_lms_id, $account->profile_email)){
    watchdog('ats', 'Remote user !userid found for !name, not creating.', array('!userid'=>$remote_user['userid'],'!name'=>$account->name));
    if (empty ($account->profile_lms_id)){
      $account->profile_lms_id = $update['profile_lms_id'] = $remote_user['userid'];
      user_save($account, $update, 'details');
      return;
    }
  }
  db_set_active('remote');
  $date = date('Y-m-d H:i:s');
  db_query(
    "INSERT INTO users (username, userpass, useremail, userlevel, grpsuper, userfreetrial, userscec, userfname, userlname, userpos, usertel, userhiredate, usertrialstdate) ".
    "VALUES ('%s', '%s', '%s', 1, 'false', 'false', 'false', '%s', '%s', '%s', '%s', '%s','%s') ",
    md5($account->name), $account->pass, $account->mail, $account->profile_fname, $account->profile_lname, $account->profile_position, $account->profile_phone, $date, $date
  );
  $userid = db_last_insert_id('users', 'userid');
  db_set_active('default');
  $account->profile_lms_id = $update['profile_lms_id'] = $userid;
  user_save($account, $update, 'details');
  watchdog('ats', 'Remote user !userid created for !name', array('!userid'=>$userid,'!name'=>$account->name));
}

/**
 * Update a user's expiration date in the remote db
 * User should have correct expiration currently set in drupal
 *
 * called by CA action on group node publish
 */
function remote_login_update_remote_expiration($account) {
  $existing_role = db_fetch_object(db_query("SELECT * FROM {uc_roles_expirations} WHERE uid = %d ", $account->uid));
  $expiration = false;
  if ($existing_role){
    $expiration = $existing_role->expiration;
  } 
  if ($expiration) {
    // convert into datetime
    $date = date('Y-m-d H:i:s', $expiration);
    $user_row = remote_login_get_remote_user($account->profile_lms_id, $account->mail);
    watchdog('ats', 'Updating subscription end in LMS for user '.$account->name." to $date from ".$user_row['usersubend'].'. User id: '.$user_row['userid']);
    db_set_active('remote');
    db_query("UPDATE users SET usersubend = '%s' WHERE userid = %d", $date, $user_row['userid']);
    db_set_active('default');
  }
}

/**
 * Called by rule when group node is published
 *
 * If a group is associated with an order, find the order uid and set supervisor status to match group
 */
function remote_login_create_remote_group(&$node) {

    watchdog ('ats-debug', 'inside remote login create remote group  function nid  ' . $node->nid );
    
  //dpm($node);
  
  /* If no remote group key, create a remote group. */
  if (!$node->field_group_grpid[0]['value'] || $node->field_group_grpid[0]['value'] = 0) {
    
    
    // we need to set the grou plan (number of hours from product purchased) into the remote db
    // this plan is best determined from the prodcut sku, which is dynamic based on their selection
    
    if ($node->uc_order_product_id){
        // get the product
        $prod_id = $node->uc_order_product_id;       

        //check to see if we have a product associated with it
        $product = uc_node_checkout_load_order_product($prod_id);
        
        //dpm($product);
        
        if (strpos($product->model,'12HR')){
          $gplan = 12;
        } elseif (strpos($product->model,'20HR')) {
          $gplan = 20;
        } elseif (strpos($product->model,'30HR')) {
          $gplan = 30;
        } elseif (strpos($product->model,'UNL')) {
          $gplan = -1;     
        }
        
        
    } else {
        // no product, so this is probably a manual group
        
        // check to see if unlimited is checked, otherwise leave the plan blank
        if ($node->field_group_unlimited[0]['value'] == 1) {
           $gplan = -1; 
        } else {
           $gplan = ''; 
        }
        
    }

      watchdog ('ats-debug', 'inside remote login create remote group  function nid  ' . $node->nid  . ' product model ' . $product->model . ' gplan: ' . $gplan);
    
    db_set_active('remote');
    
    db_query(
      "INSERT INTO _group (grpname, grpnote, grpcode, grpplan) VALUES ('%s', '', '%s', '%s') ",
      $node->title, $node->field_group_code[0]['value'], $gplan
    );

    $grpid = db_last_insert_id('_group', 'grpid');
    
    watchdog('ats','Inserted new remote group into LMS.  Group ID: ' . $grpid . ' - hours:  ' . $gplan);
     
    db_set_active('default');
    $node->field_group_grpid[0] = array('value'=> $grpid);
    node_save($node);
  }
  /* If group node created from an order, set user and customer as appropriate. */
  if ($node->uc_order_product_id){

      watchdog ('ats-debug', 'inside remote login create remote group  function nid  ' . $node->nid . ' in if node->uc_order_product_id' );


    $owner = user_load($node->uid);
    uc_roles_grant($owner, 17, null, true, true); // grant supervisor role to group owner
    $remote_user = ats_group_ensure_user_exists($owner);
    db_set_active('remote');
    $user_level = $remote_user['userlevel'] > 1 ? $remote_user['userlevel'] : 2 ;
    db_query(
      "UPDATE users SET grpcode = '%s', grpid = %d, grpsuper = 'true', userlevel = %d WHERE userid = %d ",
      $node->field_group_code[0]['value'], $node->field_group_grpid[0]['value'], $user_level, $remote_user['userid']
    );
    db_set_active('default');
    
    //create the customer node locally and remotely if this was an order    
    remote_login_create_customer($node);
  }
  
}

/**
 * Called by rule when group node is published
 */
function remote_login_create_customer(&$groupnode) {

    watchdog ('ats-debug', 'inside remote login create customer  function groupnode nid  ' . $groupnode->nid );


    // Add user to LMS customer table
  if ($groupnode->type == 'group' && !$groupnode->field_group_customer[0]['nid'] && $groupnode->uc_order_product_id) {
    $order_product = uc_node_checkout_load_order_product($groupnode->uc_order_product_id);
    $order = uc_order_load($order_product->order_id);
    
    $c_node = new stdClass;
    // get order from group node
		//@changed -- commented out old way to try new
    //$name = $order->billing_company ? $order->billing_company : $groupnode->title;
		$name = $groupnode->title;
    $contact = $order->billing_first_name .' '. $order->billing_last_name;
    $user = user_load($groupnode->uid);
    $email = $user->mail;
    if (strpos($order_product->model,'6MO')){
      $sublen = '183';
    } elseif (strpos($order_product->model,'12MO')) {
      $sublen = '365';
    } elseif (strpos($order_product->model,'3MO')) {
      $sublen = '90';
    } else {
      $sublen = '30';
    }
    $expires = strtotime('+ '. $sublen.' days');

      watchdog ('ats-debug', 'inside remote login create customer  function groupnode nid  ' . $groupnode->nid . ' $expires: ' . $expires );
    
    $c_node->type = 'customer';
    $c_node->title = $name;
    $c_node->uid = 1;
    $c_node->name = 'admin';
    $c_node->comment = 0;
    $c_node->status = 1;
    $c_node->field_c_custcont[0]['value'] = $contact;
    $c_node->field_c_custemail[0]['value'] = $email;
    $c_node->field_c_custtel[0]['value'] = $order->billing_phone;
    $c_node->field_c_custaddr[0]['value'] = $order->billing_street1;
    $c_node->field_c_custcity[0]['value'] = $order->billing_city;
    $c_node->field_c_custstate[0]['value'] = uc_zone_get_by_id($order->billing_zone);
    $c_node->field_c_custzip[0]['value'] = $order->billing_postal_code;
    $c_node->field_group_count[0] = array('value'=>$order_product->qty);
    $c_node->field_c_custsublen[0]['value'] = $sublen; //default to 90 days?
    $c_node->field_c_expiration[0]['value'] = $expires;
    remote_login_update_customer($c_node);
    watchdog('ats','Saved new customer !nid', array('!nid'=>$c_node->nid));
    $groupnode->field_group_customer[0]['nid'] = $c_node->nid;
    node_save($groupnode);
  }
}


function remote_login_update_customer(&$node) {


    watchdog ('ats-debug', 'inside remote login update customer function nid  ' . $node->nid );

  $save_node = FALSE;
  db_set_active('remote');
  if (empty($node->field_c_custid[0]['value'])) {
    db_query("INSERT INTO customer (custname) VALUES ('%s')", $node->title);
    $node->field_c_custid[0]['value'] = db_last_insert_id('customer', 'custid');
    $save_node = TRUE;

      watchdog ('ats-debug', 'inside remote login update customer function nid  ' . $node->nid  . ' inserted customer into remote db');
  }
  db_query(
    "UPDATE customer set custname = '%s', custcont = '%s', custemail = '%s', custtel = '%s', custext = '%s', custfax = '%s', ".
    "custaddr = '%s', custcity = '%s', custst = '%s', custzip = '%s', custsublen = '%s' ".
    "WHERE custid = %d ",
    $node->title, $node->field_c_custcont[0]['value'], $node->field_c_custemail[0]['value'],
    $node->field_c_custtel[0]['value'], $node->field_c_custext[0]['value'], $node->field_c_custfax[0]['value'], $node->field_c_custaddr[0]['value'],
    $node->field_c_custcity[0]['value'], $node->field_c_custst[0]['value'], $node->field_c_custzip[0]['value'],
    $node->field_c_custsublen[0]['value'],
    $node->field_c_custid[0]['value']
  );
  db_set_active('default');
  if ($save_node) {
    node_save($node);
  }
}

// update remote group
function remote_login_update_group($node) {

    //watchdog ('ats-debug', 'inside remote login update group function nid  ' . $node->nid );
  // skip nodes just imported by drush
  if (!$node->ats_group && $grpid = $node->field_group_grpid[0]['value']){
    $customer = node_load($node->field_group_customer[0]['nid']);
     // watchdog ('ats-debug', 'inside remote login update group function nid  ' . $node->nid . ' customer nid: ' . $customer->nid);
    $custid = $customer ? $customer->field_c_custid[0]['value'] : 0;
    // update fields:
    $qry = "UPDATE _group SET grpname = '%s', grpnote = '%s', grpcode = '%s', custid = %d WHERE grpid = %d";
    db_set_active('remote');
    db_query($qry, $node->title, $node->body, $node->field_group_code[0]['value'], $custid, $grpid);
    $grpcount = db_result(db_query(
      "SELECT count(useremail) FROM users WHERE grpid = '%s' AND userlevel = 1",
      $grpid
    ));
    db_set_active('default');
    $count = 0;
    foreach ($node->field_group_members as $mem){
      if ($mem['uid']) {
        // skip null values
        $count++;
      }
    }
    $count = ($count >= $grpcount) ? $count : $grpcount;
    if ($count != $node->field_group_used[0]['value']) {
      $node->field_group_used[0]['value'] = $count;
      node_save($node);
      remote_login_update_customer_used($customer);
    }
  }
  
}

/**
 * Add up all the group counts belonging to a customer, and save.
 */
function remote_login_update_customer_used(&$customer) {
  $qry = "SELECT sum(u.field_group_used_value) FROM node n
    INNER JOIN content_type_group g ON n.vid = g.vid
    INNER JOIN content_field_group_used u ON n.vid = u.vid
    WHERE g.field_group_customer_nid = %d";
  $count = db_result(db_query($qry, $customer->nid));
  if ($count != $customer->field_group_used[0]['value']){
    $customer->field_group_used[0]['value'] = $count;
    node_save($customer);
  }
}

/**
 * Make sure user has correct userlevel in remote db
 * based on drupal roles
 */
function remote_login_user_synch_roles($user) {
  $roles = $user->roles;
  $user_level = 1;
  foreach ($roles as $role) {
    if (stripos($role, 'supervisor') > -1) {
      $user_level = 2;
    }
  }
  $remote_user = remote_login_get_remote_user(NULL, $user->mail);
  if ($remote_user) {
    if ($user_level > $remote_user['userlevel']) {
      db_set_active('remote');
      db_query("UPDATE users SET userlevel = %d WHERE userid = %d", $user_level, $remote_user['userid']);
      db_set_active('default');
    }
  }
}

/**
 * Update user's password in remote db
 */
function remote_login_user_synch_password($account, $newpass = false) {
  $pass = $newpass ? md5($newpass) :  db_result(db_query("SELECT pass FROM {users} WHERE uid = %d", $account->uid));
  $remote_user = remote_login_get_remote_user(NULL, $account->mail);
  if ($remote_user) {
    db_set_active('remote');
    db_query("UPDATE users SET userpass = '%s' WHERE userid = %d", $pass, $remote_user['userid']);
    $err = db_error();
    $num = db_affected_rows();
    db_set_active('default');
    if ($err) {
      watchdog('ats', 'Error attempting to update ATS password.');
    } else {
      watchdog('ats', 'Password for %num users updated. %user updated successfully in ATS.', array('%num'=>$num,'%user'=>$account->name));
    }
  } else {
    watchdog('ats', 'Password for %user not updated at ATS because user does not exist.', array('%user'=>$account->name));
  }
}

function remote_login_user_synch_profile($account) {
  $remote_user = ats_group_ensure_user_exists($account);
  //profile_ddload_profile($account);
  // First name, last name
  if (!empty($account->profile_fname)) {
    $update[] = "userfname = '%s'";
    $data[] = $account->profile_fname;
    $update[] = "usersalut = '%s'";
    $data[] = $account->profile_fname;
  }
  if (!empty($account->profile_lname)) {
    $update[] = "userlname = '%s'";
    $data[] = $account->profile_lname;
  }
  if (!empty($account->profile_position)) {
    $update[] = "userpos = '%s'";
    $data[] = $account->profile_position;
  }
  if (!empty($account->profile_phone)) {
    $update[] = "usertel = '%s'";
    $data[] = $account->profile_phone;
  }
  if (!empty($update)) {
    $data[] = $remote_user['userid'];
    db_set_active('remote');
    db_query(
      "UPDATE users SET ". implode(', ', $update) .
      "WHERE userid = %d ",
      $data
    );
    db_set_active('default');
  }
}

/**
 * Check to see if any user information from remote
 * needs to be updated in drupal
 */
function remote_login_user_synch_remote_data($account) {
  $remote_user = remote_login_get_remote_user(NULL, $account->mail);
  if ($remote_user) {
    // Password changed in remote?
    if ($remote_user['userpass'] != $account->pass) {
      db_query("UPDATE {users} SET pass = '%s' WHERE uid = %d", $remote_user['userpass'], $account->uid);
    }
  }
}

/**
 * Add a user to the LMS individual group
 *
 * Used by CA on node checkout for individual
 */
function remote_login_add_user_individual_group($account) {
  $remote_user = ats_group_ensure_user_exists($account);
  $grpid = variable_get('ats_group_individual', 31);
  db_set_active('remote');
  $grpcode = db_result(db_query(
    "SELECT grpcode FROM _group WHERE grpid = %d ",
    $grpid
  ));
  db_query(
    "UPDATE users SET grpid = %d, grpcode = '%s', grpsuper = 'false', userlevel = 1 ".
    "WHERE userid = %d ",
    $grpid, $grpcode, $remote_user['userid']
  );
  db_set_active('default');
}
