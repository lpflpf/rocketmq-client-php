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

#include "consume_from_where.h"

static zend_class_entry *consume_from_where_ce;
void minit_consume_from_where() {
  zend_class_entry ce;
  // 初始化一个类对象，并将方法绑定到对象上
  INIT_CLASS_ENTRY(ce, CLASS_NAME_CONSUME_FROM_WHERE, NULL);
  consume_from_where_ce= zend_register_internal_class_ex(&ce, NULL);
  REGISTER_ROCKETMQ_CLASS_CONST(consume_from_where_ce, "LAST_OFFSET", 0);
  REGISTER_ROCKETMQ_CLASS_CONST(consume_from_where_ce, "LAST_OFFSET_AND_FROM_MIN_WHEN_BOOT_FIRST", 1);
  REGISTER_ROCKETMQ_CLASS_CONST(consume_from_where_ce, "MIN_OFFSET", 2);
  REGISTER_ROCKETMQ_CLASS_CONST(consume_from_where_ce, "MAX_OFFSET", 3);
  REGISTER_ROCKETMQ_CLASS_CONST(consume_from_where_ce, "FIRST_OFFSET", 4);
  REGISTER_ROCKETMQ_CLASS_CONST(consume_from_where_ce, "TIMESTAMP", 5);
}