<?php
// $Id$

/**
 * @file
 *   A way to export books with Node Export
 */

// Remove once http://drupal.org/node/858274 is resolved.
if (!function_exists('uuid_set_uuid')) {
  /**
   * API function to set the UUID of an object based on its serial ID.
   *
   * @param $table
   *   Base table of the object. Currently, one of node, revision_revisions,
   *   users, vocabulary or term_data.
   * @param $key
   *   The name of the serial ID column.
   * @param $serial_id
   *   The serial ID of the object.
   * @param $uuid
   *   Optional UUID.  If omitted, a UUID will be generated.
   * @return
   *   The UUID on success, FALSE if the uuid provided is not valid.
   */
  function uuid_set_uuid($table, $key, $serial_id, $uuid = FALSE) {
    if (empty($uuid)) {
      $uuid = uuid_uuid();
    }

    if (!uuid_is_valid($uuid)) {
      return FALSE;
    }

    $uuid_table = 'uuid_'. $table;

    db_query('START TRANSACTION'); // Added for use in node_export_book so that the UUIDs actually appear in the node object when exporting
    db_query("UPDATE {". $uuid_table ."} SET uuid = '%s' WHERE ". $key ." = %d", $uuid, $serial_id);
    if (!db_affected_rows()) {
      @db_query("INSERT INTO {". $uuid_table ."} (". $key .", uuid) VALUES (%d, '%s')", $serial_id, $uuid);
    }
    db_query('COMMIT'); // Added for use in node_export_book so that the UUIDs actually appear in the node object when exporting

    return $uuid;
  }
}

// Remove once http://drupal.org/node/858274 is resolved.
if (!function_exists('uuid_get_uuid')) {
  /**
   * API function to get the UUID of an object based on its serial ID.
   *
   * @param $table
   *   Base table of the object. Currently, one of node, revision_revisions,
   *   users, vocabulary or term_data.
   * @param $key
   *   The name of the serial ID column.
   * @param $id
   *   The serial ID of the object.
   * @return
   *   The UUID of the object, or FALSE if not found.
   */
  function uuid_get_uuid($table, $key, $id) {
    $uuid_table = 'uuid_'. $table;
    return db_result(db_query("SELECT uuid FROM {{$uuid_table}} WHERE $key = %d", $id));
  }
}
