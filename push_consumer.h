#include "common.h"

#ifndef ROCKETMQ_CLIENT_PHP_PUSH_CONSUMER_H
#define ROCKETMQ_CLIENT_PHP_PUSH_CONSUMER_H

#include "message.h"
#include <rocketmq/DefaultMQPushConsumer.h>

class MyMsgListener : public rocketmq::MessageListenerConcurrently {
	private:
		Php::Value callback;
	public:
		void setCallback(Php::Value callback){
			this->callback = callback;
		}
		MyMsgListener() {}
		~MyMsgListener() {}

		rocketmq::ConsumeStatus consumeMessage(const std::vector<rocketmq::MQMessageExt> &msgs) {
			for (size_t i = 0; i < msgs.size(); ++i) {
				Php::Value msg(Php::Object(MESSAGE_CLASS_NAME, new Message(msgs[i])));
				this->callback(msg);
			}

			return rocketmq::CONSUME_SUCCESS;
		}
};


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

	public:
		PushConsumer(){}
		virtual ~PushConsumer(){}
		virtual void __construct(){}

		void setNamesrvDomain(Php::Parameters &param);

		void setInstanceName(Php::Parameters &param);

		void setTryLockTimeout(Php::Parameters &param);

		void setConnectTimeout(Php::Parameters &param);

		void setThreadCount(Php::Parameters &param);

		void subscribe(Php::Parameters &param);
		
		void setCallback(Php::Parameters &param);

		void start();

		void shutdown();

		virtual void __destruct() { }

};

void registerPushConsumer(Php::Namespace &rocketMQNamespace);

#endif
