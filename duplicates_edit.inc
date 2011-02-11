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

  $form['nodes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Nodes'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['nodes']['1'] = array (
    '#type'  => 'textfield',
    '#title' => t('First Node'),
    '#default_value' => 'Nlll',
    '#size'  => 60,
    '#maxlength' => 60,
  );

    return $form;
}
