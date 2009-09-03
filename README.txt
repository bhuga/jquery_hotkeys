// $Id$

jquery_hotkeys supports generic JavaScript actions in response to hotkey
presses via the jQuery hotkeys module, available from:

http://code.google.com/p/js-hotkeys/

After enabling the correct permissions, you'll be able to add generic
hotkeys.  You'll need some familiarity with JavaScript to make use of them. 
A few examples:

Submit content with control-c
Hotkey: ctrl-c
JavaScript: $('#node-form').submit()
Pages: node/*

Focus on the title of a post with %
Hotkey: %
JavaScript: $('#edit-title').focus()
Pages: node/*

Please be aware that you can possibly open your site to security problems
with poorly considered JavaScript.

CREDITS
Significant portions of the admin interface here were adapted from the css
injector module, available at drupal.org/project/css_injector.
