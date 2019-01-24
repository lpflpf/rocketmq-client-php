#ifndef ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H
#define ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H

#include "common.h"
#include <rocketmq/DefaultMQPullConsumer.h>
#include "message.h"
#include "message_queue.h"


class PullConsumer:public Php::Base
{
    private:
        std::string topicName;
        rocketmq::DefaultMQPullConsumer *consumer;
        std::vector<rocketmq::MQMessageQueue> mqs;
    public:
        PullConsumer(){
            this->consumer = nullptr;
        }
        virtual ~PullConsumer(){
            if (nullptr != this->consumer){
                delete(this->consumer);
            }
        }
        virtual void __construct(Php::Parameters &params);

        void start();

        Php::Value getQueues();

        void setNamesrvDomain(Php::Parameters &param);

        void setNamesrvAddr(Php::Parameters &param);

        void setInstanceName(Php::Parameters &param);

        void setTopic(Php::Parameters &param);

        void setGroup(Php::Parameters &param);
        Php::Value pull(Php::Parameters &param);
        Php::Value pullBlockIfNotFound(Php::Parameters &param);
};

void registerPullConsumer(Php::Namespace &rocketMQNamespace);

#endif
