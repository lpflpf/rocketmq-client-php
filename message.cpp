#include "message.h"

Php::Value Message::toString() {
	std::stringstream ss;
	ss  << "MessageExt [queueId=" << this->message.getQueueId() 
		<< ", queueOffset=" << this->message.getQueueOffset()
		<< ", queueId=" << this->message.getQueueId()
		<< ", bornTimestamp=" << this->message.getBornTimestamp()
		<< ", bornHost=" << std::string(this->message.getBornHost().sa_data)
		<< ", storeTimeStamp=" << this->message.getStoreTimestamp()
		<< ", storeHost=" << std::string(this->message.getStoreHost().sa_data)
		<< ", msgId=" <<  std::string(this->message.getMsgId())
		<< ", queueOffst=" << this->message.getQueueOffset()
		<< ", commitLogOffset=" << this->message.getCommitLogOffset()
		<< ", preparedTransactionOffset=" << this->message.getPreparedTransactionOffset()
		<< ", storeSize=" << this->message.getStoreSize()
		<< ", bodyCRC=" << this->message.getBodyCRC()
		<< ", ReconsumeTimes=" << this->message.getReconsumeTimes()
		<< ", offsetMsgId=" << this->message.getOffsetMsgId()
		<< ", topic=" << this->message.getTopic()
		<< ", flag=" << this->message.getFlag()
		<< ", body=" << this->message.getBody();

	return ss.str();
}

void registerMessage(Php::Namespace &rocketMQNamespace){
	Php::Class<Message> messageClass("Message");
	messageClass.method<&Message::toString>("toString");
	messageClass.method<&Message::getQueueId>("getQueueId");
	messageClass.method<&Message::getBornTimestamp>("getBornTimestamp");
	messageClass.method<&Message::getBornHost>("getBornHost");
	messageClass.method<&Message::getBornHostString>("getBornHostString");
	messageClass.method<&Message::getBornHostNameString>("getBornHostNameString");
	messageClass.method<&Message::getStoreTimestamp>("getStoreTimestamp");
	messageClass.method<&Message::getStoreHost>("getStoreHost");
	messageClass.method<&Message::getStoreHostString>("getStoreHostString");
	messageClass.method<&Message::getMsgId>("getMsgId");
	messageClass.method<&Message::getOffsetMsgId>("getOffsetMsgId");
	messageClass.method<&Message::getBodyCRC>("getBodyCRC");
	messageClass.method<&Message::getQueueOffset>("getQueueOffset");
	messageClass.method<&Message::getCommitLogOffset>("getCommitLogOffset");
	messageClass.method<&Message::getStoreSize>("getStoreSize");
	messageClass.method<&Message::getReconsumeTimes>("getReconsumeTimes");
	messageClass.method<&Message::getPreparedTransactionOffset>("getPreparedTransactionOffset");
	messageClass.method<&Message::getProperty>("getProperty", { Php::ByVal("name", Php::Type::String), });
	messageClass.method<&Message::getTopic>("getTopic");
	messageClass.method<&Message::getTags>("getTags");
	messageClass.method<&Message::getKeys>("getKeys");
	messageClass.method<&Message::getDelayTimeLevel>("getDelayTimeLevel");
	messageClass.method<&Message::getFlag>("getFlag");
	messageClass.method<&Message::getSysFlag>("getSysFlag");
	messageClass.method<&Message::getBody>("getBody");

	rocketMQNamespace.add(messageClass);
}
