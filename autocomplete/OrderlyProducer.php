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
class OrderlyProducer extends Producer
{

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
	 * @param callable $successCallback function (SendResult $sendResult)
	 * @param callable $exceptionCallback function(MQException $mqException)
	 * @return void
	 */
	public function sendMessageOrderlyAsync(Message $message, callable $callback, $userData, callable $successCallback, callable $exceptionCallback)
	{

	}
}

