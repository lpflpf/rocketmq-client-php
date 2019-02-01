#ifndef ROCKETMQ_CLIENT_PHP_MESSAGE_QUEUE_H_
#define ROCKETMQ_CLIENT_PHP_MESSAGE_QUEUE_H_

#include <rocketmq/DefaultMQPullConsumer.h>
#include "common.h"
#include "message.h"
#include "pull_result.h"

#define MESSAGE_QUEUE_CLASS_NAME NAMESPACE_NAME"\\MessageQueue"

class MessageQueue : public Php::Base 
{
    private:
        rocketmq::MQMessageQueue messageQueue;

        virtual ~MessageQueue(){}

    public:
        MessageQueue(const rocketmq::MQMessageQueue& other);
        void __construct(Php::Parameters &params);

        Php::Value getTopic();
        void setTopic(Php::Parameters &param);

        Php::Value getBrokerName();
        void setBrokerName(Php::Parameters &param);

        Php::Value getQueueId() ;
        void setQueueId(Php::Parameters &param);

        rocketmq::MQMessageQueue& getInstance(){
            return this->messageQueue;
        }
};

void registerMessageQueue(Php::Namespace &rocketMQNamespace);

#endif
