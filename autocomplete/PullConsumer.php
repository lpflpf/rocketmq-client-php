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
class PullConsumer
{


	public function __construct(string $instanceName)
	{
	}

	public function start()
	{
	}
	public function shutdown()
	{
	}
	public function version()
	{
	}

	/**
	 * @param string $groupId
	 */
	public function setGroupId($groupId)
	{
	}

	/**
	 * @return string
	 */
	public function getGroupId()
	{
	}

	/**
	 * @param string $address
	 */
	public function setNameServerAddress($address)
	{
	}

	/**
	 * @param string $domain
	 */
	public function setNameServerDomain($domain)
	{
	}

	/**
	 * @param string $access_key
	 * @param string $secret_key
	 * @param string $one_channel
	 */
	public function setSessionCredentials($access_key, $secret_key, $one_channel)
	{
	}

	/**
	 * @param string $log_path
	 */
	public function setLogPath($log_path)
	{
	}

	/**
	 * @param int $file_num
	 * @param int $file_size
	 */
	public function setLogFileNumAndSize($file_num, $file_size)
	{
	}

	/**
	 * @param int $level
	 * @see ELogLevel
	 */
	public function setLogLevel($level)
	{
	}

	/**
	 * @param strng $topic
	 * @param MesageQueues
	 * @return int
	 */
	public function fetchSubscriptionMessageQueues()
	{
	}

	/**
	 * @param MessageQueues $message_queues
	 * @param int $queue_index
	 * @param string $sub_expression
	 * @param int $offset
	 * @param int $max_number
	 * @return PullResult
	 */
	public function pull($message_queues, $queue_index, $sub_expression, $offset, $max_number)
	{
	}
}
