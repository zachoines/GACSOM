<?php


function gacsom_admin_settings_form($form, &$form_state) {

    $form = array();

    $default = variable_get('gacsom_data_type');
    
    if (!isset($default)) {
        $default = 'Last';
    } 

    $form['gacsom_cookies_fieldset'] = array(
		'#type' => 'fieldset',
     	'#title' => t('Cookies'),
        '#description' => t('This module can use cookies to reduce the number of calls to database.'),
    );
    
    $form['gacsom_cookies_fieldset']['gacsom_cookie_usage'] = array(
        '#type' => 'checkbox', 
        '#default_value' => check_variable(variable_get('gacsom_enable_cookies')),
        '#title' => t(toggle_cookie_usage_title()),
    );

    $form['gacsom_data_fieldset'] = array(
		'#type' => 'fieldset',
        '#title' => t('POST Data'),
        '#description' => t('Select the JSON that is sent out along with a Webform submission'),
    );

    $form['gacsom_data_fieldset']['gacsom_json_data'] = array(
        '#type' => 'radios',
        '#title' => t('Choose JSON Data Sent'),
        '#options' => array(
            'All' => t('Get All History'),
            'First' => t('Get First UTM Instance'),
            'Last' => t('Get Last UTM Instance'),
        ),
        
        '#default_value' => $default,
    );
    
    $form['#validate'][] = 'gacsom_admin_settings_validate';
    
    $form['#submit'] = array(
		'gacsom_admin_settings_submit',
    );
    
    return system_settings_form($form);
}

function gacsom_admin_settings_validate($form, &$form_state) {

}

function gacsom_admin_settings_submit($form, &$form_state) {
    variable_set('gacsom_enable_cookies', $form_state['values']['gacsom_cookie_usage']);
    variable_set('gacsom_data_type',  $form_state['values']['gacsom_json_data']);

    if (check_variable(variable_get('gacsom_enable_cookies')) == 1) {
        dpm('Cookies have been turned on.');
    } else {
        dpm('Cookies have been turned off.');
    }
    
}
 
//Check for NULL values
function check_variable($var) {
    if ($var == NULL) {
        return 0; 
    } else {
        return $var;
    }
}


function toggle_cookie_usage_title(){
    
    if (check_variable(variable_get('gacsom_enable_cookies')) == 1) {
        $string = 'Turn off cookies.';
    } else {
        $string = 'Turn on cookies.';
    }

    return $string;
}