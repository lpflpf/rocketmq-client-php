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

#include "mq_exception.h"

zend_object_handlers mq_exception_object_handlers;
#define GET_MQ_EXCEPTION_OBJ() ROCKETMQ_ZVAL_GET_OBJECT(mq_exception_obj, getThis())
static zend_object* mq_exception_object_create(zend_class_entry *type ) 
{
    mq_exception_obj *obj = (mq_exception_obj *) ecalloc(1, sizeof(mq_exception_obj) + zend_object_properties_size(type));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.handlers = &mq_exception_object_handlers;
    return &obj->std;
}

void mq_exception_ext_object_free_storage(zend_object *object)
{
    DEBUG_DESTROY(CLASS_NAME_MQ_EXCEPTION);
    mq_exception_obj *intern = ROCKETMQ_GET_OBJECT(mq_exception_obj, object);
    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(mq_exception, getError)
{
    RETURN_LONG(GET_MQ_EXCEPTION_OBJ()->mq_exception.error);
}

PHP_METHOD(mq_exception, getLine)
{
    RETURN_LONG(GET_MQ_EXCEPTION_OBJ()->mq_exception.line);
}

PHP_METHOD(mq_exception, getFile)
{
    RETURN_STRING(GET_MQ_EXCEPTION_OBJ()->mq_exception.file);
}

PHP_METHOD(mq_exception, getMsg)
{
    RETURN_STRING(GET_MQ_EXCEPTION_OBJ()->mq_exception.msg);
}

PHP_METHOD(mq_exception, getType)
{
    RETURN_STRING(GET_MQ_EXCEPTION_OBJ()->mq_exception.type);
}

const zend_function_entry mq_exception_methods[] = {
    ZEND_ME(mq_exception, getError, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(mq_exception, getLine, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(mq_exception, getFile, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(mq_exception, getMsg, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(mq_exception, getType, arg_input_void, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void minit_mq_exception(){
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, CLASS_NAME_MQ_EXCEPTION, mq_exception_methods);
  mq_exception_ce= zend_register_internal_class_ex(&ce, NULL);
  mq_exception_ce->create_object = mq_exception_object_create;

  memcpy(&mq_exception_object_handlers, zend_get_std_object_handlers(), sizeof(mq_exception_object_handlers));
  mq_exception_object_handlers.offset = XtOffsetOf(mq_exception_obj, std);
  mq_exception_object_handlers.free_obj = mq_exception_ext_object_free_storage;
}