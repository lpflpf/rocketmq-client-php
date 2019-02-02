<?php

namespace RocketMQ;


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

    public function pull(Rocketmq\\MessageQueue $messageQueue, string $subExpression, int $offset, int $maxNums){
    }

    public function pullBlockIfNotFound(Rocketmq\\MessageQueue $messageQueue, string $subExpression, int $offset, int $maxNums){
    }

    public function getSessionCredentials(){
    }

    public function setSessionCredentials(string $accessKey, string $secretKey, string $authChannel){
    }

    void updateConsumeOffset(Rocketmq\\MessageQueue $messageQueue, int $offset){
    }

    public function removeConsumeOffset(Rocketmq\\MessageQueue $messageQueue){
    }

    public function fetchConsumeOffset(Rocketmq\\MessageQueue $messageQueue, string $fromStore){
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
}
