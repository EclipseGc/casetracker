<?php

/**
 * 
 */
class casetracker_property_title extends casetracker_property {

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
   * Update the {node}.title record.
   */
  function save(&$record, $current, $exits) {
    if ($current) {
       // not sure about this, need to check on how view and node modules treat this table.
      db_query("UPDATE {node} SET title = '%s'", $record['meta_id']);
    }
  }

  /**
   * 
   */
  function display($info) {
    return '<span class="' . $this->property->id. '">' . $this->property->name . ': <strong>'. check_plain($info[$this->property->id]) . '</strong></span>';
  }
}