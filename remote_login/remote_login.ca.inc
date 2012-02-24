<?php

/**
 * Implements hook_ca_action().
 */
function remote_login_ca_action() {
  // Renew a single login in the remote system.
  $actions = array();
  
  // Ensure user exists in the remote system
  $actions['remote_login_ensure_remote_user'] = array(
    '#title' => t('Ensure user exists in remote system'),
    '#category' => t('ats'),
    '#callback' => 'remote_login_action_ensure_remote_user',
    '#arguments' => array(
      'order' => array(
        '#entity' => 'uc_order',
        '#title' => t('Order'),
      ),
    ),
  );
  // Renew expiration dates in remote system
  $actions['remote_login_renew_expiration_dates'] = array(
    '#title' => t('Renew remote expiration dates'),
    '#category' => t('ats'),
    '#callback' => 'remote_login_action_renew_expiration_dates',
    '#arguments' => array(
      'order' => array(
        '#entity' => 'uc_order',
        '#title' => t('Order'),
      )
    ),
  );
  // Set the number of users field on group node checkout products
  $actions['remote_login_set_group_user_count'] = array(
    '#title' => t('Set Group Node Checkout User Count'),
    '#category' => t('ats'),
    '#callback' => 'remote_login_action_set_group_user_count',
    '#arguments' => array(
      'order' => array(
        '#entity' => 'uc_order',
        '#title' => t('Order'),
      )
    )
  );
  // Add user to individual group if only checking out one seat
  $actions['remote_login_add_user_individual'] = array(
    '#title' => t('Add User to Individual Group for checking out one seat'),
    '#category' => t('ats'),
    '#callback' => 'remote_login_action_add_user_individual',
    '#arguments' => array(
      'order' => array(
        '#entity' => 'uc_order',
        '#title' => t('Order'),
      )
    )
  );
  return $actions;
}

/**
 * Active, called by CA
 */
function remote_login_action_add_user_individual($order, $settings) {
  if (!($account = user_load($order->uid))) {
    return;
  }
  if (!empty($order->products)) {
    foreach ($order->products as $product) {
      if ($product->qty == 1 && uc_node_checkout_node_type_association($product->nid)) {
        // This is a node checkout type, but skipped by the user
        // because they only ordered one seat
        // Associate user with individual group in the LMS
        module_load_include('inc', 'remote_login');
        remote_login_add_user_individual_group($account);
        // TODO: Delete ucnc node?
      }
    }
  }
}

function remote_login_action_set_group_user_count($order, $settings) {
  if (!($account = user_load($order->uid))) {
    return;
  }
  // Look for any group node checkout products
  if (!empty($order->products)) {
    foreach ($order->products as $product) {
      if (!empty($product->data['node_checkout_nid'])) {
        $node = node_load($product->data['node_checkout_nid'],null,true);
        if ($node->type == 'group') {
          $node->field_group_count[0]['value'] = $product->qty;
          $node->status = 1;
          node_save($node);
        }
      }
    }
  }
}

function remote_login_action_ensure_remote_user($order, $settings) {
  // Load the order's user and exit if not available
  if (!($account = user_load($order->uid))) {
    return;
  } 
  module_load_include('inc', 'remote_login');
  // Look for remote user by username
  $row = remote_login_get_remote_user(NULL, $account->mail);
  if (!$row) {
    remote_login_create_remote_user($account);
  }
}

/**
 * CA Action - renew remote expiration dates
 *
 * Called when order status is complete
 * Publishes node_checkout nodes
 */
function remote_login_action_renew_expiration_dates($order, $settings) {
  // Load the order's user and exit if not available
  if (!($account = user_load($order->uid))) {
    return;
  }
  if (!empty($order->products)) {
    foreach ($order->products as $product) {
      if (!empty($product->data['node_checkout_nid'])) {
        $checkout_node = node_load($product->data['node_checkout_nid'],null, true); // flush node static cache
        $checkout_node->status = 1;
        node_save($checkout_node);
      }
    }
  }
  module_load_include('inc', 'remote_login');
  remote_login_update_remote_expiration($account);
}

