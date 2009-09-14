<?php

/**
* Case meta-data handler for the state/realm system.
*/
class casetracker_property_state {
  function setting_form(&$form, $property) {
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

  function option_form(&$form, $property, $node) {
    $form[$property->id] = array(
      '#type' => 'select',
      '#title' => $property->name,
      '#options' => casetracker_realm_load($property->realm),
      '#default_value' => isset($node->casetracker->{$property->id}) ? null : $node->casetracker->{$property->id},
    );
  }
}

