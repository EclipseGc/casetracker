<?php

/**
 * 
 */
class casetracker_property_user extends casetracker_views_property {

  function setting_form(&$form, $property) {
    parent::setting_form(&$form, $property, 'users');
  }

  function option_form(&$form, $property) {
    $form['default'] = array(
      '#type' => 'select',
      '#title' => t('Default value'),
      // '#options' => casetracker_realm_load($property->realm),
      '#default_value' => $property->value,
    );
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
