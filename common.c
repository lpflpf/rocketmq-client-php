#include "common.h"

zval create_object_zval(char *classname) {
  zval _zval;
  zend_string *_classname = zend_string_init(classname, strlen(classname), 0);
  zend_class_entry *_ce = zend_fetch_class(_classname, ZEND_FETCH_CLASS_AUTO);
  zend_string_release(_classname);
  object_init_ex(&_zval, _ce);
  return _zval;
}

static void destroy_fci(diy_callback *callback) {
  if (callback->fci.size > 0) {
    zval_ptr_dtor(&callback->fci.function_name);
    callback->fci.size = 0;
  }
  if (!Z_ISUNDEF_P(&callback->object)) {
    zval_ptr_dtor(&callback->object);
    ZVAL_UNDEF(&callback->object);
  }
}

void replace_fci(diy_callback *callback, zend_fcall_info fci, zend_fcall_info_cache fcc) {
  destroy_fci(callback);
  if (fci.size > 0) {
    callback->fci = fci;
    Z_ADDREF(fci.function_name);
    if (fci.object != NULL) {
      ZVAL_OBJ(&callback->object, fci.object);
      Z_ADDREF(callback->object);
    }
    callback->fcc = fcc;
  }
}