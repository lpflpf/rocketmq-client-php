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
				echo "queueId:" . $msg->getQueueId() . "\n";
				echo "bornTimestamp:" . $msg->getBornTimestamp() . "\n";
				echo "bornHostNameString:" . $msg->getBornHostNameString() . "\n";
				echo "storeTimestamp:" . $msg->getStoreTimestamp() . "\n";
				echo "msgId:" . $msg->getMsgId() . "\n";
				echo "offsetMsgId:" . $msg->getOffsetMsgId() . "\n";
				echo "bodyCRC:" . $msg->getBodyCRC() . "\n";
				echo "queueOffset:" . $msg->getQueueOffset() . "\n";
				echo "commitLogOffset:" . $msg->getCommitLogOffset() . "\n";
				echo "storeSize:" . $msg->getStoreSize() . "\n";
				echo "reconsumeTimes:" . $msg->getReconsumeTimes() . "\n";
				echo "preparedTransactionOffset:" . $msg->getPreparedTransactionOffset() . "\n";
				echo "topic:" . $msg->getTopic() . "\n";
				echo "tags:" . $msg->getTags() . "\n";
				echo "keys:" . $msg->getKeys() . "\n";
				echo "getDelayTimeLevel:" . $msg->getDelayTimeLevel() . "\n";
				echo "flag:" . $msg->getFlag() . "\n";
				echo "sysFlag:" . $msg->getSysFlag() . "\n";
				echo "body:" . $msg->getBody() . "\n";
				
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
		echo "position: " . $position . "\tnextBeginOffset:" . $pullResult->getNextBeginOffset() . "\tminOffset" . $pullResult->getMinOffset() . "\tmaxOffset:" . $pullResult->getMaxOffset() . "\n";
		$queue->setMessageQueueOffset($position + $pullResult->getCount());
	}
}
