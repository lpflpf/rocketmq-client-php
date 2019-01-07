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

		void start();

		Php::Value getQueues();

		void setNamesrvDomain(Php::Parameters &param);

		void setInstanceName(Php::Parameters &param);

		void setTopic(Php::Parameters &param);

};

void registerPullConsumer(Php::Namespace &rocketMQNamespace);

#endif
