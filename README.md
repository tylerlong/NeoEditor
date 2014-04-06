# NeoEditor

An extensible text editor for the 21st Century.

![NeoEditor](https://2.gravatar.com/avatar/4ef64cee069318ccce191f598d4bc294?s=128)


## Screenshot

![NeoEditor](https://raw.github.com/NeoEditor/NeoEditor/master/images/screenshot7.png)


## Features

- desktop application based on web technologies, same as [Atom](https://atom.io/).
- simple and clean source code. (LOC < 1000).
- based on experience. The author of NewEditor is also the author of [slim text] (http://slimtext.org/).
- built with extensibility in mind. In the long run, users will be able to extend the editor via [DSL](http://en.wikipedia.org/wiki/Domain-specific_language).
- cross-platform: Windows, Linux/X11, Mac OS X.


## Installation

Currently there is no binary distribution package available.

You'd have to compile the source code yourself. Here are the steps:

1. Download and Install Qt + Qt Creator
2. sudo apt-get install libxslt1-dev libgstreamer-plugins-base0.10-dev libx11-dev libglu1-mesa-dev
3. Open Qt Creator
4. Open this project
5. Ctrl + R to run


## Built with

- [Qt](http://qt-project.org/)
- [Ace](http://ace.c9.io/)
- [Ubuntu Mono font](http://font.ubuntu.com/)
- [Tango Icon Library](http://tango.freedesktop.org/Tango_Icon_Library)


## Linux IBus IME issue (中文输入问题)

edit `/etc/environment`, add:

    export GTK_IM_MODULE=ibus
    export XMODIFIERS=@im=ibus
    export QT_IM_MODULE=ibus

Relogin or reboot.


## Software license

[GPL](http://www.gnu.org/licenses/gpl.html)


## Todo list

26. create installer for Ubuntu
    1. just create deb file. allow users to apt-get install neo-editor
32. show minimap
    1. QWebView take screenshot of the whole web page.
    2. remove scroll bar because it's not needed
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
    3. this is about the extensibility, a very big topic. think about it carefully
60. detect file change and reload file
    2. check file exists or not, check file content modified or not.
    3. this is important. my work got overwrited which sucks
61. integrate terminal
    1. this is great while it's very hard
    2. https://github.com/skavanagh/KeyBox
72. switch tabs, change file highlight in left file tree.
    1. auto select newly created file / folder
73. drag & drop
    2. to move file
    3. to move folder
89. add "vim mode", a toolbar button on the left with states
92. show invisible files, otherwise cannot edit .gitignore .bashrc...etc
94. bug: presessing ESC inserts new character
96. handle binary files
    1. hide all binary files ? the editor cannot handle binary files anyway.
    2. hexadecimal editor?
98. auto complete, according to text in the same file. better than none.
    1. tab key to trigger? not a good idea, because there are conflicts
    2. use context menu to show candidates
104. toolbar icon for word wrap
105. add "open with NeoEditor" context menu to os
    1. first need to be able to open a file
    2. and create installer for OS
106. refactor code about how to choose language icon. select icon according to editor language mode. and configure icons in js file.
    1. js code call cplusplus code to set language icon
107. refactoring: make `parent` as small as possible
112. refresh treeView after adding new folder or file
    1. because not sorted
116. use Atom's theme and icons
    1. don't forget the OpenAtom idea
117. close folder tab, auto focus remaining tab, disable this behavior
    1. confirmed this issue. very annoying.
118. remember current line of active editor before exit
120. tabbar::tab:first{padding: {gutter_width}px;}
    1. gutter width is dynamic, so this needs to be dynamtic too
124. left browser tree is too dim and dark
    1. try some bright colors instead
125. when dragging, there is a white line
    1. default QTabBar doesn't have this issue
126. improve ctrl + p feature
127. tbc
