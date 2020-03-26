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
 * 拉取消息消费
 * Pull method consumer.
 *
 */
class PullConsumer{


	public function __construct(string $instanceName){}

	/**
	 * 实例名,用来组合生成client_id
	 * @param $instanceName
	 *
	 */
	public function setInstanceName($instanceName){}

	/**
	 * 设置名字服务链接地址
	 * @param $address
	 */
	public function setNamesrvAddr($address){}

	/**
	 * 获取名字服务链接地址
	 */
	public function getNamesrvAddr(){}

	/**
	 * 设置获取名字服务配置的http接口
	 * 比如http://nameserver.abc.com/get/nameserver 这个接口返回值是127.0.0.1:9876则程序会
	 * 自动链接到该地址，不需要显示的设置,便于更新
	 * @param $nameserver
	 */
	public function setNamesrvDomain($nameserver){}

	public function getNamesrvDomain(){}

	/**
	 * 注册topic
	 * @param $topic
	 */
	public function setTopic($topic){}

	public function start(){}

	/**
	 * 获取队列对象(MessageQueue)列表
	 * return array
	 */
	public function getQueues(){}

	/**
	 * 设置分组名
	 * @param string $group
	 */
	public function setGroup(string $group){}

	/**
	 * 拉取消息
	 * @param MessageQueue $messageQueue /指定对象
	 * @param string $subExpression //tag表达式
	 * @param int $offset //偏移值
	 * @param int $maxNums //每次最多取多少条消息
	 */
	public function pull(MessageQueue $messageQueue, string $subExpression, int $offset, int $maxNums){}

	/**
	 * 批量取消息
	 * @param MessageQueue $messageQueue
	 * @param string $subExpression
	 * @param int $offset
	 * @param int $maxNums
	 */
	public function pullBlockIfNotFound(MessageQueue $messageQueue, string $subExpression, int $offset, int $maxNums){}

	/**
	 * 阿里云的商用版本会用到
	 */
	public function getSessionCredentials(){}

	public function setSessionCredentials(string $accessKey, string $secretKey, string $authChannel){}

	/**
	 * 更新消费队列偏移
	 * @param MessageQueue $messageQueue
	 * @param int $offset
	 */
	public function updateConsumeOffset(MessageQueue $messageQueue, int $offset){}

	public function removeConsumeOffset(MessageQueue $messageQueue){}

	/**
	 * 获取偏移数
	 * @param MessageQueue $messageQueue
	 * @param string $fromStore
	 */
	public function fetchConsumeOffset(MessageQueue $messageQueue, string $fromStore){}

	public function persistConsumerOffset4PullConsumer(Message $messageQueue){}
	/**
	 * 设置消息模式,广播消息或者集群消息
	 * @param $model
	 */
	public function setMessageModel($model){}

	public function getMessageModel($model){}

	/**
	 * 设置传出链接线程数 默认是cpu core的数值
	 * @param int $num
	 */
	public function setTcpTransportPullThreadNum(int $num){}

	public function getTcpTransportPullThreadNum(){}

	/**
	 * 设置tcp链接超时时间
	 * @param int $timeout
	 */
	public function setTcpTransportConnectTimeout(int $timeout){}

	public function getTcpTransportConnectTimeout(){}

	/**
	 * 设置申请锁超时时间
	 * @param int $timeout
	 */
	public function setTcpTransportTryLockTimeout(int $timeout){}

	public function getTcpTransportTryLockTimeout(){}

	/**
	 * 同一个实例链接多套rocketmq的时候需要传入，可以区别生成clientId
	 * @param string $unitName
	 */
	public function setUnitName(string $unitName){}

	public function getUnitName(){}

	/**
	 * 获取模式
	 */
	public function getConsumeFromWhere(){}

	public function setConsumeFromWhere(int $consumeFromWhere){}

	public function setLogLevel(int $inputLevel){}

	public function getLogLevel(){}

	public function setLogFileSizeAndNum($fileNum, $perFileSize){}

	public function setLogPath(string $logPath){}

	public function getNameSpace(){}
	public function setNameSpace(){}

	public function getGroupName(){}
	public function setGroupName(){}

	public function getInstanceName(){}
	public function version(){}
}
