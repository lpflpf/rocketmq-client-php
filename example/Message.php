<?php

function echo_msg($msg_ext){
    $msg = $msg_ext->getMessage();
    $arr = array(
        "msgId" => $msg_ext->getMsgId(),
        "topic" => $msg->getTopic(),
        "tags" => $msg->getTags(),
        "storeHostString" => $msg_ext->getStoreHostString(),
        "bornTimestamp" => $msg_ext->getBornTimestamp(),
        "queueId" => $msg_ext->getQueue(),
        "getBornTimestamp" => $msg_ext->getBornTimestamp(),
        "offsetMsgId" => $msg_ext->getOffsetMsgId(),
        "bodyCRC" => $msg_ext->getBodyCRC(),
        "queueOffset" => $msg_ext->getQueueOffset(),
        "commitLogOffset" => $msg_ext->getCommitLogOffset(),
        "storeSize" => $msg_ext->getStoreSize(),
        "reconsumeTimes" => $msg_ext->getReconsumeTimes(),
        "preparedTransactionOffset" => $msg_ext->getPreparedTransactionOffset(),
        "keys" => $msg->getKeys(),
        "delayTimeLevel" => $msg->getDelayTimeLevel(),
        "isWaitStoreMsgOK" => $msg->isWaitStoreMsgOK() ? "true" : "false",
        "flag" => $msg->getFlag(),
        "sysFlag" => $msg->getSysFlag(),
        "body" => substr($msg->getBody(),0,40),

    );
    
    foreach($arr as $key => $val){
        printf("|%-30s|%-40s|\n", $key, $val);
    }
    echo "-------------------------------------------------------------------------\n";
}

