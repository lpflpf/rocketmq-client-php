#ifndef ROCKETMQ_CLIENT_PHP_CONSUME_STATUS_H_
#define ROCKETMQ_CLIENT_PHP_CONSUME_STATUS_H_

#include "common.h"

class ConsumeStatus: public Php::Base
{
    //consume success, msg will be cleard from memory
    // CONSUME_SUCCESS
    //consume fail, but will be re-consume by call messageLisenter again
    // RECONSUME_LATER
};

void registerConsumeStatus(Php::Namespace &rocketMQNamespace){
    Php::Class<ConsumeStatus> consumeStatusClass("ConsumeStatus");
    consumeStatusClass.constant("CONSUME_SUCCESS", (int) rocketmq::CONSUME_SUCCESS);
    consumeStatusClass.constant("RECONSUME_LATER", (int) rocketmq::RECONSUME_LATER);
    rocketMQNamespace.add(consumeStatusClass);
}

#endif
