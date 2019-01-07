<?php

namespace RocketMQ;

$consumer = new PushConsumer();
$consumer->setInstanceName("testGroup");
$consumer->subscribe("TopicTest", "*");
$consumer->setNamesrvDomain("127.0.0.1:9876");
$test = "hello";
$consumer->setCallback(function($msg)use($test){
	echo "queueId:" . $msg->getQueueId() . "\n";
	echo "bornTimestamp:" . $msg->getBornTimestamp() . "\n";
	echo "bornHostNameString:" . $msg->getBornHostNameString() . "\n";
	echo "storeTimestamp:" . $msg->getStoreTimestamp() . "\n";
	echo "msgId:" . $msg->getMsgId() . "\n";
	echo "offsetMsgId:" . $msg->getOffsetMsgId() . "\n";
	echo "bodyCRC:" . $msg->getBodyCRC() . "\n";
	echo "queueOffset:" . $msg->getQueueOffset() . "\n";
	echo "commitLogOffset:" . $msg->getCommitLogOffset() . "\n";
	echo "storeSize:" . $msg->getStoreSize() . "\n";
	echo "reconsumeTimes:" . $msg->getReconsumeTimes() . "\n";
	echo "preparedTransactionOffset:" . $msg->getPreparedTransactionOffset() . "\n";
	echo "topic:" . $msg->getTopic() . "\n";
	echo "tags:" . $msg->getTags() . "\n";
	echo "keys:" . $msg->getKeys() . "\n";
	echo "getDelayTimeLevel:" . $msg->getDelayTimeLevel() . "\n";
	echo "flag:" . $msg->getFlag() . "\n";
	echo "sysFlag:" . $msg->getSysFlag() . "\n";
	echo "body:" . $msg->getBody() . "\n";

});
$consumer->start();
$consumer->shutdown();
