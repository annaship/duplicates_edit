<?php
//!!! 37919, 28
require_once('duplicates_edit_arrays.inc');

function duplicates_edit_page()
{
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
//  dpm($form);

//  $form['persons_information'] = array(
//   '#type' => 'fieldset',
//   '#title' => t('Persons Information'),
//   '#collapsible' => FALSE,
//   '#weight' => 0,
//  );

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);

	$form['cancel'] = array(
		'#type' => 'markup',
		'#value' => l(t('Cancel'), 'duplicates_edit'),
	);

//	$form['#redirect'] = ‘featured_product_mgmt’;

//  $form['submit'] = array (
//    '#type' => 'submit',
//    '#value' => t('Submit'),
//    );

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

//function duplicates_edit_theme() {
//	return array(
//		'duplicates_edit_form' => array('arguments' => array('form' => NULL),),
//	);
//}

function duplicates_edit_theme($existing, $type, $theme, $path) {
  return array(
    'duplicates_edit_form_table' => array(
      'arguments' => array('fieldset' => NULL),
    )
  );
}

//function theme_duplicates_edit_form($form) {
function theme_duplicates_edit_form_table($container) {
  $output = '';
	$header = array();
	$rows   = array();

//    foreach($container as $field_name => $field) {
//
//    // All the fields were named 'node_' . $node->nid
//    if (strpos($field_name, 'node_') === 0) {
//
//      $nid = substr($field_name, 5);
//      $node = node_load($nid);
//
//      $rows[] = array(
//        $node->nid,
//        check_plain($node->field_person_first_name[0]['value']),
//        check_plain($node->field_person_last_name[0]['value']),
//        check_plain($node->field_person_email[0]['email']),
//        drupal_render($field),
//      );
//
//    }
//  }
//
//  return theme_table($header, $rows);
//  $form = person_subform($form, '1');
//  $form = person_subform($form, '2');

//  $form['container'][1]['last_name'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('last_name'),
//    '#default_value' => variable_get('last_name', ''),
//    '#size'  => 40,
//    '#maxlength' => 60,
//  );
//
//  $form['container'][2]['last_name'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('last_name'),
//    '#default_value' => "Meeee",
////      variable_get('last_name', ''),
//    '#size'  => 40,
//    '#maxlength' => 60,
//  );

  $side_by_side_form_array = _transpose_form_array($container);

	foreach ($side_by_side_form_array as $value) {
    $data1 = drupal_render($value[1]);
    $data2 = drupal_render($value[2]);
    $rows[] = array($value[0], $data1, $data2);
	}
  $header = array('', t('First person'), t('Second Person'));

//	$output = theme('table', $header, $rows);
  $output = theme_table($header, $rows);
  
//  dpm("\$form = ");
//  dpm($form);
	$output .= drupal_render($form);
//
	return $output;
}

function duplicates_edit_form_submit($form, &$form_state) {
  dpm('Submit!');
  dpm('$form');
  dpm($form);
//  in form is only second person! (keep is 0)
  dpm('$form_state');
  dpm($form_state);
  $good_node_nid = $bad_node_nid = 0;
  foreach ($form_state['values'] as $value) {
  dpm('$value');
  dpm($value);
  dpm('$value[\'keep_this_node\'] = ');
  dpm($value['keep_this_node']);

//  TODO: save changes in form
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
  dpm('$bad_node_nid = ' . $bad_node_nid);
  dpm('$good_node_nid = ' . $good_node_nid);

  if (!empty($good_node_nid) && !empty($bad_node_nid)) {
    $ref_node_nids = _collect_ref_nids($bad_node_nid, $good_node_nid);
    _update_ref_nodes($ref_node_nids, $bad_node_nid, $good_node_nid);
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
  dpm('$nids = ');
  dpm($nids);
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
      node_save(&$node_ref);
//      TODO: delete bad node
    }
  }
}


function _get_nodes($number) {
  $checked_nides = variable_get('checked_nides', '');

  $number == 1 ? $nid = $checked_nides[0] : $nid = $checked_nides[1];
  $node = node_load($nid);
  _del_variables();
  _set_default_values($node);
  return $node;
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


