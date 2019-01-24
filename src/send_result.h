#ifndef ROCKETMQ_CLIENT_PHP_SEND_RESULT_H
#define ROCKETMQ_CLIENT_PHP_SEND_RESULT_H

#include "common.h"
#include "message_queue.h"
#include <rocketmq/SendResult.h>

#define SEND_RESULT_CLASS_NAME NAMESPACE_NAME"\\SendResult"

class SendResult: public Php::Base
{
    private:
        rocketmq::SendResult sendResult;

    public:
        SendResult(rocketmq::SendResult& sendResult){
            this->sendResult = sendResult;
        }

        Php::Value getMsgId(){
            return this->sendResult.getMsgId();
        }

        Php::Value getOffsetMsgId(){
            return this->sendResult.getOffsetMsgId();
        }

        Php::Value getSendStatus(){
            return (int64_t)this->sendResult.getSendStatus();
        }

        Php::Value getMessageQueue(){
            rocketmq::MQMessageQueue mq = this->sendResult.getMessageQueue();
            return Php::Object(MESSAGE_QUEUE_CLASS_NAME, new MessageQueue(mq));
        }

        Php::Value getQueueOffset(){
            return (int64_t) this->sendResult.getQueueOffset();
        }
};

void registerSendResult(Php::Namespace &rocketMQNamespace);

#endif

