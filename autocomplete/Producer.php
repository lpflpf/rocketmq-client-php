<?php

class Producer {
	public function __construct(string $groupName){
	}

	public function getMQClientId(){
	}

	public function getInstanceName(){
	}

	public function setInstanceName(string $groupName){
	}

	public function getNamesrvAddr(){
	}

	public function setNamesrvAddr(string $nameserver){
	}

	public function setNamesrvDomain($nameserver){
	}

	public function getGroupName(){
	}

	public function setGroupName(string $groupName){
	}

	public function send(Message $message){
	}

	public function getSessionCredentials(){
	}

	public function setSessionCredentials(string accessKey, string secretKey, string autChannel){
	}

	public function getTopicMessageQueueInfo(string topic){
	}

	public function start(){
	}

	public function setRetryTimes(int $retryTimes){
	}

	public function getRetryTimes(){
	}

}
	
