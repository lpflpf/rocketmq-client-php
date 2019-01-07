#include "common.h"
#include "producer.h"
#include "push_consumer.h"
#include "pull_consumer.h"
#include "message.h"
#include "pull_status.h"
#include "pull_result.h"
#include "message_queue.h"
#include "consume_type.h"

// symbols are exported according to the "C" language
extern "C"
{
	// export the "get_module" function that will be called by the Zend engine
	PHPCPP_EXPORT void *get_module() 
	{ 

		// all class in RocketMQ namespace.
		Php::Namespace rocketMQNamespace(NAMESPACE_NAME);

		// class Producer
		registerProducer(rocketMQNamespace);

		// class PullStatus
		registerPullStatus(rocketMQNamespace);

		// class ConsumeType, ConsumeFromWhere, MessageModel
		registerConsumeType(rocketMQNamespace);


		// class PushConsumer
		registerPushConsumer(rocketMQNamespace);

		// class PullResult
		registerPullResult(rocketMQNamespace);

		// class PullConsumer 
		Php::Class<PullConsumer> consumerClass("PullConsumer");
		consumerClass.method<&PullConsumer::__construct>("__construct");
		consumerClass.method<&PullConsumer::setInstanceName>("setInstanceName", { Php::ByVal("groupName", Php::Type::String), });
		consumerClass.method<&PullConsumer::setNamesrvDomain>("setNamesrvDomain", { Php::ByVal("nameserver", Php::Type::String), });
		consumerClass.method<&PullConsumer::setTopic>("setTopic", { Php::ByVal("topic", Php::Type::String), });
		consumerClass.method<&PullConsumer::start>("start");
		consumerClass.method<&PullConsumer::getQueues>("getQueues");


		// class MessageQueue
//		Php::Class<MessageQueue> messageQueueClass("MessageQueue");
//		messageQueueClass.method<&MessageQueue::getMessageQueueOffset>("getMessageQueueOffset");
//		messageQueueClass.method<&MessageQueue::pull>("pull", { Php::ByVal("tag", Php::Type::String), });
//		rocketMQNamespace.add(messageQueueClass);

		registerMessageQueue(rocketMQNamespace);

		// class Message 
		registerMessage(rocketMQNamespace);

		rocketMQNamespace.add(consumerClass);

		// create extension
		static Php::Extension extension("rocketmq", "1.0");
		extension.add(std::move(rocketMQNamespace));

		// return the module entry
		return extension.module();
	}
}

