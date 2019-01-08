<?php

namespace RocketMQ;

include("message.php");

$consumer = new PushConsumer();
$consumer->setInstanceName("testGroup");
$consumer->subscribe("TopicTest", "*");
$consumer->setNamesrvDomain("127.0.0.1:9876");
$consumer->setThreadCount(10);
$consumer->setListenerType(MessageListenerType::LISTENER_ORDERLY);
$consumer->setCallback(function($msg){
	echo_msg($msg);
});
$consumer->start();
$consumer->shutdown();
