<?php

namespace RocketMQ;

class PushConsumer{
	public function setNamesrvDomain($nameserver){
	}

    public function getNamesrvDomain(){
    }

    public function setNamesrvAddr($nameserverAddr){

    }
    public function getNamesrvAddr(){
    }

	public function setInstanceName($groupName){
	}

	public function setTryLockTimeout($tryLockTimeout){
	}

	public function setConnectTimeout($connectTimeout){
	}

	public function setThreadCount($threadCount){
	}

	public function setListenerType($listenerType){
	}

	public function subscribe($topic, $tag){
	}

	public function start(){
	}

	public function shutdown(){
	}

	public function setCallback(callable $callback){
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

    public function setLogLevel(int $inputLevel){
    }

    public function getLogLevel(){
    }

    public function setLogFileSizeAndNum($fileNum, $perFileSize){
    }
}
