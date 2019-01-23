#include "push_consumer.h"
#include "msg_listener.h"

void PushConsumer::doRebalance(){
	this->consumer->doRebalance();
}

void PushConsumer::persistConsumerOffset(){
	this->consumer->persistConsumerOffset();
}
void PushConsumer::persistConsumerOffsetByResetOffset(){
	this->consumer->persistConsumerOffsetByResetOffset();
}

void PushConsumer::setNamesrvDomain(Php::Parameters &param){
	std::string nameserver =  param[0];
	this->consumer->setNamesrvDomain(nameserver);
}

void PushConsumer::setNamesrvAddr(Php::Parameters &param){
	std::string namesrvAddr = param[0];
	this->consumer->setNamesrvAddr(namesrvAddr);
}


void PushConsumer::setInstanceName(Php::Parameters &param){
	std::string groupName= param[0];
	this->consumer->setInstanceName(this->groupName);
}  

void PushConsumer::setTryLockTimeout(Php::Parameters &param){
	this->consumer->setTcpTransportTryLockTimeout((int64_t)param[0]);
}

void PushConsumer::setConnectTimeout(Php::Parameters &param){
	this->consumer->setTcpTransportConnectTimeout((int64_t)param[0]);
}

void PushConsumer::setThreadCount(Php::Parameters &param){
	this->consumer->setConsumeThreadCount((int64_t)param[0]);
}

Php::Value PushConsumer::getConsumeType(){
	return (int) this->consumer->getConsumeType();
}

Php::Value PushConsumer::getConsumeFromWhere(){
	return (int) this->consumer->getConsumeFromWhere();
}

void PushConsumer::setConsumeFromWhere(Php::Parameters &param){
	int consumeFromWhere = (int) param[0];
	this->consumer->setConsumeFromWhere(rocketmq::ConsumeFromWhere(consumeFromWhere));
}

void PushConsumer::setListenerType(Php::Parameters &param){
	this->msgListenerType = param[0];
}

void PushConsumer::subscribe(Php::Parameters &param){
	std::string topic = param[0];
	std::string tag = param[1];
	this->consumer->subscribe(topic, tag);
}
void PushConsumer::setCallback(Php::Parameters &param){
	if (!param[0].isCallable())
		throw Php::Exception("Not a callable type.");
	this->callback = param[0];
}

void PushConsumer::setMaxRequestTime(Php::Parameters &param){
	this->maxRequestTime = (int)param[0];
}

void PushConsumer::start(){
	MsgListenerOrderly* msgListenerOrderly;
	MsgListenerConcurrently* msgListenerConcurrently;
	MsgListener* msgListener;
	switch(this->msgListenerType){
		case rocketmq::messageListenerOrderly:
			msgListenerOrderly = new MsgListenerOrderly();
			msgListenerOrderly->setCallback(this->callback);
			this->consumer->registerMessageListener(msgListenerOrderly);
			break;
		case rocketmq::messageListenerConcurrently:
			msgListenerConcurrently = new MsgListenerConcurrently();
			msgListenerConcurrently->setCallback(this->callback);
			this->consumer->registerMessageListener(msgListenerConcurrently);
			break;
		default :
			msgListener = new MsgListener();
			msgListener->setCallback(this->callback);
			this->consumer->registerMessageListener(msgListener);
			break;
	}

	try {
		this->consumer->start();
	} catch (rocketmq::MQClientException &e) {
		std::cout << e << std::endl;
	}
	sleep(this->maxRequestTime);
}
void PushConsumer::shutdown(){
	this->consumer->shutdown();
}

void PushConsumer::__construct(Php::Parameters &params){
	std::string groupName = params[0];
	this->consumer = new rocketmq::DefaultMQPushConsumer(groupName);
}

void registerPushConsumer(Php::Namespace &rocketMQNamespace){
		Php::Class<PushConsumer> pushConsumer("PushConsumer");
		pushConsumer.method<&PushConsumer::doRebalance>("doRebalance");
		pushConsumer.method<&PushConsumer::persistConsumerOffset>("persistConsumerOffset");
		pushConsumer.method<&PushConsumer::persistConsumerOffsetByResetOffset>("persistConsumerOffsetByResetOffset");
		pushConsumer.method<&PushConsumer::__construct>("__construct", 				{ Php::ByVal("groupName", Php::Type::String), });
		pushConsumer.method<&PushConsumer::setNamesrvDomain>("setNamesrvDomain", 	{ Php::ByVal("nameserver", Php::Type::String), });
		pushConsumer.method<&PushConsumer::setNamesrvAddr>("setNamesrvAddr",     	{ Php::ByVal("namesrvAddr", Php::Type::String), });
		pushConsumer.method<&PushConsumer::setInstanceName>("setInstanceName", 		{ Php::ByVal("groupName", Php::Type::String), });
		pushConsumer.method<&PushConsumer::setTryLockTimeout>("setTryLockTimeout", 	{Php::ByVal("tryLockTimeout", Php::Type::Numeric),});
		pushConsumer.method<&PushConsumer::setConnectTimeout>("setConnectTimeout", 	{Php::ByVal("connectTimeout", Php::Type::Numeric),});
		pushConsumer.method<&PushConsumer::setThreadCount>("setThreadCount", 		{Php::ByVal("threadCount", Php::Type::Numeric),});
		pushConsumer.method<&PushConsumer::setListenerType>("setListenerType", 		{Php::ByVal("listenerType", Php::Type::Numeric), });
		pushConsumer.method<&PushConsumer::getConsumeType>("getConsumeType");
		pushConsumer.method<&PushConsumer::getConsumeFromWhere>("getConsumeFromWhere");
		pushConsumer.method<&PushConsumer::setConsumeFromWhere>("setConsumeFromWhere", { Php::ByVal("consumeFromWhere", Php::Type::Numeric), });
		pushConsumer.method<&PushConsumer::subscribe>("subscribe", { Php::ByVal("topic", Php::Type::String), Php::ByVal("tag", Php::Type::String), });
		pushConsumer.method<&PushConsumer::start>("start");
		pushConsumer.method<&PushConsumer::shutdown>("shutdown");
		pushConsumer.method<&PushConsumer::setMaxRequestTime>("setMaxRequestTime", {
				Php::ByVal("maxRequestTime", Php::Type::Numeric),
				});
		pushConsumer.method<&PushConsumer::setCallback>("setCallback", { Php::ByVal("callback", Php::Type::Callable), });
		rocketMQNamespace.add(pushConsumer);
}


