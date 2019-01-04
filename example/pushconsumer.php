<?php

namespace RocketMQ;

$consumer = new PushConsumer();
$consumer->setInstanceName("testGroup");
$consumer->setTopic("TopicTest");
$consumer->setNamesrvDomain("127.0.0.1:9876");
$test = "hello";
$consumer->setCallback(function($msg)use($test){
	echo $msg->getMsgId() . "\n";
	echo $msg->getBody(). "\n";
	echo $msg->getKeys() . "\n";
	echo $msg->getTopic() . "\n";
});
$consumer->start();
$consumer->shutdown();
