#include "common.h"

#ifndef ROCKETMQ_CLIENT_PHP_PUSH_CONSUMER_H
#define ROCKETMQ_CLIENT_PHP_PUSH_CONSUMER_H

#include "message.h"
#include <rocketmq/DefaultMQPushConsumer.h>


class PushConsumer : public Php::Base{
	private:
		std::string groupName;
		std::string namesrv_domain;
		std::string topic;
		rocketmq::DefaultMQPushConsumer *consumer;
		Php::Value    callback;
		int tryLockTimeout = 1000;
		int connectTimeout = 400;
		int threadCount = 1;
		std::string tag = "*";
		int msgListenerType;

	public:
		PushConsumer(){}
		virtual ~PushConsumer(){}
		virtual void __construct(Php::Parameters &params);

 		void doRebalance();

 		void persistConsumerOffset();

 		void persistConsumerOffsetByResetOffset();

		void setNamesrvDomain(Php::Parameters &param);

		void setInstanceName(Php::Parameters &param);

		void setTryLockTimeout(Php::Parameters &param);

		void setConnectTimeout(Php::Parameters &param);

		void setListenerType(Php::Parameters &param);

		void setThreadCount(Php::Parameters &param);

		void subscribe(Php::Parameters &param);
		
		void setCallback(Php::Parameters &param);

		Php::Value getConsumeType();

		Php::Value getConsumeFromWhere();

  		void setConsumeFromWhere(Php::Parameters &param);

		void start();

		void shutdown();

		virtual void __destruct() { }

};

void registerPushConsumer(Php::Namespace &rocketMQNamespace);

#endif
