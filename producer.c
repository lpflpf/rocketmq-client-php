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

#include "producer.h"


#define GET_PRODUCER_OBJ() ROCKETMQ_ZVAL_GET_OBJECT(producer_obj, getThis())

zend_object_handlers producer_object_handlers;
void producer_object_free_storage(zend_object *object)
{
    producer_obj *intern = ROCKETMQ_GET_OBJECT(producer_obj, object);
    zend_object_std_dtor(&intern->std);
    DEBUG_DESTROY(CLASS_NAME_PRODUCER);
    if (intern->producer){
        DestroyProducer(intern->producer);
    }
}

static zend_object* producer_object_create(zend_class_entry *type ) 
{
    producer_obj *obj = ecalloc(1, sizeof(producer_obj) + zend_object_properties_size(type));
    obj->producer = NULL;
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);

    obj->std.handlers = &producer_object_handlers;
    return &obj->std;
}

// __construct args
ZEND_BEGIN_ARG_INFO_EX(arg_producer___construct, 0, 0, 1)
ZEND_ARG_INFO(0, groupId)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arg_orderly_producer___construct, 0, 0, 1)
ZEND_ARG_INFO(0, groupId)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arg_transaction_producer___construct, 0, 0, 2)
ZEND_ARG_INFO(0, groupId)
ZEND_ARG_INFO(0, callback)
ZEND_ARG_INFO(0, userdata)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, __construct)
{
    ROCKETMQ_GET_STR_PARAM(group_id);
    producer_obj *obj = ROCKETMQ_ZVAL_GET_OBJECT(producer_obj, getThis());
    obj->producer = CreateProducer(group_id);
    RETURN_TRUE;
}

PHP_METHOD(orderly_producer, __construct)
{
    ROCKETMQ_GET_STR_PARAM(group_id);
    GET_PRODUCER_OBJ()->producer = CreateOrderlyProducer(group_id);
}

typedef struct _transaction_checker_data{
    diy_callback checker;
    zval *user_data;
} transaction_checker_data;

CTransactionStatus transaction_checker_callback(CProducer* producer, CMessageExt* msg, void* data){
    transaction_checker_data * user_data = (transaction_checker_data*)data;
    zval retval;
    zval args[2];

    zval message_ext_zval = create_object_zval(CLASS_NAME_MESSAGE_EXT);
    message_ext_obj *message_ext = ROCKETMQ_ZVAL_GET_OBJECT(message_ext_obj, &message_ext_zval);
    message_ext->message_ext = msg;
    args[0] = message_ext_zval;
    args[1] = *user_data->user_data;

	zend_fcall_info		*fci= &user_data->checker.fci;
	fci->retval	= &retval;
	fci->params	= args;
	fci->param_count = 2;
	zend_call_function(fci, &user_data->checker.fcc);
    return (int)Z_LVAL(retval);
}

PHP_METHOD(transaction_producer, __construct)
{
    zval *zval_user_data;
    char* group_id;
    size_t group_id_len;

	zend_fcall_info			checker_callback_fci;
	zend_fcall_info_cache	checker_callback_fcc;
    ZEND_PARSE_PARAMETERS_START(3, 3) 
        Z_PARAM_STRING(group_id, group_id_len)
        Z_PARAM_FUNC(checker_callback_fci, checker_callback_fcc)
        Z_PARAM_ZVAL(zval_user_data)
    ZEND_PARSE_PARAMETERS_END(); 

    transaction_checker_data *user_data = ecalloc(1, sizeof(transaction_checker_data));
    user_data->user_data= zval_user_data;
    replace_fci(&user_data->checker, checker_callback_fci, checker_callback_fcc);

    GET_PRODUCER_OBJ()->producer = CreateTransactionProducer(group_id, transaction_checker_callback, user_data);
}

PHP_METHOD(producer, start) {
    RETURN_LONG(StartProducer(GET_PRODUCER_OBJ()->producer));
}

PHP_METHOD(producer, shutdown) {
    RETURN_LONG(ShutdownProducer(GET_PRODUCER_OBJ()->producer));
}

PHP_METHOD(producer, version) {
    RETURN_STRING(ShowProducerVersion(GET_PRODUCER_OBJ()->producer));
}
ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_name_server_address, 0, 0, 1)
ZEND_ARG_INFO(0, address)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setNameServerAddress) {
    ROCKETMQ_GET_STR_PARAM(address);
    RETURN_LONG(SetProducerNameServerAddress(GET_PRODUCER_OBJ()->producer, address));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_name_server_domain, 0, 0, 1)
ZEND_ARG_INFO(0, domain)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setNameServerDomain) {
    ROCKETMQ_GET_STR_PARAM(domain);
    RETURN_LONG(SetProducerNameServerDomain(GET_PRODUCER_OBJ()->producer, domain));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_group_name, 0, 0, 1)
ZEND_ARG_INFO(0, group_name)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setGroupName) {
    ROCKETMQ_GET_STR_PARAM(group_name);
    RETURN_LONG(SetProducerGroupName(GET_PRODUCER_OBJ()->producer, group_name));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_instance_name, 0, 0, 1)
ZEND_ARG_INFO(0, instance_name)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setInstanceName) {
    ROCKETMQ_GET_STR_PARAM(instance_name);
    RETURN_LONG(SetProducerInstanceName(GET_PRODUCER_OBJ()->producer, instance_name));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_session_credentials, 0, 0, 3)
ZEND_ARG_INFO(0, access_key)
ZEND_ARG_INFO(0, secret_key)
ZEND_ARG_INFO(0, one_channel)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setSessionCredentials) {
    char *access_key, *secret_key, *one_channel; 
    size_t ak_len, sk_len, one_channel_len; 
    ZEND_PARSE_PARAMETERS_START(1, 1) 
    Z_PARAM_STRING(access_key, ak_len) 
    Z_PARAM_STRING(secret_key, sk_len) 
    Z_PARAM_STRING(one_channel, one_channel_len) 
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(SetProducerSessionCredentials(GET_PRODUCER_OBJ()->producer, access_key, secret_key, one_channel));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_log_path, 0, 0, 1)
ZEND_ARG_INFO(0, log_path)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setLogPath) {
    ROCKETMQ_GET_STR_PARAM(log_path);
    RETURN_LONG(SetProducerLogPath(GET_PRODUCER_OBJ()->producer, log_path));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_log_file_num_and_size, 0, 0, 2)
ZEND_ARG_INFO(0, file_num)
ZEND_ARG_INFO(0, file_size)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setLogFileNumAndSize) {
    zend_long file_num, file_size;
    ZEND_PARSE_PARAMETERS_START(2, 2) 
    Z_PARAM_LONG(file_num)
    Z_PARAM_LONG(file_size)
    ZEND_PARSE_PARAMETERS_END();

    RETURN_LONG(SetProducerLogFileNumAndSize(GET_PRODUCER_OBJ()->producer, file_num, file_size));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_log_level, 0, 0, 1)
ZEND_ARG_INFO(0, log_level)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setLogLevel) {
    ROCKETMQ_GET_LONG_PARAM(log_level);
    RETURN_LONG(SetProducerLogLevel(GET_PRODUCER_OBJ()->producer, (CLogLevel) log_level));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_send_msg_timeout, 0, 0, 1)
ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setSendMsgTimeout) {
    ROCKETMQ_GET_LONG_PARAM(timeout);
    RETURN_LONG(SetProducerSendMsgTimeout(GET_PRODUCER_OBJ()->producer, timeout));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_compress_level, 0, 0, 1)
ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setCompressLevel) {
    ROCKETMQ_GET_LONG_PARAM(level);
    RETURN_LONG(SetProducerCompressLevel(GET_PRODUCER_OBJ()->producer, level));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_max_message_size, 0, 0, 1)
ZEND_ARG_INFO(0, size)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setMaxMessageSize) {
    ROCKETMQ_GET_LONG_PARAM(size);
    RETURN_LONG(SetProducerMaxMessageSize(GET_PRODUCER_OBJ()->producer, size));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__set_trace, 0, 0, 1)
ZEND_ARG_INFO(0, trace)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, setMessageTrace) {
    ROCKETMQ_GET_LONG_PARAM(trace);
    RETURN_LONG(SetProducerMessageTrace(GET_PRODUCER_OBJ()->producer, (CTraceModel)trace));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__send_message_sync, 0, 0, 1)
ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, sendMessageSync)
{
    zval *zval_msg_val = NULL;

    ZEND_PARSE_PARAMETERS_START(1,1) 
    Z_PARAM_ZVAL_EX(zval_msg_val, 0, 1)
    ZEND_PARSE_PARAMETERS_END();

    message_obj* msg_val = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, zval_msg_val);

    CSendResult *result = ecalloc(1, sizeof(CSendResult));
    if (SendMessageSync(GET_PRODUCER_OBJ()->producer, msg_val->message, result) == 0) {
        zval result_zval;
        zend_string *class_name = zend_string_init(CLASS_NAME_SEND_RESULT, strlen(CLASS_NAME_SEND_RESULT), 0);
        zend_class_entry *ce = zend_fetch_class(class_name, ZEND_FETCH_CLASS_AUTO);
        zend_string_release(class_name);
        object_init_ex(&result_zval, ce);
        send_result_obj *send_result = ROCKETMQ_ZVAL_GET_OBJECT(send_result_obj, &result_zval);
        memcpy(&send_result->send_result, result, sizeof(CSendResult));
        efree(result);
        RETURN_OBJ(&send_result->std);
    }
    RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__send_batch_message, 0, 0, 2)
ZEND_ARG_INFO(0, batch_msg)
ZEND_ARG_INFO(0, result)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, sendBatchMessage)
{
    zval *zval_batch_message_val = NULL;
    zval *zval_result_val = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 2) 
    Z_PARAM_ZVAL_EX(zval_batch_message_val , 0, 1)
    Z_PARAM_ZVAL_EX(zval_result_val, 0, 1)
    ZEND_PARSE_PARAMETERS_END();

    batch_message_obj *batch_message_val = ROCKETMQ_ZVAL_GET_OBJECT(batch_message_obj, zval_batch_message_val);
    send_result_obj* send_result_val = ROCKETMQ_ZVAL_GET_OBJECT(send_result_obj, zval_result_val);
    int ret = SendBatchMessage(GET_PRODUCER_OBJ()->producer, batch_message_val->batch_message, &send_result_val->send_result);
    RETURN_LONG(ret);
}

/* {{{ async send message*/
typedef struct {
    diy_callback success_callback;
    diy_callback exception_callback;
    zval *user_data;
} send_message_async_user_data;

void on_send_success_callback(CSendResult result, CMessage* msg, void* data){
    send_message_async_user_data* user_data = (send_message_async_user_data *)data;
        zval retval;
        zval args[3];

        zval result_zval;
        zend_string *class_name = zend_string_init(CLASS_NAME_SEND_RESULT, strlen(CLASS_NAME_SEND_RESULT), 0);
        zend_class_entry *ce = zend_fetch_class(class_name, ZEND_FETCH_CLASS_AUTO);
        zend_string_release(class_name);
        object_init_ex(&result_zval, ce);
        send_result_obj *send_result = ROCKETMQ_ZVAL_GET_OBJECT(send_result_obj, &result_zval);
        send_result->send_result = result;
        args[0] = result_zval;

        zval message_zval = create_object_zval(CLASS_NAME_MESSAGE);
        message_obj *message = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, &message_zval);
        message->message = msg;
        args[1] = message_zval;
        args[2] = *user_data->user_data;

        zend_fcall_info		*fci= &user_data->success_callback.fci;
        fci->retval	= &retval;
        fci->params	= args;
        fci->param_count = 3;
        zend_call_function(fci, &user_data->success_callback.fcc);
        efree(user_data);

        DestroyMessage(msg);
}

void on_send_exception_callback(CMQException e, CMessage *msg, void* data){
    send_message_async_user_data * user_data = (send_message_async_user_data *)data;
        zval retval;
        zval args[3];

        zval mq_exception_zval = create_object_zval(CLASS_NAME_MQ_EXCEPTION);
        mq_exception_obj *mq_exception = ROCKETMQ_ZVAL_GET_OBJECT(mq_exception_obj, &mq_exception_zval);
        memcpy(&mq_exception,&e, sizeof(CMQException));
        args[0] = mq_exception_zval;

        zval message_zval = create_object_zval(CLASS_NAME_MESSAGE);
        message_obj *message = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, &message_zval);
        message->message = msg;
        args[1] = message_zval;
        if (user_data->user_data) {
            args[2] = *user_data->user_data;
        }

        zend_fcall_info		*fci= &user_data->exception_callback.fci;
        fci->retval	= &retval;
        fci->params	= args;
        fci->param_count = 3;
        zend_call_function(fci, &user_data->exception_callback.fcc);
        efree(user_data);
        DestroyMessage(msg);
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__send_message_async, 0, 0, 4)
ZEND_ARG_INFO(0, msg)
ZEND_ARG_INFO(0, success_callback)
ZEND_ARG_INFO(0, exception_callback)
ZEND_ARG_INFO(0, user_data)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, sendMessageAsync)
{
    zval *zval_msg_val = NULL, *user_data = NULL;

	zend_fcall_info			success_fci, exception_fci;
	zend_fcall_info_cache	success_fcc, exception_fcc;

    ZEND_PARSE_PARAMETERS_START(3, 4) 
    Z_PARAM_ZVAL_EX(zval_msg_val, 0, 1)
    Z_PARAM_FUNC_EX(success_fci, success_fcc, 1, 0)
    Z_PARAM_FUNC_EX(exception_fci, exception_fcc, 1, 0)
    Z_PARAM_OPTIONAL
    Z_PARAM_ZVAL(user_data)
    ZEND_PARSE_PARAMETERS_END();

    message_obj* msg_val = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, zval_msg_val);
    send_message_async_user_data *async_user_data = ecalloc(1, sizeof(send_message_async_user_data));
    replace_fci(&async_user_data->success_callback, success_fci, success_fcc);
    replace_fci(&async_user_data->exception_callback, exception_fci, exception_fcc);

    Z_ADDREF(*zval_msg_val);
    if (ZEND_NUM_ARGS() == 4) {
        async_user_data->user_data = user_data;
    }

    producer_obj *obj = ROCKETMQ_ZVAL_GET_OBJECT(producer_obj, getThis());
    RETURN_LONG(SendAsync(obj->producer, msg_val->message, on_send_success_callback, on_send_exception_callback, async_user_data));
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__send_message_oneway, 0, 0, 1)
ZEND_ARG_INFO(0, msg)
ZEND_END_ARG_INFO()

PHP_METHOD(producer, sendMessageOneway) 
{
    zval *zval_msg_val = NULL;

    ZEND_PARSE_PARAMETERS_START(1,1) 
    Z_PARAM_ZVAL_EX(zval_msg_val, 0, 1)
    ZEND_PARSE_PARAMETERS_END();

    message_obj *message = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, zval_msg_val);
    int ret = (SendMessageOneway(GET_PRODUCER_OBJ()->producer, message->message));
    DestroyMessage(message->message);
    RETURN_LONG(ret);
}

typedef struct {
    diy_callback selector;
    zval *args;
} queue_selector_callback_arg;


int queue_selector_callback (int size, CMessage* msg, void* data){
    queue_selector_callback_arg* arg= (queue_selector_callback_arg*)data;
    zval retval;
    zval args[3];

    zval message_zval = create_object_zval(CLASS_NAME_MESSAGE);
    message_obj *message = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, &message_zval);
    message->message = msg;

    ZVAL_LONG(args + 0, size);
    args[1] = message_zval;
    args[2] = *arg->args;

    zend_fcall_info		*fci= &arg->selector.fci;
    fci->retval	= &retval;
    fci->params	= args;
    fci->param_count = 3;
    zend_call_function(fci, &arg->selector.fcc);
    efree(arg);

    return (int)Z_LVAL(retval);
    return 0;
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__send_message_oneway_orderly, 0, 0, 3)
ZEND_ARG_INFO(0, msg)
ZEND_ARG_INFO(0, selector)
ZEND_ARG_INFO(0, arg)
ZEND_END_ARG_INFO()

PHP_METHOD(orderly_producer, sendMessageOnewayOrderly)
{
    zval *zval_msg_val = NULL, *zval_arg = NULL;
	zend_fcall_info			selector_fci;
	zend_fcall_info_cache	selector_fcc;
    ZEND_PARSE_PARAMETERS_START(3, 3) 
    Z_PARAM_ZVAL_EX(zval_msg_val, 0, 1)
    Z_PARAM_FUNC_EX(selector_fci, selector_fcc, 1, 0)
    Z_PARAM_ZVAL(zval_arg)
    ZEND_PARSE_PARAMETERS_END();

    message_obj* msg_val = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, zval_msg_val);
    queue_selector_callback_arg *arg = ecalloc(1, sizeof(queue_selector_callback_arg));
    replace_fci(&arg->selector, selector_fci, selector_fcc);
    arg->args = zval_arg;
    int ret = SendMessageOnewayOrderly(GET_PRODUCER_OBJ()->producer, msg_val->message, queue_selector_callback, arg);
    DestroyMessage(msg_val->message);
    RETURN_LONG(ret);
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__send_message_orderly, 0, 0, 5)
    ZEND_ARG_INFO(0, msg)
    ZEND_ARG_INFO(0, selector)
    ZEND_ARG_INFO(0, arg)
    ZEND_ARG_INFO(0, autoRetryTimes)
    ZEND_ARG_INFO(0, result)
ZEND_END_ARG_INFO()

PHP_METHOD(orderly_producer, sendMessageOrderly)
{
    zval *zval_msg_val = NULL, *zval_arg = NULL, *zval_send_result;
    zend_long auto_retry_times;
	zend_fcall_info			selector_fci;
	zend_fcall_info_cache	selector_fcc;

    ZEND_PARSE_PARAMETERS_START(5, 5) 
    Z_PARAM_ZVAL(zval_msg_val)
    Z_PARAM_FUNC_EX(selector_fci, selector_fcc, 1, 0)
    Z_PARAM_ZVAL(zval_arg)
    Z_PARAM_LONG(auto_retry_times)
    Z_PARAM_ZVAL(zval_send_result)
    ZEND_PARSE_PARAMETERS_END();

    message_obj* msg_val = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, zval_msg_val);
    queue_selector_callback_arg *arg = ecalloc(1, sizeof(queue_selector_callback_arg));
    replace_fci(&arg->selector, selector_fci, selector_fcc);
    if (ZEND_NUM_ARGS() >= 3) {
        arg->args = zval_arg;
    }

    send_result_obj *send_result_val = ROCKETMQ_ZVAL_GET_OBJECT(send_result_obj, zval_send_result);
    int ret = SendMessageOrderly(GET_PRODUCER_OBJ()->producer, msg_val->message, queue_selector_callback, arg, (int)auto_retry_times, &send_result_val->send_result);
    DestroyMessage(msg_val->message);
    RETURN_LONG(ret);
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__send_message_orderly_by_sharding_key, 0, 0, 3)
    ZEND_ARG_INFO(0, msg)
    ZEND_ARG_INFO(0, sharding_key)
    ZEND_ARG_INFO(0, result)
ZEND_END_ARG_INFO()

PHP_METHOD(orderly_producer, sendMessageOrderlyByShardingKey)
{
    zval *zval_msg_val = NULL, *zval_send_result = NULL;
    char *sharding_key;
    size_t sharding_key_len;

    ZEND_PARSE_PARAMETERS_START(3, 3) 
        Z_PARAM_ZVAL(zval_msg_val)
        Z_PARAM_STRING(sharding_key, sharding_key_len)
        Z_PARAM_ZVAL(zval_send_result)
    ZEND_PARSE_PARAMETERS_END(); 

    producer_obj* producer = ROCKETMQ_ZVAL_GET_OBJECT(producer_obj, getThis());
    message_obj* message = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, zval_msg_val);
    send_result_obj* send_result = ROCKETMQ_ZVAL_GET_OBJECT(send_result_obj, zval_send_result);
    int ret = SendMessageOrderlyByShardingKey(producer->producer, message->message, sharding_key, &send_result->send_result);
    DestroyMessage(message->message);
    RETURN_LONG(ret);
}

typedef struct _transaction_callback_data{
    diy_callback callback;
    zval *args;
} transaction_callback_data;


CTransactionStatus transaction_callback(CProducer* producer, CMessage* msg, void* data){
    transaction_callback_data* user_data = (transaction_callback_data*)data;
    zval retval;
    zval args[2];

    zval message_zval = create_object_zval(CLASS_NAME_MESSAGE);
    message_obj *message = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, &message_zval);
    message->message = msg;
    args[0] = message_zval;
    args[1] = *user_data->args;

    zend_fcall_info	*fci= &user_data->callback.fci;
    fci->retval	= &retval;
    fci->params	= args;
    fci->param_count = 2;
    zend_call_function(fci, &user_data->callback.fcc);
    efree(user_data);
    return (int)Z_LVAL(retval);
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__send_message_transaction, 0, 0, 4)
    ZEND_ARG_INFO(0, msg)
    ZEND_ARG_INFO(0, callback)
    ZEND_ARG_INFO(0, user_data)
    ZEND_ARG_INFO(0, result)
ZEND_END_ARG_INFO()

PHP_METHOD(transaction_producer, sendMessageTransaction)
{
    zval *zval_msg_val = NULL, *zval_send_result, *zval_user_data;
    char *sharding_key;
    size_t sharding_key_len;

	zend_fcall_info			callback_fci;
	zend_fcall_info_cache	callback_fcc;

    ZEND_PARSE_PARAMETERS_START(4, 4) 
        Z_PARAM_ZVAL(zval_msg_val)
        Z_PARAM_FUNC(callback_fci, callback_fcc)
        Z_PARAM_ZVAL(zval_user_data)
        Z_PARAM_ZVAL(zval_send_result)
    ZEND_PARSE_PARAMETERS_END(); 

    transaction_callback_data* executor_data = ecalloc(1, sizeof(transaction_callback_data));
    executor_data->args = zval_user_data;
    replace_fci(&executor_data->callback, callback_fci, callback_fcc);

    message_obj* message = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, zval_msg_val);
    send_result_obj* send_result = ROCKETMQ_ZVAL_GET_OBJECT(send_result_obj, zval_send_result);
    int ret = SendMessageTransaction(GET_PRODUCER_OBJ()->producer, message->message, transaction_callback, executor_data, &send_result->send_result);
    RETURN_LONG(ret);
}

void send_success_callback(CSendResult result)
{
    zval retval;
    zval args [1];
    args[0] = create_object_zval(CLASS_NAME_SEND_RESULT);
    send_result_obj* send_result = ROCKETMQ_ZVAL_GET_OBJECT(send_result_obj, args + 0);
	zend_fcall_info		*fci= &IF_G(producer_send_success).fci;
	fci->retval	= &retval;
	fci->params	= args;
	fci->param_count = 1;
    send_result->send_result = result;
	zend_call_function(fci, &IF_G(producer_send_success).fcc);
    zend_object_release(&send_result->std);
}

void send_exception_callback(CMQException e)
{
    zval retval;
    zval args [1];
    args[0] = create_object_zval(CLASS_NAME_MQ_EXCEPTION);
    mq_exception_obj *mq_exception = ROCKETMQ_ZVAL_GET_OBJECT(mq_exception_obj, args + 0);
	zend_fcall_info		*fci= &IF_G(producer_send_exception).fci;
	fci->retval	= &retval;
	fci->params	= args;
	fci->param_count = 1;
	zend_call_function(fci, &IF_G(producer_send_exception).fcc);
    zend_object_release(&mq_exception->std);
}

ZEND_BEGIN_ARG_INFO_EX(arg_producer__send_message_orderly_async, 0, 0, 5)
ZEND_ARG_INFO(0, msg)
ZEND_ARG_INFO(0, selector)
ZEND_ARG_INFO(0, user_data)
ZEND_ARG_INFO(0, success_callback)
ZEND_ARG_INFO(0, exception_callback)
ZEND_END_ARG_INFO()

PHP_METHOD(orderly_producer, sendMessageOrderlyAsync)
{
    zval *zval_msg_val = NULL, *zval_selector_callback, *zval_selector_user_data;

	zend_fcall_info			success_fci, exception_fci, selector_fci;
	zend_fcall_info_cache	success_fcc, exception_fcc, selector_fcc;

    ZEND_PARSE_PARAMETERS_START(5, 5) 
        Z_PARAM_ZVAL_EX(zval_msg_val, 0, 1)
        Z_PARAM_FUNC_EX(selector_fci, selector_fcc, 1, 0)
        Z_PARAM_ZVAL(zval_selector_user_data)
		Z_PARAM_FUNC_EX(success_fci, success_fcc, 1, 0)
		Z_PARAM_FUNC_EX(exception_fci, exception_fcc, 1, 0)
    ZEND_PARSE_PARAMETERS_END(); 

    message_obj* message = ROCKETMQ_ZVAL_GET_OBJECT(message_obj, zval_msg_val);

    replace_fci(&IF_G(producer_send_success), success_fci, success_fcc);
    replace_fci(&IF_G(producer_send_exception), exception_fci, exception_fcc);

    queue_selector_callback_arg *arg = ecalloc(1, sizeof(queue_selector_callback_arg));
    replace_fci(&arg->selector, selector_fci, selector_fcc);
    arg->args = zval_selector_user_data;
    SendMessageOrderlyAsync(GET_PRODUCER_OBJ()->producer, message->message , queue_selector_callback , arg , send_success_callback, send_exception_callback);
}

const zend_function_entry producer_methods[] = {
    ZEND_ME(producer, __construct, arg_producer___construct, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, start, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, shutdown, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, version, arg_input_void, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setNameServerDomain, arg_producer__set_name_server_domain, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setNameServerAddress, arg_producer__set_name_server_address, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setGroupName, arg_producer__set_group_name, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setInstanceName, arg_producer__set_instance_name, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setSessionCredentials, arg_producer__set_session_credentials, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setLogPath, arg_producer__set_log_path, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setLogFileNumAndSize, arg_producer__set_log_file_num_and_size, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setLogLevel, arg_producer__set_log_level, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setSendMsgTimeout, arg_producer__set_send_msg_timeout, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setCompressLevel, arg_producer__set_compress_level, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setMaxMessageSize, arg_producer__set_max_message_size, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, setMessageTrace, arg_producer__set_trace, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, sendBatchMessage, arg_producer__send_batch_message, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, sendMessageSync, arg_producer__send_message_sync, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, sendMessageAsync, arg_producer__send_message_async, ZEND_ACC_PUBLIC)
    ZEND_ME(producer, sendMessageOneway, arg_producer__send_message_oneway, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

const zend_function_entry transaction_producer_methods[] = {
    ZEND_ME(transaction_producer, __construct, arg_transaction_producer___construct, ZEND_ACC_PUBLIC)
    ZEND_ME(transaction_producer, sendMessageTransaction, arg_producer__send_message_transaction, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

const zend_function_entry orderly_producer_methods[] = {
    ZEND_ME(orderly_producer, __construct, arg_orderly_producer___construct, ZEND_ACC_PUBLIC)
    ZEND_ME(orderly_producer, sendMessageOnewayOrderly, arg_producer__send_message_oneway_orderly, ZEND_ACC_PUBLIC)
    ZEND_ME(orderly_producer, sendMessageOrderly, arg_producer__send_message_orderly, ZEND_ACC_PUBLIC)
    ZEND_ME(orderly_producer, sendMessageOrderlyByShardingKey, arg_producer__send_message_orderly_by_sharding_key, ZEND_ACC_PUBLIC)
    ZEND_ME(orderly_producer, sendMessageOrderlyAsync, arg_producer__send_message_orderly_async, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

static zend_class_entry *producer_ce;
static zend_class_entry *orderly_producer_ce;
static zend_class_entry *transaction_producer_ce;

void minit_producer(){
  zend_class_entry ce, transaction_ce, orderly_ce;
  // 初始化一个类对象，并将方法绑定到对象上
  INIT_CLASS_ENTRY(ce, CLASS_NAME_PRODUCER, producer_methods);
  producer_ce = zend_register_internal_class_ex(&ce, NULL);
  producer_ce->create_object = producer_object_create;

  INIT_CLASS_ENTRY(transaction_ce, CLASS_NAME_TRANSACTION_PRODUCER, transaction_producer_methods);
  transaction_producer_ce = zend_register_internal_class_ex(&transaction_ce, producer_ce);
  transaction_producer_ce->create_object = producer_object_create;

  INIT_CLASS_ENTRY(orderly_ce, CLASS_NAME_ORDERLY_PRODUCER, orderly_producer_methods);
  orderly_producer_ce = zend_register_internal_class_ex(&orderly_ce, producer_ce);
  orderly_producer_ce->create_object = producer_object_create;

  memcpy(&producer_object_handlers, zend_get_std_object_handlers(), sizeof(producer_object_handlers));
  producer_object_handlers.offset = XtOffsetOf(producer_obj, std);
  producer_object_handlers.free_obj = producer_object_free_storage;
}