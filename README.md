# rocketmq-client-php

A Php Client for Apache RocketMQ.

# dependence
* [rocketmq-client-cpp](https://github.com/apache/rocketmq-client-cpp)
* [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP)
* linux environment.
* php7

## INSTALL
1. install rocketmq-client-cpp
2. install php-cpp
3. download rocketmq-client-php  
```shell
    git clone https://github.com/lpflpf/rocketmq-client-php;
    cd rocketmq-client-php;
    make && make install
```
4. update php.ini file, add line `extension=rocketmq.so`;
5. try to run example in example directory.

## Example 

### Producer Example

```php
namespace RocketMQ;

$groupName = "testGroupName";
$instanceName = "testInstanceName";
$namesrvAddr = "127.0.0.1:9876";
$topic = "TestTopic";
$tag = "*";

$producer = new Producer($groupName);
$producer->setInstanceName($instanceName);
$producer->setNamesrvAddr($namesrvAddr);
$producer->start();
for ($i = 0;$i < 10000; $i ++){
	$producer->push($topic, $tag, "hello world $i");
	echo "push message $i" . "\n";
}
```

### PullConsumer Example

It is a good idea to save offset in local.

```php
namespace RocketMQ;

$consumer = new PullConsumer("pullTestGroup");
$consumer->setInstanceName("testInstanceName");
$consumer->setTopic("TopicTest");
$consumer->setNamesrvAddr("127.0.0.1:9876");
$consumer->start();
$queues = $consumer->getQueues();

foreach($queues as $queue){
	$newMsg = true;
	while($newMsg){
		$pullResult = $queue->pull("*", 8);
	
		switch ($pullResult->getPullStatus()){
		case PullStatus::FOUND:
			echo "pullStatus: " . $pullResult->getPullStatus() . "\n";
			echo "count: " . $pullResult->getCount() . "\n";
			echo "nextBeginOffset: " . $pullResult->getNextBeginOffset() . "\n";
			echo "minOffset: " . $pullResult->getMinOffset() . "\n";
			echo "maxOffset: " . $pullResult->getMaxOffset() . "\n";
			echo "pullStatus: " . $pullResult->getPullStatus() . "\n";
			echo "\n";
			for($i = 0; $i < $pullResult->getCount(); $i ++){
				$msg = $pullResult->getMessage($i);
                echo $msg->getBody();
			}
			break;
		case PullStatus::NO_MATCHED_MSG:
            break;
		case PullStatus::OFFSET_ILLEGAL:
			$newMsg = false;
            break;
		case PullStatus::BROKER_TIMEOUT:
			$newMsg = false;
            break;
		case PullStatus::NO_NEW_MSG:
			$newMsg = false;
			break;
		default:
		}
		$position = $queue->getMessageQueueOffset();
		echo "position: " . $position . "\tnextBeginOffset:" . $pullResult->getNextBeginOffset() . "\tminOffset" . $pullResult->getMinOffset() . "\tmaxOffset:" . $pullResult->getMaxOffset() . "\n";
		$queue->setMessageQueueOffset($position + $pullResult->getCount());
	}
}
```

### PushConsumer Example

```php
namespace RocketMQ;

$consumer = new PushConsumer("testGroup");
$consumer->setInstanceName("testInstanceName");
$consumer->setNamesrvAddr("127.0.0.1:9876");

// for php, maybe set 1 is a good idea.
$consumer->setThreadCount(1);
$consumer->setListenerType(MessageListenerType::LISTENER_ORDERLY);
$result = array();
$count = 0;
$consumer->setCallback(function ($msg) use (&$count){
	// if thread > 1 & use echo method will core dump.
	file_put_contents("1", $msg->getMsgId() .  "\t" . $count .  "\n", FILE_APPEND);
	$count ++;
});
$consumer->subscribe("TopicTest", "*");
$consumer->start();
$consumer->shutdown();

```

## [Usage](https://github.com/lpflpf/rocketmq-client-php/wiki/Usage)
