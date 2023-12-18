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

#ifndef PHP_ROCKETMQ_COMMON_H_
#define PHP_ROCKETMQ_COMMON_H_

#include "rocketmq/CBatchMessage.h" // DONE
#include "rocketmq/CCommon.h"
#include "rocketmq/CErrorMessage.h" // DONE
#include "rocketmq/CMQException.h"
#include "rocketmq/CMessage.h"    // DONE
#include "rocketmq/CMessageExt.h" // DONE
#include "rocketmq/CMessageQueue.h"
#include "rocketmq/CProducer.h"
#include "rocketmq/CPullConsumer.h"
#include "rocketmq/CPullResult.h"
#include "rocketmq/CPushConsumer.h"
#include "rocketmq/CSendResult.h" // DONE
#include "rocketmq/CTransactionStatus.h"

#include "php.h"

#define ROCKETMQ_DEBUG 1
#define ROCKETMQ_GET_STR_PARAM(STR)                                                                                    \
  char *STR;                                                                                                           \
  size_t len;                                                                                                          \
  ZEND_PARSE_PARAMETERS_START(1, 1)                                                                                    \
  Z_PARAM_STRING(STR, len)                                                                                             \
  ZEND_PARSE_PARAMETERS_END();

#define ROCKETMQ_GET_LONG_PARAM(longdata)                                                                                      \
  zend_long longdata;                                                                                            \
  ZEND_PARSE_PARAMETERS_START(1, 1)                                                                                    \
  Z_PARAM_LONG(longdata)                                                                                         \
  ZEND_PARSE_PARAMETERS_END();

#define ROCKETMQ_GET_OBJECT(class_entry, o) ((class_entry *)((char *)o - XtOffsetOf(class_entry, std)))

#define ROCKETMQ_ZVAL_GET_OBJECT(class_entry, z) ROCKETMQ_GET_OBJECT(class_entry, Z_OBJ_P(z))

ZEND_BEGIN_ARG_INFO(arg_input_void, 0)
ZEND_END_ARG_INFO()

#define DEBUG_DESTROY(classname)
#define DEBUG_CREATE(classname)

typedef struct _diy_callback {
  zval object;
  zend_fcall_info fci;
  zend_fcall_info_cache fcc;
} diy_callback;

ZEND_BEGIN_MODULE_GLOBALS(rocketmq)
diy_callback push_callback;
diy_callback push_callback_orderly;
diy_callback producer_send_success;
diy_callback producer_send_exception;
ZEND_END_MODULE_GLOBALS(rocketmq)
ZEND_DECLARE_MODULE_GLOBALS(rocketmq);
#define IF_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(rocketmq, v)

#define ROCKETMQ_NS "RocketMQ"
#define REGISTER_ROCKETMQ_CLASS_CONST(ce, const_name, value)                                                           \
  zend_declare_class_constant_long(ce, const_name, sizeof(const_name) - 1, value);

zval create_object_zval(char *classname);

void replace_fci(diy_callback *callback, zend_fcall_info fci, zend_fcall_info_cache fcc);

#endif
