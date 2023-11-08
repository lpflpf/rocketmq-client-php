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

#include "message_queues.h"

zend_object_handlers message_queues_object_handlers;

void message_queues_object_free_storage(zend_object *object)
{
    message_queues_obj *intern = ROCKETMQ_GET_OBJECT(message_queues_obj, object);
    zend_object_std_dtor(&intern->std);
    if (intern->message_queues){
        DEBUG_DESTROY(CLASS_NAME_MESSAGE_QUEUE);
        ReleaseSubscriptionMessageQueue(intern->message_queues);
    }
}

static zend_object* message_queues_object_create(zend_class_entry *type ) 
{
    message_queues_obj *obj = ecalloc(1, sizeof(message_queues_obj) + zend_object_properties_size(type));
    obj->message_queues = NULL;
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);

    obj->std.handlers = &message_queues_object_handlers;
    obj->size = 0;
    obj->message_queues = NULL;
    return &obj->std;
}

PHP_METHOD(message_queues, getTopic)
{
    message_queues_obj *obj = ROCKETMQ_ZVAL_GET_OBJECT(message_queues_obj, getThis());

    if (obj->size > 0 && obj->message_queues != NULL) {
        RETURN_STRING(obj->message_queues[0].topic);
    }
    RETURN_NULL();
}

PHP_METHOD(message_queues, getQueueSize)
{
    message_queues_obj *obj = ROCKETMQ_ZVAL_GET_OBJECT(message_queues_obj, getThis());
    RETURN_LONG(obj->size);
}


const zend_function_entry message_queues_methods[] = {
    ZEND_ME(message_queues, getTopic, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_queues, getQueueSize, arg_input_void, ZEND_ACC_PUBLIC)

    {NULL, NULL, NULL}
};

static zend_class_entry *message_queue_ce;

void minit_message_queues(){
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, CLASS_NAME_MESSAGE_QUEUE, message_queues_methods);
  message_queue_ce = zend_register_internal_class_ex(&ce, NULL);
  message_queue_ce->create_object = message_queues_object_create;

  memcpy(&message_queues_object_handlers, zend_get_std_object_handlers(), sizeof(message_queues_object_handlers));
  message_queues_object_handlers.offset = XtOffsetOf(message_queues_obj, std);
  message_queues_object_handlers.free_obj = message_queues_object_free_storage;
}