<?php
namespace RocketMQ;
$instanceName = "MessageQueue";

$producer = new Producer($instanceName);
$producer->setInstanceName($instanceName);
$producer->setNamesrvAddr("127.0.0.1:9876");
$producer->start();

for ($i = 0; $i < 10000; $i ++){
	$message = new Message("TopicTest", "*", "hello world $i");
	$sendResult = $producer->send($message);
	printf("|%-30s|%-40s|\n", "msgId", $sendResult->getMsgId());
	printf("|%-30s|%-40s|\n", "offsetMsgId", $sendResult->getOffsetMsgId());
	printf("|%-30s|%-40s|\n", "sendStatus", $sendResult->getSendStatus());
	printf("|%-30s|%-40s|\n", "queueOffset", $sendResult->getQueueOffset());
	echo "-------------------------------------------------------------------------\n";
}
