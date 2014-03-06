# NeoEditor

An extensible text editor for the 21st Century.


## todo list

5. remember opened folders and files (and other things, such as window size, panel size...etc)
    1. saveSetting and readSettings
11. check memory leak, avoid using keyword `new`
12. handle binary files
23. make it easily extensible
    1. setStyleSheet is super powerful! extract styles to a separate file and let user customize it
24. change name to NotAtom and open source it?
26. application icon background color (why is it green like Qt?)
    1. It's unity laucher's backlight
    2. there is specific functionality already in Ubuntu that enables apps to select any tile colour they like.
    3. choosing the app icon and tile colour is up to the app author.
    4. https://bugs.launchpad.net/ubuntu/+source/unity/+bug/1173886
    5. defining the tile background colour in the .desktop file is a hackey solution
    6. https://developer.gnome.org/integration-guide/stable/desktop-files.html.en
27. show splash screen
    1. not very necessary
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
44. add menu (menu and toolbar take the same line)
45. add status bar
46. change app title text
    1. if file opened, show file path
    2. if folder opened, show folder path
    3. show "an extensible editor for the 21st Century"
47. context menu to close, close all, close other.. etc
48. platform specific save icon and open folder icon
    1. not necessary
49. bug: not share the same clipboard with the system ?
    1. maybe caused by debug mode
50. fork ACE and write code there
    1. ensure_newline_at_eof
54. prompt to save before exit if changed
56.
