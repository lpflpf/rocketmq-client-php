#include "common.h"
#ifndef ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H
#define ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H
#include <rocketmq/DefaultMQPullConsumer.h>
#include "message.h"
void PrintPullResult(rocketmq::PullResult* result) {
	std::cout << result->toString() << std::endl;
	if (result->pullStatus == rocketmq::FOUND) {
		std::cout << result->toString() << std::endl;
		std::vector<rocketmq::MQMessageExt>::iterator it =
			result->msgFoundList.begin();
	}
}


std::map<rocketmq::MQMessageQueue, uint64_t> g_offseTable;
void putMessageQueueOffset(rocketmq::MQMessageQueue mq, uint64_t offset) {
	g_offseTable[mq] = offset;
}
uint64_t getMessageQueueOffset(rocketmq::MQMessageQueue mq) {
	std::map<rocketmq::MQMessageQueue, uint64_t>::iterator it = g_offseTable.find(mq);
	if (it != g_offseTable.end()) {
		return it->second;
	}
	return 0;
}



class MConsumer : public Php::Base 
{
	private:
		std::string groupName;
		std::string namesrv_domain;
		std::string topic;
		rocketmq::DefaultMQPullConsumer *consumer;
		std::vector<rocketmq::MQMessageQueue> mqs;

	public:
		MConsumer(){}
		virtual ~MConsumer(){}
		virtual void __construct(){}

		void start(){
			this->consumer = new rocketmq::DefaultMQPullConsumer(this->groupName);
			this->consumer->setNamesrvAddr(this->namesrv_domain);
			this->consumer->setGroupName(this->groupName);
			this->consumer->setInstanceName(this->groupName);
			this->consumer->start();
		}

		void fetch(){
			bool noNewMsg = false;
			this->consumer->fetchSubscribeMessageQueues(this->topic, this->mqs);
			std::vector<rocketmq::MQMessageQueue>::iterator iter = mqs.begin();
			for (; iter != mqs.end(); ++iter) {
				std::cout << "mq:" << (*iter).toString() << std::endl;
				rocketmq::MQMessageQueue mq = (*iter);
				do {
					try {
						rocketmq::PullResult result = consumer->pull(mq, "*", getMessageQueueOffset(mq), 32);
						std::cout << result.msgFoundList.size() << std::endl; 
						if (result.pullStatus != rocketmq::BROKER_TIMEOUT) {
							putMessageQueueOffset(mq, result.nextBeginOffset);
							PrintPullResult(&result);
						} else {
							std::cout << "broker timeout occur" << std::endl;
						}
						switch (result.pullStatus) {
							case rocketmq::FOUND:
							case rocketmq::NO_MATCHED_MSG:
							case rocketmq::OFFSET_ILLEGAL:
							case rocketmq::BROKER_TIMEOUT:
								break;
							case rocketmq::NO_NEW_MSG:
								noNewMsg = true;
								break;
							default:
								break;
						}

					} catch (rocketmq::MQClientException &e) {
						std::cout << e << std::endl;
					}

				} while (!noNewMsg);

			}
		}

		void setNamesrvDomain(Php::Parameters &param){
			Php::Value nameserver = param[0];
			std::string tmp =  nameserver;
			this->namesrv_domain = tmp;
		}

		void setInstanceName(Php::Parameters &param){
			Php::Value groupName = param[0];
			std::string test = groupName;
			this->groupName = test;
		}

		void setTopic(Php::Parameters &param){
			Php::Value val = param[0];
			std::string topic = val;
			this->topic = topic;
		}
};


#endif
