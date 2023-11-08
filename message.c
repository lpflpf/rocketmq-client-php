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
#include "message.h"

zend_object_handlers message_object_handlers;

#define GET_MESSAGE_OBJ() ROCKETMQ_ZVAL_GET_OBJECT(message_obj, getThis())

void message_object_free_storage(zend_object *object)
{
    message_obj *intern = ROCKETMQ_GET_OBJECT(message_obj, object);
    zend_object_std_dtor(&intern->std);
    DEBUG_DESTROY(CLASS_NAME_MESSAGE);
}

static zend_object* message_object_create(zend_class_entry *type ) 
{
    message_obj *obj = ecalloc(1, sizeof(message_obj) + zend_object_properties_size(type));
    obj->message = NULL;
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);

    obj->std.handlers = &message_object_handlers;
    return &obj->std;
}

// create_message_args
ZEND_BEGIN_ARG_INFO_EX(arg_msg__construct, 0, 0, 1)
ZEND_ARG_INFO(0, topic)
ZEND_END_ARG_INFO()

// destroy_message args
ZEND_BEGIN_ARG_INFO_EX(arg_msg_destroy_message, 0, 0, 1)
ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

// set_message_topic args
ZEND_BEGIN_ARG_INFO_EX(arg_msg_set_message_topic, 0, 0, 1)
ZEND_ARG_INFO(0, topic)
ZEND_END_ARG_INFO()

// set_message_tags args
ZEND_BEGIN_ARG_INFO_EX(arg_msg_set_message_tags, 0, 0, 1)
ZEND_ARG_INFO(0, tags)
ZEND_END_ARG_INFO()

// set_message_keys args
ZEND_BEGIN_ARG_INFO_EX(arg_msg_set_message_keys, 0, 0, 1)
ZEND_ARG_INFO(0, keys)
ZEND_END_ARG_INFO()

// set_message_body args
ZEND_BEGIN_ARG_INFO_EX(arg_msg_set_message_body, 0, 0, 1)
ZEND_ARG_INFO(0, body)
ZEND_END_ARG_INFO()

// set_message_property
ZEND_BEGIN_ARG_INFO_EX(arg_msg_set_message_property, 0, 0, 2)
ZEND_ARG_INFO(0, key)
ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

// set_delay_time_level args
ZEND_BEGIN_ARG_INFO_EX(arg_msg_set_delay_time_level, 0, 0, 1)
ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()


ZEND_BEGIN_ARG_INFO_EX(arg_msg_get_origin_message_property, 0, 0, 1)
ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

PHP_METHOD(message, __construct) {
    ROCKETMQ_GET_STR_PARAM(topic);
    message_obj *obj = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, getThis());
    obj->message = CreateMessage(topic);
    RETURN_TRUE;
}

PHP_METHOD(message, __destruct) {
    RETURN_TRUE;
}

PHP_METHOD(message, setMessageTopic)
{
    ROCKETMQ_GET_STR_PARAM(topic);
    RETURN_LONG(SetMessageTopic(GET_MESSAGE_OBJ()->message, topic));
}

PHP_METHOD(message, setMessageTags)
{
    ROCKETMQ_GET_STR_PARAM(tags);
    RETURN_LONG(SetMessageTags(GET_MESSAGE_OBJ()->message, tags));
}

PHP_METHOD(message, setMessageKeys)
{
    ROCKETMQ_GET_STR_PARAM(keys);
    RETURN_LONG(SetMessageKeys(GET_MESSAGE_OBJ()->message, keys));
}

PHP_METHOD(message, setMessageBody)
{
    ROCKETMQ_GET_STR_PARAM(body);
    RETURN_LONG(SetMessageBody(GET_MESSAGE_OBJ()->message, body));
}

PHP_METHOD(message, setMessageProperty) 
{
    char *key, *value;
    size_t key_len, value_len;
    ZEND_PARSE_PARAMETERS_START(2, 2) 
    Z_PARAM_STRING(key, key_len) 
    Z_PARAM_STRING(value, value_len) 
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(SetMessageProperty(GET_MESSAGE_OBJ()->message, key, value));
}

PHP_METHOD(message, setDelayTimeLevel)
{
    zend_long level;

    ZEND_PARSE_PARAMETERS_START(1,1) 
    Z_PARAM_LONG(level)
    ZEND_PARSE_PARAMETERS_END();
    RETURN_LONG(SetDelayTimeLevel(GET_MESSAGE_OBJ()->message, level));
}

PHP_METHOD(message, getOriginMessageTopic) 
{
    RETURN_STRING(GetOriginMessageTopic(GET_MESSAGE_OBJ()->message));
}

PHP_METHOD(message, getOriginMessageTags)
{
    RETURN_STRING(GetOriginMessageTags(GET_MESSAGE_OBJ()->message));
}

PHP_METHOD(message, getOriginMessageKeys)
{
    RETURN_STRING(GetOriginMessageKeys(GET_MESSAGE_OBJ()->message));
}

PHP_METHOD(message, getOriginMessageBody)
{
    RETURN_STRING(GetOriginMessageBody(GET_MESSAGE_OBJ()->message));
}

PHP_METHOD(message, getOriginMessageProperty)
{
    ROCKETMQ_GET_STR_PARAM(key);
    RETURN_STRING(GetOriginMessageProperty(GET_MESSAGE_OBJ()->message, key));
}

PHP_METHOD(message, getOriginDelayTimeLevel)
{
    RETURN_LONG(GetOriginDelayTimeLevel(GET_MESSAGE_OBJ()->message));
}

const zend_function_entry message_methods[] = {
    ZEND_ME(message, __construct, arg_msg__construct, ZEND_ACC_PUBLIC)
    ZEND_ME(message, __destruct, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message, setMessageTopic, arg_msg_set_message_topic, ZEND_ACC_PUBLIC)
    ZEND_ME(message, setMessageTags, arg_msg_set_message_tags, ZEND_ACC_PUBLIC)
    ZEND_ME(message, setMessageKeys, arg_msg_set_message_keys, ZEND_ACC_PUBLIC)
    ZEND_ME(message, setMessageBody, arg_msg_set_message_body, ZEND_ACC_PUBLIC)
    ZEND_ME(message, setMessageProperty, arg_msg_set_message_property, ZEND_ACC_PUBLIC)
    ZEND_ME(message, setDelayTimeLevel, arg_msg_set_delay_time_level, ZEND_ACC_PUBLIC)
    ZEND_ME(message, getOriginMessageTopic, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message, getOriginMessageTags, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message, getOriginMessageKeys, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message, getOriginMessageBody, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message, getOriginMessageProperty, arg_msg_get_origin_message_property, ZEND_ACC_PUBLIC)
    ZEND_ME(message, getOriginDelayTimeLevel, arg_input_void, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_class_entry *message_ce;
void minit_message(){
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, CLASS_NAME_MESSAGE, message_methods);
  message_ce = zend_register_internal_class_ex(&ce, NULL);
  message_ce ->create_object = message_object_create;

  memcpy(&message_object_handlers, zend_get_std_object_handlers(), sizeof(message_object_handlers));
  message_object_handlers.offset = XtOffsetOf(message_obj, std);
  message_object_handlers.free_obj = message_object_free_storage;
}