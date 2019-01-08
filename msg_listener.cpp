#include "msg_listener.h"
#include "message.h"

void registerMessageListenerType(Php::Namespace &rocketMQNamespace){
	Php::Class<MessageListenerType> messageListenerTypeClass("MessageListenerType");
	messageListenerTypeClass.constant("LISTENER_DEFAULTLY", (int) rocketmq::messageListenerDefaultly);
	messageListenerTypeClass.constant("LISTENER_ORDERLY", (int) rocketmq::messageListenerOrderly);
	messageListenerTypeClass.constant("LISTENERCONCURRENTLY", (int) rocketmq::messageListenerConcurrently);

	rocketMQNamespace.add(messageListenerTypeClass);
}

rocketmq::ConsumeStatus commonConsumeMessage(const std::vector<rocketmq::MQMessageExt> &msgs, Php::Value callback){
	for (size_t i = 0; i < msgs.size(); ++i) {
		Php::Value msg(Php::Object(MESSAGE_CLASS_NAME, new Message(msgs[i])));
		int ret = callback(msg);
		if (rocketmq::CONSUME_SUCCESS != ret){
			return rocketmq::RECONSUME_LATER;
		}
	}
	return rocketmq::CONSUME_SUCCESS;
}

rocketmq::ConsumeStatus MsgListenerConcurrently::consumeMessage(const std::vector<rocketmq::MQMessageExt> &msgs) {
	return commonConsumeMessage(msgs, this->callback);
//	for (size_t i = 0; i < msgs.size(); ++i) {
//		Php::Value msg(Php::Object(MESSAGE_CLASS_NAME, new Message(msgs[i])));
//		if (rocketmq::CONSUME_SUCCESS != this->callback(msg)){
//			return rocketmq::RECONSUME_LATER;
//		}
//	}
//
//	return rocketmq::CONSUME_SUCCESS;
}

rocketmq::ConsumeStatus MsgListenerOrderly::consumeMessage(const std::vector<rocketmq::MQMessageExt> &msgs) {
	return commonConsumeMessage(msgs, this->callback);
//	for (size_t i = 0; i < msgs.size(); ++i) {
//		Php::Value msg(Php::Object(MESSAGE_CLASS_NAME, new Message(msgs[i])));
//		if (rocketmq::CONSUME_SUCCESS != this->callback(msg)){
//			return rocketmq::RECONSUME_LATER;
//		}
//	}
//
//	return rocketmq::CONSUME_SUCCESS;
}

rocketmq::ConsumeStatus MsgListener::consumeMessage(const std::vector<rocketmq::MQMessageExt> &msgs) {
	return commonConsumeMessage(msgs, this->callback);
//	for (size_t i = 0; i < msgs.size(); ++i) {
//		Php::Value msg(Php::Object(MESSAGE_CLASS_NAME, new Message(msgs[i])));
//		if (rocketmq::CONSUME_SUCCESS != this->callback(msg)){
//			return rocketmq::RECONSUME_LATER;
//		}
//	}

//	return rocketmq::CONSUME_SUCCESS;
}

