#include "message_queue.h"

MessageQueue::MessageQueue(rocketmq::MQMessageQueue queue, rocketmq::DefaultMQPullConsumer *consumer){
	this->queue = queue;
	this->consumer = consumer;
	this->offset = 0;
}
Php::Value MessageQueue::getMessageQueueOffset(){
	return this->offset;
}
void MessageQueue::setMessageQueueOffset(Php::Parameters &param){
	int64_t off = Php::Value(param[0]);
	this->offset = off;
}

Php::Value MessageQueue::pull(Php::Parameters &param){
	std::string tag  = Php::Value(param[0]);
	rocketmq::PullResult result = this->consumer->pull(this->queue, tag, this->offset, 32);

	PullResult *pullResult = new PullResult(result);
//	std::vector<rocketmq::MQMessageExt>::iterator it =
//		result.msgFoundList.begin();
//	for (; it != result.msgFoundList.end(); ++it) {
//		std::cout << "=======================================================" << std::endl
//			<< (*it).toString() << std::endl;
//	}
	Php::Value pv(Php::Object(PULL_RESULT_CLASS_NAME, pullResult));
	return pv;
}


void registerMessageQueue(Php::Namespace &rocketMQNamespace){
	Php::Class<MessageQueue> messageQueueClass("MessageQueue");

	messageQueueClass.method<&MessageQueue::getMessageQueueOffset>("getMessageQueueOffset");
	messageQueueClass.method<&MessageQueue::setMessageQueueOffset>("setMessageQueueOffset");
	messageQueueClass.method<&MessageQueue::pull>("pull", { Php::ByVal("tag", Php::Type::String), });

	rocketMQNamespace.add(messageQueueClass);
}
