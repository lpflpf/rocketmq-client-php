<?php
namespace RocketMQ;
$instanceName = "MessageQueue";

$producer = new Producer();
$producer->setInstanceName($instanceName);
$producer->setNamesrvDomain("127.0.0.1:9876");
$producer->start();
for ($i = 0;$i < 100; $i ++){
	$producer->push("TopicTest", "*", "hello world $i");
	echo "push message $i" . "\n";
}
