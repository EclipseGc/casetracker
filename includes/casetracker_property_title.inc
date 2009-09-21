<?php

/**
 * 
 */
class casetracker_property_title extends casetracker_property {

  function option_form(&$form, $node) {
    if (isset($node->nid)) {
      $form[$this->id] = array(
        '#type' => 'textfield',
        '#title' => $this->name,
        '#default_value' => isset($node->casetracker->{$this->id}) ? $node->title : $node->casetracker->{$this->id},
      );      
    }
  }
  
  /**
   * Update the {node}.title record.
   */
  function save(&$record, $current, $exits) {
    if ($current) {
       // not sure about this, need to check on how view and node modules treat this table.
      db_query("UPDATE {node} SET title = '%s'", $record['value']);
    }
  }

  /**
   * 
   */
  function display($info) {
    return '<span class="' . $this->id. '">' . $this->name . ': <strong>'. check_plain($info[$this->id]) . '</strong></span>';
  }
}