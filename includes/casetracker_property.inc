<?php

/**
 * 
 */
class casetracker_property {

  /**
   * Set all the attributes on the property.
   */
  function set($p) {
    foreach ($p as $k => $v) {
      $this->{$k} = $v;
    }
  }

  function setting_form(&$form) {}

  function option_form(&$form, $node) {}
  
  function save(&$record, $current, $exits) {}

  /**
   * 
   */
  function display($info) {
    return '<span class="' . $this->id. '">' . $this->name . ': <strong>'. check_plain($info[$this->id]['value']) . '</strong></span>';
  }
}