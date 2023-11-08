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
 * message ext
 * Class MessageExt
 * @package RocketMQ
 */
class MessageExt
{

	/**
	 * @return string
	 */
	public function getMessageTopic()
	{
	}

	/**
	 * @return string
	 */
	public function getMessageTags()
	{
	}

	/**
	 * @return string
	 */
	public function getMessageKeys()
	{
	}

	/**
	 * @return string
	 */
	public function getMessageBody()
	{
	}

	/**
	 * @param $key string
	 * @return string
	 */
	public function getMessageProperty($key)
	{
	}

	/**
	 * 消息Id
	 * @param string $msgId
	 */
	public function getMssagegId()
	{
	}

	/**
	 * @return int
	 */
	public function getMessageDelayTimeLevel()
	{
	}


	/**
	 * 记录MessageQueue编号，消息会被发送到Topic下的MessageQueue
	 * @param int $setQueueid
	 */
	public function getMessageQueueId()
	{
	}

	/**
	 * @return int
	 */
	public function getMessageReconsumeTimes()
	{
	}

	/**
	 * @return int
	 */
	public function getMessageStoreSize()
	{
	}

	/**
	 * 消息创建时间，在Producer发送消息时设置
	 * @param int 
	 */
	public function getMessageBornTimestamp()
	{
	}

	/**
	 * @param int
	 */
	public function getMessageStoreTimestamp()
	{
	}
	/**
	 * @param int
	 */
	public function getMessageQueueOffset()
	{
	}

	/**
	 * @param int
	 */
	public function getMessageCommitLogOffset()
	{
	}

	/**
	 * @param int
	 */
	public function getMessagePreparedTransactionOffset()
	{
	}
}
