<?php

namespace RocketMQ;

$consumer = new PullConsumer();
$consumer->setInstanceName("testGroup");
$consumer->setTopic("TopicTest");
$consumer->setNamesrvDomain("127.0.0.1:9876");
$consumer->start();
$queues = $consumer->getQueues();

echo "FOUND:          " . PullStatus::FOUND . "\n";
echo "NO_MATCHED_MSG: " . PullStatus::NO_MATCHED_MSG. "\n";
echo "OFFSET_ILLEGAL: " . PullStatus::OFFSET_ILLEGAL. "\n";
echo "BROKER_TIMEOUT: " . PullStatus::BROKER_TIMEOUT . "\n";
echo "NO_NEW_MSG:     " . PullStatus::NO_NEW_MSG . "\n";

foreach($queues as $queue){

	$newMsg = true;
	while($newMsg){
		$pullResult = $queue->pull("*");
	
		switch ($pullResult->getPullStatus()){
		case PullStatus::FOUND:
			echo "pullStatus: " . $pullResult->getPullStatus() . "\n";
			echo "count: " . $pullResult->getCount() . "\n";
			echo "nextBeginOffset: " . $pullResult->getNextBeginOffset() . "\n";
			echo "minOffset: " . $pullResult->getMinOffset() . "\n";
			echo "maxOffset: " . $pullResult->getMaxOffset() . "\n";
			echo "->pullStatus: " . $pullResult->getPullStatus() . "\n";
			echo "\n";
			for($i = 0; $i < $pullResult->getCount(); $i ++){
				echo $i . "\n";
				$msg = $pullResult->getMessage($i);
				echo $msg->getMsgId() . "\n";
				echo $msg->getBody(). "\n";
				echo $msg->getKeys() . "\n";
				echo $msg->getTopic() . "\n";
				echo "-----------------------------------------\n";
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
		$position = $queue->getMessageQueueOffset();
		echo "position: " . $position . "\n";
		$queue->setMessageQueueOffset($position + $pullResult->getCount());
	}
}
