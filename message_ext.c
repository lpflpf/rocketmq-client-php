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

#include "message_ext.h"

zend_object_handlers message_ext_object_handlers;

#define GET_MESSAGE_EXT_OBJ()  ROCKETMQ_ZVAL_GET_OBJECT(message_ext_obj, getThis())

static zend_object* message_ext_object_create(zend_class_entry *type ) 
{
    message_ext_obj *obj = (message_ext_obj *) ecalloc(1, sizeof(message_ext_obj) + zend_object_properties_size(type));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.handlers = &message_ext_object_handlers;
    DEBUG_CREATE(CLASS_NAME_MESSAGE_EXT);
    return &obj->std;
}

void message_ext_object_free_storage(zend_object *object)
{
    message_ext_obj *intern = ROCKETMQ_GET_OBJECT(message_ext_obj, object);

    DEBUG_DESTROY(CLASS_NAME_MESSAGE_EXT);
    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(message_ext, getMessageTopic) {
    RETURN_STRING(GetMessageTopic(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessageTags) {
    RETURN_STRING(GetMessageTags(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessageKeys){
    RETURN_STRING(GetMessageKeys(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessageBody){
    RETURN_STRING(GetMessageBody(GET_MESSAGE_EXT_OBJ()->message_ext));
}

ZEND_BEGIN_ARG_INFO_EX(arg_msg_ext__getMessageProperty, 0, 0, 1)
ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

PHP_METHOD(message_ext, getMessageProperty){
    ROCKETMQ_GET_STR_PARAM(key);
    RETURN_STRING(GetMessageProperty(GET_MESSAGE_EXT_OBJ()->message_ext, key));
}

PHP_METHOD(message_ext, getMessageId){
    RETURN_STRING(GetMessageId(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessageDelayTimeLevel){
    RETURN_LONG(GetMessageDelayTimeLevel(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessageQueueId){
    RETURN_LONG(GetMessageQueueId(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessageReconsumeTimes){
    RETURN_LONG(GetMessageReconsumeTimes(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessageStoreSize){
    RETURN_LONG(GetMessageStoreSize(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessageBornTimestamp){
    RETURN_LONG(GetMessageBornTimestamp(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessageStoreTimestamp){
    RETURN_LONG(GetMessageStoreTimestamp(ROCKETMQ_ZVAL_GET_OBJECT(message_ext_obj, getThis())->message_ext));
}

PHP_METHOD(message_ext, getMessageQueueOffset){
    RETURN_LONG(GetMessageQueueOffset(GET_MESSAGE_EXT_OBJ()->message_ext));
}


PHP_METHOD(message_ext, getMessageCommitLogOffset){
    RETURN_LONG(GetMessageCommitLogOffset(GET_MESSAGE_EXT_OBJ()->message_ext));
}

PHP_METHOD(message_ext, getMessagePreparedTransactionOffset){
    RETURN_LONG(GetMessagePreparedTransactionOffset(GET_MESSAGE_EXT_OBJ()->message_ext));
}

const zend_function_entry message_ext_methods[] = {
    ZEND_ME(message_ext, getMessageTopic, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageTags, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageKeys, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageBody, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageProperty, arg_msg_ext__getMessageProperty, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageId, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageDelayTimeLevel, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageQueueId, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageReconsumeTimes, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageStoreSize, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageBornTimestamp, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageStoreTimestamp, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageQueueOffset, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessageCommitLogOffset, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(message_ext, getMessagePreparedTransactionOffset, arg_input_void, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_class_entry *message_ext_ce;
void minit_message_ext(){
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, CLASS_NAME_MESSAGE_EXT, message_ext_methods);
  message_ext_ce = zend_register_internal_class_ex(&ce, NULL);
  message_ext_ce ->create_object = message_ext_object_create;

  memcpy(&message_ext_object_handlers, zend_get_std_object_handlers(), sizeof(message_ext_object_handlers));
  message_ext_object_handlers.offset = XtOffsetOf(message_ext_obj, std);
  message_ext_object_handlers.free_obj = message_ext_object_free_storage;
}