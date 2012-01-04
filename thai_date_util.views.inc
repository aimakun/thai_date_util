<?php
/**
 * Implementation of hook_views_data_alter()
 */
function thai_date_util_views_data_alter(&$data) {
  // created field
  if (isset($data['node']['created'])) {
    $data['node']['created']['field'] = array(
      'handler' => 'thai_date_util_handler_field_date',
      'click sortable' => TRUE,
    );
  }
  if (isset($data['node']['changed'])) {
    $data['node']['changed']['field'] = array(
      'handler' => 'thai_date_util_handler_field_date',
      'click sortable' => TRUE,
    );
  }
}
/* Failed to render views field
function thai_date_util_views_data() {
  $data['date_container']['table']['group'] = t('Date Container');
  $data['date_container']['table']['join'] = array(
    '#global' => array(),
  );
  
  $data['date_container']['date'] = array(
    'title' => t('Markup'),
    'help' => t('Display custom markup text.'),
    'field' => array(
      'handler' => 'thai_date_util_handler_field_markup',
      'click sortable' => FALSE,
      'notafield' => TRUE,
    ),
  );
  
  return $data;
}
*/

function thai_date_util_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'thai_date_util') .'/includes',
    ),
    'handlers' => array(
      'thai_date_util_handler_field_date' => array(
        'parent' => 'date_handler_field_multiple',
      ),
      /* Failed to render views field
      'thai_date_util_handler_field_markup' => array(
		'parent' => 'views_handler_field',
      ),
      */
    ),
  );
}
