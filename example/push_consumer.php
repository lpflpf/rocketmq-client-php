<?php
namespace RocketMQ;
include_once("example/message_ext.php");
$pushConsumer = new PushConsumer("my_push_consumer");
$pushConsumer->setNameServerAddress("10.203.165.25:9876");
$pushConsumer->subscribe("helloTopic", "*");
$pushConsumer->setThreadCount(1);
$pushConsumer->registerCallback(function($consumer, $messageExt){
	echo "[message_ext.message_id] --> " . $messageExt->getMessageId() . "\n";
	return 0;
});

$pushConsumer->start();
for ($i = 0; $i < 10; $i ++){
	echo "now running ". $i * 10 .  "s\n";
	sleep(10);
}
$pushConsumer->shutdown();
