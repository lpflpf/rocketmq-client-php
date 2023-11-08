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

#include "e_log_level.h"

static zend_class_entry *e_log_level_ce;
void minit_e_log_level() {
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, CLASS_NAME_E_LOG_LEVEL, NULL);
  e_log_level_ce = zend_register_internal_class_ex(&ce, NULL);
  REGISTER_ROCKETMQ_CLASS_CONST(e_log_level_ce, "FATAL", E_LOG_LEVEL_FATAL);
  REGISTER_ROCKETMQ_CLASS_CONST(e_log_level_ce, "ERROR", E_LOG_LEVEL_ERROR);
  REGISTER_ROCKETMQ_CLASS_CONST(e_log_level_ce, "WARN", E_LOG_LEVEL_WARN);
  REGISTER_ROCKETMQ_CLASS_CONST(e_log_level_ce, "INFO", E_LOG_LEVEL_INFO);
  REGISTER_ROCKETMQ_CLASS_CONST(e_log_level_ce, "DEBUG", E_LOG_LEVEL_DEBUG);
  REGISTER_ROCKETMQ_CLASS_CONST(e_log_level_ce, "TRACE", E_LOG_LEVEL_TRACE);
  REGISTER_ROCKETMQ_CLASS_CONST(e_log_level_ce, "LEVEL_NUM", E_LOG_LEVEL_LEVEL_NUM);
}