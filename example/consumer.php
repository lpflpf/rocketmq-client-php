<?php
$instanceName = "MessageQueue";

$consumer = new MQConsumer();
$consumer->setInstanceName($instanceName);
$consumer->setNamesrvDomain("127.0.0.1:9876");
$consumer->start();
$consumer->setTopic("TopicTest");
$consumer->fetch();
