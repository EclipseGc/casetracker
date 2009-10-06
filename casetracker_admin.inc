<?php
// $Id: casetracker_admin.inc,v 1.2.2.4 2009/06/12 20:04:45 jmiccolis Exp $

/**
 * Assign case templates to node types.
 */
function casetracker_settings() {
  ctools_include('export');
  $templates = ctools_export_load_object('casetracker_templates', 'all');
  $node_types = node_get_types('names');
  $settings = variable_get('casetracker_case_node_types', array());

  $options = array('' => t('--Disabled--'));
  foreach ($templates as $v) {
    $options[$v->name] = $v->name;
  }

  $form['types'] = array('#tree' => true);
  foreach ($node_types as $k => $v) {
    $form['types'][$k] = array(
      '#type' => 'select',
      '#title' => $v,
      '#options' => $options,
      '#default_value' => $settings[$k],
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Submit handler for casetracker_settings.
 */
function casetracker_settings_submit($form, &$form_state) {
  variable_set('casetracker_case_node_types', $form_state['values']['types']);
}

/**
 * Displays an administrative overview of all case templates available.
 */
function casetracker_templates_page() {
  ctools_include('export');
  $templates = ctools_export_load_object('casetracker_templates', 'all');

  $rows = array(); 
  $headers = array(t('Name'), t('Status'), array('data' => t('Operations'), 'colspan' => 3));
  foreach ($templates as $t) {
    $row = array();
    $row[] = check_plain($t->name);
    $row[] = check_plain($t->type);
    if ($t->in_code_only) {
      $row[] = l(t('clone'), 'admin/settings/casetracker/templates/'. $t->name .'/clone');
      $row[] = l(t('disable'), 'admin/settings/casetracker/templates/'. $t->name .'/disable');
    }
    else {
      $row[] = l(t('edit'), 'admin/settings/casetracker/templates/'. $t->name .'/edit');
      $row[] = l(t('delete'), 'admin/settings/casetracker/templates/'. $t->name .'/delete');
    }
    $row[] = l(t('export'), 'admin/settings/casetracker/templates/'. $t->name .'/export');
    $rows[] = $row;
  }
  return theme('table', $headers, $rows);
}

/**
 * Displays a form for adding or editing a case template.
 */
function casetracker_template_edit($form_state, $template = NULL) {
  $form = array();
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Template name'),
    '#required' => TRUE,
    '#default_value' => isset($template) ? $template->name : NULL,
    '#description' => t('The name for this case template.'),
  );
  $form['properties'] = array('#tree' => true);
  foreach ($template->properties as $i => $p) {
    $element = array('#type' => 'fieldset');
    $element['type'] = array(
      '#type' => 'value',
      '#value' => $p->type,
    );
    $element["remove"] = array(
      '#type' => 'checkbox',
      '#title' => t('Remove'),
    );
   $element['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => $p->name,
    );
    $element['id'] = array(
      '#type' => 'textfield',
      '#title' => t('Id'),
      '#default_value' => $p->id,
    );
    $p->setting_form($element);
    $form['properties'][] = $element;
  }

  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Submit'),
  );

  $form['add'] = array(
    '#tree' => true,
    '#type' => 'fieldset',
  );
  $plugins = ctools_get_plugins('casetracker', 'properties');
  $options = array();
  foreach ($plugins as $k => $v) {
    if (isset($v['title'])) {
      $options[$k] = $v['title'];
    }
  }
  $form['add']['property'] = array(
    '#options' => $options,
    '#type' => 'select',
    '#title' => 'Add property',
  );
  $form['add']['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Add'),
    '#submit' => array('casetracker_property_add_submit'),
  );

  return $form;
}

/**
 * Submit handler for case template editing.
 */
function casetracker_template_edit_submit($form, &$form_state) {
  $record = array('name' => $form_state['values']['name']);
  $record['properties'] = array();
  foreach ($form_state['values']['properties'] as $item) {
    if ($item['remove'] !== 1) {
      unset($item['remove']);
      $record['properties'][] = (object)$item;
    }
  }

  ctools_include('export');
  $templates = ctools_export_load_object('casetracker_templates', 'names', array($record['name']));
  if (
    isset($templates[$record['name']]) && 
    ($templates[$record['name']]->export_type & EXPORT_IN_DATABASE)
  ) {
    drupal_write_record('casetracker_templates', $record, array('name'));
  }
  else {
    drupal_write_record('casetracker_templates', $record);
  }
}

/**
 * Submit handler for adding a property to a case template.
 */
function casetracker_property_add_submit($form, &$form_state) {
  $form_state['values']['properties'][] = array('type' => $form_state['values']['add']['property']);
  casetracker_template_edit_submit($form, $form_state);
}

/**
 * Displays an administrative overview of all case states available.
 */
function casetracker_states() {
  ctools_include('export');
  $states = ctools_export_load_object('casetracker_states', 'all');
  $form = array('#theme' => 'casetracker_states_form');
  $form['states'] = array('#tree' => true);
  foreach ($states as $s) {
    $item = array();
    $item['title'] = array(
      '#value' => $s->title .' ('. $s->name .')',
      '#title' => t('State'),
    );
    $item['realm'] = array(
      '#type' => 'select',
      '#title' => t('Realm'),
      '#options' => casetracker_realm_list(),
      '#default_value' => $s->realm,
      '#attributes' => array('class' => 'realm-select realm-select-'.$s->realm),
    );
    $item['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $s->weight,
      '#attributes' => array('class' => "state-weight state-weight-{$s->realm}"),
    );
    $item['type'] = array(
      '#title' => t('Status'),
      '#value' => $s->type,
    );
    if ($s->in_code_only) {
      $ops = l(t('clone'), 'admin/settings/casetracker/states/'. $s->name .'/clone');
      $ops .= ' | '. l(t('disable'), 'admin/settings/casetracker/states/'. $s->name .'/disable');
    }
    else {
      $ops = l(t('edit'), 'admin/settings/casetracker/states/'. $s->name .'/edit');
      $ops .= ' | '. l(t('delete'), 'admin/settings/casetracker/states/'. $s->name .'/delete');
    }
    $ops .= ' | '. l(t('export'), 'admin/settings/casetracker/states/'. $s->name .'/export');
    $item['operations'] = array('#value' => $ops, '#title' => t('Operations'));

    if (!isset($form['states'][$s->realm])) {
      $form['states'][$s->realm] = array();
    }
    $form['states'][$s->realm][$s->name] = $item;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form['realm'] = array(
    '#tree' => 'true',
    '#type' => 'fieldset',
    '#description' => t('Add a new realm'),
  );
  $form['realm']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Realm'),
  );
  $form['realm']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name'),
  );
  $form['realm']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#submit' => array('casetracker_realm_add_submit'),
  );
  return $form;
}

/**
 * Theme states admin interface as table.
 */
function theme_casetracker_states_form($form) {
  $realms = casetracker_realm_list();
  $o = drupal_render($form['realm']) . drupal_render($form['submit']);
  $rows = array();
  $header = array();
  foreach (element_children($form['states']) as $realm) {
    if (!empty($realm)) {
      // TODO fancy js.
      // drupal_add_tabledrag('casetracker_states_admin', 'order', 'sibling', "state-weight", "state-weight-$realm");
      // drupal_add_tabledrag('casetracker_states_admin', 'match', 'sibling', "realm-select", "realm-select-$realm", null, false);
    }
    $rows[] = array(array(
      'data' => $realms[$realm], 
      'colspan' => count($form['states'][$realm][$i]),
    ));
    foreach (element_children($form['states'][$realm]) as $i) {
      $row = array();
      foreach(element_children($form['states'][$realm][$i]) as $j) {
        if (!isset($header[$j])) {
          $header[$j] = $form['states'][$realm][$i][$j]['#title'];
        }
        unset($form['states'][$realm][$i][$j]['#title']);
        $row[] = drupal_render($form['states'][$realm][$i][$j]);
      }
      $rows[] = array('data' => $row, 'class' => 'draggable');
    }
  }
  $o = theme('table', $header, $rows, array('id' => 'casetracker_states_admin')) . $o;
  $o .= drupal_render($form);

  return $o;
}

/**
 * TODO delete unused realms.
 */
function casetracker_states_submit($form, &$form_state) {
  ctools_include('export');
  $states = ctools_export_load_object('casetracker_states', 'all');

  foreach($form_state['values']['states'] as $realm) {
    foreach ($realm as $i => $v) {
      if (
        $states[$i]->weight !== $v['weight'] || 
        $states[$i]->realm !== $v['realm']
      ) {
        $v['name'] = $i;
        $v['title'] = $states[$i]->title;

        if ($states[$i]->export_type & EXPORT_IN_DATABASE) {
          drupal_write_record('casetracker_states', $v, array('name'));
        }
        else {
          drupal_write_record('casetracker_states', $v);
        }
      }
    }
  }
  drupal_set_message(t('Updated case states.'));
}

/**
 * Create new casetracker realm
 * TODO validation.
 */
function casetracker_realm_add_submit($form, &$form_state) {
  $realms = variable_get('casetracker_realms', array());

  $name = $form_state['values']['realm']['name'];
  $title = $form_state['values']['realm']['title'];

  // Add the new realm.
  $realms[$name] = $title;
  variable_set('casetracker_realms', $realms);
  drupal_set_message(t('Updated realm: %title', array('%title' => $title)));
}

/**
 * Displays a form for adding or editing a case state.
 */
function casetracker_state_edit($form_state, $state = NULL) {
  $form = array();
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('State title'),
    '#required' => TRUE,
    '#default_value' => isset($state) ? $state->title : NULL,
    '#description' => t('The title for this case template.'),
  );

  if ($state) {
    $form['existing_name'] = array(
      '#type' => 'value',
      '#default_value' => $state->name,
    );
    $form['title']['#description'] .= ' '.t('Machine name: %name', array('%name' => $state->name));
  }
  else {
    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('State name'),
      '#required' => TRUE,
      '#default_value' => isset($state) ? $state->name : NULL,
      '#description' => t('The machine name for this case template.'),
    );
  }

  $form['realm'] = array(
    '#type' => 'select',
    '#title' => t('Realm'),
    '#options' => casetracker_realm_list(),
    '#default_value' => isset($state->realm) ? $state->realm : NULL,
  );

  $form['submit'] = array(
    '#type' => 'submit', 
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Processes the submitted results of our case state addition or editing.
 */
function casetracker_state_edit_submit($form, &$form_state) {
  $state = array(
    'title' => $form_state['values']['title'], 
    'realm' => $form_state['values']['realm']
  );

  if (!empty($form_state['values']['existing_name'])) {
    $state['name'] = $form_state['values']['existing_name'];
    drupal_write_record('casetracker_states', $state, array('name'));
    drupal_set_message(t('The case state %name has been updated.', array('%name' =>  $form_state['values']['name'])));
  }
  else {
    $state['name'] = $form_state['values']['name'];
    drupal_write_record('casetracker_states', $state);
    drupal_set_message(t('The case state %name has been created.', array('%name' =>  $form_state['values']['name'])));
  }
  $form_state['redirect'] = 'admin/settings/casetracker/states';
}

/**
 * If the user has asked to delete a case state, we'll double-check.
 */
function casetracker_case_state_confirm_delete(&$form_state, $case_state) {
  if (!empty($case_state)) {
    $form = array(
      'csid' => array('#type' => 'value', '#value' => $case_state->csid),
      'name' => array('#type' => 'value', '#value' => $case_state->name),
    );
    return confirm_form($form,
                        t('Are you sure you want to delete the case state %name?', array('%name' => $case_state->name)),
                        'admin/settings/casetracker/states', t('This action can not be undone.'), t('Delete'), t('Cancel'));
  }
}

/**
 * Ayup, the user definitely wants to delete this case state.
 */
function casetracker_case_state_confirm_delete_submit($form, &$form_state) {
  drupal_set_message(t('Deleted case state %name.', array('%name' =>  $form_state['values']['name'])));
  casetracker_case_state_delete($form_state['values']['csid']);
  $form_state['redirect'] = 'admin/settings/casetracker/states';
}