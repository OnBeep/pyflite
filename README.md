pyflite
=======

A simple python wrapper for the Flite TTS library.


Install
=======
On linux you can run "sudo python setup.py install"
NOTE:  At this time it only installs the c libary, i'll update to install the python wrapper later

Usage
=====
```python
  from pyflite import PyFlite

  pf = PyFlite()

  pf.voices -- returns a list of voices

  pf.text2wave("YOUR TEXT GOES HERE", "FILENAME.WAV", "VOICE NAME")

  pf.file2speech("filename", "VOICE NAME")

  pf.text2speech("YOUR TEXT GOES HERE", "VOICE NAME")

```


NOTE
====
This was thrown together in a day so use at your own risk 
