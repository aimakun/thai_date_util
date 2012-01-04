<?php
class thai_date_util_handler_field_date extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['date_format'] = array('default' => 'small');
    $options['custom_date_format'] = array('default' => '');
    $options['era_type'] = array('default' => 'christmas');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $time = time();

    $form['date_format'] = array(
      '#type' => 'select',
      '#title' => t('Date format'),
      '#options' => array(
        'small' => t('Short date format') . ' ' . format_date($time, 'small'),
        'medium' => t('Medium date format') . ' ' . format_date($time, 'medium'),
        'large' => t('Long date format') . ' ' . format_date($time, 'large'),
        'custom' => t('Custom'),
        'raw time ago' => t('Time ago'),
        'time ago' => t('Time ago (with "ago" appended)'),
        'raw time span' => t('Time span (future dates start with - )'),
        'time span' => t('Time span (with "ago/hence" appended)'),
      ),
      '#default_value' => isset($this->options['date_format']) ? $this->options['date_format'] : 'small',
    );
    $form['custom_date_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom date format'),
      '#description' => t('If "Custom", see <a href="http://us.php.net/manual/en/function.date.php" target="_blank">the PHP docs</a> for date formats. If "Time ago", enter the number of different time units to display, which defaults to 2.'),
      '#default_value' => isset($this->options['custom_date_format']) ? $this->options['custom_date_format'] : '',
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-options-date-format' => array('custom', 'raw time ago', 'time ago', 'raw time span', 'time span')),
    );
    $form['era_type'] = array(
      '#type' => 'select',
      '#title' => t('Type of Era'),
      '#options' => array(
        'default' => t('Default'),
        'christmas' => t('Christmas Era'),
        'buddhist' => t('Buddhist Era'),
      ),
      '#default_value' => isset($this->options['era_type']) ? $this->options['era_type'] : 'default',
    );
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    $format = $this->options['date_format'];
    if (in_array($format, array('custom', 'raw time ago', 'time ago', 'raw time span', 'time span'))) {
      $custom_format = $this->options['custom_date_format'];
    }
    
    if ($value) {
      $this->options['era_type'] = $this->options['era_type'] == 'default' ? variable_get('thai_date_util_node_era_type', 'buddhist') : $this->options['era_type'];
      return thai_date_util_format($value, $format, $custom_format, $this->options['era_type']);
    }
  }
}
