<?php

//namespace RocketMQ;

//$message = new Message("TopicTest", "*", "hello world $i");

//$topic = "TopicTest";
//$tag = "*";
//$message = new Message($topic, $tag);
//
$ref = new ReflectionClass('RocketMQ\\Message');
$consts = $ref->getConstants();
foreach($consts as $key => $val){
	echo "$key: $val \n";
}

$methods = $ref->getMethods();   //返回类中所有方法
echo "-----------------methods:---------------" . PHP_EOL . PHP_EOL;
foreach ($methods as $method)
{
	  echo $method->getName() . PHP_EOL;
}

$message = new RocketMQ\Message('TopicTest', '*');
