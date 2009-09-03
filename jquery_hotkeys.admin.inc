<?php
// $Id$
/**
 * @file
 * Admin functions for jQuery Hotkeys.
 *
*/

function theme_jquery_hotkeys_admin_form(&$form) {
  $headers = array(t('Name'), t('Actions'));
  $rows = array();
  if (!empty($form['hotkeys'])) {
    foreach (element_children($form['hotkeys']) as $jhid) {
      $row = array();
      $hotkey = $form['hotkeys'][$jhid]['#hotkey'];
      $row[] = isset($hotkey['module']) ? $hotkey['name'] : l($hotkey['name'], 'admin/settings/jquery_hotkeys/edit/' .$hotkey['jhid']);
      $row[] = isset($hotkey['module']) ? '-' : l(t('edit'), 'admin/settings/jquery_hotkeys/edit/' .$hotkey['jhid']);
      $row[] = isset($hotkey['module']) ? '-' : l(t('delete'), 'admin/settings/jquery_hotkeys/delete/' .$hotkey['jhid']);
      $rows[] = $row;
    }
  }
  $link = l(t('Create a new rule'), 'admin/settings/jquery_hotkeys/add');
  $row = array();
  if (empty($rows)) {
    $row[] = array(
      'data' => t('No jQuery Hotkeys have been set up yet. !url.', array('!url' => $link)),
      'colspan' => 3,
    );
  } 
  else {
    $row[] = array(
      'data' => $link,
      'colspan' => 3,
    );
  }
  $rows[] = $row;
  
  $output = theme('table', $headers, $rows);
  $output .= drupal_render($form);
  return $output;
}

function jquery_hotkeys_admin_form() {
  $hotkeys = jquery_hotkeys_load_hotkeys();
  $form = array();
  $form['#tree'] = TRUE;
  foreach ($hotkeys as $hotkey) {
    $form['hotkeys'][$hotkey['jhid']]['#hotkey'] = $hotkey;
  }
  return $form;
} 

function jquery_hotkeys_edit($form_state, $jhid = NULL) {
  $form = array();
  if (isset($jhid)) {
    $hotkey = jquery_hotkeys_load_hotkey($jhid);
    $form['jhid'] = array(
      '#type' => 'value',
      '#value' => $hotkey['jhid']
    );
  } 
  else {
    $hotkey = array('name' => '', 'hotkey' => '',  'javascript' => '', 'visibility' => '0', 'pages' => '');
  }

  $options = array(t('Show on every page except the listed pages.'), t('Show on only the listed pages.'));
  $pages_description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
  if (user_access('use PHP for hotkeys visibility')) {
    $options[] = t('Show if the following PHP code returns <code>TRUE</code> (PHP-mode, experts only).');
    $pages_description .= ' '. t('If the PHP-mode is chosen, enter PHP code between %php. Note that executing incorrect PHP-code can break your Drupal site.', array('%php' => '<?php ?>'));
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $hotkey['name'],
    '#required' => TRUE,
  );
  $form['hotkey'] = array(
    '#type' => 'textfield',
    '#length' => 5,
    '#default_value' => $hotkey['hotkey'],
    '#title' => t('Hotkey'),
    '#required' => TRUE,
    '#description' => t('The key to bind this JavaScript to.  See http://code.google.com/p/js-hotkeys for more information.'),
  ); 
  $form['javascript'] = array(
    '#type' => 'textarea',
    '#default_value' => $hotkey['javascript'],
    '#title' => t('JavaScript'),
    '#required' => TRUE,
    '#description' => t('The JavaScript code to be executed when this hotkey is pressed.'),
  );
  $form['visibility'] = array(
    '#type' => 'radios',
    '#options' => $options,
    '#title' => t('Visibility style'),
    '#default_value' => isset($hotkey['visibility']) ? $hotkey['visibility'] : 0,
    '#required' => TRUE
  );
  $form['pages'] = array(
    '#type' => 'textarea',
    '#default_value' => $hotkey['pages'],
    '#description' => $pages_description,
    '#title' => t('Pages'),
  );
  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#submit' => array('jquery_hotkeys_edit_save'),
    '#value' => t('Save changes'),
  );

  return $form; 
}

function jquery_hotkeys_edit_save($form, &$form_state) {
  $hotkey = $form_state['values'];
  drupal_write_record('jquery_hotkeys', $hotkey, isset($hotkey['jhid']) ? 'jhid' : NULL );
  drupal_set_message(t('Hotkey changes saved.'));
  $form_state['redirect'] = '/admin/settings/jquery_hotkeys';
}

function jquery_hotkeys_delete_confirm(&$form_state, $jhid) {
  $hotkey = jquery_hotkeys_load_hotkey($jhid);
  $form = array(
    'jhid' => array(
      '#type' => 'value',
      '#value' => $jhid
    )
  );
  return confirm_form($form,
                      t('Are you sure you want to delete the hotkey %name?', array('%name' => $hotkey['name'])),
                      'admin/settings/jquery_hotkeys',
                      t('This action cannot be undone.'),
                      t('Delete this hotkey'),
                      t('Cancel'));
}

function jquery_hotkeys_delete_confirm_submit($form, &$form_state) {
  $hotkey = jquery_hotkeys_load_hotkey($form_state['values']['jhid']);
  if ($form_state['values']['confirm']) {
    db_query('DELETE FROM {jquery_hotkeys} where jhid = %d', $hotkey['jhid']);
    drupal_set_message(t('Hotkey %name deleted', array('%name' => $hotkey['name'])));
  }
  $form_state['redirect'] = 'admin/settings/jquery_hotkeys';
}

