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
 * 消息扩展类
 * Class MessageExt
 * @package RocketMQ
 */
class MessageExt{

	public function parseTopicFilterType(int $parseTopicFilterType){}

	/**
	 * 记录MessageQueue编号，消息会被发送到Topic下的MessageQueue
	 * @param int $setQueueid
	 */
	public function getQueueId(){}
	public function setQueueId(int $setQueueid){}

	/**
	 * 消息创建时间，在Producer发送消息时设置
	 * @param int $bornTimestamp
	 */
	public function getBornTimestamp(){}
	public function setBornTimestamp(int $bornTimestamp){}

	/**
	 * 记录存储该消息的Broker地址
	 */
	public function getStoreHostString(){}

	/**
	 * 消息Id
	 * @param string $msgId
	 */
	public function getMsgId(){}
	public function setMsgId(string $msgId){}

	/**
	 *  根据MsgId查询消息
	 * @param int $offsetMsgId
	 */
	public function getOffsetMsgId(){}
	public function setOffsetMsgId(int $offsetMsgId){}

	/**
	 * 消息内容CRC校验值
	 * @param int $bodyCRC
	 */
	public function getBodyCRC(){}
	public function setBodyCRC(int $bodyCRC){}

	/**
	 * 记录在ConsumeQueue中的偏移
	 * @param int $queueOffset
	 */
	public function getQueueOffset(){}
	public function setQueueOffset(int $queueOffset){}

	/**
	 * 记录在Broker中存储偏移
	 */
	public function getCommitLogOffset(){}
	public function setCommitLogOffset(int $physicOffset){}

	/**
	 * 记录消息在Broker存盘大小
	 * @param int $storeSize
	 */
	public function getStoreSize(){}
	public function setStoreSize(int $storeSize){}

	/**
	 * 消息重试消费次数
	 */
	public function getReconsumeTimes(){}

	/**
	 * 事务详细相关字段
	 */
	public function getPreparedTransactionOffset(){}
	public function setPreparedTransactionOffset(int $preparedTransactionOffset){}

	public function toString(){}

	/**
	 * 获取message消息对象
	 */
	public function getMessage(){}

	public function getBornHostString(){}
	public function setBornHostNameString(){}

	public function getStoreTimestamp(){}
	public function setStoreTimestamp(string $storeTimeStamp){}


}
