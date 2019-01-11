<?php
namespace RocketMQ;
$instanceName = "MessageQueue";

$producer = new Producer($instanceName);
$producer->setInstanceName($instanceName);
$producer->setNamesrvAddr("127.0.0.1:9876");
$producer->start();
for ($i = 0;$i < 10000; $i ++){
	$producer->push("TopicTest", "*", "hello world $i");
	echo "push message $i" . "\n";
}
