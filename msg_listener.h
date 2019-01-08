#ifndef ROCKETMQ_CLIENT_PHP_MESSAGE_LISTENER_TYPE_H
#define ROCKETMQ_CLIENT_PHP_MESSAGE_LISTENER_TYPE_H

#include "rocketmq/MQMessageListener.h"
#include "common.h"
//  messageListenerDefaultly = 0,
//  messageListenerOrderly = 1,
//  messageListenerConcurrently = 2

class MessageListenerType : public Php::Base{

};

void registerMessageListenerType(Php::Namespace &rocketMQNamespace);

class MsgListenerConcurrently : public rocketmq::MessageListenerConcurrently {
	private:
		Php::Value callback;
	public:
		void setCallback(Php::Value callback){
			this->callback = callback;
		}
		MsgListenerConcurrently() {}
		~MsgListenerConcurrently() {}

		rocketmq::ConsumeStatus consumeMessage(const std::vector<rocketmq::MQMessageExt> &msgs);
};

class MsgListenerOrderly: public rocketmq::MessageListenerOrderly {
	private:
		Php::Value callback;
	public:
		void setCallback(Php::Value callback){
			this->callback = callback;
		}
		MsgListenerOrderly() {}
		~MsgListenerOrderly() {}

		rocketmq::ConsumeStatus consumeMessage(const std::vector<rocketmq::MQMessageExt> &msgs);
};

class MsgListener : public rocketmq::MQMessageListener {
	private:
		Php::Value callback;
	public:
		void setCallback(Php::Value callback){
			this->callback = callback;
		}
		MsgListener() {}
		~MsgListener() {}

		rocketmq::ConsumeStatus consumeMessage(const std::vector<rocketmq::MQMessageExt> &msgs);
};

#endif
