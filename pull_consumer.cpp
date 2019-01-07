#include "pull_consumer.h"

void PullConsumer::start(){
	this->consumer = new rocketmq::DefaultMQPullConsumer(this->groupName);
	this->consumer->setNamesrvAddr(this->namesrv_domain);
	this->consumer->setGroupName(this->groupName);
	this->consumer->setInstanceName(this->groupName);
	this->consumer->start();
}

Php::Value PullConsumer::getQueues(){
	this->consumer->fetchSubscribeMessageQueues(this->topic, this->mqs);
	Php::Value result;
	int idx = 0;

	std::vector<rocketmq::MQMessageQueue>::iterator iter = mqs.begin();
	for (; iter != mqs.end(); ++iter) {
		rocketmq::MQMessageQueue mq = (*iter);
		result[idx++] = Php::Object(MESSAGE_QUEUE_CLASS_NAME , new MessageQueue(mq, this->consumer)); 
	}
	return result;
}

void PullConsumer::setNamesrvDomain(Php::Parameters &param){
	std::string namesrv_domain = param[0];
	this->namesrv_domain = namesrv_domain;
}

void PullConsumer::setInstanceName(Php::Parameters &param){
	std::string groupName = param[0];
	this->groupName = groupName;
}

void PullConsumer::setTopic(Php::Parameters &param){
	std::string topic = param[0];
	this->topic = topic;
}


void registerPullConsumer(Php::Namespace &rocketMQNamespace){
		Php::Class<PullConsumer> pullConsumer("PullConsumer");
		pullConsumer.method<&PullConsumer::__construct>("__construct");
		pullConsumer.method<&PullConsumer::setInstanceName>("setInstanceName", { Php::ByVal("groupName", Php::Type::String), });
		pullConsumer.method<&PullConsumer::setNamesrvDomain>("setNamesrvDomain", { Php::ByVal("nameserver", Php::Type::String), });
		pullConsumer.method<&PullConsumer::setTopic>("setTopic", { Php::ByVal("topic", Php::Type::String), });
		pullConsumer.method<&PullConsumer::start>("start");
		pullConsumer.method<&PullConsumer::getQueues>("getQueues");
		rocketMQNamespace.add(pullConsumer);
}
