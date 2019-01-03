#include "common.h"
#include <rocketmq/DefaultMQProducer.h>


#ifndef ROCKETMQ_CLIENT_PHP_PRODUCER_H
#define ROCKETMQ_CLIENT_PHP_PRODUCER_H

class MProducer : public Php::Base
{
	private:
		std::string groupName;
		std::string namesrv_domain;
		rocketmq::DefaultMQProducer *producer;

	public:
		MProducer()
		{
		}

		virtual ~MProducer()
		{
		}

		virtual void __construct()
		{
		}

		void setInstanceName(Php::Parameters &param){
			Php::Value groupName = param[0];
			std::string test = groupName;
			this->groupName = test;
		}

		void setNamesrvDomain(Php::Parameters &param){
			Php::Value nameserver = param[0];
			std::string tmp =  nameserver;
			this->namesrv_domain = tmp;
		}

		void start(){
			this->producer = new rocketmq::DefaultMQProducer(this->groupName);
			this->producer->setGroupName(this->groupName);
			this->producer->setInstanceName(this->groupName);
			this->producer->setNamesrvAddr(this->namesrv_domain);
			this->producer->start();
		}

		void push(Php::Parameters &params){
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

		virtual void __destruct()
		{
			producer->shutdown();
			delete(this->producer);
		}
};

#endif
