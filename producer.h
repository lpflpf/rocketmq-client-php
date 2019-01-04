#ifndef ROCKETMQ_CLIENT_PHP_PRODUCER_H
#define ROCKETMQ_CLIENT_PHP_PRODUCER_H
#include "common.h"
#include <rocketmq/DefaultMQProducer.h>

class Producer : public Php::Base
{
	private:
		std::string groupName;
		std::string namesrv_domain;
		rocketmq::DefaultMQProducer *producer;

	public:
		Producer() { }

		virtual ~Producer() { }

		virtual void __construct() { }

		void setInstanceName(Php::Parameters &param);

		void setNamesrvDomain(Php::Parameters &param);

		void start();

		void push(Php::Parameters &params);

		virtual void __destruct(){
			producer->shutdown();
			delete(this->producer);
		}
};

#endif
