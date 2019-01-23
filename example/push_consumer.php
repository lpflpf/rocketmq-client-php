<?php

namespace RocketMQ;

include("message.php");

$consumer = new PushConsumer("testGroup");
$consumer->setInstanceName("testGroup");
$consumer->setNamesrvAddr("127.0.0.1:9876");
$consumer->setThreadCount(10);
$consumer->setListenerType(MessageListenerType::LISTENER_ORDERLY);
$result = array();
$count = 0;
$consumer->setCallback(function ($msg) use (&$count){
	// if thread > 1 & use echo method will core dump.
	//file_put_contents("1", $msg->getMsgId() .  "\t" . $count .  "\n", FILE_APPEND);
	echo_msg($msg);
	$count ++;
});
$consumer->subscribe("TopicTest", "*");
$consumer->start();
$consumer->shutdown();

