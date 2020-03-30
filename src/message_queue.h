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

#ifndef ROCKETMQ_CLIENT_PHP_MESSAGE_QUEUE_H_
#define ROCKETMQ_CLIENT_PHP_MESSAGE_QUEUE_H_

#include <rocketmq/DefaultMQPullConsumer.h>
#include "common.h"

#define MESSAGE_QUEUE_CLASS_NAME NAMESPACE_NAME"\\MessageQueue"

class MessageQueue : public Php::Base 
{
	private:
		rocketmq::MQMessageQueue *messageQueue;


	public:
		MessageQueue() {
			this->messageQueue = nullptr;
		}
		virtual ~MessageQueue(){			
		}
		MessageQueue(rocketmq::MQMessageQueue* other);
		void __construct(Php::Parameters &params);

		Php::Value getTopic();
		void setTopic(Php::Parameters &param);

		Php::Value getBrokerName();
		void setBrokerName(Php::Parameters &param);

		Php::Value getQueueId() ;
		void setQueueId(Php::Parameters &param);

		rocketmq::MQMessageQueue& getInstance(){
			return *this->messageQueue;
		}


		virtual void __destruct(){
//			if (this->messageQueue != nullptr) {
//				delete(this->messageQueue);
//			}
		}
};

void registerMessageQueue(Php::Namespace &rocketMQNamespace);

#endif
