jquery_hotkeys supports generic javascript actions in response to hotkey presses via 
the jquery hotkeys module, available from http://code.google.com/p/js-hotkeys/

For this module to work, you'll need to download a version of jquery hotkeys and create
a symlink at jquery.hotkeys.js for the module to load.  For example, to install the
minified version of 0.7.9 on *nix:

wget http://js-hotkeys.googlecode.com/files/jquery.hotkeys-0.7.9.min.js
ln -s jquery.hotkeys-0.7.9.min.js jquery.hotkeys.js

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
