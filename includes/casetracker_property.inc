<?php

/**
 * Base class for casetracker properties.
 */
class casetracker_property {

  /**
   * Set all the attributes on the property. 
   */
  function __construct($p) {
    foreach ($p as $k => $v) {
      $this->{$k} = $v;
    }
  }

  /**
   * Provide the administrative setting form. By default we include some info
   * about how this property should interact with views.
   */
  function setting_form(&$form) {
    $form['views'] = array('#parent' => true);
    $form['views']['display'] = array(
      '#title' => t('Display in table listings'),
      '#type' => 'checkbox',
      '#default_value' => $this->views['display'],
    );
    $form['views']['filter'] = array(
      '#title' => t('Display in filtering options'),
      '#type' => 'checkbox',
      '#default_value' => $this->views['filter'],
    );
  }

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
   * 
   * @param $info
   *  An array of state changes.
   *
   * @param $delta
   *  Boolean indicating whether to show what the update changed or just the 
   *  final status of the update.
   */
  function display($info, $delta) {
    $output = '<span class="' . $this->id. '">' . check_plain($info[$this->id]->value) . '</span>';
    if ($delta) {
      $output = '<span class="' . $this->id. '">' . check_plain($info[$this->id]->previous_value) . '</span> >> ' . $output;
    }
    return $output;
  }

  /**
   * Let the field add itself to a view that's being built.
   *
   * @param $field
   *  The field object, by reference.
   */
  function view_init(&$view, $field, $options) {
    $handler = views_get_handler('casetracker_update_property', 'value', 'field');
    if ($handler) {
      $handler->init($view, $options);
      return $handler;
    }
  }
}
