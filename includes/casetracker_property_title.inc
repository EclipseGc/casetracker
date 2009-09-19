<?php

/**
 * 
 */
class casetracker_property_title {
  function set($p) {
    $this->property = $p;
  }
  
  function setting_form(&$form) {
    // $form['realm'] = array(
    //   '#type' => 'select',
    //   '#title' => t('Realm'),
    //   '#options' => casetracker_realm_list(),
    //   '#default_value' => $this->property->realm,
    // );
    // // TODO default value via AJAX
    // $form['default_state'] = array(
    //   '#type' => 'select',
    //   '#title' => t('Default value'),
    //   '#options' => casetracker_realm_load($this->property->realm),
    //   '#default_value' => $this->property->default_state,
    // );
  }

  function option_form(&$form, $node) {
    if (isset($node->nid)) {
      $form[$this->property->id] = array(
        '#type' => 'textfield',
        '#title' => $this->property->name,
        '#default_value' => isset($node->casetracker->{$this->property->id}) ? $node->title : $node->casetracker->{$this->property->id},
      );      
    }
  }

  /**
   * 
   */
  function display($info) {
    return '<span class="' . $this->property->id. '">' . $this->property->name . ': <strong>'. check_plain($info[$this->property->id]['meta_id']) . '</strong></span>';
  }
}