#ifndef ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H
#define ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H

#include "common.h"
#include <rocketmq/DefaultMQPullConsumer.h>
#include "message.h"
#include "message_queue.h"


class PullConsumer:public Php::Base
{
	private:
		std::string groupName;
		std::string namesrv_domain;
		std::string topic;
		rocketmq::DefaultMQPullConsumer *consumer;
		std::vector<rocketmq::MQMessageQueue> mqs;
	public:
		PullConsumer(){}
		virtual ~PullConsumer(){}
		virtual void __construct(){}

		void start(){
			this->consumer = new rocketmq::DefaultMQPullConsumer(this->groupName);
			this->consumer->setNamesrvAddr(this->namesrv_domain);
			this->consumer->setGroupName(this->groupName);
			this->consumer->setInstanceName(this->groupName);
			this->consumer->start();
		}

		Php::Value getQueues(){
			this->consumer->fetchSubscribeMessageQueues(this->topic, this->mqs);
			Php::Value result;
			int idx = 0;

			std::vector<rocketmq::MQMessageQueue>::iterator iter = mqs.begin();
			for (; iter != mqs.end(); ++iter) {
				rocketmq::MQMessageQueue mq = (*iter);
				result[idx++] = Php::Object(MESSAGE_QUEUE_CLASS_NAME , new MessageQueue(mq, this->consumer)); 
			}
			return result;
		}

		void setNamesrvDomain(Php::Parameters &param){
			Php::Value nameserver = param[0];
			std::string tmp =  nameserver;
			this->namesrv_domain = tmp;
		}

		void setInstanceName(Php::Parameters &param){
			Php::Value groupName = param[0];
			std::string test = groupName;
			this->groupName = test;
		}

		void setTopic(Php::Parameters &param){
			Php::Value val = param[0];
			std::string topic = val;
			this->topic = topic;
		}

};

#endif
