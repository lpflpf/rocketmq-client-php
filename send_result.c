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

#include "send_result.h"

#define GET_SEND_RESULT_OBJ() ROCKETMQ_ZVAL_GET_OBJECT(send_result_obj, getThis())

zend_object_handlers send_result_object_handlers;
static zend_object* send_result_object_create(zend_class_entry *type ) 
{
    send_result_obj *obj = (send_result_obj *) ecalloc(1, sizeof(send_result_obj) + zend_object_properties_size(type));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    
    obj->std.handlers = &send_result_object_handlers;
    return &obj->std;
}

void send_result_object_free_storage(zend_object *object)
{
    DEBUG_DESTROY(CLASS_NAME_SEND_RESULT);
    send_result_obj *intern = ROCKETMQ_GET_OBJECT(send_result_obj, object);
    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(send_result, getMsgId) 
{
    RETURN_STRING(GET_SEND_RESULT_OBJ()->send_result.msgId);
}

PHP_METHOD(send_result, getSendStatus)
{
    RETURN_LONG(GET_SEND_RESULT_OBJ()->send_result.sendStatus);
}

PHP_METHOD(send_result, getOffset)
{
    RETURN_LONG(GET_SEND_RESULT_OBJ()->send_result.offset);
}

const zend_function_entry send_result_methods[] = {
    ZEND_ME(send_result, getMsgId, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(send_result, getSendStatus, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(send_result, getOffset, arg_input_void, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_class_entry *send_result_ce;
void minit_send_result(){
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, CLASS_NAME_SEND_RESULT, send_result_methods);
    send_result_ce = zend_register_internal_class_ex(&ce, NULL);
    send_result_ce->create_object = send_result_object_create;

    memcpy(&send_result_object_handlers, zend_get_std_object_handlers(), sizeof(send_result_object_handlers));
    send_result_object_handlers.offset = XtOffsetOf(send_result_obj, std);
    send_result_object_handlers.free_obj = send_result_object_free_storage;
}