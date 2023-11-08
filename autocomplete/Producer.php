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
 * 消息生产者
 * Class Producer
 * @package RocketMQ
 */
class Producer
{

	/**
	 * Producer constructor.
	 * @param string $groupId 
	 */
	public function __construct(string $groupId)
	{
	}

	/**
	 * 启动
	 */
	public function start()
	{
	}

	public function shutdown()
	{
	}

	/**
	 * @return version
	 */
	public function version()
	{
	}

	/**
	 * 设置名字服务链接地址
	 * @param string $nameserver
	 */
	public function setNameServerAddress(string $nameserver)
	{
	}

	/**
	 * 设置名字服务domain
	 * @param string domain$
	 */
	public function setNameServerDomain(string $domain)
	{
	}

	/**
	 * 设置分组名
	 * @param string $groupName
	 */
	public function setGroupName(string $groupName)
	{
	}


	/**
	 * 设置实例名
	 * @param string $instanceName  实例名
	 */
	public function setInstanceName(string $instanceName)
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
	 *  设置日志路径
	 */
	public function setLogPath(string $logPath)
	{
	}

	/**
	 * 设置日志生成规则
	 * @param $fileNum //保留日志数目
	 * @param $perFileSize //每个日志多大
	 */
	public function setLogFileNumAndSize($fileNum, $perFileSize)
	{
	}

	/**
	 * 设置日志等级
	 * @param int $inputLevel
	 */
	public function setLogLevel(int $inputLevel)
	{
	}

	/**
	 * 发送消息超时时间
	 * @param $sendMsgTimeout 单位是毫秒  默认3000毫秒
	 */
	public function setSendMsgTimeout($sendMsgTimeout)
	{
	}

	/**
	 * 设置消息压缩等级   level = [-1, 9]
	 * @param $compressLevel //默认是5
	 */
	public function setCompressLevel($compressLevel)
	{
	}

	/**
	 * 设置消息长度最大限制
	 * @param $messageSize
	 */
	public function setMaxMessageSize($messageSize)
	{
	}

	/**
	 * @param int traceModel
	 * @return int
	 * @see TraceModel
	 */
	public function setMessageTrace($traceModel)
	{
	}

	/**
	 * @param Message $message
	 * @return int
	 */
	public function setMessageSync($message)
	{

	}

	/**
	 * Summary of setMessageAsync
	 * @param Message $message
	 * @param callable $successCallback function(SendResult $sendresult, Message $message, $userData) 
	 * @param callable $exceptionCallback function(MQException $exception, Message $message, $userData) 
	 * @param mixed $userData
	 * @return void
	 */
	public function sendMessageAsync($message, $successCallback, $exceptionCallback, $userData)
	{

	}

	/**
	 * @param Message $message
	 * @return int
	 */
	public function sendMessageOneway($message)
	{

	}

	/**
	 * @param \RocketMQ\Message $message
	 * @param callable $selector function (int $size, Message $message, $userData)
	 * @param mixed $userData
	 * @return void
	 */
	public function sendMessageOnewayOrderly(Message $message,callable $selector, $userData)
	{

	}

	/**
	 * @param \RocketMQ\Message $message
	 * @param callable $selector function (int $size, Message $message, $userData)
	 * @param mixed $userData
	 * @param int $retryTimes
	 * @param \RocketMQ\SendResult $sendResult
	 * @return void
	 */
	public function sendMessageOrderly(Message $message, callable $selector, $userData, int $retryTimes, SendResult $sendResult)
	{

	}

	/**
	 * @param \RocketMQ\Message $message
	 * @param string $shardingKey
	 * @param \RocketMQ\SendResult $result
	 * @return void
	 */
	public function sendMessageOrderlyByShardingKey(Message $message, string $shardingKey, SendResult $result)
	{

	}

	/**
	 * @param \RocketMQ\Message $message
	 * @param callable $callback function(Message $message, $userData)
	 * @param mixed $userData
	 * @param \RocketMQ\SendResult $sendResult
	 * @return void
	 */
	public function sendMessageTranscation(Message $message, callable $callback, $userData, SendResult $sendResult)
	{

	}

	/**
	 * @param \RocketMQ\Message $message
	 * @param callable $callback function(Message $message, $userData)
	 * @param mixed $userData
	 * @param callable $successCallback function (SendResult $sendResult)
	 * @param callable $exceptionCallback function(MQException $mqException)
	 * @return void
	 */
	public function sendMessageOrderlyAsync(Message $message, callable $callback, $userData, callable $successCallback, callable $exceptionCallback)
	{

	}
}

