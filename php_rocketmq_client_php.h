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

#ifndef PHP_ROCKETMQ_CLIENT_PHP_H_
#define PHP_ROCKETMQ_CLIENT_PHP_H_

extern zend_module_entry rocketmq_client_php_module_entry;
# define phpext_rocketmq_client_php_ptr &rocketmq_client_php_module_entry

#include "php_version.h"
# define PHP_ROCKETMQ_CLIENT_PHP_VERSION PHP_VERSION

# if defined(ZTS) && defined(COMPILE_DL_ROCKETMQ_CLIENT_PHP)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#include "message.h"
#include "batch_message.h"
#include "message_ext.h"
#include "send_result.h"
#include "mq_exception.h"
#include "message_queues.h"
#include "pull_result.h"
#include "push_consumer.h"
#include "e_log_level.h"
#include "consume_status.h"
#include "consume_from_where.h"
#include "message_model.h"
#include "transaction_status.h"
#include "send_status.h"
#include "pull_consumer.h"
#include "trace_model.h"
#include "push_consumer.h"

PHP_MINIT_FUNCTION(rocketmq_client_php);
PHP_MSHUTDOWN_FUNCTION(rocketmq_client_php);
#endif	/* PHP_ROCKETMQ_CLIENT_PHP_H */
