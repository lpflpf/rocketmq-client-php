#include "message_queue.h"

Php::Value MessageQueue::getTopic(){
    return this->messageQueue.getTopic();
}

void MessageQueue::setTopic(Php::Parameters &param){
    std::string topic = param[0];
    this->messageQueue.setTopic(topic);
}

Php::Value MessageQueue::getBrokerName(){
    return this->messageQueue.getBrokerName();
}
void MessageQueue::setBrokerName(Php::Parameters &param){
    std::string brokerName = param[0];
    this->messageQueue.setBrokerName(brokerName);
}

Php::Value MessageQueue::getQueueId() {
    return this->messageQueue.getQueueId();
}
void MessageQueue::setQueueId(Php::Parameters &param){
    return this->messageQueue.setQueueId(param[0]);
}

void registerMessageQueue(Php::Namespace &rocketMQNamespace){
    Php::Class<MessageQueue> messageQueueClass("MessageQueue");
    messageQueueClass.method<&MessageQueue::getTopic>("getTopic");
    messageQueueClass.method<&MessageQueue::setTopic>("setTopic", { Php::ByVal("topic", Php::Type::String), });

    messageQueueClass.method<&MessageQueue::getBrokerName>("getBrokerName");
    messageQueueClass.method<&MessageQueue::setBrokerName>("setBrokerName", { Php::ByVal("brokerName", Php::Type::String), });

    messageQueueClass.method<&MessageQueue::getQueueId>("getQueueId");
    messageQueueClass.method<&MessageQueue::setQueueId>("setQueueId", { Php::ByVal("queueId", Php::Type::String), });

    messageQueueClass.method<&MessageQueue::__construct>("__construct", {
            Php::ByVal("topic", Php::Type::String),
            Php::ByVal("brokerName", Php::Type::String),
            Php::ByVal("queueId", Php::Type::Numeric),
            });

    rocketMQNamespace.add(messageQueueClass);
}
