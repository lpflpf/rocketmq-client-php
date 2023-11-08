<?php
namespace RocketMQ;
include_once("example/message_ext.php");
$pullConsumer = new PullConsumer("hello_consumer");
$pullConsumer->setNameServerAddress("10.203.165.25:9876");
$queues = new MessageQueues();
$pullConsumer->start();
$ret = $pullConsumer->fetchSubscriptionMessageQueues("helloTopic", $queues);
$pullResult = $pullConsumer->pull($queues, 0, "*", 0, 1000);
echo "pull_result count:" . count($pullResult) . "\n";
echo "body:" . $pullResult->get(0)->getMessageBody() . "\n";

/**
 * Summary of RocketMQ\printMessageExt
 * @param MessageExt $msg
 */

foreach($pullResult as $key => $value){
    echo printMessageExt($value);
}

$pullConsumer->shutdown();
