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

#include "pull_consumer.h"

zend_object_handlers pull_consumer_object_handlers;

#define GET_PULL_CONSUMER_OBJ()  ROCKETMQ_ZVAL_GET_OBJECT(pull_consumer_obj, getThis())

void pull_consumer_object_free_storage(zend_object *object) {
  pull_consumer_obj *intern = ROCKETMQ_GET_OBJECT(pull_consumer_obj, object);
  zend_object_std_dtor(&intern->std);
  DEBUG_DESTROY(CLASS_NAME_PULL_CONSUMER);
  if (intern->pull_consumer) {
    DestroyPullConsumer(intern->pull_consumer);
  }
  efree(intern);
}

static zend_object *pull_consumer_object_create(zend_class_entry *type) {
  pull_consumer_obj *obj = ecalloc(1, sizeof(pull_consumer_obj) + zend_object_properties_size(type));
  obj->pull_consumer = NULL;
  zend_object_std_init(&obj->std, type);
  object_properties_init(&obj->std, type);

  obj->std.handlers = &pull_consumer_object_handlers;
  return &obj->std;
}

// __construct args
ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__construct, 0, 0, 1)
ZEND_ARG_INFO(0, groupId)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, __construct) {
  ROCKETMQ_GET_STR_PARAM(groupId);
  GET_PULL_CONSUMER_OBJ()->pull_consumer = CreatePullConsumer(groupId);
  RETURN_TRUE;
}

PHP_METHOD(pull_consumer, start) {
  RETURN_LONG(StartPullConsumer(GET_PULL_CONSUMER_OBJ()->pull_consumer));
}

PHP_METHOD(pull_consumer, shutdown) {
  RETURN_LONG(ShutdownPullConsumer(GET_PULL_CONSUMER_OBJ()->pull_consumer));
}

PHP_METHOD(pull_consumer, version) {
  RETURN_STRING(ShowPullConsumerVersion(GET_PULL_CONSUMER_OBJ()->pull_consumer));
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__set_group_id, 0, 0, 1)
ZEND_ARG_INFO(0, groupId)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, setGroupId) {
  ROCKETMQ_GET_STR_PARAM(groupId);
  RETURN_LONG(SetPullConsumerGroupID(GET_PULL_CONSUMER_OBJ()->pull_consumer, groupId));
}

PHP_METHOD(pull_consumer, getGroupId) {
  RETURN_STRING(GetPullConsumerGroupID(GET_PULL_CONSUMER_OBJ()->pull_consumer));
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__setNameServerAddress, 0, 0, 1)
ZEND_ARG_INFO(0, nameserver_address)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, setNameServerAddress) {
  ROCKETMQ_GET_STR_PARAM(nameserver_address);
  RETURN_LONG(SetPullConsumerNameServerAddress(GET_PULL_CONSUMER_OBJ()->pull_consumer, nameserver_address));
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__setNameServerDomain, 0, 0, 1)
ZEND_ARG_INFO(0, nameserver_domain)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, setNameServerDomain) {
  ROCKETMQ_GET_STR_PARAM(nameserver_domain);
  RETURN_LONG(SetPullConsumerNameServerDomain(GET_PULL_CONSUMER_OBJ()->pull_consumer, nameserver_domain));
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__set_session_credentials, 0, 0, 3)
ZEND_ARG_INFO(0, access_key)
ZEND_ARG_INFO(0, secret_key)
ZEND_ARG_INFO(0, one_channel)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, setSessionCredentials) {
  char *access_key, *secret_key, *one_channel;
  size_t ak_len, sk_len, one_channel_len;
  ZEND_PARSE_PARAMETERS_START(1, 1)
  Z_PARAM_STRING(access_key, ak_len)
  Z_PARAM_STRING(secret_key, sk_len)
  Z_PARAM_STRING(one_channel, one_channel_len)
  ZEND_PARSE_PARAMETERS_END();

  RETURN_LONG(SetPullConsumerSessionCredentials(GET_PULL_CONSUMER_OBJ()->pull_consumer, access_key, secret_key, one_channel));
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__setLogPath, 0, 0, 1)
ZEND_ARG_INFO(0, log_path)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, setLogPath) {
  ROCKETMQ_GET_STR_PARAM(log_path);
  RETURN_LONG(SetPullConsumerLogPath(GET_PULL_CONSUMER_OBJ()->pull_consumer, log_path));
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__set_log_file_num_and_size, 0, 0, 2)
ZEND_ARG_INFO(0, file_num)
ZEND_ARG_INFO(0, file_size)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, setLogFileNumAndSize) {
  zend_long file_num, file_size;
  ZEND_PARSE_PARAMETERS_START(2, 2)
  Z_PARAM_LONG(file_num)
  Z_PARAM_LONG(file_size)
  ZEND_PARSE_PARAMETERS_END();

  RETURN_LONG(SetPullConsumerLogFileNumAndSize(GET_PULL_CONSUMER_OBJ()->pull_consumer, file_num, file_size));
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__set_log_level, 0, 0, 1)
ZEND_ARG_INFO(0, log_level)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, setLogLevel) {
  ROCKETMQ_GET_LONG_PARAM(log_level);
  RETURN_LONG(SetPullConsumerLogLevel(GET_PULL_CONSUMER_OBJ()->pull_consumer, (CLogLevel)log_level));
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__fetch_subscription_message_queues, 0, 0, 2)
ZEND_ARG_INFO(0, topic)
ZEND_ARG_INFO(0, messageQueue)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, fetchSubscriptionMessageQueues) {
  char *topic;
  size_t topic_len;
  zval *zval_message_queues;
  ZEND_PARSE_PARAMETERS_START(2, 2)
  Z_PARAM_STRING(topic, topic_len)
  Z_PARAM_ZVAL(zval_message_queues)
  ZEND_PARSE_PARAMETERS_END();

  message_queues_obj *message_queues = ROCKETMQ_ZVAL_GET_OBJECT(message_queues_obj, zval_message_queues);

  RETURN_LONG(FetchSubscriptionMessageQueues(GET_PULL_CONSUMER_OBJ()->pull_consumer, topic, &message_queues->message_queues,
                                             &message_queues->size));
}

ZEND_BEGIN_ARG_INFO_EX(arg_pull_consumer__pull, 0, 5, 5)
ZEND_ARG_INFO(0, message_queues)
ZEND_ARG_INFO(0, queue_index)
ZEND_ARG_INFO(0, sub_expression)
ZEND_ARG_INFO(0, offset)
ZEND_ARG_INFO(0, max_number)
ZEND_END_ARG_INFO()

PHP_METHOD(pull_consumer, pull) {
  zval *zval_message_queues;
  zend_long offset, max_number, queue_index;
  char *sub_expression;
  size_t sub_expression_len;

  ZEND_PARSE_PARAMETERS_START(5, 5)
  Z_PARAM_ZVAL(zval_message_queues)
  Z_PARAM_LONG(queue_index)
  Z_PARAM_STRING(sub_expression, sub_expression_len)
  Z_PARAM_LONG(offset)
  Z_PARAM_LONG(max_number)
  ZEND_PARSE_PARAMETERS_END();

  message_queues_obj *message_queues = ROCKETMQ_ZVAL_GET_OBJECT(message_queues_obj, zval_message_queues);

  CPullResult result = Pull(GET_PULL_CONSUMER_OBJ()->pull_consumer, message_queues->message_queues + queue_index, sub_expression,
                            offset, max_number);

  zval result_zval;
  zend_string *class_name = zend_string_init(CLASS_NAME_PULL_RESULT, strlen(CLASS_NAME_PULL_RESULT), 0);
  zend_class_entry *ce = zend_fetch_class(class_name, ZEND_FETCH_CLASS_AUTO);
  zend_string_release(class_name);
  object_init_ex(&result_zval, ce);

  pull_result_obj *pull_result = ROCKETMQ_ZVAL_GET_OBJECT(pull_result_obj, &result_zval);
  pull_result->pull_result = result;
  pull_result->current = 0;
  RETURN_OBJ(&pull_result->std);
}

const zend_function_entry pull_consumer_methods[] = {
    ZEND_ME(pull_consumer, __construct, arg_pull_consumer__construct, ZEND_ACC_PUBLIC) 
    ZEND_ME(pull_consumer, start, arg_input_void, ZEND_ACC_PUBLIC) 
    ZEND_ME(pull_consumer, shutdown, arg_input_void, ZEND_ACC_PUBLIC) 
    ZEND_ME(pull_consumer, version, arg_input_void, ZEND_ACC_PUBLIC) 
    ZEND_ME(pull_consumer, setGroupId, arg_pull_consumer__set_group_id, ZEND_ACC_PUBLIC) 
    ZEND_ME(pull_consumer, getGroupId, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_consumer, setNameServerAddress, arg_pull_consumer__setNameServerAddress, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_consumer, setNameServerDomain, arg_pull_consumer__setNameServerDomain, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_consumer, setSessionCredentials, arg_pull_consumer__set_session_credentials, ZEND_ACC_PUBLIC) 
    ZEND_ME(pull_consumer, setLogPath, arg_pull_consumer__setLogPath, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_consumer, setLogFileNumAndSize, arg_pull_consumer__set_log_file_num_and_size, ZEND_ACC_PUBLIC) 
    ZEND_ME(pull_consumer, setLogLevel, arg_pull_consumer__set_log_level, ZEND_ACC_PUBLIC) 
    ZEND_ME(pull_consumer, fetchSubscriptionMessageQueues, arg_pull_consumer__fetch_subscription_message_queues, ZEND_ACC_PUBLIC)
    ZEND_ME(pull_consumer, pull, arg_pull_consumer__pull, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}};

static zend_class_entry *pull_consumer_ce;
void minit_pull_consumer() {
  zend_class_entry ce;
  // 初始化一个类对象，并将方法绑定到对象上
  INIT_CLASS_ENTRY(ce, CLASS_NAME_PULL_CONSUMER, pull_consumer_methods);
  pull_consumer_ce = zend_register_internal_class_ex(&ce, NULL);
  pull_consumer_ce->create_object = pull_consumer_object_create;

  memcpy(&pull_consumer_object_handlers, zend_get_std_object_handlers(), sizeof(pull_consumer_object_handlers));
  pull_consumer_object_handlers.offset = XtOffsetOf(pull_consumer_obj, std);
  pull_consumer_object_handlers.free_obj = pull_consumer_object_free_storage;
}