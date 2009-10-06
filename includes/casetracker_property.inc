<?php

/**
 * Base class for casetracker properties.
 */
class casetracker_property {

  /**
   * Set all the attributes on the property. Should be folded into the a
   * constructor at some point.
   */
  function set($p) {
    foreach ($p as $k => $v) {
      $this->{$k} = $v;
    }
  }

  /**
   * Provide the administrative setting form.
   */
  function setting_form(&$form) {}

  /**
   * Provide the setting form to be used when a case is updated.
   */
  function option_form(&$form, $node) {}

  /**
   * Allow for extra action to be taken as a case is saved.
   */
  function save(&$record, $current, $exits) {}

  /**
   * Generate a display for this property.
   */
  function display($info) {
    return '<span class="' . $this->id. '">' . $this->name . ': <strong>'. check_plain($info[$this->id]['value']) . '</strong></span>';
  }
}