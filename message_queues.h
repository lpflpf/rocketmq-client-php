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

#ifndef PHP_ROCKETMQ_MESSAGE_QUEUES_H_
#define PHP_ROCKETMQ_MESSAGE_QUEUES_H_

#include "common.h"
#include "php.h"

extern const zend_function_entry message_queues_methods[];

#define CLASS_NAME_MESSAGE_QUEUE ZEND_NS_NAME( ROCKETMQ_NS, "MessageQueues")

static zend_class_entry *message_queue_ce;
typedef struct _message_queues_obj {
    CMessageQueue *message_queues;
    int size;
    zend_object std;
} message_queues_obj;

void minit_message_queues();

#endif
