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

#ifndef PHP_ROCKETMQ_PRODUCER_H_
#define PHP_ROCKETMQ_PRODUCER_H_

#include "batch_message.h"
#include "common.h"
#include "message.h"
#include "message_ext.h"
#include "mq_exception.h"
#include "php.h"
#include "send_result.h"

extern const zend_function_entry producer_methods[];
extern const zend_function_entry orderly_producer_methods[];
extern const zend_function_entry transaction_producer_methods[];

#define CLASS_NAME_PRODUCER ZEND_NS_NAME(ROCKETMQ_NS, "Producer")
#define CLASS_NAME_ORDERLY_PRODUCER ZEND_NS_NAME(ROCKETMQ_NS, "OrderlyProducer")
#define CLASS_NAME_TRANSACTION_PRODUCER ZEND_NS_NAME(ROCKETMQ_NS, "TransactionProducer")

typedef struct _producer_obj {
  CProducer *producer;
  zend_object std;
} producer_obj;

void minit_producer();

#endif
