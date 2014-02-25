$ ->
    $('#quit').click ->
        app.quit()

    $('#open').click ->
        alert "You select file: #{mainWindow.openFileDialog()}"
