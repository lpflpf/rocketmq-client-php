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
				Php::Value msg(Php::Object("Message", new Message(msgs[i])));
				this->callback(msg);
			}

			return rocketmq::CONSUME_SUCCESS;
		}
};


class MPushConsumer : public Php::Base{
	private:
		std::string groupName;
		std::string namesrv_domain;
		std::string topic;
		rocketmq::DefaultMQPushConsumer *consumer;
		Php::Value    callback;
	public:
		MPushConsumer(){}
		virtual ~MPushConsumer(){}
		virtual void __construct(){}

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
		void setCallback(Php::Parameters &param){
			if (!param[0].isCallable())
				throw Php::Exception("Not a callable type.");
			this->callback = param[0];
		}
		void start(){
			this->consumer = new rocketmq::DefaultMQPushConsumer(this->groupName);
			this->consumer->setGroupName(this->groupName);
			this->consumer->setInstanceName(this->groupName);
			this->consumer->setNamesrvAddr(this->namesrv_domain);
			this->consumer->subscribe(this->topic, "*");
			this->consumer->setConsumeThreadCount(1);
			this->consumer->setTcpTransportTryLockTimeout(1000);
			this->consumer->setTcpTransportConnectTimeout(400);
			MyMsgListener msglistener;
			msglistener.setCallback(this->callback);
			this->consumer->registerMessageListener(&msglistener);
			this->consumer->setConsumeFromWhere(rocketmq::CONSUME_FROM_FIRST_OFFSET);
			std::cout << this->groupName << this->namesrv_domain << std::endl;
			try {
				this->consumer->start();
			} catch (rocketmq::MQClientException &e) {
				std::cout << e << std::endl;
			}
			sleep(10);
		}
		void shutdown(){
			this->consumer->shutdown();
		}
		virtual void __destruct()
		{
		}

};

#endif
