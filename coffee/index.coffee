$ ->
    $('#quit').click ->
        qt.quit()

    $('#open').click ->
        alert "You select file: #{qt.openFileDialog()}"
