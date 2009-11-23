<?php
// $Id$

/**
 *
 */
class casetracker_views_handler_field_case extends views_handler_field {

  /**
   *
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
   *
   */
  function pre_query() {
    $this->view->field += $this->casetracker_fields;
  }
}
