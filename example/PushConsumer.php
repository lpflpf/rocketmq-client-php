<?php

namespace RocketMQ;

include("Message.php");

$consumer = new PushConsumer("testGroup");
$consumer->setInstanceName("testGroup");
$consumer->setNamesrvAddr("127.0.0.1:9876");
$consumer->setThreadCount(1);
$consumer->setListenerType(MessageListenerType::LISTENER_ORDERLY);
$result = array();
$count = 0;
// if thread > 1 & use echo method will core dump.
$consumer->setCallback(function ($msg) use (&$count){
    echo_msg($msg);
    $count ++;
});
$consumer->subscribe("TopicTest", "*");
$consumer->start();
$consumer->shutdown();

