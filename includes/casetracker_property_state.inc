<?php

/**
* 
*/
class casetracker_property_state {
  function setting_form(&$form, $property) {
    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => $property->name,
    );
    $form['realm'] = array(
      '#type' => 'select',
      '#title' => t('Realm'),
      '#options' => casetracker_realm_list(),
      '#default_value' => $property->realm,
    );
    // TODO default value via AJAX
    $form['default_state'] = array(
      '#type' => 'select',
      '#title' => t('Default value'),
      '#options' => casetracker_realm_load($property->realm),
      '#default_value' => $property->default_state,
    );
  }

  function option_form(&$form, $property) {
    $form['default'] = array(
      '#type' => 'select',
      '#title' => t('Default value'),
      '#options' => casetracker_realm_load($property->realm),
      '#default_value' => $property->state,
    );
  }
}

