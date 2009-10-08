<?php

/**
* Case meta-data handler for the state/realm system.
*/
class casetracker_property_state extends casetracker_property {
  
  function setting_form(&$form) {
    $form['realm'] = array(
      '#type' => 'select',
      '#title' => t('Realm'),
      '#options' => casetracker_realm_list(),
      '#default_value' => $this->realm,
    );
    // TODO default value via AJAX
    $form['default_state'] = array(
      '#type' => 'select',
      '#title' => t('Default value'),
      '#options' => casetracker_realm_load($this->realm),
      '#default_value' => $this->default_state,
    );
  }

  function option_form(&$form, $node) {
    $form[$this->id] = array(
      '#type' => 'select',
      '#title' => $this->name,
      '#options' => casetracker_realm_load($this->realm),
      '#default_value' => isset($node->casetracker->{$this->id}) ? $node->casetracker->{$this->id} : null,
    );
  }

  /**
   * 
   */
  function display($info) {
    $state = casetracker_state_load($info[$this->id]->value, $this->realm);
    $output = '<span class="' . $this->realm. '">' . $state->title . '</span>';

    if (!empty($info[$this->id]->previous_reference) && $info[$this->id]->reference != $info[$this->id]->previous_reference) {
      $state = casetracker_state_load($info[$this->id]->previous_value, $this->realm);
      $output .= '>> <span class="' . $this->realm. '">' . $state->title . '</span>';
    }

    return $output;
  }
}

