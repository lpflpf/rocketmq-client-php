#include "message_ext.h"

void registerMessageExt(Php::Namespace &rocketMQNamespace){
	Php::Class<MessageExt> messageExtClass("MessageExt");

	messageExtClass.method<&MessageExt::parseTopicFilterType>("parseTopicFilterType", { Php::ByVal("filterType", Php::Type::Numeric), });
	messageExtClass.method<&MessageExt::getQueueId>("getQueue");
	messageExtClass.method<&MessageExt::setQueueId>("setQueueId", { Php::ByVal("queueId", Php::Type::Numeric), });
	messageExtClass.method<&MessageExt::getBornTimestamp>("getBornTimestamp");
	messageExtClass.method<&MessageExt::setBornTimestamp>("setBornTimestamp", { Php::ByVal("bornTimestamp", Php::Type::Numeric), });
	messageExtClass.method<&MessageExt::getStoreHostString>("getStoreHostString");

	messageExtClass.method<&MessageExt::getMsgId>("getMsgId");
	messageExtClass.method<&MessageExt::setMsgId>("setMsgId", { Php::ByVal("msgId", Php::Type::String), });

	messageExtClass.method<&MessageExt::getOffsetMsgId>("getOffsetMsgId");
	messageExtClass.method<&MessageExt::setOffsetMsgId>("setOffsetMsgId", {
			Php::ByVal("offsetMsgId", Php::Type::Numeric),
			});

	messageExtClass.method<&MessageExt::getBodyCRC>("getBodyCRC");
	messageExtClass.method<&MessageExt::setBodyCRC>("setBodyCRC", {
			Php::ByVal("bodyCRC", Php::Type::Numeric),
			});
	messageExtClass.method<&MessageExt::getQueueOffset>("getQueueOffset");
	messageExtClass.method<&MessageExt::setQueueOffset>("setQueueOffset", {
			Php::ByVal("queueOffset", Php::Type::Numeric),
			});
	messageExtClass.method<&MessageExt::getCommitLogOffset>("getCommitLogOffset");
	messageExtClass.method<&MessageExt::setCommitLogOffset>("setCommitLogOffset", {
			Php::ByVal("physicOffset", Php::Type::Numeric),
			});
	messageExtClass.method<&MessageExt::getStoreSize>("getStoreSize");
	messageExtClass.method<&MessageExt::setStoreSize>("setStoreSize", {
			Php::ByVal("storeSize", Php::Type::Numeric),
			});
	messageExtClass.method<&MessageExt::getReconsumeTimes>("getReconsumeTimes");
	messageExtClass.method<&MessageExt::getPreparedTransactionOffset>("getPreparedTransactionOffset");
	messageExtClass.method<&MessageExt::setPreparedTransactionOffset>("setPreparedTransactionOffset", {
			Php::ByVal("preparedTransactionOffset", Php::Type::Numeric),
			});
	messageExtClass.method<&MessageExt::toString>("toString");
	messageExtClass.method<&MessageExt::getMessage>("getMessage");
	rocketMQNamespace.add(messageExtClass);
}
