#include "message_queue.h"

MessageQueue::MessageQueue(rocketmq::MQMessageQueue queue){
	this->queue = queue;
	offset = 0;
}
Php::Value MessageQueue::getMessageQueueOffset(){
	return offset;
}

void MessageQueue::pull (Php::Parameters param){
	std::string tag  = Php::Value(param[0]);
	rocketmq::PullResult result = consumer->pull(this->queue, tag, this->offset, 32);
}
