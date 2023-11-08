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

#include "batch_message.h"
zend_object_handlers batch_message_object_handlers;

void batch_message_object_free_storage(zend_object *object) {
  batch_message_obj *intern = ROCKETMQ_GET_OBJECT(batch_message_obj, object);
  zend_object_std_dtor(&intern->std);
  if (intern->batch_message) {
    DEBUG_DESTROY(CLASS_NAME_BATCH_MESSAGE);
    DestroyBatchMessage(intern->batch_message);
  }
}

static zend_object *message_object_create(zend_class_entry *type) {
  batch_message_obj *obj = ecalloc(1, sizeof(batch_message_obj) + zend_object_properties_size(type));
  obj->batch_message = NULL;
  zend_object_std_init(&obj->std, type);
  object_properties_init(&obj->std, type);

  obj->std.handlers = &batch_message_object_handlers;
  return &obj->std;
}

PHP_METHOD(batch_message, __construct) {
  batch_message_obj *obj = ROCKETMQ_ZVAL_GET_OBJECT(batch_message_obj, getThis());
  obj->batch_message = CreateBatchMessage();
}

ZEND_BEGIN_ARG_INFO_EX(arg_batch_message__addMessage, 0, 0, 1)
ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

PHP_METHOD(batch_message, addMessage) {
  zval *zval_msg_val = NULL;
  ZEND_PARSE_PARAMETERS_START(1, 1)
  Z_PARAM_ZVAL_EX(zval_msg_val, 0, 1)
  ZEND_PARSE_PARAMETERS_END();

  message_obj *msg_val = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, zval_msg_val);
  batch_message_obj *obj = ROCKETMQ_ZVAL_GET_OBJECT(batch_message_obj, getThis());

  RETURN_LONG(AddMessage(obj->batch_message, msg_val->message));
}

const zend_function_entry batch_message_methods[] = {
    ZEND_ME(batch_message, __construct, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(batch_message, addMessage, arg_batch_message__addMessage, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_class_entry *batch_message_ce;
void minit_batch_message() {
  zend_class_entry ce;

  INIT_CLASS_ENTRY(ce, CLASS_NAME_BATCH_MESSAGE, batch_message_methods);
  batch_message_ce = zend_register_internal_class_ex(&ce, NULL);
  batch_message_ce->create_object = message_object_create;

  memcpy(&batch_message_object_handlers, zend_get_std_object_handlers(), sizeof(batch_message_object_handlers));
  batch_message_object_handlers.offset = XtOffsetOf(batch_message_obj, std);
  batch_message_object_handlers.free_obj = batch_message_object_free_storage;
}