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

//  $transpose_form = _transpose_form($form);
//  variable_set('transpose_form', $transpose_form);

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Create'),
    );

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

//TODO "submit"

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

	$output = theme('table', $header, $rows);
	return $output;
}

function _get_nodes($number) {
  $checked_nides = variable_get('checked_nides', '');

  $number == 1 ? $nid = $checked_nides[0] : $nid = $checked_nides[1];
  $node = node_load($nid);
  _set_default_values($node);
//  $person_field_names = _person_field_names();
//  foreach($person_field_names as $var_name => $node_field_name) {
//    $node_value = $node->$node_field_name;
//    $value = $node_value[0]['value'];
//    variable_set($var_name, $value);
//  }
//  variable_set('email', $node->field_person_email[0]['email']);
  return $node;
}

function _set_default_values($node) {
  $person_field_names = _person_field_names();
  foreach($person_field_names as $var_name => $node_field_name) {
    $node_value = $node->$node_field_name;
    $value = $node_value[0]['value'];
    variable_set($var_name, $value);
  }
  variable_set('email', $node->field_person_email[0]['email']);
}

function _transpose_form_array($form) {
  $person_fields = _person_fields();

  foreach ($person_fields as $field_name => $field_title) {
    $side_by_side_form_array[] = array($field_title, $form['persons']['1'][$field_name], $form['persons']['2'][$field_name]);
  }

  return $side_by_side_form_array;
}


