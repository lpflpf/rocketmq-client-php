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

#pragma once

#include "common.h"
#include "php.h"

extern const zend_function_entry pull_result_methods[];

#define CLASS_NAME_PULL_RESULT ZEND_NS_NAME(ROCKETMQ_NS, "PullResult")

typedef struct _pull_result_obj{
    CPullResult pull_result;
    int current;
    zend_object std;
} pull_result_obj;

void minit_pull_result();