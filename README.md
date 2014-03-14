# NeoEditor

An extensible text editor for the 21st Century.

![NeoEditor](https://2.gravatar.com/avatar/4ef64cee069318ccce191f598d4bc294?s=128)


## Screenshot

![NeoEditor](https://raw.github.com/NeoEditor/NeoEditor/master/images/screenshot4.png)


## Features

- desktop application based on web technologies, same as [Atom](https://atom.io/).
- simple and clean source code. (LOC <= 800).
- based on experience. The author of NewEditor is also the author of [slim text] (http://slimtext.org/).
- built with extensibility in mind. In the long run, users will be able to extend the editor via [DSL](http://en.wikipedia.org/wiki/Domain-specific_language).
- cross-platform: Windows, Linux/X11, Mac OS X.


## Installation

Currently there is no binary distribution package available.

You'd have to install [Qt](http://qt-project.org/downloads) and compile the source code yourself.


## Built with

- [Qt](http://qt-project.org/) 5.2.1
- [Ace](http://ace.c9.io/) [package 03.08.2014](https://github.com/ajaxorg/ace-builds/commit/fc9d2cae9fe8e6e95e74c86a31d21caadd8f9f39)
- [Ubuntu Mono font](http://font.ubuntu.com/)
- [Tango Icon Library](http://tango.freedesktop.org/Tango_Icon_Library)


## Software license

[GPL](http://www.gnu.org/licenses/gpl.html)


## Todo list

11. check memory leak, avoid using keyword `new`
12. handle binary files
26. create installer for ubuntu
    1. application icon background color (why is it green like Qt?) It's unity laucher's backlight
    2. there is specific functionality already in Ubuntu that enables apps to select any tile colour they like.
    3. choosing the app icon and tile colour is up to the app author.
    4. https://bugs.launchpad.net/ubuntu/+source/unity/+bug/1173886
    5. defining the tile background colour in the .desktop file is a hackey solution
    6. https://developer.gnome.org/integration-guide/stable/desktop-files.html.en
32. show minimap
    1. QWebView take screenshot of the whole web page.
33. handle exceptions (file not readable, not writable, binary file...etc).
46. change app title text -- necessary, user don't need to check tooltip for whole file path
    1. if file opened, show file path
    2. if folder opened, show folder path
    3. show "an extensible editor for the 21st Century"
50. fork ACE and write code there
    1. ensure_newline_at_eof
    2. Or I can create a repo and write extension for ACE
        1. a faster way to add new features to ACE
        2. there are examples about how to write ACE extensions
        3. maybe this is the key that how can I make the editor extensible
        4. yes, write ext in org NeoEditor on Github
59. change all the cross class method calls to use signal/slot ?
60. detect file change and reload file
61. integrate terminal
    1. this is great while it's very hard
71. more language icons
72. switch tabs, change file highlight in left file tree.
73. drag & drop to reorder tabs
77. create file
78. create folder
79. rename file
80. rename folder
81. delete file
82. delete folder
83. quick open file (ctrl + p)
84. drag & drop to move file
85. drag & drop to move folder
88. use command line + NeoEditor to write NeoEditor, get rid of qtcreator
89. add "vim mode", a toolbar button on the left with states
90. left and right two toolbars, editing toolbar on the right, others on the left
92. show invisible files, otherwise cannot edit .gitignore .bashrc...etc
94. bug: presessing ESC inserts new character
95. hide all binary files ? the editor cannot handle binary files anyway.
96. remove `direction` from WebView context menu
97. bug: open file, rename file's folder, save file. cannot save
98. auto complete, according to text in the same file. better than none. tab key to trigger?
100. context menu issue
    1. if no selection, copy & cut don't make sense
    2. `direction` doesn't make sense
    3. if selected, select all doesn't make sense
101. tbc
