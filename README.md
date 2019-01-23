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

## TODO

1. manual commit an offset.
2. push consumer can set a queue to consumer.
3. producer can get some extra information for sending message.

## Example 

### Producer Example

```php
namespace RocketMQ;
$instanceName = "MessageQueue";

$producer = new Producer($instanceName);
$producer->setInstanceName($instanceName);
$producer->setNamesrvAddr("127.0.0.1:9876");
$producer->start();

for ($i = 0; $i < 10000; $i ++){
	$message = new Message("TopicTest", "*", "hello world $i");
	$sendResult = $producer->send($message);
	echo $sendResult->getMsgId() . "\n";
	echo $sendResult->getOffsetMsgId() . "\n";
	echo $sendResult->getSendStatus() . "\n";
	//echo $sendResult->getMessageQueue();
	echo $sendResult->getQueueOffset() . "\n";
}
```

### PullConsumer Example

It is a good idea to save offset in local.

```php
namespace RocketMQ;

include("message.php");

$consumer = new PullConsumer("pullTestGroup");
$consumer->setGroup("pullTestGroup");
$consumer->setInstanceName("testGroup");
$consumer->setTopic("TopicTest");
$consumer->setNamesrvAddr("127.0.0.1:9876");
$consumer->start();
$queues = $consumer->getQueues();

foreach($queues as $queue){
	$newMsg = true;
	$offset = 0;
	while($newMsg){
		$pullResult = $consumer->pull($queue, "*", $offset, 8);
	
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
				$msg_ext = $pullResult->getMessage($i);
				$msg = $msg_ext->getMessage();
				printf("|%-30s|%-40s|\n", "msgId", $msg_ext->getMsgId());
				printf("|%-30s|%-40s|\n", "topic", $msg->getTopic());
				printf("|%-30s|%-40s|\n", "tags", $msg->getTags());
				printf("|%-30s|%-40s|\n", "storeHostString", $msg_ext->getStoreHostString());
				printf("|%-30s|%-40s|\n", "bornTimestamp", $msg_ext->getBornTimestamp());
				printf("|%-30s|%-40s|\n", "queueId", $msg_ext->getQueue());
				printf("|%-30s|%-40s|\n", "getBornTimestamp", $msg_ext->getBornTimestamp());
				printf("|%-30s|%-40s|\n", "offsetMsgId", $msg_ext->getOffsetMsgId());
				printf("|%-30s|%-40s|\n", "bodyCRC", $msg_ext->getBodyCRC());
				printf("|%-30s|%-40s|\n", "queueOffset", $msg_ext->getQueueOffset());
				printf("|%-30s|%-40s|\n", "commitLogOffset", $msg_ext->getCommitLogOffset());
				printf("|%-30s|%-40s|\n", "storeSize", $msg_ext->getStoreSize());
				printf("|%-30s|%-40s|\n", "reconsumeTimes", $msg_ext->getReconsumeTimes());
				printf("|%-30s|%-40s|\n", "preparedTransactionOffset", $msg_ext->getPreparedTransactionOffset());
				printf("|%-30s|%-40s|\n", "keys", $msg->getKeys());
				printf("|%-30s|%-40s|\n", "delayTimeLevel", $msg->getDelayTimeLevel());
				printf("|%-30s|%-40s|\n", "isWaitStoreMsgOK", $msg->isWaitStoreMsgOK() ? "true" : "false");
				printf("|%-30s|%-40s|\n", "flag", $msg->getFlag());
				printf("|%-30s|%-40s|\n", "sysFlag", $msg->getSysFlag());
				printf("|%-30s|%-40s|\n", "body", substr($msg->getBody(),0,40));
				echo "-------------------------------------------------------------------------\n";
			}
			break;
		case PullStatus::NO_MATCHED_MSG:
		case PullStatus::OFFSET_ILLEGAL:
			$newMsg = false;
		case PullStatus::BROKER_TIMEOUT:
			$newMsg = false;
		case PullStatus::NO_NEW_MSG:
			$newMsg = false;
			break;
		default:
		}
		$offset += $pullResult->getCount();
//		$queue->setMessageQueueOffset($position + $pullResult->getCount());
	}
}
```

### PushConsumer Example

```php
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
	$msg = $msg_ext->getMessage();
	printf("|%-30s|%-40s|\n", "msgId", $msg_ext->getMsgId());
	printf("|%-30s|%-40s|\n", "topic", $msg->getTopic());
	printf("|%-30s|%-40s|\n", "tags", $msg->getTags());
	printf("|%-30s|%-40s|\n", "storeHostString", $msg_ext->getStoreHostString());
	printf("|%-30s|%-40s|\n", "bornTimestamp", $msg_ext->getBornTimestamp());
	printf("|%-30s|%-40s|\n", "queueId", $msg_ext->getQueue());
	printf("|%-30s|%-40s|\n", "getBornTimestamp", $msg_ext->getBornTimestamp());
	printf("|%-30s|%-40s|\n", "offsetMsgId", $msg_ext->getOffsetMsgId());
	printf("|%-30s|%-40s|\n", "bodyCRC", $msg_ext->getBodyCRC());
	printf("|%-30s|%-40s|\n", "queueOffset", $msg_ext->getQueueOffset());
	printf("|%-30s|%-40s|\n", "commitLogOffset", $msg_ext->getCommitLogOffset());
	printf("|%-30s|%-40s|\n", "storeSize", $msg_ext->getStoreSize());
	printf("|%-30s|%-40s|\n", "reconsumeTimes", $msg_ext->getReconsumeTimes());
	printf("|%-30s|%-40s|\n", "preparedTransactionOffset", $msg_ext->getPreparedTransactionOffset());
	printf("|%-30s|%-40s|\n", "keys", $msg->getKeys());
	printf("|%-30s|%-40s|\n", "delayTimeLevel", $msg->getDelayTimeLevel());
	printf("|%-30s|%-40s|\n", "isWaitStoreMsgOK", $msg->isWaitStoreMsgOK() ? "true" : "false");
	printf("|%-30s|%-40s|\n", "flag", $msg->getFlag());
	printf("|%-30s|%-40s|\n", "sysFlag", $msg->getSysFlag());
	printf("|%-30s|%-40s|\n", "body", substr($msg->getBody(),0,40));
	echo "-------------------------------------------------------------------------\n";

	$count ++;
});
$consumer->subscribe("TopicTest", "*");
$consumer->start();
$consumer->shutdown();

```

## [Usage](https://github.com/lpflpf/rocketmq-client-php/wiki/Usage)
