<?php

namespace RocketMQ;

include("message.php");

$consumer = new PullConsumer("pullTestGroup");
$consumer->setGroup("pullTestGroup");
$consumer->setInstanceName("testGroup");
$consumer->setTopic("TopicTest");
$consumer->setNamesrvAddr("127.0.0.1:9876");
$consumer->start();
$queues = $consumer->getQueues();

//foreach($queues as $queue){
$queue = $queues[3];
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
				$msg = $pullResult->getMessage($i);
				echo_msg($msg);
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
//		echo "position: " . $position . "\tnextBeginOffset:" . $pullResult->getNextBeginOffset() . "\tminOffset" . $pullResult->getMinOffset() . "\tmaxOffset:" . $pullResult->getMaxOffset() . "\n";
		$offset += $pullResult->getCount();
//		$queue->setMessageQueueOffset($position + $pullResult->getCount());
	}
//}
