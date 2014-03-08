# NeoEditor

An extensible text editor for the 21st Century.

![NeoEditor](https://2.gravatar.com/avatar/4ef64cee069318ccce191f598d4bc294?s=128)


## Screenshots

![NeoEditor](https://raw.github.com/NeoEditor/NeoEditor/master/images/screenshot.png)
![NeoEditor](https://raw.github.com/NeoEditor/NeoEditor/master/images/screenshot2.png)


## Features

- desktop application based on web technologies, same as [Atom](https://atom.io/).
- simple and clean source code. (LOC <= 600).
- based on experience. The author of NewEditor is also the author of [slim text] (http://slimtext.org/).
- built with extensibility in mind. In the long run, users will be able to extend the editor via [DSL](http://en.wikipedia.org/wiki/Domain-specific_language)


## Installation

Currently there is no binary distribution package available.

You'd have to install [Qt](http://qt-project.org/downloads) and compile the source code yourself.


## Built with

- [Qt](http://qt-project.org/) 5.2.1
- [Ace](http://ace.c9.io/) [package 02.28.2014](https://github.com/ajaxorg/ace-builds/commit/88f0661bc2b7118e2697d42e36f0985e5edfa5a1)
- [Ubuntu Mono font](http://font.ubuntu.com/)
- [Tango Icon Library](http://tango.freedesktop.org/Tango_Icon_Library)


## Software license

[GPL](http://www.gnu.org/licenses/gpl.html)


## Todo list

5. remember opened folders and files (and other things, such as window size, panel size...etc)
    1. saveSetting and readSettings
11. check memory leak, avoid using keyword `new`
12. handle binary files
23. make it easily extensible
    1. setStyleSheet is super powerful! extract styles to a separate file and let user customize it
26. create installer for ubuntu
    1. application icon background color (why is it green like Qt?) It's unity laucher's backlight
    2. there is specific functionality already in Ubuntu that enables apps to select any tile colour they like.
    3. choosing the app icon and tile colour is up to the app author.
    4. https://bugs.launchpad.net/ubuntu/+source/unity/+bug/1173886
    5. defining the tile background colour in the .desktop file is a hackey solution
    6. https://developer.gnome.org/integration-guide/stable/desktop-files.html.en
31. right panel horizontal scrollbar and vertical scrollbar intersection color
    1. not easy
32. show minimap
    1. QWebView take screenshot of the whole web page.
33. handle exceptions (file not readable, not writable, binary file...etc).
35. style the whole app according to monokai style
    1. then not only the right panel, then whole app can have a consistent look and feel.
36. treeView don't show folder and file icons
41. disable splitter round corner
    1. not easy
42. change "Close Tab" to "Close Folder" and "Close File"
46. change app title text -- necessary, user don't need to check tooltip for whole file path
    1. if file opened, show file path
    2. if folder opened, show folder path
    3. show "an extensible editor for the 21st Century"
47. context menu to close, close all, close other.. etc
50. fork ACE and write code there
    1. ensure_newline_at_eof
    2. Or I can create a repo and write extension for ACE
        1. a faster way to add new features to ACE
        2. there are examples about how to write ACE extensions
        3. maybe this is the key that how can I make the editor extensible
54. prompt to save before exit if changed
59. change all the cross class method calls to use signal/slot ?
60. detect file change and reload file
61. integrate terminal
    1. this is great while it's very hard
65. double click selection behaviour not the same as other editors.
71. more language icons
72. switch tabs, change file highlight in left file tree.
73. drag & drop to reorder tabs
76. alt + tab icon size too small
    1. different os different behavior
77. create file
78. create folder
79. rename file
80. rename folder
81. delete file
82. delete folder
83. quick open file (ctrl + p)
84. drag & drop to move file
85. drag & drop to move folder
86. i18n
    1. not urgent
88. tbc
