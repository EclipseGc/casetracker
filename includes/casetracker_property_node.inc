<?php

/**
 * 
 */
class casetracker_property_node extends casetracker_views_property {
  function setting_form(&$form, $property) {
    parent::setting_form(&$form, $property, 'node');
  }
}

 //  // project to set as the default is based on how the user got here.
 // if (empty($default_project) && !empty($node->casetracker->pid)) {
 //    $default_project = $node->casetracker->pid;
 //  }
 // 
 //  $project_options = casetracker_project_options();
  // 
  // 
  // 
  // // if there's no project ID from the URL, or more than one project,
  // // we'll create a select menu for the user; otherwise, we'll save
  // // the passed (or only) project ID into a hidden field.
  // if (count($project_options) > 1) {
  //   $form['casetracker']['pid'] = array(
  //     '#title' => t('Project'),
  //     '#type' => 'select',
  //     '#default_value' => $default_project,
  //     '#options' => $project_options,
  //   );
  // }
  // else {
  //   $form['casetracker']['pid'] = array(
  //     '#type' => 'value', // default value, or the only the project ID in the project_options array.
  //     '#value' => !empty($default_project) ? $default_project : key($project_options),
  //   );
  // }