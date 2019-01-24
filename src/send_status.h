#ifndef ROCKETMQ_CLIENT_PHP_SEND_STATUS_H
#define ROCKETMQ_CLIENT_PHP_SEND_STATUS_H

#include "common.h"
#include <rocketmq/SendResult.h>

class SendStatus : public Php::Base
{
    //SEND_OK,
    //SEND_FLUSH_DISK_TIMEOUT,
    //SEND_FLUSH_SLAVE_TIMEOUT,
    //SEND_SLAVE_NOT_AVAILABLE
};

void registerSendStatus(Php::Namespace &rocketMQNamespace)
{
    Php::Class<SendStatus> sendStatusClass("SendStatus");
    sendStatusClass.constant("SEND_OK", rocketmq::SEND_OK);
    sendStatusClass.constant("SEND_FLUSH_DISK_TIMEOUT", rocketmq::SEND_FLUSH_DISK_TIMEOUT);
    sendStatusClass.constant("SEND_FLUSH_SLAVE_TIMEOUT", rocketmq::SEND_FLUSH_SLAVE_TIMEOUT);
    sendStatusClass.constant("SEND_SLAVE_NOT_AVAILABLE", rocketmq::SEND_SLAVE_NOT_AVAILABLE);
    rocketMQNamespace.add(sendStatusClass);
}

#endif
