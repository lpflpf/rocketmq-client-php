<?php

class PullConsumer{
    public function __construct(string $groupName){
    }

	public function setInstanceName($instanceName){
	}

    public function setNamesrvAddr($address){
    }

	public function setNamesrvDomain($nameserver){
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
}
