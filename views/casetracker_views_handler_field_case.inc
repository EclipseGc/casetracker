<?php
// $Id$

/**
 *
 */
class casetracker_views_handler_field_case extends views_handler_field {

  /**
   * The case handler is a meta handler that adds fields for other case
   * elements to a view.
   */
  function init(&$view, $options) {
    $this->casetracker_fields = array();
    $template = casetracker_template_load($this->definition['template']);
    foreach ($template->properties as $property) {
      if ($property->views['display']) {
	$this->casetracker_fields['casetracker_' . $property->id] = $property->view_init($view, $this, $options);
      }
    }
    parent::init(&$view, $options);
  }

  /**
   * Because of how handlers are initialized we have to stash the handlers we
   * add somewhere and then merge them into place later. pre_query() provides a 
   * place to do that after all handers have been initialized but before 
   * anything has beed built.
   *
   * note: handlers we add in this way won't have thier pre_query() method run.
   */
  function pre_query() {
    $this->view->field += $this->casetracker_fields;
  }
}
