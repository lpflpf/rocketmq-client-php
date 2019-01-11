#include "pull_consumer.h"

void PullConsumer::__construct(Php::Parameters &params){
	std::string groupName = params[0];
	this->consumer = new rocketmq::DefaultMQPullConsumer(groupName);
}

void PullConsumer::setGroup(Php::Parameters &params){
	std::string groupName = params[0];
	this->consumer->setGroupName(groupName);
}

void PullConsumer::start(){
	this->consumer->start();
}

Php::Value PullConsumer::getQueues(){
	Php::Array result;
	int idx = 0;
	this->consumer->fetchSubscribeMessageQueues(this->topicName, this->mqs);
	std::cout << this->mqs.size() << std::endl;
	std::vector<rocketmq::MQMessageQueue>::iterator iter = mqs.begin();
	for (; iter != mqs.end(); ++iter) {
		rocketmq::MQMessageQueue mq = (*iter);
		result[idx++] = Php::Object(MESSAGE_QUEUE_CLASS_NAME , new MessageQueue(mq, this->consumer)); 
	}
	return result;
}

void PullConsumer::setNamesrvDomain(Php::Parameters &param){
	std::string namesrv_domain = param[0];
	this->consumer->setNamesrvDomain(namesrv_domain);
}

void PullConsumer::setNamesrvAddr(Php::Parameters &param){
	std::string namesrv_addr = param[0];
	this->consumer->setNamesrvAddr(namesrv_addr);
}

void PullConsumer::setInstanceName(Php::Parameters &param){
	std::string instanceName = param[0];
	this->consumer->setInstanceName(instanceName);
}

void PullConsumer::setTopic(Php::Parameters &param){
	std::string topic = param[0];
	this->topicName= topic;
}


void registerPullConsumer(Php::Namespace &rocketMQNamespace){
		Php::Class<PullConsumer> pullConsumer("PullConsumer");
		pullConsumer.method<&PullConsumer::__construct>("__construct", { Php::ByVal("groupName", Php::Type::String), });
		pullConsumer.method<&PullConsumer::setInstanceName>("setInstanceName", { Php::ByVal("groupName", Php::Type::String), });
		pullConsumer.method<&PullConsumer::setNamesrvDomain>("setNamesrvDomain", { Php::ByVal("nameserver", Php::Type::String), });
		pullConsumer.method<&PullConsumer::setTopic>("setTopic", { Php::ByVal("topic", Php::Type::String), });
		pullConsumer.method<&PullConsumer::start>("start");
		pullConsumer.method<&PullConsumer::getQueues>("getQueues");
		pullConsumer.method<&PullConsumer::setNamesrvAddr>("setNamesrvAddr", { Php::ByVal("namesrvAddr", Php::Type::String), });
		pullConsumer.method<&PullConsumer::setGroup>("setGroup", { Php::ByVal("group", Php::Type::String), });
		rocketMQNamespace.add(pullConsumer);
}
