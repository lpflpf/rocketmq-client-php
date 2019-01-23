#include "send_result.h"


void registerSendResult(Php::Namespace &rocketMQNamespace){
	Php::Class<SendResult> sendResultClass("SendResult");

	sendResultClass.method<&SendResult::getMsgId>("getMsgId");
	sendResultClass.method<&SendResult::getOffsetMsgId>("getOffsetMsgId");
	sendResultClass.method<&SendResult::getSendStatus>("getSendStatus");
	sendResultClass.method<&SendResult::getMessageQueue>("getMessageQueue");
	sendResultClass.method<&SendResult::getQueueOffset>("getQueueOffset");

	rocketMQNamespace.add(sendResultClass);
}

