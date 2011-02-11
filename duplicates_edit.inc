<?php

function duplicates_edit_page()
{
  $checked_nides = variable_get('checked_nides', '');
  dpm('HERE! duplicates_edit_page');

  dpr($checked_nides);
  dpm($checked_nides);
}


//
//function eml_config_form($form_state) {
//  $form = array();
//  unset($last_settings);
//
//  // $q = db_query('SELECT nid FROM node WHERE nid > 689;');
//  // while ($nid = db_result($q)) {
//  //   node_delete($nid);
//  // }
//  // dpm(node_load(2890));
//
//  // $last_settings = get_last_settings();
//  $default_setting = '';
//  $last_settings   = array (
//    'last_acronym'             => variable_get('eml_settings_acronym', $default_setting),
//    'last_language'            => variable_get('eml_settings_language', $default_setting),
//    'last_intellectual_rights' => variable_get('eml_settings_intellectual_rights', $default_setting),
//    // 'last_data_policies'       => variable_get('eml_settings_data_policies', $default_setting),
//  );
//
//  $form['acronym'] = array(
//    '#type'  => 'textfield',
//    '#title' => t('Site name acronym'),
//    // '#required'  => TRUE,
//    '#size'  => 3,
//    '#maxlength' => 3,
//    '#default_value' => variable_get('acronym', $last_settings['last_acronym']),
//    // '#description' => t('Site name acronym'),
//  );
//
//  $form['language'] = array(
//    '#type'  => 'textfield',
//    '#title' => t('Language'),
//    // '#required'  => TRUE,
//    '#size'  => 15,
//    '#maxlength' => 64,
//    '#default_value' => variable_get('language', 'english'),
//  );
//
//  $form['intellectual_rights'] = array(
//    '#type' => 'textarea',
//    '#title' => t('Intellectual Rights'),
//    '#default_value' => variable_get('intellectual_rights', $last_settings['last_intellectual_rights']),
//    '#cols' => 60,
//    '#rows' => 5,
//  );
//
//  // $form['data_policies'] = array(
//  //   '#type' => 'textarea',
//  //   '#title' => t('Data Policies'),
//  //   '#default_value' => variable_get('data_policies', $last_settings['last_data_policies']),
//  //   '#cols' => 60,
//  //   '#rows' => 5,
//  // );
//
//  $form['persons'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Metadata Provider and Publisher'),
//    '#tree' => TRUE,
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
//  $form = person_subform($form, 'metadataProvider');
//  $form = person_subform($form, 'publisher');
//
//  // $form_state['redirect'] = array('page1', 'id=' . $form_state['values']['index_search']);
//
//  $form['submit'] = array (
//    '#type' => 'submit',
//    '#value' => t('Create'),
//    );
//
//  return $form;
//}