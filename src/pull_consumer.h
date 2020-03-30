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

#ifndef ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H_
#define ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H_

#include "common.h"
#include <rocketmq/DefaultMQPullConsumer.h>
#include "message.h"
#include "message_queue.h"
#include "pull_result.h"


class PullConsumer:public Php::Base
{
	private:
		std::string topicName;
		rocketmq::DefaultMQPullConsumer *consumer;
		std::vector<rocketmq::MQMessageQueue> mqs;
	public:
		PullConsumer(){
			this->consumer = nullptr;
		}
		virtual ~PullConsumer(){
			//           if (nullptr != this->consumer){
			//               delete(this->consumer);
			//           }
		}
		virtual void __construct(Php::Parameters &params);
		virtual void __destruct() {
		}

		void start();
		void shutdown();

		Php::Value getQueues();

		Php::Value getNamesrvDomain();
		void setNamesrvDomain(Php::Parameters &param);

		Php::Value getNamesrvAddr();
		void setNamesrvAddr(Php::Parameters &param);

		void setInstanceName(Php::Parameters &param);

		void setTopic(Php::Parameters &param);

		void setGroup(Php::Parameters &param);

		Php::Value pull(Php::Parameters &param);
		Php::Value pullBlockIfNotFound(Php::Parameters &param);

		void setSessionCredentials(Php::Parameters &param);
		Php::Value getSessionCredentials();

		void updateConsumeOffset(Php::Parameters &params);
		void removeConsumeOffset(Php::Parameters &params);

		Php::Value fetchConsumeOffset(Php::Parameters &params);

		void persistConsumerOffset4PullConsumer(Php::Parameters &params);

		//void setLogLevel(elogLevel inputLevel);
		void setLogLevel(Php::Parameters &param);
		//ELogLevel getLogLevel();
		Php::Value getLogLevel();
		//void setLogFileSizeAndNum(int fileNum, long perFileSize);  // perFileSize is MB unit
		void setLogFileSizeAndNum(Php::Parameters &param);

		//const std::string& getGroupName() const;
		Php::Value getGroupName();

		//void setGroupName(const std::string& groupname);
		void setGroupName(Php::Parameters &param);


		// const std::string& getNameSpace() const;
		Php::Value getNameSpace();

		//void setNameSpace(const std::string& nameSpace);
		void setNameSpace(Php::Parameters &param);


		//const std::string& getInstanceName() const;
		Php::Value getInstanceName();

		// std::string version()
		Php::Value version();

		//void setLogPath(const std::string& logPath);
		void setLogPath(Php::Parameters &logPath);
};

void registerPullConsumer(Php::Namespace &rocketMQNamespace);

#endif
