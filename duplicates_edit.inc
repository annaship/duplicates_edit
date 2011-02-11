<?php

function duplicates_edit_page()
{
//  $checked_nides = variable_get('checked_nides', '');
//  dpm('HERE! duplicates_edit_page');
//
//  dpr($checked_nides);
//  dpm($checked_nides);
  return drupal_get_form('duplicates_edit_form');

}

function duplicates_edit_form($form_state) {
  $form = array();

  $form['nodes']['1'] = array(
    '#type' => 'fieldset',
    '#title' => t('First Node'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['nodes']['1']['name'] = array (
    '#type'  => 'textfield',
    '#title' => t('Name'),
    '#default_value' => 'Nlll',
    '#size'  => 60,
    '#maxlength' => 60,
  );

  $form['nodes']['2'] = array(
    '#type' => 'fieldset',
    '#title' => t('Second Node'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['nodes']['2']['name'] = array (
    '#type'  => 'textfield',
    '#title' => t('Name'),
    '#default_value' => 'Nlll',
    '#size'  => 60,
    '#maxlength' => 60,
  );

    return $form;
}
