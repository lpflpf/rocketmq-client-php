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
		result[idx++] = Php::Object(MESSAGE_QUEUE_CLASS_NAME , new MessageQueue(mq)); 
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

// pull( MessageQueue mq, string subExpression, int offset, int maxNums)
Php::Value PullConsumer::pull(Php::Parameters &param){
	Php::Value mq = param[0];
	std::string subExpression = param[1];
	int64_t offset = param[2];
	int64_t maxNums = param[3];
	MessageQueue* messageQueue = (MessageQueue*)mq.implementation();
	rocketmq::PullResult result = this->consumer->pull(messageQueue->getInstance(), subExpression, offset, maxNums);
	PullResult *pullResult = new PullResult(result);
	Php::Value pv(Php::Object(PULL_RESULT_CLASS_NAME, pullResult));
	return pv;
}

/*
void PullConsumer::persistConsumerOffset(){
	this->consumer->persistConsumerOffset();
}

void PullConsumer::persistConsumerOffsetByResetOffset(){
	this->consumer->persistConsumerOffsetByResetOffset();
}
*/

Php::Value PullConsumer::pullBlockIfNotFound(Php::Parameters &param){
	Php::Value mq = param[0];
	std::string subExpression = param[1];
	int64_t offset = param[2];
	int64_t maxNums = param[3];
	MessageQueue* messageQueue = (MessageQueue*)mq.implementation();
	rocketmq::PullResult result = this->consumer->pullBlockIfNotFound(messageQueue->getInstance(), subExpression, offset, maxNums);
	PullResult *pullResult = new PullResult(result);
	Php::Value pv(Php::Object(PULL_RESULT_CLASS_NAME, pullResult));
	return pv;
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
		pullConsumer.method<&PullConsumer::pull>("pull", {
            	Php::ByVal("mq", MESSAGE_QUEUE_CLASS_NAME),
				Php::ByVal("subExpression", Php::Type::String),
				Php::ByVal("offset", Php::Type::Numeric),
				Php::ByVal("maxNums", Php::Type::Numeric),
				});
		pullConsumer.method<&PullConsumer::pullBlockIfNotFound>("pullBlockIfNotFound", {
            	Php::ByVal("mq", MESSAGE_QUEUE_CLASS_NAME),
				Php::ByVal("subExpression", Php::Type::String),
				Php::ByVal("offset", Php::Type::Numeric),
				Php::ByVal("maxNums", Php::Type::Numeric),
				});
		rocketMQNamespace.add(pullConsumer);
}
