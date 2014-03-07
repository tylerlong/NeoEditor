# NeoEditor

An extensible text editor for the 21st Century.


## todo list

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
39. What does `tr` mean in `tr("some text")`?
41. disable splitter round corner
    1. not easy
42. change "Close Tab" to "Close Folder" and "Close File"
43. about dialog icon size
46. change app title text -- necessary, user don't need to check tooltip for whole file path
    1. if file opened, show file path
    2. if folder opened, show folder path
    3. show "an extensible editor for the 21st Century"
47. context menu to close, close all, close other.. etc
50. fork ACE and write code there
    1. ensure_newline_at_eof
54. prompt to save before exit if changed
58. Move webView code to its constructor
59. change all the cross class method calls to use signal/slot ?
60. detect file change and reload file
61. integrate terminal
    1. this is great while it's very hard
64. make it open source
    1. alipay receive money link
    2. add screenshot to readme file
65. double click selection behaviour not the same as other editors.
66. move copy/cut/paste code to WebView class only
67. remove editor context menu
68. tbc
