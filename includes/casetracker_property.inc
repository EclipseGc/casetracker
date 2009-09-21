<?php

/**
 * 
 */
class casetracker_property {
  function set($p) {
    $this->property = $p;
  }
  
  function setting_form(&$form) {}

  function option_form(&$form, $node) {}
  
  function save(&$record, $current, $exits) {}

  /**
   * 
   */
  function display($info) {
    return '<span class="' . $this->property->id. '">' . $this->property->name . ': <strong>'. check_plain($info[$this->property->id]['meta_id']) . '</strong></span>';
  }
}