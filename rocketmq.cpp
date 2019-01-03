#include "common.h"
#include "producer.h"
#include "push_consumer.h"
#include "pull_consumer.h"
#include "message.h"
#include "pull_status.h"
#include "pull_result.h"

// symbols are exported according to the "C" language
extern "C"
{
	// export the "get_module" function that will be called by the Zend engine
	PHPCPP_EXPORT void *get_module() 
	{ 
		// create extension
		static Php::Extension extension("rocketmq", "1.0");

		// define classes
		Php::Class<MProducer> producerClass("MQProducer");

		producerClass.method<&MProducer::__construct>("__construct");
		producerClass.method<&MProducer::setInstanceName>("setInstanceName", {
				Php::ByVal("groupName", Php::Type::String),
				});
		producerClass.method<&MProducer::setNamesrvDomain>("setNamesrvDomain", {
				Php::ByVal("nameserver", Php::Type::String),
				});
		producerClass.method<&MProducer::start>("start");
		producerClass.method<&MProducer::push>("push", {
				Php::ByVal("topic", Php::Type::String),
				Php::ByVal("tag", Php::Type::String),
				Php::ByVal("body", Php::Type::String),
				});

		// add to extension
		extension.add(producerClass);

		Php::Class<MPushConsumer> pushConsumer("MQPushConsumer");
		pushConsumer.method<&MPushConsumer::__construct>("__construct");
		pushConsumer.method<&MPushConsumer::setNamesrvDomain>("setNamesrvDomain", {
				Php::ByVal("nameserver", Php::Type::String),
				});
		pushConsumer.method<&MPushConsumer::setInstanceName>("setInstanceName", {
				Php::ByVal("groupName", Php::Type::String),
				});
		pushConsumer.method<&MPushConsumer::setTopic>("setTopic", {
				Php::ByVal("topic", Php::Type::String),
				});
		pushConsumer.method<&MPushConsumer::start>("start");
		pushConsumer.method<&MPushConsumer::shutdown>("shutdown");
		pushConsumer.method<&MPushConsumer::setCallback>("setCallback", {
				Php::ByVal("callback", Php::Type::Callable),
				});
		extension.add(pushConsumer);

		Php::Class<PullStatus> pullStatusClass("PullStatus");
		pullStatusClass.constant("FOUND", rocketmq::FOUND);
		pullStatusClass.constant("NO_MATCHED_MSG", rocketmq::NO_MATCHED_MSG);
		pullStatusClass.constant("OFFSET_ILLEGAL", rocketmq::OFFSET_ILLEGAL);
		pullStatusClass.constant("BROKER_TIMEOUT", rocketmq::BROKER_TIMEOUT);
		pullStatusClass.constant("NO_NEW_MSG", rocketmq::NO_NEW_MSG);
		extension.add(pullStatusClass);

		Php::Class<PullResult> pullResultClass("PullResult");
		pullResultClass.method<&PullResult::getPullStatus>("getPullStatus");
		pullResultClass.method<&PullResult::getNextBeginOffset>("getNextBeginOffset");
		pullResultClass.method<&PullResult::getMinOffset>("getMinOffset");
		pullResultClass.method<&PullResult::getMaxOffset>("getMaxOffset");
		pullResultClass.method<&PullResult::current>("current");
		pullResultClass.method<&PullResult::rewind>("rewind");
		pullResultClass.method<&PullResult::key>("key");
		pullResultClass.method<&PullResult::next>("next");
		pullResultClass.method<&PullResult::valid>("valid");
		extension.add(pullResultClass);

		Php::Class<MConsumer> consumerClass("MQConsumer");
		consumerClass.method<&MConsumer::__construct>("__construct");
		consumerClass.method<&MConsumer::setInstanceName>("setInstanceName", { Php::ByVal("groupName", Php::Type::String), });
		consumerClass.method<&MConsumer::setNamesrvDomain>("setNamesrvDomain", { Php::ByVal("nameserver", Php::Type::String), });
		consumerClass.method<&MConsumer::setTopic>("setTopic", { Php::ByVal("topic", Php::Type::String), });
		consumerClass.method<&MConsumer::start>("start");
		consumerClass.method<&MConsumer::fetch>("fetch");
		extension.add(consumerClass);

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
		messageClass.method<&Message::getProperty>("getProperty", {
				Php::ByVal("name", Php::Type::String),
				});
		messageClass.method<&Message::getTopic>("getTopic");
		messageClass.method<&Message::getTags>("getTags");
		messageClass.method<&Message::getKeys>("getKeys");
		messageClass.method<&Message::getDelayTimeLevel>("getDelayTimeLevel");
		messageClass.method<&Message::getFlag>("getFlag");
		messageClass.method<&Message::getSysFlag>("getSysFlag");
		messageClass.method<&Message::getBody>("getBody");
		extension.add(messageClass);

		Php::Namespace rocketMQNamespace("RocketMQ");
		rocketMQNamespace.add(pushConsumer);
		rocketMQNamespace.add(consumerClass);
		rocketMQNamespace.add(producerClass);
		rocketMQNamespace.add(messageClass);
		rocketMQNamespace.add(pullStatusClass);
		extension.add(std::move(rocketMQNamespace));

		// return the module entry
		return extension.module();
	}
}

