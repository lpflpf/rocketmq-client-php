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

#include "transaction_status.h"

static zend_class_entry *transaction_status_ce;
void minit_transaction_status() {
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, CLASS_NAME_TRANSACTION_STATUS, NULL);
  transaction_status_ce = zend_register_internal_class_ex(&ce, NULL);
  REGISTER_ROCKETMQ_CLASS_CONST(transaction_status_ce, "COMMIT", E_COMMIT_TRANSACTION);
  REGISTER_ROCKETMQ_CLASS_CONST(transaction_status_ce, "ROLLBACK", E_ROLLBACK_TRANSACTION);
  REGISTER_ROCKETMQ_CLASS_CONST(transaction_status_ce, "UNKNOWN", E_UNKNOWN_TRANSACTION);
}