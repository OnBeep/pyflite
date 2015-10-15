pyflite
=======

A simple python wrapper for the Flite TTS library.

Install
=======
On linux you can run "make install"

Usage
=====

Example usage::

    import pyflite
    pf = pyflite.PyFlite()
    print pf.voices  # Returns a list of voices
    pf.text2wave("YOUR TEXT GOES HERE", "FILENAME.WAV", "VOICE NAME")
    pf.file2speech("filename", "VOICE NAME")
    pf.text2speech("YOUR TEXT GOES HERE", "VOICE NAME")
