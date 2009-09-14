<?php

/**
 * 
 */
class casetracker_property_user extends casetracker_views_property {

  function setting_form(&$form, $property) {
    parent::setting_form(&$form, $property, 'users');
  }

  /**
   * API function that returns valid user options.
   */
  function options($view_name) {
    $options = parent::options($view_name);

    // fill in anonymous value because view is not rendered and the redundant option in views is irrelevant
    // @TODO render the view before display so this isn't needed.
    $anon_user = variable_get('anonymous', t('Anonymous'));
    if (isset($options[0])) {
      $options[0] = variable_get('casetracker_default_assign_to', $anon_user);
    }
    // if anonymous user is the default assignee, we graft him/her onto the view results here as most views
    // that do any substantive filtering will exclude the anonymous user.
    else if (variable_get('casetracker_default_assign_to', $anon_user) == $anon_user) {
      array_splice($options, 0, 0, array($anon_user));
    }
    return $options;
  }
}

  // // Retrieve the assign_to default value.
  // if (isset($node->casetracker->assign_to)) {
  //   $default_assign_to = is_numeric($node->casetracker->assign_to) ? casetracker_get_name($node->casetracker->assign_to) : $node->casetracker->assign_to;
  // }
  // else {
  //   $default_assign_to = variable_get('casetracker_default_assign_to', variable_get('anonymous', t('Anonymous')));
  // }
  // 
  // $form['casetracker']['assign_to'] = array(
  //   '#title' => t('Assign to'),
  //   '#required' => TRUE,
  // );
  // 
  // // Use different widgets based on the potential assignees.
  // $options = drupal_map_assoc(casetracker_user_options());
  // if (count($options) < 25) {
  //   $form['casetracker']['assign_to']['#type'] = 'radios';
  //   $form['casetracker']['assign_to']['#options'] = $options;
  // }
  // else if (count($options) < 50) {
  //   $form['casetracker']['assign_to']['#type'] = 'select';
  //   $form['casetracker']['assign_to']['#options'] = $options;
  // }
  // else {
  //   $form['casetracker']['assign_to']['#type'] = 'textfield';
  //   $form['casetracker']['assign_to']['#autocomplete_path'] = 'casetracker_autocomplete';
  //   $form['casetracker']['assign_to']['#size'] = 12;
  // }
  // 
  // // Set the default value if it is valid.
  // $form['casetracker']['assign_to']['#default_value'] = in_array($default_assign_to, $options, TRUE) ? $default_assign_to : NULL;
