#ifndef ROCKETMQ_CLIENT_PHP_CONSUME_TYPE_H_
#define ROCKETMQ_CLIENT_PHP_CONSUME_TYPE_H_

#include "common.h"


class ConsumeType : public Php::Base
{
    // CONSUME_ACTIVELY,
    // CONSUME_PASSIVELY,
};


class ConsumeFromWhere : public Php::Base {
    /**
     *new consumer will consume from end offset of queue, 
     * and then consume from last consumed offset of queue follow-up 
     */
    //CONSUME_FROM_LAST_OFFSET,

    // @Deprecated
    //CONSUME_FROM_LAST_OFFSET_AND_FROM_MIN_WHEN_BOOT_FIRST,
    // @Deprecated
    //CONSUME_FROM_MIN_OFFSET,
    // @Deprecated
    //CONSUME_FROM_MAX_OFFSET,
    /**
     *new consumer will consume from first offset of queue, 
     * and then consume from last consumed offset of queue follow-up 
     */
    //CONSUME_FROM_FIRST_OFFSET,
    /**
     *new consumer will consume from the queue offset specified by timestamp, 
     * and then consume from last consumed offset of queue follow-up 
     */
    //CONSUME_FROM_TIMESTAMP,

};

class MessageModel : public Php::Base
{
    //  BROADCASTING,
    //	CLUSTERING,
};


void registerConsumeType(Php::Namespace &rocketMQNamespace)
{
    // class ConsumeType
    Php::Class<ConsumeType> consumeTypeClass("ConsumeType");
    consumeTypeClass.constant("CONSUME_ACTIVELY", rocketmq::CONSUME_ACTIVELY);
    consumeTypeClass.constant("CONSUME_PASSIVELY", rocketmq::CONSUME_PASSIVELY);
    rocketMQNamespace.add(consumeTypeClass);

    // class ConsumeFromWhere
    Php::Class<ConsumeFromWhere> consumeFromWhereClass("ConsumeFromWhere");
    consumeFromWhereClass.constant("CONSUME_FROM_LAST_OFFSET", rocketmq::CONSUME_FROM_LAST_OFFSET);
    consumeFromWhereClass.constant("CONSUME_FROM_LAST_OFFSET_AND_FROM_MIN_WHEN_BOOT_FIRST", rocketmq::CONSUME_FROM_LAST_OFFSET_AND_FROM_MIN_WHEN_BOOT_FIRST);
    consumeFromWhereClass.constant("CONSUME_FROM_MIN_OFFSET", rocketmq::CONSUME_FROM_MIN_OFFSET);
    consumeFromWhereClass.constant("CONSUME_FROM_MAX_OFFSET", rocketmq::CONSUME_FROM_MAX_OFFSET);
    consumeFromWhereClass.constant("CONSUME_FROM_FIRST_OFFSET", rocketmq::CONSUME_FROM_FIRST_OFFSET);
    consumeFromWhereClass.constant("CONSUME_FROM_TIMESTAMP", rocketmq::CONSUME_FROM_TIMESTAMP);
    rocketMQNamespace.add(consumeFromWhereClass);

    // class MessageModel
    Php::Class<MessageModel> messageModelClass("MessageModel");
    messageModelClass.constant("BROADCASTING", rocketmq::BROADCASTING);
    messageModelClass.constant("CLUSTERING", rocketmq::CLUSTERING);
    rocketMQNamespace.add(messageModelClass);
}

#endif

