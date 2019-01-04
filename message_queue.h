#ifndef ROCKETMQ_CLIENT_PHP_MESSAGE_QUEUE_H
#define ROCKETMQ_CLIENT_PHP_MESSAGE_QUEUE_H

#include <rocketmq/DefaultMQPullConsumer.h>
#include "common.h"
#include "message.h"
#include "pull_result.h"

#define MESSAGE_QUEUE_CLASS_NAME NAMESPACE_NAME"\\MessageQueue"

class MessageQueue : public Php::Base 
{
	private:
		virtual ~MessageQueue(){}
		rocketmq::MQMessageQueue queue;
		rocketmq::DefaultMQPullConsumer *consumer;
		int64_t offset;

	public:
		MessageQueue(rocketmq::MQMessageQueue queue, rocketmq::DefaultMQPullConsumer *consumer);

		// @return int offset
		Php::Value getMessageQueueOffset();
		void setMessageQueueOffset(Php::Parameters &param);

		// @return RocketMQ\\PullResult
		Php::Value pull(Php::Parameters &param);
};

void registerMessageQueue(Php::Namespace &rocketMQNamespace);

#endif
