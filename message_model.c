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

#include "message_model.h"

static zend_class_entry *message_model_ce;
void minit_message_model() {
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, CLASS_NAME_MESSAGE_MODEL, NULL);
  message_model_ce = zend_register_internal_class_ex(&ce, NULL);
  REGISTER_ROCKETMQ_CLASS_CONST(message_model_ce, "BROADCASTING", BROADCASTING);
  REGISTER_ROCKETMQ_CLASS_CONST(message_model_ce, "CLUSTERING", CLUSTERING);
}