<?php

/**
 * 
 */
class casetracker_property_node extends casetracker_views_property {
  function setting_form(&$form) {
    parent::setting_form(&$form, 'node');
  }

  function display($info) {
    // TODO test preview...
    // On node preview the form logic can't translate assign_to back to a uid for
    // us so we need to be able handle it either way.
    // if (is_numeric($case->casetracker->assign_to)) {
      $node = node_load(array('nid' => $info[$this->id]));
    // }
    // else {
    //   $account = user_load(array('name' => $case->casetracker->assign_to));
    // }
    
    return '<span class="' . $this->id. '">' . $this->name . ': <strong>'. check_plain($node->title) . '</strong></span>';
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