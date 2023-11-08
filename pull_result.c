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

#include "pull_result.h"
#include "message_ext.h"
#include "ext/spl/spl_iterators.h"
#include "ext/spl/spl_exceptions.h"
#include "zend_interfaces.h"

zend_object_handlers pull_result_object_handlers;

#define GET_PULL_RESULT_OBJ()  ROCKETMQ_ZVAL_GET_OBJECT(pull_result_obj, getThis())

void pull_result_object_free_storage(zend_object *object) {
  pull_result_obj *intern = ROCKETMQ_GET_OBJECT(pull_result_obj, object);
  zend_object_std_dtor(&intern->std);
  DEBUG_DESTROY(CLASS_NAME_PULL_RESULT);
  ReleasePullResult(intern->pull_result);
  efree(intern);
}

static zend_object *pull_result_object_create(zend_class_entry *type) {
  pull_result_obj *obj =
      ecalloc(1, sizeof(pull_result_obj) + zend_object_properties_size(type));
  zend_object_std_init(&obj->std, type);
  object_properties_init(&obj->std, type);

  DEBUG_CREATE(CLASS_NAME_PULL_RESULT);
  obj->current = 0;
  obj->std.handlers = &pull_result_object_handlers;
  return &obj->std;
}

PHP_METHOD(pull_result, getPullStatus) {
  RETURN_LONG(GET_PULL_RESULT_OBJ()->pull_result.pullStatus);
}

PHP_METHOD(pull_result, getNextBeginOffset) {
  RETURN_LONG(GET_PULL_RESULT_OBJ()->pull_result.nextBeginOffset);
}

PHP_METHOD(pull_result, getMinOffset) {
  RETURN_LONG(GET_PULL_RESULT_OBJ()->pull_result.minOffset);
}

PHP_METHOD(pull_result, getMaxOffset) {
  RETURN_LONG(GET_PULL_RESULT_OBJ()->pull_result.maxOffset);
}

PHP_METHOD(pull_result, count) {
  RETURN_LONG(GET_PULL_RESULT_OBJ()->pull_result.size);
}

PHP_METHOD(pull_result, valid) 
{
  pull_result_obj *obj = GET_PULL_RESULT_OBJ();
  RETURN_LONG(obj->current >= 0 && obj->current < obj->pull_result.size);
}

PHP_METHOD(pull_result, next) {
  ++ GET_PULL_RESULT_OBJ()->current;
}

PHP_METHOD(pull_result, key) {
  RETURN_LONG(GET_PULL_RESULT_OBJ()->current);
}

PHP_METHOD(pull_result, current) {
  pull_result_obj *obj = GET_PULL_RESULT_OBJ();

  zval message_ext_zval;
  zend_string *class_name = zend_string_init(CLASS_NAME_MESSAGE_EXT, strlen(CLASS_NAME_MESSAGE_EXT), 0);
  zend_class_entry *ce = zend_fetch_class(class_name, ZEND_FETCH_CLASS_AUTO);
  zend_string_release(class_name);
  object_init_ex(&message_ext_zval, ce);

  message_ext_obj *message_ext = ROCKETMQ_ZVAL_GET_OBJECT(message_ext_obj, &message_ext_zval);
  message_ext->message_ext = obj->pull_result.msgFoundList[obj->current];
  RETURN_OBJ(&message_ext->std);
}

PHP_METHOD(pull_result, rewind) {
  GET_PULL_RESULT_OBJ()->current = 0;
  RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_result_get, 0, 0, 1)
ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_result, get) {
  zend_long index;
  ZEND_PARSE_PARAMETERS_START(1, 1)
  Z_PARAM_LONG(index)
  ZEND_PARSE_PARAMETERS_END();

  pull_result_obj *obj = GET_PULL_RESULT_OBJ();

  zval message_ext_zval;
  zend_string *class_name = zend_string_init(CLASS_NAME_MESSAGE_EXT, strlen(CLASS_NAME_MESSAGE_EXT), 0);
  zend_class_entry *ce = zend_fetch_class(class_name, ZEND_FETCH_CLASS_AUTO);
  zend_string_release(class_name);
  object_init_ex(&message_ext_zval, ce);

  message_ext_obj *message_ext = ROCKETMQ_ZVAL_GET_OBJECT(message_ext_obj, &message_ext_zval);
  message_ext->message_ext = obj->pull_result.msgFoundList[index];
  RETURN_OBJ(&message_ext->std);
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_result_seek, 0, 0, 1)
ZEND_ARG_INFO(0, index)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_result, seek)
{
  pull_result_obj *obj = GET_PULL_RESULT_OBJ();

  ROCKETMQ_GET_LONG_PARAM(index);
  if (index > obj->pull_result.size) {
    zend_throw_exception(spl_ce_OutOfBoundsException, "invalid seek position", (zend_long)(uint32_t)-1);
  }
  obj->current = index;
}

const zend_function_entry pull_result_methods[] = {
    ZEND_ME(pull_result, getPullStatus, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, getNextBeginOffset, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, getMinOffset, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, getMaxOffset, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, count, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, valid, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, next, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, key, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, current, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, rewind, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, get, arg_pull_result_get, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_result, seek, arg_pull_result_seek, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_class_entry *pull_result_ce;
void minit_pull_result(){
  zend_class_entry ce;
  // 初始化一个类对象，并将方法绑定到对象上
  INIT_CLASS_ENTRY(ce, CLASS_NAME_PULL_RESULT, pull_result_methods);
  pull_result_ce = zend_register_internal_class_ex(&ce, NULL);

	zend_class_implements(pull_result_ce, 2, spl_ce_SeekableIterator, zend_ce_countable);
  pull_result_ce ->create_object = pull_result_object_create;

  memcpy(&pull_result_object_handlers, zend_get_std_object_handlers(), sizeof(pull_result_object_handlers));
  pull_result_object_handlers.offset = XtOffsetOf(pull_result_obj, std);
  pull_result_object_handlers.free_obj = pull_result_object_free_storage;
}