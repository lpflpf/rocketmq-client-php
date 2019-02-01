#include "send_result.h"

SendResult::SendResult(rocketmq::SendResult& sendResult){
    this->sendResult = sendResult;
}
Php::Value SendResult::getMsgId(){
    return this->sendResult.getMsgId();
}
Php::Value SendResult::getOffsetMsgId(){
    return this->sendResult.getOffsetMsgId();
}
Php::Value SendResult::getSendStatus(){
    return (int64_t)this->sendResult.getSendStatus();
}

Php::Value SendResult::getMessageQueue(){
    rocketmq::MQMessageQueue mq = this->sendResult.getMessageQueue();
    return Php::Object(MESSAGE_QUEUE_CLASS_NAME, new MessageQueue(mq));
}

Php::Value SendResult::getQueueOffset(){
    return (int64_t) this->sendResult.getQueueOffset();
}

void registerSendResult(Php::Namespace &rocketMQNamespace){
    Php::Class<SendResult> sendResultClass("SendResult");

    sendResultClass.method<&SendResult::getMsgId>("getMsgId");
    sendResultClass.method<&SendResult::getOffsetMsgId>("getOffsetMsgId");
    sendResultClass.method<&SendResult::getSendStatus>("getSendStatus");
    sendResultClass.method<&SendResult::getMessageQueue>("getMessageQueue");
    sendResultClass.method<&SendResult::getQueueOffset>("getQueueOffset");

    rocketMQNamespace.add(sendResultClass);
}

