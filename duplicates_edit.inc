<?php

require_once('duplicates_edit_arrays.inc');

function duplicates_edit_page()
{
//  $checked_nides = $checked_nides', ',
//  dpm('HERE! duplicates_edit_page');
//
//  dpr($checked_nides);
//  dpm($checked_nides);
  return drupal_get_form('duplicates_edit_form');

}

function duplicates_edit_form($form_state) {
  $form = array();

//  $form['persons']['1'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('First node'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
//    $form['persons']['2'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Second node'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );

  $form = person_subform($form, '1');
  $form = person_subform($form, '2');

  // $form_state['redirect'] = array('page1', 'id=' . $form_state['values']['index_search']);

  $form['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Create'),
    );

  return $form;
}

function person_subform($form, $number) {
  $states       = states();
  $country_list = country_list();

  $number == '1' ? $ord_number = 'First' : $ord_number = 'Second';
  $form['persons'][$number] = array(
    '#type' => 'fieldset',
    '#title' => t($ord_number . ' node'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['persons'][$number]['organization'] = array (
    '#type'  => 'textfield',
    '#title' => t('organization'),
//     '#default_value' => $organization,
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['address'] = array (
    '#type'  => 'textfield',
    '#title' => t('address'),
//     '#default_value' => $address,
    '#size'  => 60,
    '#maxlength' => 100,
    );

  $form['persons'][$number]['city'] = array (
    '#type'  => 'textfield',
    '#title' => t('city'),
//     '#default_value' => $city,
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['state'] = array(
    '#type' => 'select',
    '#title' => t('state'),
//     '#default_value' => $state,
    '#options' => $states,
  );

  $form['persons'][$number]['zipcode'] = array (
    '#type'  => 'textfield',
    '#title' => t('zipcode'),
//     '#default_value' => $zipcode,
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['country'] = array(
    '#type' => 'select',
    '#title' => t('country'),
//     '#default_value' => $country,
    '#options' => $country_list,
  );

  $form['persons'][$number]['phone'] = array (
    '#type'  => 'textfield',
    '#title' => t('phone'),
//     '#default_value' => $phone,
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['fax'] = array (
    '#type'  => 'textfield',
    '#title' => t('fax'),
//     '#default_value' => $fax,
    '#size'  => 60,
    '#maxlength' => 60,
    );

  $form['persons'][$number]['role'] = array(
    '#type' => 'value',
    '#value' => $number_title,
  );

  $form['persons'][$number]['email'] = array (
    '#type'  => 'textfield',
    '#title' => t('email'),
//     '#default_value' => $email,
    // '#required'  => TRUE,
    '#size'  => 60,
    '#maxlength' => 60,
    );

  // Commented fields are here in case we will need them

  // $form['persons'][$number]['first_name'] = array (
  //   '#type'  => 'textfield',
  //   '#title' => t('first_name'),
//   //   '#default_value' => $first_name,
  //   '#size'  => 60,
  //   '#maxlength' => 60,
  //   );
  //
  // $form['persons'][$number]['last_name'] = array (
  //   '#type'  => 'textfield',
  //   '#title' => t('last_name'),
//   //   '#default_value' => $last_name,
  //   '#size'  => 60,
  //   '#maxlength' => 60,
  //   );

  // $form['persons'][$number]['personid'] = array (
  //   '#type'  => 'textfield',
  //   '#title' => t('personid'),
//   //   '#default_value' => $personid,
  //   '#size'  => 60,
  //   '#maxlength' => 60,
  //   );

  return $form;
}


//
//function duplicates_edit_form($form_state) {
//  $form = array();
//
////  $form['persons'] = array(
////    '#type' => 'fieldset',
////    '#title' => t('Metadata Provider and Publisher'),
////    '#tree' => TRUE,
////    '#collapsible' => TRUE,
////    '#collapsed' => FALSE,
////  );
//
//
//  $form['nodes']['1'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('First Node'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
////  $form['nodes']['1']['name'] = array (
////    '#type'  => 'textfield',
////    '#title' => t('Name'),
// ////    '#default_value' => 'Nlll',
////    '#size'  => 60,
////    '#maxlength' => 60,
////  );
////
//  $form['nodes']['2'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Second Node'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
////  $form['nodes']['2']['name'] = array (
////    '#type'  => 'textfield',
////    '#title' => t('Name'),
// ////    '#default_value' => 'Nlll',
////    '#size'  => 60,
////    '#maxlength' => 60,
////  );
//
//  /*
//   *   $form['persons'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Metadata Provider and Publisher'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
//  $form = person_subform($form, 'metadataProvider');
//  $form = person_subform($form, 'publisher');
//   */
//
//  $form = person_subform($form, '1');
//  $form = person_subform($form, '2');
//
//  // $form_state['redirect'] = array('page1', 'id=' . $form_state['values']['index_search']);
//
//  $form['submit'] = array (
//    '#type' => 'submit',
//    '#value' => t('Create'),
//    );
//
//    return $form;
//}
//
//function person_subform($form, $number) {
////
////  $form['nodes'][$number] = array(
////   '#type' => 'fieldset',
////   '#title' => t($number_title),
////   '#tree' => TRUE,
////   '#collapsible' => TRUE,
////   '#collapsed' => FALSE,
////  );
//
//  $form['nodes'][$number]['organization'] = array (
//   '#type'  => 'textfield',
//   '#title' => t('organization'),
// //   '#default_value' => $organization,
//   '#size'  => 60,
//   '#maxlength' => 60,
//   );
//
//  $form['nodes'][$number]['address'] = array (
//   '#type'  => 'textfield',
//   '#title' => t('address'),
// //   '#default_value' => $address,
//   '#size'  => 60,
//   '#maxlength' => 100,
//   );
//
//  $form['nodes'][$number]['city'] = array (
//   '#type'  => 'textfield',
//   '#title' => t('city'),
// //   '#default_value' => $city,
//   '#size'  => 60,
//   '#maxlength' => 60,
//   );
//
//  $form['nodes'][$number]['state'] = array(
//   '#type' => 'select',
//   '#title' => t('state'),
// //   '#default_value' => $state,
//   '#options' => $states,
//  );
//
//  $form['nodes'][$number]['zipcode'] = array (
//   '#type'  => 'textfield',
//   '#title' => t('zipcode'),
// //   '#default_value' => $zipcode,
//   '#size'  => 60,
//   '#maxlength' => 60,
//   );
//
//  $form['nodes'][$number]['country'] = array(
//   '#type' => 'select',
//   '#title' => t('country'),
// //   '#default_value' => $country,
//   '#options' => $country_list,
//  );
//
//  $form['nodes'][$number]['phone'] = array (
//   '#type'  => 'textfield',
//   '#title' => t('phone'),
// //   '#default_value' => $phone,
//   '#size'  => 60,
//   '#maxlength' => 60,
//   );
//
//  $form['nodes'][$number]['fax'] = array (
//   '#type'  => 'textfield',
//   '#title' => t('fax'),
// //   '#default_value' => $fax,
//   '#size'  => 60,
//   '#maxlength' => 60,
//   );
//
//  $form['nodes'][$number]['role'] = array(
//   '#type' => 'value',
//   '#value' => $number_title,
//  );
//
//  $form['nodes'][$number]['email'] = array (
//   '#type'  => 'textfield',
//   '#title' => t('email'),
// //   '#default_value' => $email,
//   // '#required'  => TRUE,
//   '#size'  => 60,
//   '#maxlength' => 60,
//   );
//
//
//  $form['nodes'][$number]['first_name'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('first_name'),
// //    '#default_value' => $first_name,
//    '#size'  => 60,
//    '#maxlength' => 60,
//  );
//
//  $form['nodes'][$number]['last_name'] = array (
//    '#type'  => 'textfield',
//    '#title' => t('last_name'),
// //    '#default_value' => $last_name,
//    '#size'  => 60,
//    '#maxlength' => 60,
//  );
//
//}
