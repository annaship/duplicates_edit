<?php

require_once('duplicates_edit_arrays.inc');

function duplicates_edit_page()
{
  return drupal_get_form('duplicates_edit_form');
}

function duplicates_edit_form($form_state) {
  $form = array();

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

  $form['persons'][$number] = array(
    '#type' => 'fieldset',
//    '#title' => t($ord_number . ' node'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['persons'][$number]['nid']  = array(
    '#type' => 'hidden',
    '#value' => variable_get('nid', ''),
  );

  $form['persons'][$number]['first_name'] = array (
    '#type'  => 'textfield',
//    '#title' => t('first_name'),
    '#default_value' => variable_get('first_name', ''),
    '#size'  => 40,
    '#maxlength' => 60,
  );

  $form['persons'][$number]['last_name'] = array (
    '#type'  => 'textfield',
//    '#title' => t('last_name'),
    '#default_value' => variable_get('last_name', ''),
    '#size'  => 40,
    '#maxlength' => 60,
  );

  $form['persons'][$number]['organization'] = array (
    '#type'  => 'textfield',
//    '#title' => t('organization'),
    '#default_value' => variable_get('organization', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['address'] = array (
    '#type'  => 'textfield',
//    '#title' => t('address'),
    '#default_value' => variable_get('address', ''),
    '#size'  => 40,
    '#maxlength' => 100,
    );

  $form['persons'][$number]['city'] = array (
    '#type'  => 'textfield',
//    '#title' => t('city'),
    '#default_value' => variable_get('city', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['state'] = array(
    '#type' => 'select',
//    '#title' => t('state'),
    '#default_value' => variable_get('state', ''),
    '#options' => $states,
  );

  $form['persons'][$number]['zipcode'] = array (
    '#type'  => 'textfield',
//    '#title' => t('zipcode'),
    '#default_value' => variable_get('zipcode', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['country'] = array(
    '#type' => 'select',
//    '#title' => t('country'),
    '#default_value' => variable_get('country', ''),
    '#options' => $country_list,
  );

  $form['persons'][$number]['phone'] = array (
    '#type'  => 'textfield',
//    '#title' => t('phone'),
    '#default_value' => variable_get('phone', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['fax'] = array (
    '#type'  => 'textfield',
//    '#title' => t('fax'),
    '#default_value' => variable_get('fax', ''),
    '#size'  => 40,
    '#maxlength' => 60,
    );

//  $form['persons'][$number]['role'] = array(
//    '#type' => 'value',
//    '#value' => $number_title,
//  );

  $form['persons'][$number]['email'] = array (
    '#type'  => 'textfield',
//    '#title' => t('email'),
    '#default_value' => variable_get('email', ''),
    // '#required'  => TRUE,
    '#size'  => 40,
    '#maxlength' => 60,
  );

  $form['persons'][$number]['keep_this_node'] = array (
      '#type' => 'checkbox',
//      '#title' => t('keep_this_node'),
      '#size' => 4,
      '#default_value' => 1,
  );

  // Commented fields are here in case we will need them



  // $form['persons'][$number]['personid'] = array (
  //   '#type'  => 'textfield',
  //   '#title' => t('personid'),
//   //   '#default_value' => $personid,
  //   '#size'  => 40,
  //   '#maxlength' => 60,
  //   );

  return $form;
}

function duplicates_edit_theme() {
	return array(
		'duplicates_edit_form' => array('arguments' => array('form' => NULL),),
	);
}

function theme_duplicates_edit_form($form) {
	$header = array();
	$rows = array();
  $side_by_side_form_array = _transpose_form_array($form);

	foreach ($side_by_side_form_array as $value) {
    $data1 = drupal_render($value[1]);
    $data2 = drupal_render($value[2]);
    $rows[] = array($value[0], $data1, $data2);
	}
  $header = array('', t('First person'), t('Second Person'));

//	$output = theme('table', $header, $rows);
  
//  $output .= drupal_render($form['submit']);
//  $output .= drupal_render($form['cancel']);
	$output .= drupal_render($form);

	return $output;
}


function duplicates_edit_form_submit($form, &$form_state) {
  $good_node_nid = $bad_node_nid = 0;
  foreach ($form_state['values'] as $key => $value) {
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

  $ref_fields = _ref_fields();
  foreach ($ref_fields as $tab_name => $field_name) {
    $full_field_name = $field_name . "_nid";
    $nids = array();
    $sql        = "SELECT nid FROM {node} WHERE nid IN (SELECT nid FROM {%s} WHERE %s = %d);";
    $db_result  = db_query($sql, $tab_name, $full_field_name, (int)$bad_node_nid);
    while ($nid = db_result($db_result)) {
      dpm($nid);
      $dataset_node = node_load($nid);
      dpm('node_load');
      dpm($dataset_node);

      $dataset_ref = $dataset_node->$field_name;
      /*TODO: take array, modify, save back to node*/
      foreach ($dataset_ref as $number => $value) {
        foreach ($value as $key => $ref_nid) {
          if ($ref_nid == $bad_node_nid) {
            dpm('$number = ' . $number);
            dpm('$bad_node_nid = ' . $bad_node_nid);
            dpm('$good_node_nid = ' . $good_node_nid);
            dpm('BEFORE: $dataset_ref = ');
            dpm($dataset_ref);
            $dataset_ref[$number][nid] = $good_node_nid;
            dpm('$dataset_ref = ');
            dpm('BEFORE: $dataset_node = ');
            dpm($dataset_node);
            $dataset_node->$field_name = $dataset_ref;
            node_save($dataset_node);
            dpm('AFTER: $dataset_node = ');
            dpm($dataset_node);
          }
        }
      }
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
    $side_by_side_form_array[] = array($field_title, $form['persons']['1'][$field_name], $form['persons']['2'][$field_name]);
  }

  return $side_by_side_form_array;
}


