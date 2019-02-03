<?php

namespace RocketMQ;

/**
 * Pull method consumer.
 *
 */
class PullConsumer{
    public function __construct(string $groupName){
    }

	public function setInstanceName($instanceName){
	}

    public function setNamesrvAddr($address){
    }

    public function getNamesrvAddr(){
    }

	public function setNamesrvDomain($nameserver){
	}

    public function getNamesrvDomain(){
    }

	public function setTopic($topic){
	}

	public function start(){
	}

	public function getQueues(){
	}

    public function setGroup(string $group){
    }

    public function pull(MessageQueue $messageQueue, string $subExpression, int $offset, int $maxNums){
    }

    public function pullBlockIfNotFound(MessageQueue $messageQueue, string $subExpression, int $offset, int $maxNums){
    }

    public function getSessionCredentials(){
    }

    public function setSessionCredentials(string $accessKey, string $secretKey, string $authChannel){
    }

    public function updateConsumeOffset(MessageQueue $messageQueue, int $offset){
    }

    public function removeConsumeOffset(MessageQueue $messageQueue){
    }

    public function fetchConsumeOffset(MessageQueue $messageQueue, string $fromStore){
    }

    public function setMessageModel($model){
    }

    public function getMessageModel($model){
    }

    public function setTcpTransportPullThreadNum(int $num){
    }

    public function getTcpTransportPullThreadNum(){
    }

    public function setTcpTransportConnectTimeout(int $timeout){
    }

    public function getTcpTransportConnectTimeout(){
    }
    
    public function setTcpTransportTryLockTimeout(int $timeout){
    }

    public function getTcpTransportTryLockTimeout(){
    }

    public function setUnitName(string $unitName){
    }

    public function getUnitName(){
    }

    public function getConsumeFromWhere(){
    }

    public function setConsumeFromWhere(int $consumeFromWhere){
    }
}
