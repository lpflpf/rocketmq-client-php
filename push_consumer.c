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

#include "push_consumer.h"

zend_object_handlers push_consumer_object_handlers;

#define GET_PUSH_CONSUMER_OBJ()  ROCKETMQ_ZVAL_GET_OBJECT(push_consumer_obj, getThis())

void push_consumer_object_free_storage(zend_object *object) {
  push_consumer_obj *intern = ROCKETMQ_GET_OBJECT(push_consumer_obj, object);
  zend_object_std_dtor(&intern->std);
  DEBUG_DESTROY(CLASS_NAME_PUSH_CONSUMER);
  if (intern->push_consumer) {
  }
  efree(intern);
}

static zend_object *push_consumer_object_create(zend_class_entry *type) {
  push_consumer_obj *obj = ecalloc(1, sizeof(push_consumer_obj) + zend_object_properties_size(type));
  obj->push_consumer = NULL;
  zend_object_std_init(&obj->std, type);
  object_properties_init(&obj->std, type);

  DEBUG_CREATE(CLASS_NAME_PUSH_CONSUMER);
  obj->std.handlers = &push_consumer_object_handlers;
  return &obj->std;
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__construct, 0, 0, 1)
ZEND_ARG_INFO(0, groupId)
ZEND_END_ARG_INFO()

PHP_METHOD(push_consumer, __construct)
{
  ROCKETMQ_GET_STR_PARAM(groupId);
  ROCKETMQ_ZVAL_GET_OBJECT(push_consumer_obj, getThis())->push_consumer = CreatePushConsumer(groupId);
  RETURN_TRUE;
}

PHP_METHOD(push_consumer, start)
{
    RETURN_LONG(StartPushConsumer(GET_PUSH_CONSUMER_OBJ()->push_consumer));
}

PHP_METHOD(push_consumer, shutdown)
{
    ShutdownPushConsumer(GET_PUSH_CONSUMER_OBJ()->push_consumer);
    RETURN_LONG(DestroyPushConsumer(GET_PUSH_CONSUMER_OBJ()->push_consumer));

}

PHP_METHOD(push_consumer, version)
{
    RETURN_STRING(ShowPushConsumerVersion(GET_PUSH_CONSUMER_OBJ()->push_consumer));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_group_id, 0, 0, 1)
ZEND_ARG_INFO(0, groupId)
ZEND_END_ARG_INFO()

PHP_METHOD(push_consumer, setGroupId)
{
    ROCKETMQ_GET_STR_PARAM(group_id);
    RETURN_LONG(SetPushConsumerGroupID(GET_PUSH_CONSUMER_OBJ()->push_consumer, group_id));
}

PHP_METHOD(push_consumer, getGroupId)
{
    RETURN_STRING(GetPushConsumerGroupID(GET_PUSH_CONSUMER_OBJ()->push_consumer));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_name_server_address, 0, 0, 1)
ZEND_ARG_INFO(0, address)
ZEND_END_ARG_INFO()

PHP_METHOD(push_consumer, setNameServerAddress)
{
    ROCKETMQ_GET_STR_PARAM(address);
    RETURN_LONG(SetPushConsumerNameServerAddress(GET_PUSH_CONSUMER_OBJ()->push_consumer, address));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_name_server_domain, 0, 0, 1)
ZEND_ARG_INFO(0, domain)
ZEND_END_ARG_INFO()

PHP_METHOD(push_consumer, setNameServerDomain)
{
    ROCKETMQ_GET_STR_PARAM(domain);
    RETURN_LONG(SetPushConsumerNameServerDomain(GET_PUSH_CONSUMER_OBJ()->push_consumer, domain));
}

PHP_METHOD(push_consumer, unregisterMessageCallbackOrderly)
{
    RETURN_LONG(UnregisterMessageCallbackOrderly(GET_PUSH_CONSUMER_OBJ()->push_consumer));
}
PHP_METHOD(push_consumer, unregisterMessageCallback)
{
    RETURN_LONG(UnregisterMessageCallback(GET_PUSH_CONSUMER_OBJ()->push_consumer));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__subscribe, 0, 0, 2)
ZEND_ARG_INFO(0, topic)
ZEND_ARG_INFO(0, expression)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, subscribe)
{

    char *topic, *expression;
    size_t topic_len, expression_len;
    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(topic, topic_len)
        Z_PARAM_STRING(expression, expression_len)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(Subscribe(GET_PUSH_CONSUMER_OBJ()->push_consumer, topic, expression));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_thread_count, 0, 0, 1)
ZEND_ARG_INFO(0, count)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, setThreadCount)
{
    ROCKETMQ_GET_LONG_PARAM(count);
    RETURN_LONG(SetPushConsumerThreadCount(GET_PUSH_CONSUMER_OBJ()->push_consumer, count));
}


ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_log_path, 0, 0, 1)
ZEND_ARG_INFO(0, log_path)
ZEND_END_ARG_INFO()

PHP_METHOD(push_consumer, setLogPath)
{
    ROCKETMQ_GET_STR_PARAM(log_path);
    RETURN_LONG(SetPushConsumerLogPath(GET_PUSH_CONSUMER_OBJ()->push_consumer, log_path));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_log_level, 0, 0, 1)
ZEND_ARG_INFO(0, log_level)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, setLogLevel)
{
    zend_long log_level;

    ZEND_PARSE_PARAMETERS_START(1,1)
    Z_PARAM_LONG(log_level)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(SetPushConsumerLogLevel(GET_PUSH_CONSUMER_OBJ()->push_consumer, log_level));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_instance_name, 0, 0, 1)
ZEND_ARG_INFO(0, instance_name)
ZEND_END_ARG_INFO()

PHP_METHOD(push_consumer, setInstanceName)
{
    ROCKETMQ_GET_STR_PARAM(instance_name);
    RETURN_LONG(SetPushConsumerInstanceName(GET_PUSH_CONSUMER_OBJ()->push_consumer, instance_name));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_max_cache_message_size, 0, 0, 1)
ZEND_ARG_INFO(0, max_cache_size)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, setMaxCacheMessageSize)
{
    ROCKETMQ_GET_LONG_PARAM(max_cache_size);
    RETURN_LONG(SetPushConsumerMaxCacheMessageSize(GET_PUSH_CONSUMER_OBJ()->push_consumer, max_cache_size));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_max_cache_message_size_in_mb, 0, 0, 1)
ZEND_ARG_INFO(0, max_cache_size_mb)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, setMaxCacheMessageSizeInMb)
{
    ROCKETMQ_GET_LONG_PARAM(max_cache_size_mb);
    RETURN_LONG(SetPushConsumerMaxCacheMessageSizeInMb(GET_PUSH_CONSUMER_OBJ()->push_consumer, max_cache_size_mb));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_log_file_num_and_size, 0, 0, 2)
ZEND_ARG_INFO(0, file_num)
ZEND_ARG_INFO(0, file_size)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, setLogFileNumAndSize)
{
    zend_long file_num, file_size;

    ZEND_PARSE_PARAMETERS_START(1,1)
    Z_PARAM_LONG(file_num)
    Z_PARAM_LONG(file_size)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(SetPushConsumerLogFileNumAndSize(GET_PUSH_CONSUMER_OBJ()->push_consumer, file_num, file_size));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_session_credentials, 0, 0, 2)
ZEND_ARG_INFO(0, ak)
ZEND_ARG_INFO(0, sk)
ZEND_ARG_INFO(0, channel)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, setSessionCredentials)
{
    char *ak, *sk, *channel;
    size_t ak_len, sk_len, channel_len;

    ZEND_PARSE_PARAMETERS_START(3,3)
    Z_PARAM_STRING(ak, ak_len)
    Z_PARAM_STRING(sk, sk_len)
    Z_PARAM_STRING(channel, channel_len)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(SetPushConsumerSessionCredentials(GET_PUSH_CONSUMER_OBJ()->push_consumer, ak, sk, channel));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_message_model, 0, 0, 1)
ZEND_ARG_INFO(0, model)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, setMessageModel)
{
    ROCKETMQ_GET_LONG_PARAM(model);
    RETURN_LONG(SetPushConsumerMessageModel(GET_PUSH_CONSUMER_OBJ()->push_consumer, model));
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__set_message_trace, 0, 0, 1)
ZEND_ARG_INFO(0, switch_trace)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, setMessageTrace)
{
    ROCKETMQ_GET_LONG_PARAM(switch_trace);
    RETURN_LONG(SetPushConsumerMessageTrace(GET_PUSH_CONSUMER_OBJ()->push_consumer, switch_trace));
}

int push_consumer_callback(CPushConsumer* consumer, CMessageExt* ext)
{
    zval retval;
    zval args [2];

    args[0] = create_object_zval(CLASS_NAME_PUSH_CONSUMER);
    push_consumer_obj* push_consumer = ROCKETMQ_ZVAL_GET_OBJECT(push_consumer_obj, args + 0);
    push_consumer->push_consumer = consumer;

    args[1] = create_object_zval(CLASS_NAME_MESSAGE_EXT);
    message_ext_obj *message_ext = ROCKETMQ_ZVAL_GET_OBJECT(message_ext_obj, args + 1);
    message_ext->message_ext = ext;

	zend_fcall_info		*fci= &IF_G(push_callback).fci;
	fci->retval	= &retval;
	fci->params	= args;
	fci->param_count = 2;

	zend_call_function(fci, &IF_G(push_callback).fcc);
	
    zend_object_release(&push_consumer->std);
    zend_object_release(&message_ext->std);
    return (int) Z_LVAL(retval);
}

int push_consumer_callback_orderly(CPushConsumer* consumer, CMessageExt* ext)
{
    zval retval;
    zval args [2];

    args[0] = create_object_zval(CLASS_NAME_PUSH_CONSUMER);
    push_consumer_obj* push_consumer = ROCKETMQ_ZVAL_GET_OBJECT(push_consumer_obj, args + 0);
    push_consumer->push_consumer = consumer;

    args[1] = create_object_zval(CLASS_NAME_MESSAGE_EXT);
    message_ext_obj *message_ext = ROCKETMQ_ZVAL_GET_OBJECT(message_ext_obj, args + 1);
    message_ext->message_ext = ext;

	zend_fcall_info		*fci= &IF_G(push_callback_orderly).fci;
	fci->retval	= &retval;
	fci->params	= args;
	fci->param_count = 2;

	zend_call_function(fci, &IF_G(push_callback_orderly).fcc);
	
    zend_object_release(&push_consumer->std);
    zend_object_release(&message_ext->std);
    return (int) Z_LVAL(retval);
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__register_callback_orderly, 0, 0, 1)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()
PHP_METHOD(push_consumer, registerCallbackOrderly)
{
	zend_fcall_info			fci;
	zend_fcall_info_cache	fcc;
    ZEND_PARSE_PARAMETERS_START(1, 1) 
		Z_PARAM_FUNC_EX(fci, fcc, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    replace_fci(&IF_G(push_callback_orderly), fci, fcc);
    RegisterMessageCallback(GET_PUSH_CONSUMER_OBJ()->push_consumer,
        push_consumer_callback_orderly);
}

ZEND_BEGIN_ARG_INFO_EX(arg_push_consumer__register_callback, 0, 0, 1)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

PHP_METHOD(push_consumer, registerCallback)
{
	zend_fcall_info			fci;
	zend_fcall_info_cache	fcc;
    ZEND_PARSE_PARAMETERS_START(1, 1) 
		Z_PARAM_FUNC_EX(fci, fcc, 1, 0)
    ZEND_PARSE_PARAMETERS_END();

    replace_fci(&IF_G(push_callback), fci, fcc);
    RegisterMessageCallback(GET_PUSH_CONSUMER_OBJ()->push_consumer,
        push_consumer_callback);
}

const zend_function_entry push_consumer_methods[] = {
    ZEND_ME(push_consumer, __construct, arg_push_consumer__construct, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, start, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, shutdown, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, version, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setGroupId, arg_push_consumer__set_group_id, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, getGroupId, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setNameServerDomain, arg_push_consumer__set_name_server_domain, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setNameServerAddress, arg_push_consumer__set_name_server_address, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, unregisterMessageCallbackOrderly, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, unregisterMessageCallback, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, subscribe, arg_push_consumer__subscribe, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setThreadCount, arg_push_consumer__set_thread_count, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setLogPath, arg_push_consumer__set_log_path, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setLogLevel, arg_push_consumer__set_log_level, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setLogFileNumAndSize, arg_push_consumer__set_log_file_num_and_size, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setInstanceName, arg_push_consumer__set_instance_name, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setMaxCacheMessageSize, arg_push_consumer__set_max_cache_message_size, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setMaxCacheMessageSizeInMb, arg_push_consumer__set_max_cache_message_size_in_mb, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setSessionCredentials, arg_push_consumer__set_session_credentials, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setMessageModel, arg_push_consumer__set_message_model, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, setMessageTrace, arg_push_consumer__set_message_trace, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, registerCallbackOrderly, arg_push_consumer__register_callback_orderly, ZEND_ACC_PUBLIC)
    ZEND_ME(push_consumer, registerCallback, arg_push_consumer__register_callback, ZEND_ACC_PUBLIC)

    {NULL, NULL, NULL}
};

static zend_class_entry *push_consumer_ce;
void minit_push_consumer(){
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, CLASS_NAME_PUSH_CONSUMER, push_consumer_methods);
  push_consumer_ce = zend_register_internal_class_ex(&ce, NULL);
  push_consumer_ce->create_object = push_consumer_object_create;

  memcpy(&push_consumer_object_handlers, zend_get_std_object_handlers(), sizeof(push_consumer_object_handlers));
  push_consumer_object_handlers.offset = XtOffsetOf(push_consumer_obj, std);
  push_consumer_object_handlers.free_obj = push_consumer_object_free_storage;
}