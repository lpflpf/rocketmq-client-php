/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

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