<?php
namespace RocketMQ;

function NewMessage($body)
{
    $message = new Message("helloTopic");

    // $message->setDelayTimeLevel(1);
    $message->setMessageBody($body);
    $message->setMessageKeys("trace-123");
    $message->setMessageProperty("key", "value-1");
    $message->setMessageTags("hello");
    $message->setMessageTopic("helloTopic");

    return $message;
}

function printMessage($message)
{
    echo "--------Message--------\n";
    echo "  topic     : " . $message->getOriginMessageTopic() . "\n";
    echo "  tags      : " . $message->getOriginMessageTags() . "\n";
    echo "  delayTime : " . $message->getOriginDelayTimeLevel() . "\n";
    echo "  keys      : " . $message->getOriginMessageKeys() . "\n";
    echo "  body      : " . $message->getOriginMessageBody() . "\n";
}

/**
 * Summary of RocketMQ\printResult
 * @param SendResult $sendResult
 * @return void
 */
function printResult($sendResult)
{
    echo "--------SendResult--------\n"
        . "  msgId     : " . $sendResult->getMsgId() . "\n"
        . "  sendStatus: " . $sendResult->getSendStatus() . "\n"
        . "  offset    : " . $sendResult->getOffset() . "\n";
}

function printException($exception)
{
    echo "exception: "
        . "error: " . $exception->getError() . ","
        . "line: " . $exception->getLine() . ","
        . "file: " . $exception->getFile() . ","
        . "msg" . $exception->getMsg() . ","
        . "type" . $exception->getType() . "\n";

}

function onSuccessCallback($sendResult, $message, $data)
{
    printMessage($message);
    printResult($sendResult);
    print "  userData . :" . $data . "\n";
}
function onExceptionCallback($exception, $message, $data)
{
    printException($exception);
}
function sendMessageSync($producer)
{
    echo __FUNCTION__ . "\n";
    $message = NewMessage("new-message");
    printMessage($message);
    $result = new SendResult();
    $result = $producer->sendMessageSync($message);
    if ($result == NULL) {
        echo "send failed " . getLatestErrorMessage();
    } else {
        printResult($result);
    }
    echo __FUNCTION__ . " END\n";
}


function sendMessageAsync($producer)
{
    echo __FUNCTION__ . "\n";
    $producer->sendMessageAsync(NewMessage("send_message_async"), "RocketMQ\\onSuccessCallback", "RocketMQ\\onExceptionCallback", "sendMessageAsync");
    sleep(1);
    echo __FUNCTION__ . " END\n";
}

function sendMessageOneway($producer)
{
    echo __FUNCTION__ . "\n";
    $producer->sendMessageOneway(NewMessage(__FUNCTION__));
    echo __FUNCTION__ . " END\n";
}

function selector($size, $msg, $data)
{
    echo " size :" . $size . "\n";
    printMessage($msg);
    echo $data . "\n";
    return 1;
}

/**
 * @return Producer
 */
function newProducer($group)
{
    $producer = new Producer($group);
    $ret = $producer->setNameServerAddress("10.203.165.25:9876");
    $producer->setGroupName($group);
    $producer->setInstanceName($group);
    if ($ret == 1) {
        echo "error" . getLatestErrorMessage();
    }

    $producer->setLogPath("/tmp/");
    $ret = $producer->start();
    if ($ret != 0) {
        echo "start error" . getLatestErrorMessage() . "\n";
    }
    return $producer;
}

function newTransactionProducer($group)
{
    $producer = new TransactionProducer($group, function ($messageExt, $userData) {
        echo "in checker\n";
        echo $userData . "\n";
        echo $messageExt->getMessageId() . "\n";
        echo "\n";
        return 0;
    }, "transaction_check_user_data");
    $producer->setNameServerAddress("10.203.165.25:9876");
    $producer->setGroupName($group);
    $producer->setInstanceName($group);
    $ret = $producer->start();
    if ($ret != 0) {
        echo "start error" . getLatestErrorMessage() . "\n";
    }
    return $producer;
}

function newOrderlyProducer($groupId)
{
    $producer = new OrderlyProducer($groupId);
    $ret = $producer->setNameServerAddress("10.203.165.25:9876");
    if ($ret == 1) {
        echo "error" . getLatestErrorMessage();
        return;
    }
    $producer->setGroupName($groupId);
    $producer->setInstanceName($groupId);
    $ret = $producer->start();
    if ($ret != 0) {
        echo "start error" . getLatestErrorMessage() . "\n";
    }
    return $producer;
}

function sendMessageOnewayOrderly($producer)
{
    echo __FUNCTION__ . "\n";
    $producer->sendMessageOnewayOrderly(NewMessage("sendMessageOnewayOrderly"), "RocketMQ\\selector", __FUNCTION__);
    echo __FUNCTION__ . " END\n";
}

function sendMessageOrderly($producer)
{
    echo __FUNCTION__ . "\n";
    $selector = function ($size, $msg, $data) {
        printMessage($msg);
        print $data . "\n";
        return 1;
    };

    $result = new SendResult();
    $ret = $producer->sendMessageOrderly(NewMessage("sendMessageOrderly"), $selector, __FUNCTION__, 3, $result);
    if ($ret != 0) {
        echo "start error" . getLatestErrorMessage() . "\n";
    }
    printResult($result);
    echo __FUNCTION__ . " END\n";
}

function sendMessageOrderlyByShardingKey($producer)
{
    echo __FUNCTION__ . "\n";

    $result = new SendResult();
    $ret = $producer->sendMessageOrderlyByShardingKey(NewMessage(__FUNCTION__), "test-key", $result);
    printResult($result);
    echo __FUNCTION__ . " END\n";
}

function transactionCallback($message, $userData)
{
    return 0;
}
function sendMessageTransaction($producer)
{
    $group = "transactionProducerGroupID";
   echo __FUNCTION__ . "\n";
    $result = new SendResult();
    $producer->sendMessageTransaction(NewMessage(__FUNCTION__), "RocketMQ\\transactionCallback", __FUNCTION__ . "user_data", $result);
    printResult($result);
    echo __FUNCTION__ . " END\n";
}
function successCallback($sendResult)
{
    echo "success \n";
    printResult($sendResult);
}
function exceptionCallback($exception)
{
    printException($exception);
}

function sendMessageOrderlyAsync($producer)
{
    echo __FUNCTION__ . "\n";
    $selector = function ($size, $msg, $data) {
        printMessage($msg);
        echo "sendMessageOrderlyAsync user-data: " . $data . "\n";
        return 1;
    };

    $ret = $producer->sendMessageOrderlyAsync(NewMessage(__FUNCTION__), $selector, __FUNCTION__, "RocketMQ\\successCallback", "RocketMQ\\exceptionCallback");
    if ($ret != 0) {
        echo "start error" . getLatestErrorMessage() . "\n";
    }
    echo __FUNCTION__ . " END\n";
}

function sendBatchMessage($producer)
{
    echo __FUNCTION__ . "\n";
    $result = new SendResult();
    $batchMessage = new BatchMessage();
    for ($i = 0; $i < 10; $i ++){
        $message = NewMessage("BatchMessage" . $i);
        $batchMessage->addMessage($message);
        printMessage($message);
    }
    $ret = $producer->sendBatchMessage($batchMessage, $result);
    if ($ret > 0){
        echo "send failed " . getLatestErrorMessage();
    } else {
        echo "batch message offset: " . $result->getOffset() . "\n";
    }
    echo __FUNCTION__ . " END\n";
}


$producer = newProducer("producer");
sendMessageSync($producer);
sendMessageAsync($producer);
sendMessageOneway($producer);
sendBatchMessage($producer);
$producer->shutdown();

$transactionProducer = newTransactionProducer("transactionProducer");
sendMessageTransaction($transactionProducer);
$transactionProducer->shutdown();

$orderlyProducer = newOrderlyProducer("orderlyProducer");
sendMessageOrderly($orderlyProducer);
sendMessageOrderlyByShardingKey($orderlyProducer);
sendMessageOrderlyAsync($orderlyProducer);
sendMessageOnewayOrderly($orderlyProducer);
$orderlyProducer->shutdown();

