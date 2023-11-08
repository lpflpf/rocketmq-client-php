<?php

/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

namespace RocketMQ;

/**
 * 长轮训推消费消息
 * Class PushConsumer
 * @package RocketMQ
 */
class PushConsumer
{


	public function __construct(string $instanceName)
	{
	}

	/**
	 * 设置获取名字服务配置的http接口
	 * 比如http://nameserver.abc.com/get/nameserver 这个接口返回值是127.0.0.1:9876则程序会
	 * 自动链接到该地址，不需要显示的设置,便于更新
	 * @param $nameserver
	 */
	public function setNamesrvDomain($nameserver)
	{
	}

	public function getNamesrvDomain()
	{
	}

	/**
	 * 设置名字服务链接地址
	 * @param string $nameserver
	 */
	public function setNamesrvAddr($nameserver)
	{
	}

	public function getNamesrvAddr()
	{
	}

	/**
	 * 设置实例名
	 * @param string $instanceName  实例名
	 */
	public function setInstanceName($instanceName)
	{
	}

	/**
	 * 设置枷锁超时时间
	 * @param $tryLockTimeout
	 */
	public function setTryLockTimeout($tryLockTimeout)
	{
	}

	/**
	 * 设置链接超时时间
	 * @param $connectTimeout
	 */
	public function setConnectTimeout($connectTimeout)
	{
	}

	/**
	 * 设置消费进程数
	 * @param $threadCount
	 */
	public function setThreadCount($threadCount)
	{
	}

	/**
	 * 监听对象类型
	 * @param $listenerType
	 */
	public function setListenerType($listenerType)
	{
	}

	/**
	 * 阿里云商用版本需要使用这个方法链接，开源版本不需要管
	 */
	public function getSessionCredentials()
	{
	}

	/**
	 * 阿里云商用版本需要使用这个方法链接，开源版本不需要管
	 * @param string $accessKey
	 * @param string $secretKey
	 * @param string $autChannel
	 */
	public function setSessionCredentials(string $accessKey, string $secretKey, string $autChannel)
	{
	}

	/**
	 * 订阅
	 * @param $topic
	 * @param $tag
	 */
	public function subscribe($topic, $tag)
	{
	}

	/**
	 * 开始
	 */
	public function start()
	{
	}

	/**
	 * 结束
	 */
	public function shutdown()
	{
	}

	/**
	 * 消息回调方法
	 * @param callable $callback
	 */
	public function setCallback(callable $callback)
	{
	}

	/**
	 * 设置消息类型
	 * @param $model
	 */
	public function setMessageModel($model)
	{
	}

	public function getMessageModel($model)
	{
	}

	/**
	 * 设置传出链接线程数 默认是cpu core的数值
	 * @param int $num
	 */
	public function setTcpTransportPullThreadNum(int $num)
	{
	}
	public function getTcpTransportPullThreadNum()
	{
	}

	/**
	 *  设置tcp链接超时时间
	 * @param int $timeout
	 */
	public function setTcpTransportConnectTimeout(int $timeout)
	{
	}
	public function getTcpTransportConnectTimeout()
	{
	}

	/**
	 * 设置申请锁超时时间
	 * @param int $timeout
	 */
	public function setTcpTransportTryLockTimeout(int $timeout)
	{
	}
	public function getTcpTransportTryLockTimeout()
	{
	}

	/**
	 * 同一个实例链接多套rocketmq的时候需要传入，可以区别生成clientId
	 * @param string $unitName
	 */
	public function setUnitName(string $unitName)
	{
	}
	public function getUnitName()
	{
	}

	/**
	 * 获取模式
	 */
	public function getConsumeFromWhere()
	{
	}
	public function setConsumeFromWhere(int $consumeFromWhere)
	{
	}

	public function getConsumeThreadCount()
	{
	}

	public function getNameSpace()
	{
	}
	public function setNameSpace(string $space)
	{
	}

	public function setLogLevel(int $inputLevel)
	{
	}

	public function getLogLevel()
	{
	}

	public function setLogFileSizeAndNum($fileNum, $perFileSize)
	{
	}

	public function setLogPath(string $logPath)
	{
	}

	public function setMaxReconsumeTimes(int $maxReconsumeTimes)
	{
	}
	public function getMaxReconsumeTimes()
	{
	}

	public function setPullMsgThreadPoolCount(int $threadCount)
	{
	}
	public function getPullMsgThreadPoolCount()
	{
	}

	public function setConsumeMessageBatchMaxSize(int $consumeMessageBatchMaxSize)
	{
	}
	public function getConsumeMessageBatchMaxSize()
	{
	}

	public function setMaxCacheMsgSizePerQueue(int $maxCacheSize)
	{
	}
	public function getMaxCacheMsgSizePerQueue()
	{
	}

	public function setAsyncPull(bool $setAsyncPull)
	{
	}

	public function setMessageTrace(bool $messageTrace)
	{
	}
	public function getMessageTrace()
	{
	}
}
