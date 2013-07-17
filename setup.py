
from distutils.core import setup, Extension

text2wave = Extension('_pyflite',
                      include_dirs = ['/usr/include/flite/', './include/'],
                      libraries=['flite', 'flite_cmu_us_slt', 
                      'flite_cmu_us_kal', 'flite_cmu_us_kal16',
                      'flite_cmu_us_awb', 'flite_cmu_us_rms',
                      'flite_usenglish', 'flite_cmulex'],
                      sources=['_pyflite.c'])

setup(name='_pyflite', version='1.0',\
ext_modules=[text2wave])

