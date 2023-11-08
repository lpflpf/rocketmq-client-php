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
class TransactionProducer extends Producer
{

	/**
	 * @param string $groupId
	 * @param callable $callback function(MessageExt $ext, $userdata)
	 * @param mixed $userData
	 */
	public function __construct(string $groupId, callable $callback, $userData)
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
}

