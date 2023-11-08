<?php
namespace RocketMQ;
function printMessageExt($msg){
    echo "-----------------\n";
    echo "  topic: " . $msg->getMessageTopic() . "\n";
    echo "  tags: " . $msg->getMessageTags() . "\n";
    echo "  keys: " . $msg->getMessageKeys() . "\n";
    echo "  body: " . $msg->getMessageBody() . "\n";
    echo "  msgId: " . $msg->getMessageId() . "\n";
    echo "  timelevel: " . $msg->getMessageDelayTimeLevel() . "\n";
    echo "  queueId: " . $msg->getMessageQueueId() . "\n";
    echo "  resconsumeTimes: " . $msg->getMessageReconsumeTimes() . "\n";
    echo "  getMessageStoreSize: " . $msg->getMessageBornTimestamp() . "\n";
    echo "  getMessageBornTimestamp: " . $msg->getMessageBornTimestamp() . "\n";
    echo "  getMessageStoreTimestamp: " . $msg->getMessageStoreTimestamp() . "\n";
    echo "  getMessageQueueOffset: " . $msg->getMessageQueueOffset() . "\n";
    echo "  getMessageCommitLogOffset: " . $msg->getMessageCommitLogOffset() . "\n";
    echo "  getMessagePreparedTransactionOffset: " . $msg->getMessagePreparedTransactionOffset() . "\n";
}