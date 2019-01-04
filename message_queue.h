#ifndef ROCKETMQ_CLIENT_PHP_MESSAGE_QUEUE_H
#define ROCKETMQ_CLIENT_PHP_MESSAGE_QUEUE_H
#include "common.h"
#include <rocketmq/DefaultMQPullConsumer.h>
#include "message.h"

class MessageQueue : public Php::Base 
{
	private:
		rocketmq::MQMessageQueue queue;
		rocketmq::DefaultMQPullConsumer *consumer;
		int64_t offset;

	public:
		MessageQueue(rocketmq::MQMessageQueue queue);

		Php::Value getMessageQueueOffset();

		void pull (Php::Parameters param);
};


#endif
