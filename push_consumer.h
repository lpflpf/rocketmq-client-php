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

#ifndef PHP_ROCKETMQ_PUSH_CONSUMER_H_
#define PHP_ROCKETMQ_PUSH_CONSUMER_H_

#include "common.h"
#include "php.h"
#include "message_ext.h"

extern const zend_function_entry push_consumer_methods[];

#define CLASS_NAME_PUSH_CONSUMER ZEND_NS_NAME( ROCKETMQ_NS, "PushConsumer")

typedef struct _push_consumer_obj{
    CPushConsumer *push_consumer;
    zend_object std;
} push_consumer_obj;

void minit_push_consumer();

#endif