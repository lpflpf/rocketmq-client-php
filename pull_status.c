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

#include "pull_status.h"

static zend_class_entry *pull_status_ce;
void minit_pull_status() {
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, CLASS_NAME_PULL_STATUS, NULL);
  pull_status_ce = zend_register_internal_class_ex(&ce, NULL);
  REGISTER_ROCKETMQ_CLASS_CONST(pull_status_ce, "FOUND", E_FOUND);
  REGISTER_ROCKETMQ_CLASS_CONST(pull_status_ce, "NO_NEW_MSG", E_NO_NEW_MSG);
  REGISTER_ROCKETMQ_CLASS_CONST(pull_status_ce, "NO_MATCHED_MSG", E_NO_MATCHED_MSG);
  REGISTER_ROCKETMQ_CLASS_CONST(pull_status_ce, "OFFSET_ILLEGAL", E_OFFSET_ILLEGAL);
  REGISTER_ROCKETMQ_CLASS_CONST(pull_status_ce, "BROKER_TIMEOUT", E_BROKER_TIMEOUT);
}
