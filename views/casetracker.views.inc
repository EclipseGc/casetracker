<?php
// $Id: casetracker.views.inc,v 1.3.2.1 2009/03/02 15:59:54 jmiccolis Exp $

/**
 * Implementation of hook_views_data().
 */
function casetracker_views_data() {
  $types = array_keys(node_get_types('names'));
  $data = array();
  $data['casetracker_case']['table']['group'] = t('Case Tracker');
  $data['casetracker_case']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  foreach ($types as $type) {
    if ($template = casetracker_is_case($type)) {
      $data['casetracker_case']['cuid'] = array(
	'title' => $template,
	'help' => t('Case update information.'),
	'field' => array(
	  'handler' => 'casetracker_views_handler_field_case',
	)
      );
    }
  }

  $data['casetracker_update']['table']['group'] = t('Case Tracker');
  $data['casetracker_update']['table']['base'] = array(
    'field' => 'cuid',
    'title' => t('Case tracker'),
    'help' => t("Updates to cases."),
  );
  $data['casetracker_update']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  foreach ($types as $type) {
    if ($template = casetracker_is_case($type)) {
      $data['casetracker_update']['cuid'] = array(
	'title' => $template,
	'help' => t('Case update information.'),
	'field' => array(
	  'handler' => 'casetracker_views_handler_field_case',
	),
      );
    }
  }

  $data['casetracker_update_property']['table']['join'] = array(
    'casetracker_update' => array(
      'left_field' => 'cuid',
      'field' => 'cuid',
    ),
  );
  $data['casetracker_update_property']['table']['group'] = t('Case Tracker');
  $data['casetracker_update_property']['property'] = array(
    'title' => t('Property'),
    'help' => t('Type of case property'),
    'field' => array('handler' => 'views_handler_field'),
  );
  return $data;
}
 
/**
 * Implementation of hook_views_data_alter().
 */
function casetracker_views_data_alter(&$data) {
  $data['node']['case'] = array(
    'title' => t('Case Tracker case'),
    'help' => t('Whether the node is a casetracker case'),
    'filter' => array(
      'handler' => 'casetracker_views_handler_filter_case',
    ),
  );
  $data['node']['project'] = array(
    'title' => t('Case Tracker project'),
    'help' => t('Whether the node is a casetracker project'),
    'filter' => array(
      'handler' => 'casetracker_views_handler_filter_project',
    ),
  );
}

/**
 * Implementation of hook_views_handlers().
 */
function casetracker_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'casetracker') .'/views',
    ),
    'handlers' => array(
      'casetracker_views_handler_field_case' => array(
	'parent' => 'views_handler_field',
      ),
      // ---------- Fields ----------
      // fields: casetracker_case
      /*
      'casetracker_views_handler_field_project_name' => array(
        'parent' => 'views_handler_field',
      ),
      'casetracker_views_handler_field_user_name' => array(
        'parent' => 'views_handler_field',
      ),
      'casetracker_views_handler_field_priority_name' => array(
        'parent' => 'views_handler_field',
      ),
      'casetracker_views_handler_field_status_name' => array(
        'parent' => 'views_handler_field',
      ),
      'casetracker_views_handler_field_type_name' => array(
        'parent' => 'views_handler_field',
      ),
      'casetracker_views_handler_field_case_count' => array(
        'parent' => 'views_handler_field',
      ),
      */

      // ---------- Filters ----------
      // filters: casetracker_case
      /*
      'casetracker_views_handler_filter_user_options' => array(
        'parent' => 'views_handler_filter_many_to_one',
      ),
      'casetracker_views_handler_filter_priority_options' => array(
        'parent' => 'views_handler_filter_many_to_one',
      ),
      'casetracker_views_handler_filter_status_options' => array(
        'parent' => 'views_handler_filter_many_to_one',
      ),
      'casetracker_views_handler_filter_type_options' => array(
        'parent' => 'views_handler_filter_many_to_one',
      ),
      'casetracker_views_handler_filter_project_options' => array(
        'parent' => 'views_handler_filter_many_to_one',
      ),

      // arguments: casetracker_case
      'casetracker_views_handler_argument_status' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'casetracker_views_handler_argument_priority' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'casetracker_views_handler_argument_type' => array(
        'parent' => 'views_handler_argument_numeric',
      ),

      // filters: casetracker_project
      'casetracker_views_handler_filter_project_published' => array(
        'parent' => 'views_handler_filter_equality',
      ),
      */

      // filters: node-type
      'casetracker_views_handler_filter_case' => array(
        'parent' => 'views_handler_filter',
      ),
      'casetracker_views_handler_filter_project' => array(
        'parent' => 'views_handler_filter',
      )
    ),
  );
}
