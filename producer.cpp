#include "producer.h"
#include "message_queue.h"
#include "session_credentials.h"

void Producer::__construct(Php::Parameters &param){
	std::string groupName = param[0];
	this->producer = new rocketmq::DefaultMQProducer(groupName);
}

void Producer::setInstanceName(Php::Parameters &param){
	std::string instanceName = param[0];
	this->producer->setInstanceName(instanceName);
}

Php::Value Producer::getInstanceName(){
	return this->producer->getInstanceName();
}


void Producer::setGroupName(Php::Parameters &param){
	std::string groupName = param[0];
	this->producer->setGroupName(groupName);
}

Php::Value Producer::getGroupName(){
	return this->producer->getGroupName();
}

void Producer::setNamesrvAddr(Php::Parameters &param){
	std::string nameserver =  param[0];
	this->producer->setNamesrvAddr(nameserver);
}

void Producer::start(){
	this->producer->start();
}

void Producer::push(Php::Parameters &params){
	std::string topic = params[0];
	std::string tag = params[1];
	std::string body = params[2];

	rocketmq::MQMessage msg(topic, tag, body);
	try {
		this->producer->send(msg);
	}catch (rocketmq::MQException& e){
		std::cout <<e << std::endl;
	}
}

Php::Value Producer::getMQClientId(){
	return this->producer->getMQClientId();
}

Php::Value Producer::getNamesrvAddr(){
	return this->producer->getNamesrvAddr();
}

//Php::Value Producer::getTopicMessageQueueInfo(Php::Parameters &params){
//	std::string topic = params[0];
//	Php::Array result;
//
//	std::vector<rocketmq::MQMessageQueue> mqs = this->producer->getTopicMessageQueueInfo(topic);
//	std::vector<rocketmq::MQMessageQueue>::iterator iter = mqs.begin();
//	int idx = 0;
//
//	for (; iter != mqs.end(); ++iter) {
//		rocketmq::MQMessageQueue mq = (*iter);
//		result[idx++] = Php::Object(MESSAGE_QUEUE_CLASS_NAME , new MessageQueue(mq, this->consumer)); 
//	}
//
//	return result;
//}

void Producer::setSessionCredentials(Php::Parameters &param){
	std::string accessKey = param[0];
	std::string secretKey = param[1];
	std::string authChannel = param[2];

	this->producer->setSessionCredentials(accessKey, secretKey, authChannel);
}

Php::Value Producer::getSessionCredentials(){
	rocketmq::SessionCredentials sc = this->producer->getSessionCredentials();
	SessionCredentials *sessionCredentials = new SessionCredentials(&sc);
	Php::Value pv(Php::Object(SESSION_CREDENTIALS_CLASS_NAME , sessionCredentials));
	return pv;
}

void Producer::setNamesrvDomain(Php::Parameters &param){
	std::string domain = param[0];
	return this->producer->setNamesrvDomain(domain);
}

// int getRetryTimes() const;
Php::Value Producer::getRetryTimes(){
	return this->producer->getRetryTimes();
}

// void setRetryTimes(int times);
void Producer::setRetryTimes(Php::Parameters &param){
	this->producer->setRetryTimes(param[0]);
}

void registerProducer(Php::Namespace &rocketMQNamespace){
	Php::Class<Producer> producerClass("Producer");
	producerClass.method<&Producer::getMQClientId>("getMQClientId");
	producerClass.method<&Producer::__construct>("__construct", { 
			Php::ByVal("groupName", Php::Type::String), 
			});

	producerClass.method<&Producer::getInstanceName>("getInstanceName");
	producerClass.method<&Producer::setInstanceName>("setInstanceName", { 
			Php::ByVal("groupName", Php::Type::String), 
			});

	producerClass.method<&Producer::getNamesrvAddr>("getNamesrvAddr");
	producerClass.method<&Producer::setNamesrvAddr>("setNamesrvAddr", { 
			Php::ByVal("nameserver", Php::Type::String), 
			});
	producerClass.method<&Producer::setNamesrvDomain>("setNamesrvDomain", {
			Php::ByVal("domain", Php::Type::String),
			});

	producerClass.method<&Producer::getGroupName>("getGroupName");
	producerClass.method<&Producer::setGroupName>("setGroupName", {
			Php::ByVal("groupName", Php::Type::String),
			});

	producerClass.method<&Producer::getSessionCredentials>("getSessionCredentials");
	producerClass.method<&Producer::setSessionCredentials>("setSessionCredentials", {
			Php::ByVal("accessKey", Php::Type::String),
			Php::ByVal("secretKey", Php::Type::String),
			Php::ByVal("authChannel", Php::Type::String),
			});

//	producerClass.method<&Producer::getTopicMessageQueueInfo>("getTopicMessageQueueInfo", {
//			Php::ByVal("topic", Php::Type::String),
//			});

	producerClass.method<&Producer::start>("start");
	producerClass.method<&Producer::push>("push", {
			Php::ByVal("topic", Php::Type::String),
			Php::ByVal("tag", Php::Type::String),
			Php::ByVal("body", Php::Type::String),
			});

	producerClass.method<&Producer::setRetryTimes>("setRetryTimes", { Php::ByVal("retryTimes", Php::Type::Numeric), });
	producerClass.method<&Producer::getRetryTimes>("getRetryTimes");

	rocketMQNamespace.add(producerClass);
}


