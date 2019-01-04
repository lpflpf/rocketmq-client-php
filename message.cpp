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

