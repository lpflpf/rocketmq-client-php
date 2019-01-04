#include "producer.h"

void Producer::setInstanceName(Php::Parameters &param){
	Php::Value groupName = param[0];
	std::string test = groupName;
	this->groupName = test;
}

void Producer::setNamesrvDomain(Php::Parameters &param){
	Php::Value nameserver = param[0];
	std::string tmp =  nameserver;
	this->namesrv_domain = tmp;
}

void Producer::start(){
	this->producer = new rocketmq::DefaultMQProducer(this->groupName);
	this->producer->setGroupName(this->groupName);
	this->producer->setInstanceName(this->groupName);
	this->producer->setNamesrvAddr(this->namesrv_domain);
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
