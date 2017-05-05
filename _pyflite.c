/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <tflowers@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Tim Flowers
 * ----------------------------------------------------------------------------
 */


#include "pyflite.h"


//TODO:  Add support for default voice...

static PyObject *PyFliteError;

cst_voice* register_voice(const char *voice)
{
  //TODO: Make this dynamically look at the voice list
  cst_voice* v;
  if (strcmp(voice, "slt") == 0) {
    v = register_cmu_us_slt(NULL);
  } else if (strcmp(voice, "kal") == 0) {
    v = register_cmu_us_kal(NULL);
  } else if (strcmp(voice, "kal16") == 0) {
    v = register_cmu_us_kal16(NULL);
  } else if (strcmp(voice, "awb") == 0) {
    v = register_cmu_us_awb(NULL);
  } else if (strcmp(voice, "rms") == 0) {
    v = register_cmu_us_rms(NULL);
  } else {
    PyErr_SetString(PyFliteError, "Invalid Voice");
    return NULL;
  }

  return v;

}

int text_to_wave(const char *text, const char *wave, const char *voice)
{

  int s;
  cst_voice* v;
  flite_init();
  v = register_voice(voice);
  if (v == NULL)
    return NULL;
  cst_wave* w;
  w = flite_text_to_wave(text, v);
  cst_wave_resample(w, 8000);
  return cst_wave_save_riff(w, wave);

}


int file_to_speech(const char *filename, const char *voice)
{

  cst_voice *v;
  flite_init();
  v = register_voice(voice);
  if (v == NULL)
    return NULL;
  flite_file_to_speech(filename, v, "play");
  return 0;

}

int text_to_speech(const char *text, const char *voice)
{

  cst_voice *v;
  flite_init();
  v = register_voice(voice);
  if (v == NULL)
    return NULL;
  flite_text_to_speech(text, v, "play");
  return 0;

}

static void PyFlite_dealloc(PyFlite* self)
{

  Py_XDECREF(self->voices);
  self->ob_type->tp_free((PyObject*)self);

}

static PyObject * PyFlite_new(PyTypeObject *type)
{

  PyFlite *self;

  self = (PyFlite *)type->tp_alloc(type, 0);

  if (self != NULL) {
    self->voices = PyString_FromString("");
    if (self->voices == NULL) {
      Py_DECREF(self);
      return NULL;
    }
  }

  return (PyObject *)self;

}

static int PyFlite_init(PyFlite *self)
{

  PyObject *voices, *tmp;

  cst_voice *voice;
  const cst_val *v;

  //TODO: Make this dynamic!
  voices = Py_BuildValue("[s,s,s,s,s]", "slt", "kal", "kal16", "awb", "rms");

  tmp = self->voices;
  Py_INCREF(voices);
  self->voices = voices;
  Py_XDECREF(tmp);

  return 0;

}


static PyObject* PyFlite_text2wave(PyObject *self, PyObject *args)
{
  const char *wave;
  const char *text;
  const char *voice;
  int sts;

  if (!PyArg_ParseTuple(args, "sss", &text, &wave, &voice))
    return NULL;

  sts = text_to_wave(text, wave, voice);
  if (sts == -1)
    return NULL;

  return Py_BuildValue("i", sts);

}

static PyObject* PyFlite_file2speech(PyObject *self, PyObject *args)
{

  const char *filename;
  const char *voice;
  int sts;

  if (!PyArg_ParseTuple(args, "ss", &filename, &voice))
    return NULL;

  sts = file_to_speech(filename, voice);
  return Py_BuildValue("i", sts);

}

static PyObject* PyFlite_text2speech(PyObject *self, PyObject *args)
{

  const char *text;
  const char *voice;
  int sts;

  if (!PyArg_ParseTuple(args, "ss", &text, &voice))
    return NULL;

  sts = text_to_speech(text, voice);
  return Py_BuildValue("i", sts);

}

static PyMemberDef PyFlite_members[] = {
  {"voices", T_OBJECT_EX, offsetof(PyFlite, voices), 0, "List Of Voices"},
  {NULL},
};

static PyMethodDef PyFlite_methods[] = {

  {"text2wave", (PyCFunction)PyFlite_text2wave, METH_VARARGS, "Convert text to wave"},
  {"file2speech", (PyCFunction)PyFlite_file2speech, METH_VARARGS, "Convert File to Speech"},
  {"text2speech", (PyCFunction)PyFlite_text2speech, METH_VARARGS, "Convert Text to Speech"},
  {NULL},

};

static PyTypeObject PyFliteType = {
  PyObject_HEAD_INIT(NULL)
  0,                                /*ob_size*/
  "_pyflite._PyFlite",                /*tp_name*/
  sizeof(PyFlite),                  /*tp_basicsize*/
  0,                                /*tp_itemsize*/
  (destructor)PyFlite_dealloc,      /*tp_dealloc*/
  0,                                /*tp_print*/
  0,                                /*tp_getattr*/
  0,                                /*tp_setattr*/
  0,                                /*tp_compare*/
  0,                                /*tp_repr*/
  0,                                /*tp_as_number*/
  0,                                /*tp_as_sequence*/
  0,                                /*tp_as_mapping*/
  0,                                /*tp_hash */
  0,                                /*tp_call*/
  0,                                /*tp_str*/
  0,                                /*tp_getattro*/
  0,                                /*tp_setattro*/
  0,                                /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,       /*tp_flags*/
  "PyFlite Object",                 /*tp_doc */
  0,                                /*tp_traverse */
  0,                                /*tp_clear */
  0,                                /*tp_richcompare */
  0,                                /*tp_weaklistoffset */
  0,                                /*tp_iter */
  0,                                /*tp_iternext */
  PyFlite_methods,                  /*tp_methods */
  PyFlite_members,                  /*tp_members */
  0,                                /*tp_getset */
  0,                                /*tp_base */
  0,                                /*tp_dict */
  0,                                /*tp_descr_get */
  0,                                /*tp_descr_set */
  0,                                /*tp_dictoffset */
  (initproc)PyFlite_init,           /*tp_init */
  0,                                /*tp_alloc */
  PyFlite_new,                      /*tp_new */
};


static PyObject* pyflite_text_to_wave(PyObject *self, PyObject *args)
{
  const char *wave;
  const char *text;
  int sts;

  if (!PyArg_ParseTuple(args, "ss", &text, &wave))
    return NULL;

  sts = text_to_wave(text, wave, "slt");
  return Py_BuildValue("i", sts);

}


static PyMethodDef pyflite_funcs[] = {
  {"flite_text_to_wave", (PyCFunction)pyflite_text_to_wave, METH_VARARGS,
  "This method converts text to wave. I'll probably remove it"},
  {NULL, NULL, 0, NULL},
};


#ifndef PyMODINIT_FUNC  /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif

PyMODINIT_FUNC init_pyflite(void)
{

  PyObject* m;

  PyFliteType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&PyFliteType) < 0)
    return;

  m = Py_InitModule("_pyflite", pyflite_funcs);
  Py_INCREF(&PyFliteType);
  PyModule_AddObject(m, "_PyFlite", (PyObject *)&PyFliteType);

  PyFliteError = PyErr_NewException("PyFlite.error", NULL, NULL);
  Py_INCREF(PyFliteError);
  PyModule_AddObject(m, "error", PyFliteError);

}
