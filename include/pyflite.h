

#include <Python.h>
#include <stdio.h>
#include <flite.h>
#include <structmember.h>


cst_voice * register_cmu_us_slt();
cst_voice * register_cmu_us_kal();
cst_voice * register_cmu_us_kal16();
cst_voice * register_cmu_us_awb();
cst_voice * register_cmu_us_rms();

// Function to convert test to wave given voice file
int text_to_wave(const char *text, const char *wave, const char *voice);


// My Type
typedef struct {
  PyObject_HEAD
  PyObject *voices;
} PyFlite;


static void PyFlite_dealloc(PyFlite* self);

static PyObject *PyFlite_new(PyTypeObject *type);

static int PyFlite_init(PyFlite *self);

static PyObject* PyFlite_text2wave(PyObject *self, PyObject *args);

static PyObject* pyflite_text_to_wave(PyObject *self, PyObject *args);

PyMODINIT_FUNC initpyflite(void);
