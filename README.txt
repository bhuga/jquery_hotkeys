jquery_hotkeys supports generic javascript actions in response to hotkey presses via 
the jquery hotkeys module, available from http://code.google.com/p/js-hotkeys/

After enabling the correct permissions, you'll be able to add generic hotkeys.  You'll
need some familiarity with javascript to make use of them.  A few examples:

Submit content with control-c
Hotkey: ctrl-c
Javascript: $('#node-form').submit()
Pages: node/*

Focus on the title of a post with %
Hotkey: %
Javascript: $('#edit-title').focus()
Pages: node/*

Please be aware that you can possibly open your site to security problems with
poorly considered javascript.
