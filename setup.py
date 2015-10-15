#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Setup for PYFlite Python Module.

Source:: https://github.com/onbeep/pyflite
"""


__title__ = 'pyflite'
__version__ = '1.0.0'
__author__ = 'Greg Albrecht <gba@orionlabs.co>'
__license__ = 'Apache License, Version 2.0'
__copyright__ = 'Copyright 2015 Orion Labs, Inc.'


import os
import sys


try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension  # pylint: disable=F0401,E0611


def publish():
    """Function for publishing package to pypi."""
    if sys.argv[-1] == 'publish':
        os.system('python setup.py sdist upload')
        sys.exit()


publish()


setup(
    name='pyflite',
    version=__version__,
    description='Python Bindings for Flite.',
    author='Tim Flowers',
    author_email='tflowers@gmail.com',
    maintainer='Orion',
    maintainer_email='code@orionlabs.co',
    package_data={'': ['LICENSE']},
    license=open('LICENSE').read(),
    #long_description=open('README.rst').read(),
    url='https://github.com/onbeep/pyflite',
    package_dir={'pyflite': 'pyflite'},
    zip_safe=False,
    include_package_data=True,
    py_modules=['pyflite'],
    ext_modules=[
        Extension(
            '_pyflite',
            include_dirs=['/usr/include/flite/', './include/'],
            libraries=[
                'flite',
                'flite_cmu_us_slt',
                'flite_cmu_us_kal',
                'flite_cmu_us_kal16',
                'flite_cmu_us_awb',
                'flite_cmu_us_rms',
                'flite_usenglish',
                'flite_cmulex'
            ],
            sources=['_pyflite.c']
        )
    ]
)
