<?php
//TODO: clear theme cashe
// TODO: tests
// show message, what deleted and what updated

require_once('duplicates_edit_arrays.inc');

function duplicates_edit_page()
{
  drupal_rebuild_theme_registry();
  return drupal_get_form('duplicates_edit_form');
}

function duplicates_edit_form($form_state) {
  $form = array();

  $form['container'] = array(
    '#type' => 'markup',
    '#value' => '',
    '#theme' => 'duplicates_edit_form_table',
  );

  $form = person_subform($form, '1');
  $form = person_subform($form, '2');

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);

	$form['cancel'] = array(
		'#type' => 'markup',
		'#value' => l(t('Cancel'), 'duplicates_check'),
	);

  return $form;
}

function person_subform($form, $number) {
  $states       = states();
  $country_list = country_list();
  $node         = _get_nodes($number);


  $number == '1' ? $ord_number = 'First' : $ord_number = 'Second';

  $form['container']['person'][$number] = array(
    '#type' => 'fieldset',
//    '#title' => t($ord_number . ' node'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['container']['person'][$number]['nid']  = array(
    '#type' => 'hidden',
    '#value' => variable_get('nid', ''),
  );

  $form['container']['person'][$number]['first_name'] = array (
    '#type'  => 'textfield',
//    '#title' => t('first_name'),
    '#default_value' => variable_get('first_name', ''),
    '#size'  => 40,
    '#maxlength' => 60,
  );

  $form['container']['person'][$number]['last_name'] = array (
    '#type'  => 'textfield',
//    '#title' => t('last_name'),
    '#default_value' => variable_get('last_name', ''),
    '#size'  => 40,
    '#maxlength' => 60,
  );

  $form['container']['person'][$number]['organization'] = array (
    '#type'  => 'textfield',
//    '#title' => t('organization'),
    '#default_value' => variable_get('organization', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

  $form['container']['person'][$number]['address'] = array (
    '#type'  => 'textfield',
//    '#title' => t('address'),
    '#default_value' => variable_get('address', ''),
    '#size'  => 40,
    '#maxlength' => 100,
    );

  $form['container']['person'][$number]['city'] = array (
    '#type'  => 'textfield',
//    '#title' => t('city'),
    '#default_value' => variable_get('city', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

  $form['container']['person'][$number]['state'] = array(
    '#type' => 'select',
//    '#title' => t('state'),
    '#default_value' => variable_get('state', ''),
    '#options' => $states,
  );

  $form['container']['person'][$number]['zipcode'] = array (
    '#type'  => 'textfield',
//    '#title' => t('zipcode'),
    '#default_value' => variable_get('zipcode', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

  $form['container']['person'][$number]['country'] = array(
    '#type' => 'select',
//    '#title' => t('country'),
    '#default_value' => variable_get('country', ''),
    '#options' => $country_list,
  );

  $form['container']['person'][$number]['phone'] = array (
    '#type'  => 'textfield',
//    '#title' => t('phone'),
    '#default_value' => variable_get('phone', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

  $form['container']['person'][$number]['fax'] = array (
    '#type'  => 'textfield',
//    '#title' => t('fax'),
    '#default_value' => variable_get('fax', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

//  $form['container']['person'][$number]['role'] = array(
//    '#type' => 'value',
//    '#value' => $number_title,
//  );

  $form['container']['person'][$number]['email'] = array (
    '#type'  => 'textfield',
//    '#title' => t('email'),
    '#default_value' => variable_get('email', ''),
    // '#required'  => TRUE,
    '#size'  => 40,
    '#maxlength' => 60,
  );

  $form['container']['person'][$number]['keep_this_node'] = array (
      '#type' => 'checkbox',
//      '#title' => t('keep_this_node'),
      '#size' => 4,
      '#default_value' => 1,
  );

  // Commented fields are here in case we will need them

  // $form['container']['person'][$number]['personid'] = array (
  //   '#type'  => 'textfield',
  //   '#title' => t('personid'),
//   //   '#default_value' => $personid,
  //   '#size'  => 40,
  //   '#maxlength' => 60,
  //   );

  return $form;
}

function duplicates_edit_theme($existing, $type, $theme, $path) {
  return array(
    'duplicates_edit_form_table' => array(
      'arguments' => array('fieldset' => NULL),
    )
  );
}

function theme_duplicates_edit_form_table($container) {
  
  $output = '';
	$header = array();
	$rows   = array();

  $side_by_side_form_array = _transpose_form_array($container);

	foreach ($side_by_side_form_array as $value) {
    $data1 = drupal_render($value[1]);
    $data2 = drupal_render($value[2]);
    $rows[] = array($value[0], $data1, $data2);
	}
  $header = array('', t('First person'), t('Second Person'));

  $output = theme_table($header, $rows);
  
	$output .= drupal_render($form);

  return $output;
}

function duplicates_edit_form_submit($form, &$form_state) {
  $good_node_nid = $bad_node_nid = 0;
  foreach ($form_state['values'] as $value) {

//  TODO: save node if smth is changed in a form
//TODO: should work, if only one is checked,
// handle another situation (1,1; 0,0)
    if (is_array($value)) {
      if ($value['keep_this_node'] == 0) {
        $bad_node_nid = $value['nid'];
      }
      elseif ($value['keep_this_node'] == 1) {
        $good_node_nid = $value['nid'];
      }
    }
  }

  if (!empty($good_node_nid) && !empty($bad_node_nid)) {
    $ref_node_nids = _collect_ref_nids($bad_node_nid, $good_node_nid);
    _update_ref_nodes($ref_node_nids, $bad_node_nid, $good_node_nid);
    _update_good_node($form_state);
    node_delete($bad_node_nid);
  }
}

function _collect_ref_nids($bad_node_nid, $good_node_nid) {
  $ref_fields   = _ref_fields();
  $nids       = array();
  foreach ($ref_fields as $tab_name => $field_name) {
    $full_field_name = $field_name . "_nid";
    $sql        = "SELECT nid FROM {node} WHERE nid IN (SELECT nid FROM {%s} WHERE %s = %d);";
    $db_result  = db_query($sql, $tab_name, $full_field_name, (int)$bad_node_nid);
    while ($nid = db_result($db_result)) {
      $nids[$nid][]   = $field_name;
    }
  }
  return $nids;
}

function _update_ref_nodes($ref_node_nids, $bad_node_nid, $good_node_nid) {
  if (!empty($ref_node_nids)) {
    foreach ($ref_node_nids as $ref_nid => $value) {
      $node_ref = node_load($ref_nid);
      foreach ($value as $ref_field) {
        $new_ref_array = array();
        foreach ($node_ref->$ref_field as $person_ref_nid) {
          if ($person_ref_nid[nid] == $bad_node_nid) {
            $new_ref_array[] = array('nid' => $good_node_nid);
          }
          else {
            $new_ref_array[] = array('nid' => $person_ref_nid[nid]);
          }
        }
        $node_ref->$ref_field = $new_ref_array;
      }
//      save dataset with new ref
      node_save(&$node_ref);
    }
  }
}


function _get_nodes($number) {
  $checked_nides = variable_get('checked_nides', '');

  $number == 1 ? $nid = $checked_nides[0] : $nid = $checked_nides[1];
  $person_node = node_load($nid);
  _del_variables();
  _set_default_values($person_node);
  return $person_node;
}

function _set_default_values($node) {
  $person_field_names = _person_field_names();
  variable_set('nid', $node->nid);
  foreach($person_field_names as $var_name => $node_field_name) {
    $node_value = $node->$node_field_name;
    $value = $node_value[0]['value'];
    variable_set($var_name, $value);
  }
  variable_set('email', $node->field_person_email[0]['email']);
}

function _del_variables() {
  $person_field_names = _person_field_names();
  foreach(array_keys($person_field_names) as $var_name) {
    variable_del($var_name);
  }
  variable_del('nid');
  variable_del('email');
}

function _transpose_form_array($form) {
  $person_fields = _person_fields();

  foreach ($person_fields as $field_name => $field_title) {
    $side_by_side_form_array[] = array($field_title, $form['person']['1'][$field_name], $form['person']['2'][$field_name]);
  }

  return $side_by_side_form_array;
}

function _update_good_node($form_state) {
  dpm($form_state);
  dpm($good_node_nid);

  $person_field_names = _person_field_names();

  foreach ($form_state['values'] as $form_value) {
    if ($form_value['keep_this_node'] == 1) {
//      $good_values[] = $form_value;
      $person_g_node = node_load($form_value['nid']);
      $person_g_node->field_person_state = Array (0 => Array ('value' => $form_value['state']));

      dpm('$person_g_node = ');
      dpm($person_g_node);
    }
  }
//  dpm($good_values);
}

/*
     'organization' => $form_state['values']['persons']['metadataProvider']['organization'],
    'address'      => $form_state['values']['persons']['metadataProvider']['address'],
    'city'         => $form_state['values']['persons']['metadataProvider']['city'],
    'state'        => $form_state['values']['persons']['metadataProvider']['state'],
    'zipcode'      => $form_state['values']['persons']['metadataProvider']['zipcode'],
    'country'      => $form_state['values']['persons']['metadataProvider']['country'],
    'phone'        => $form_state['values']['persons']['metadataProvider']['phone'],
    'fax'          => $form_state['values']['persons']['metadataProvider']['fax'],
    'role'         => $form_state['values']['persons']['metadataProvider']['role'],
    'email'        => $form_state['values']['persons']['metadataProvider']['email'],

  global $user;

  $uid = $user->uid;
  $node = new StdClass();
  $node->type = "person";
  $node->uid = $uid;
  $node->field_person_organization = Array (0 => Array ('value' => $person_settings['organization']));
  $node->field_person_address = Array (0 => Array ('value' => $person_settings['address']));
  $node->field_person_city = Array (0 => Array ('value' => $person_settings['city']));
  $node->field_person_state = Array (0 => Array ('value' => $person_settings['state']));
  $node->field_person_zipcode = Array (0 => Array ('value' => $person_settings['zipcode']));
  $node->field_person_country = Array (0 => Array ('value' => $person_settings['country']));
  $node->field_person_phone = Array (0 => Array ('value' => $person_settings['phone']));
  $node->field_person_fax = Array (0 => Array ('value' => $person_settings['fax']));
  $node->field_person_role = Array (0 => Array ('value' => $person_settings['role']));
  $node->field_person_email = Array (0 => Array ('email' => $person_settings['email']));

  // Commented fields are here in case we will need them
  // $node->field_person_title = Array (0 => Array ('value' => ''));
  // $node->field_person_first_name = Array (0 => Array ('value' => ''));
  // $node->field_person_last_name = Array (0 => Array ('value' => ''));
  // $node->field_person_personid = Array (0 => Array ('value' => $personid));

  node_save($node);

  return $node->nid;
}

 */