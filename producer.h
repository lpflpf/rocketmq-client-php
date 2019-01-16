#ifndef ROCKETMQ_CLIENT_PHP_PRODUCER_H
#define ROCKETMQ_CLIENT_PHP_PRODUCER_H
#include "common.h"
#include <rocketmq/DefaultMQProducer.h>

class Producer : public Php::Base
{
	private:
		rocketmq::DefaultMQProducer *producer;

	public:
		Producer() { }

		virtual ~Producer() { }

		void __construct(Php::Parameters &param);

		void setInstanceName(Php::Parameters &param);
		Php::Value getInstanceName();

		void setNamesrvAddr(Php::Parameters &param);
		Php::Value getNamesrvAddr();
		void setNamesrvDomain(Php::Parameters &param);

//		Php::Value getTopicMessageQueueInfo(Php::Parameters &param);

		Php::Value getMQClientId();

		void setGroupName(Php::Parameters &param);
		Php::Value getGroupName();

//		void setTcpTransportPullThreadNum(Php::Parameters &param);

		void start();


		void push(Php::Parameters &params);


  		void setSessionCredentials(Php::Parameters &param);
		Php::Value getSessionCredentials();

		virtual void __destruct(){
			if (this->producer != nullptr){
				producer->shutdown();
				delete(this->producer);
			}
		}
};

void registerProducer(Php::Namespace &rocketMQNamespace);

#endif
