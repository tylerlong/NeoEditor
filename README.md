# NeoEditor

An extensible text editor for the 21st Century.


## todo list

5. remember opened folders and files (and other things, such as window size, panel size...etc)
7. indicate file changed or not
8. add states to saveFile icon
9. trim trailing space
10. ensure new line at the end of file
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
31. horizontal scroll bar and vertical scroll bar cross point color
32. show minimap
    1. QWebView take screenshot of the whole web page.
33. handle exceptions (file not readable, not writable, binary file...etc).
34. bug, file tab tooltip color wrong
    1. commenting out `rightTabWidget->setStyleSheet("border: 0");` fixes issue.
    2. maybe I should set style on its parent widget
    3. what's qt stylesheet selector rule?
35. style the whole app according to monokai style
    1. then not only the right panel, then whole app can have a consistent look and feel.
36. treeView don't show folder and file icons
38. merge toolbar and top tab bar, like chrome
    1. add label above left panel
39. What does `tr` mean in `tr("some text")`?
40. left treeView show header of current folder name
    1. or a label above the treeView
    2. dropdown box instead? then no need of left tab widget
41.
