<?php

function echo_msg($msg_ext){
	$msg = $msg_ext->getMessage();
	printf("|%-30s|%-40s|\n", "msgId", $msg_ext->getMsgId());
	printf("|%-30s|%-40s|\n", "topic", $msg->getTopic());
	printf("|%-30s|%-40s|\n", "tags", $msg->getTags());
	printf("|%-30s|%-40s|\n", "bornTimestamp", $msg_ext->getBornTimestamp());
	printf("|%-30s|%-40s|\n", "queueId", $msg_ext->getQueue());
	printf("|%-30s|%-40s|\n", "getBornTimestamp", $msg_ext->getBornTimestamp());
//	printf("|%-30s|%-40s|\n", "bornHostNameString", $msg_ext->getBornHostNameString());
//	printf("|%-30s|%-40s|\n", "storeTimestamp", $msg_ext->getStoreTimestamp());
	printf("|%-30s|%-40s|\n", "offsetMsgId", $msg_ext->getOffsetMsgId());
	printf("|%-30s|%-40s|\n", "bodyCRC", $msg_ext->getBodyCRC());
	printf("|%-30s|%-40s|\n", "queueOffset", $msg_ext->getQueueOffset());
	printf("|%-30s|%-40s|\n", "commitLogOffset", $msg_ext->getCommitLogOffset());
	printf("|%-30s|%-40s|\n", "storeSize", $msg_ext->getStoreSize());
	printf("|%-30s|%-40s|\n", "reconsumeTimes", $msg_ext->getReconsumeTimes());
	printf("|%-30s|%-40s|\n", "preparedTransactionOffset", $msg_ext->getPreparedTransactionOffset());
	printf("|%-30s|%-40s|\n", "keys", $msg->getKeys());
	printf("|%-30s|%-40s|\n", "delayTimeLevel", $msg->getDelayTimeLevel());
	printf("|%-30s|%-40s|\n", "flag", $msg->getFlag());
	printf("|%-30s|%-40s|\n", "sysFlag", $msg->getSysFlag());
	printf("|%-30s|%-40s|\n", "body", substr($msg->getBody(),0,40));
	echo "-------------------------------------------------------------------------\n";
}

