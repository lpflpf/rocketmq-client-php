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

#include "php.h"
#include "ext/standard/info.h"
#include "php_rocketmq_client_php.h"
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif


PHP_FUNCTION(getLatestErrorMessage)
{
	ZEND_PARSE_PARAMETERS_NONE();
    RETURN_STRING(GetLatestErrorMessage());
}

PHP_RINIT_FUNCTION(rocketmq_client_php)
{
#if defined(ZTS) && defined(COMPILE_DL_ROCKETMQ_CLIENT_PHP)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

PHP_MINFO_FUNCTION(rocketmq_client_php)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "rocketmq_client_php support", "enabled");
	php_info_print_table_end();
}

static const zend_function_entry rocketmq_client_php_functions[] = {
	PHP_FE(getLatestErrorMessage, 			arg_input_void)
	PHP_FE_END
};

/* {{{ rocketmq_client_php_module_entry
 */
zend_module_entry rocketmq_client_php_module_entry = {
	STANDARD_MODULE_HEADER,
	"rocketmq_client_php",					/* Extension name */
	rocketmq_client_php_functions,			/* zend_function_entry */
	PHP_MINIT(rocketmq_client_php),  /* PHP_MINIT - Module initialization */
    NULL,                            /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(rocketmq_client_php),  /* PHP_RINIT - Request initialization */
    NULL,                            /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(rocketmq_client_php),  /* PHP_MINFO - Module info */
    PHP_ROCKETMQ_CLIENT_PHP_VERSION, /* Version */
    STANDARD_MODULE_PROPERTIES
    };

// 当模块启动时执行的方法
PHP_MINIT_FUNCTION(rocketmq_client_php) {
  minit_message();
  minit_mq_exception();
  minit_message_ext();
  minit_batch_message();
  minit_send_result();
  minit_producer();
  minit_message_queues();
  minit_pull_result();
  minit_pull_consumer();
  minit_push_consumer();
  minit_e_log_level();
  minit_consume_status();
  minit_consume_from_where();
  minit_message_model();
  minit_transaction_status();
  minit_send_result();
  minit_pull_status();
  minit_trace_model();
  minit_push_status();
  minit_send_status();

  return SUCCESS;
}

#ifdef COMPILE_DL_ROCKETMQ_CLIENT_PHP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(rocketmq_client_php)
#endif
