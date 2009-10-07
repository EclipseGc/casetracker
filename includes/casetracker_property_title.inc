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
       // Conveniently we can update node.title and have all 'node' listing in
       // views pull from it without disrupting the normal happenings of 
       // node_load which will pull from the node_revisions table.
      db_query("UPDATE {node} SET title = '%s'", $record['value']);
    }
  }

  /**
   * 
   */
  function display($info) {
    return '<span class="' . $this->id. '">' . check_plain($info[$this->id]->value) . '</span>';
  }
}