#ifndef ROCKETMQ_CLIENT_PHP_SEND_RESULT_H_
#define ROCKETMQ_CLIENT_PHP_SEND_RESULT_H_

#include "common.h"
#include "message_queue.h"
#include <rocketmq/SendResult.h>

#define SEND_RESULT_CLASS_NAME NAMESPACE_NAME"\\SendResult"

class SendResult: public Php::Base
{
    private:
        rocketmq::SendResult sendResult;

    public:
        SendResult(rocketmq::SendResult& sendResult);

        Php::Value getMsgId();

        Php::Value getOffsetMsgId();

        Php::Value getSendStatus();

        Php::Value getMessageQueue();

        Php::Value getQueueOffset();
};

void registerSendResult(Php::Namespace &rocketMQNamespace);

#endif

