<?php

/**
 * Base handler for views based properties.
 */
class casetracker_views_property extends casetracker_property {
  
  function setting_form(&$form, $base_table = null) {
    parent::setting_form($form);
    $form['view'] = array(
      '#type' => 'select',
      '#title' => t('View'),
      '#options' => $this->views_options($base_table),
      '#default_value' => $this->view,
    );
    // TODO default value via AJAX
    $form['default_value'] = array(
      '#type' => 'select',
      '#title' => t('Default value'),
      '#options' => $this->options($this->view),
      '#default_value' => $this->default_value
    );
  }
  
  /**
   * Retreive a list of views that could be used to generate options.
   */
  function views_options($base_table, $reset = true) {
    static $type_cache;
    if (!isset($type_cache) || $reset) {
      $all_views = views_get_all_views();
      foreach($all_views as $view) {
        $type_cache[$view->base_table][$view->name] = $view->name;
        $type_cache['all'][$view->name] = $view->name;
      }
    }
    if ($base_table) {
      return $type_cache[$base_table];
    }
    return $type_cache['all'];
  }
  
  /**
   * API function that returns valid user options.
   */
  function options($view_name) {
    $users = array();
    $options = array();
    if ($view = views_get_view($view_name)) {
      $view->set_display();
      $view->set_items_per_page(0);
      $view->execute();

      foreach($view->field as $v) {
        if (!$v->options['exclude']) {
          $field = $v;
          break;
        }
      }

      foreach ($view->result as $row) {
        $options[$row->{$view->base_field}] = $row->{$field->field_alias};
      }
    }
    return $options;
  }
  
  /**
   * 
   */
  function option_form(&$form, $node) {
    $form[$this->property->id] = array(
      '#type' => 'select',
      '#title' => $this->name,
      '#options' => $this->options($this->view),
      '#default_value' => isset($node->casetracker->{$this->id}) ? null : $node->casetracker->{$this->id},
    );
  }

}
