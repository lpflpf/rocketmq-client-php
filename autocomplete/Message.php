<?php

namespace RocketMQ;

class Message {
	public function __construct(string $topic, string $tags, string $body = "", string $keys){
	}
	public function setProperty(string $name, string $value){
	}
	public function getProperty(){
	}
	public function getTopic(){
	}
	public function setTopic(string $topic){
	}
	public function setTags(string $tags){
	}
	public function getKeys(){
	} 
	public function setKeys(string $keys){
	}
	public function getDelayTimeLevel(){
	}
	public function setDelayTimeLevel(int $delayTimeLevel){
	}
	public function isWaitStoreMsgOK(){
	}
	public function setWaitStoreMsgOK(bool $waitStoreMsgOK){
	}
	public function getFlag(){
	}
	public function setFlag(int $flag){
	}
	public function getSysFlag(){
	}
	public function setSysFlag(int $sysFlag){
	}
	public function getBody(){
	}
	public function setBody(string $body){
	}
	public function getProperties(){
	}
	public function setProperties(array $properties){
	}
	public function toString(){
	}

}
