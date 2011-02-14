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

  $transpose_form = _transpose_form($form);


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
    '#title' => t($ord_number . ' node'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['persons'][$number]['first_name'] = array (
    '#type'  => 'textfield',
    '#title' => t('first_name'),
    '#default_value' => variable_get('first_name', ''),
    '#size'  => 60,
    '#maxlength' => 60,
   );

  $form['persons'][$number]['last_name'] = array (
    '#type'  => 'textfield',
    '#title' => t('last_name'),
    '#default_value' => variable_get('last_name', ''),
    '#size'  => 60,
    '#maxlength' => 60,
  );

  $form['persons'][$number]['organization'] = array (
    '#type'  => 'textfield',
    '#title' => t('organization'),
    '#default_value' => variable_get('organization', ''),
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['address'] = array (
    '#type'  => 'textfield',
    '#title' => t('address'),
    '#default_value' => variable_get('address', ''),
    '#size'  => 60,
    '#maxlength' => 100,
    );

  $form['persons'][$number]['city'] = array (
    '#type'  => 'textfield',
    '#title' => t('city'),
    '#default_value' => variable_get('city', ''),
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['state'] = array(
    '#type' => 'select',
    '#title' => t('state'),
    '#default_value' => variable_get('state', ''),
    '#options' => $states,
  );

  $form['persons'][$number]['zipcode'] = array (
    '#type'  => 'textfield',
    '#title' => t('zipcode'),
    '#default_value' => variable_get('zipcode', ''),
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['country'] = array(
    '#type' => 'select',
    '#title' => t('country'),
    '#default_value' => variable_get('country', ''),
    '#options' => $country_list,
  );

  $form['persons'][$number]['phone'] = array (
    '#type'  => 'textfield',
    '#title' => t('phone'),
    '#default_value' => variable_get('phone', ''),
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['fax'] = array (
    '#type'  => 'textfield',
    '#title' => t('fax'),
    '#default_value' => variable_get('fax', ''),
    '#size'  => 60,
    '#maxlength' => 60,
    );

//  $form['persons'][$number]['role'] = array(
//    '#type' => 'value',
//    '#value' => $number_title,
//  );

  $form['persons'][$number]['email'] = array (
    '#type'  => 'textfield',
    '#title' => t('email'),
    '#default_value' => variable_get('email', ''),
    // '#required'  => TRUE,
    '#size'  => 60,
    '#maxlength' => 60,
    );

  // Commented fields are here in case we will need them



  // $form['persons'][$number]['personid'] = array (
  //   '#type'  => 'textfield',
  //   '#title' => t('personid'),
//   //   '#default_value' => $personid,
  //   '#size'  => 60,
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
	$rows = array();
//      dpm($form['persons']['1']);
//      dpm($form['persons']['2']);
  
	foreach (element_children($form['persons']) as $key) {
		$row = array();
		if (isset($form['persons'][$key])) {
      foreach ($form['persons'][$key] as $field_value) {
        $new_array[] = $field_value;
      }
      $new_arrays[] = $new_array;
//  dpm($form['persons'][$key]['first_name']);
//      dpm($form['persons'][$key]);
//			$data = drupal_render($form['persons'][$key]);
//			$row[] = array('data' => $data);
//      dpm($row);
//
//			$row[] = drupal_render($form['persons']['1'])  drupal_render($form['persons']['2']);
//			$row[] = array('data' => drupal_render($form['persons'][$key]['first_name']));
//			$row[] = array('data' => drupal_render($form[$key]['discount']));
//			$row[] = array('data' => drupal_render($form[$key]['createdon']));
//
		}
	}
  $rows[] = $row;
//  dpm('$rows = ');
//  dpm($rows);

	// Individual table headers.
	$header = array();
	$header[] = array('data' => t('Featured'), 'class' => 'checkbox');
	$header[] = t('Name');
	$header[] = t('Category');
	$header[] = t('Discount');
	$header[] = t('Created on');

	$output = theme('table', $header, $rows);
	$output .= drupal_render($form);
	return $output;
}

function _get_nodes($number) {
  $checked_nides = variable_get('checked_nides', '');

  $number == 1 ? $nid = $checked_nides[0] : $nid = $checked_nides[1];
  $node = node_load($nid);

  variable_set('first_name', $node->field_person_first_name[0]['value']);
  variable_set('last_name', $node->field_person_last_name[0]['value']);
  variable_set('organization', $node->field_person_organization[0]['value']);
  variable_set('title', $node->field_person_title[0]['value']);
  variable_set('address', $node->field_person_address[0]['value']);
  variable_set('city', $node->field_person_city[0]['value']);
  variable_set('state', $node->field_person_state[0]['value']);
  variable_set('zipcode', $node->field_person_zipcode[0]['value']);
  variable_set('country', $node->field_person_country[0]['value']);
  variable_set('phone', $node->field_person_phone[0]['value']);
  variable_set('fax', $node->field_person_fax[0]['value']);
  variable_set('email', $node->field_person_email[0]['email']);
//  variable_set('personid', $node->field_person_personid);
  variable_set('role', $node->field_person_role[0]['value']);

  return $node;
}

function _transpose_form($form) {
//  dpm('HERE!');
//      dpm($form['persons']['1']);
//      dpm($form['persons']['2']);


  $person_fields = array(
    'first_name',
    'last_name',
    'organization',
    'address',
    'city',
    'state',
    'zipcode',
    'country',
    'phone',
    'fax',
    'email',
  );

//	foreach (element_children($form['persons']) as $key) {
  foreach ($person_fields as $field_name) {
//  dpm($form['persons']['1'][$field_name]);
    $a[] = array($form['persons']['1'][$field_name], $form['persons']['2'][$field_name]);
  }
  dpm($a);
//  dpm($form['persons']['1'][$field_name]);


//    if (isset($form['persons'][$key])) {
//      foreach ($form['persons'][$key] as $field_value) {
//        $new_array[] = $field_value;
//        dpm($new_array);
//      }
////      $new_arrays[] = $new_array;
////      dpm($new_arrays);
//    }
//  }

}

/*
 <?php
function product_theme() {
	return array(
		'featured_product_form' => array('arguments' => array('form' => NULL),),
	);
}
?>
Step 5:- Then finally define your theme function which actually format your form layout in list using the $form array. Using “foreach” loop we navigate through each item of $form array and create $rows array which we pass to “theme_table()” function later. Create the header of your table and call “table_theme()” function with $header and $rows parameters. Call the “drupal_render()” function for render the submit and cancel buttons.

<?php
function theme_featured_product_form($form) {
	$rows = array();
	foreach (element_children($form) as $key) {
		$row = array();
		if (isset($form[$key]['name'])) {

			$status = drupal_render($form['featured'][$key]);
			$row[] = array('data' => $status, 'class' => 'checkbox');

			$row[] = ''. drupal_render($form[$key]['name']) .'';
			$row[] = array('data' => drupal_render($form[$key]['category']));
			$row[] = array('data' => drupal_render($form[$key]['discount']));
			$row[] = array('data' => drupal_render($form[$key]['createdon']));

			$rows[] = $row;
		}
	}

	// Individual table headers.
	$header = array();
	$header[] = array('data' => t('Featured'), 'class' => 'checkbox');
	$header[] = t('Name');
	$header[] = t('Category');
	$header[] = t('Discount');
	$header[] = t('Created on');

	$output = theme('table', $header, $rows);
	$output .= drupal_render($form);
	return $output;
}
?>
 */