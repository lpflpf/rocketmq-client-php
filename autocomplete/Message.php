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
 * 消息对象
 * Class Message
 * @package RocketMQ
 */
class Message
{

    /**
     *
     * Message constructor.
     * @param string $topic //topic
     */
    public function __construct(string $topic)
    {
    }

    public function getOriginMessageTopic()
    {
    }

    public function setMessageTopic(string $topic)
    {
    }

    /**
     * @return string
     */
    public function getOriginMessageTags(){

    }

    /**
     * 在消费消息时可以通过tag进行消息过滤判定
     * @param string $tags
     */
    public function setMessageTags(string $tags)
    {
    }

    public function getOriginMessageKeys()
    {
    }

    /**
     * 可以设置业务相关标识，用于消费处理判定，或消息追踪查询
     * @param string $keys
     */
    public function setMessageKeys(string $keys)
    {
    }

    public function getOriginDelayTimeLevel()
    {
    }

    /**
     * 消息延迟处理级别，不同级别对应不同延迟时间
     * @param int $delayTimeLevel second
     */
    public function setDelayTimeLevel(int $delayTimeLevel)
    {
    }

    /**
     * @return string
     */
    public function getOriginMessageBody()
    {
    }

    /**
     * Producer要发送的实际消息内容，以字节数组形式进行存储。Message消息有一定大小限制。
     * @param string $body
     */
    public function setMessageBody(string $body)
    {
    }

    public function getOriginMessageProperty(string $key)
    {
    }

    public function setMessageProperty($key, $value)
    {
    }
}
