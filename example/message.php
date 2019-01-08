<?php

function echo_msg($msg){
	printf("|%-30s|%-40s|\n", "msgId", $msg->getMsgId());
	printf("|%-30s|%-40s|\n", "topic", $msg->getTopic());
	printf("|%-30s|%-40s|\n", "tags", $msg->getTags());
	printf("|%-30s|%-40s|\n", "bornTimestamp", $msg->getBornTimestamp());
	printf("|%-30s|%-40s|\n", "queueId", $msg->getQueueId());
	printf("|%-30s|%-40s|\n", "bornHostNameString", $msg->getBornHostNameString());
	printf("|%-30s|%-40s|\n", "storeTimestamp", $msg->getStoreTimestamp());
	printf("|%-30s|%-40s|\n", "offsetMsgId", $msg->getOffsetMsgId());
	printf("|%-30s|%-40s|\n", "bodyCRC", $msg->getBodyCRC());
	printf("|%-30s|%-40s|\n", "queueOffset", $msg->getQueueOffset());
	printf("|%-30s|%-40s|\n", "commitLogOffset", $msg->getCommitLogOffset());
	printf("|%-30s|%-40s|\n", "storeSize", $msg->getStoreSize());
	printf("|%-30s|%-40s|\n", "reconsumeTimes", $msg->getReconsumeTimes());
	printf("|%-30s|%-40s|\n", "preparedTransactionOffset", $msg->getPreparedTransactionOffset());
	printf("|%-30s|%-40s|\n", "keys", $msg->getKeys());
	printf("|%-30s|%-40s|\n", "delayTimeLevel", $msg->getDelayTimeLevel());
	printf("|%-30s|%-40s|\n", "flag", $msg->getFlag());
	printf("|%-30s|%-40s|\n", "sysFlag", $msg->getSysFlag());
	printf("|%-30s|%-40s|\n", "body", substr($msg->getBody(),0,40));
	echo "-------------------------------------------------------------------------\n";
}

