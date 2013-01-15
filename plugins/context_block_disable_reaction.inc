<?php

class Context_Block_Disable_Reaction extends context_reaction_block {

  function options_form($context) {

    $form = parent::options_form($context);

    // Change the wrapper class to avoid JS from context_reaction_block
    $form['selector']['#prefix'] = '<div class="context-blockdisableform-selector">';

    $defaults = $this->fetch_from_context($context);

    foreach ($defaults['blocks'] as $module => $block_info) {

      foreach ($block_info as $block_name) {

        $form['selector'][$module][$block_name]['#default_value'] = TRUE;
      }
    }

    return $form['selector'];
  }

  function options_form_submit($values) {

    $blocks = array();

    foreach ($values as $module => $block_data) {

      foreach ($block_data as $name => $selected) {

        if (!empty($selected)) {

          $blocks[$module][$name] = $selected;
        }
      }
    }

    return array('blocks' => $blocks);
  }

  function execute(&$data, $block) {

    $contexts = $this->get_contexts();

    foreach ($contexts as $context) {

      if (empty($context->reactions[$this->plugin])) {

        continue;
      }

      $blocks = $context->reactions[$this->plugin]['blocks'];

      if (empty($blocks[$block->module])) {

        continue;
      }

      foreach ($blocks[$block->module] as $block_info);

      list($module_name, $block_id) = explode('-', $block_info, 2);

      if ($block->delta == $block_id) {

        $data = NULL;
      }
    }
  }
}