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

#ifndef ROCKETMQ_CLIENT_PHP_ELOG_LEVEL_H_
#define ROCKETMQ_CLIENT_PHP_ELOG_LEVEL_H_

#include "common.h"

class ELogLevel: public Php::Base
{
    //eLOG_LEVEL_FATAL,
    //eLOG_LEVEL_ERROR,
    //eLOG_LEVEL_WARN,
    //eLOG_LEVEL_INFO,
    //eLOG_LEVEL_DEBUG,
    //eLOG_LEVEL_TRACE,
    //eLOG_LEVEL_LEVEL_NUM,
};

void registerELogLevel(Php::Namespace &rocketMQNamespace)
{
    Php::Class<ELogLevel> ELogLevelClass("ELogLevel");
    ELogLevelClass.constant("eLOG_LEVEL_FATAL", rocketmq::eLOG_LEVEL_FATAL);
    ELogLevelClass.constant("eLOG_LEVEL_ERROR", rocketmq::eLOG_LEVEL_ERROR);
    ELogLevelClass.constant("eLOG_LEVEL_WARN", rocketmq::eLOG_LEVEL_WARN);
    ELogLevelClass.constant("eLOG_LEVEL_INFO", rocketmq::eLOG_LEVEL_INFO);
    ELogLevelClass.constant("eLOG_LEVEL_DEBUG", rocketmq::eLOG_LEVEL_DEBUG);
    ELogLevelClass.constant("eLOG_LEVEL_TRACE", rocketmq::eLOG_LEVEL_TRACE);
    ELogLevelClass.constant("eLOG_LEVEL_LEVEL_NUM", rocketmq::eLOG_LEVEL_LEVEL_NUM);
    rocketMQNamespace.add(ELogLevelClass);
}

#endif
