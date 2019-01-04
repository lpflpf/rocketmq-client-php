#include "common.h"
#include "producer.h"
#include "push_consumer.h"
#include "pull_consumer.h"
#include "message.h"
#include "pull_status.h"
#include "pull_result.h"
#include "message_queue.h"

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


		// class PushConsumer
		Php::Class<PushConsumer> pushConsumer("PushConsumer");
		pushConsumer.method<&PushConsumer::__construct>("__construct");
		pushConsumer.method<&PushConsumer::setNamesrvDomain>("setNamesrvDomain", { Php::ByVal("nameserver", Php::Type::String), });
		pushConsumer.method<&PushConsumer::setInstanceName>("setInstanceName", { Php::ByVal("groupName", Php::Type::String), });
		pushConsumer.method<&PushConsumer::setTopic>("setTopic", { Php::ByVal("topic", Php::Type::String), });
		pushConsumer.method<&PushConsumer::start>("start");
		pushConsumer.method<&PushConsumer::shutdown>("shutdown");
		pushConsumer.method<&PushConsumer::setCallback>("setCallback", { Php::ByVal("callback", Php::Type::Callable), });


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

		rocketMQNamespace.add(pushConsumer);
		rocketMQNamespace.add(consumerClass);

		// create extension
		static Php::Extension extension("rocketmq", "1.0");
		extension.add(std::move(rocketMQNamespace));

		// return the module entry
		return extension.module();
	}
}

