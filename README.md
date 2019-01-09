# rocketmq-client-php

A Php Client for Apache RocketMQ.

# dependence
* [rocketmq-client-cpp](https://github.com/apache/rocketmq-client-cpp)
* [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP)
* linux environment.
* php7

## INSTALL
1. install rocketmq-client-cpp
2. install php-cpp
3. download rocketmq-client-php  
```shell
    git clone https://github.com/lpflpf/rocketmq-client-php;
    cd rocketmq-client-php;
    make && make install
```
4. update php.ini file, add line `extension=rocketmq.so`;
5. try to run example in example directory.


## Interface 

### Producer
   - __construct($groupName)
   - getInstanceName()
   - setInstanceName($instanceName)
   - setNamesrvDomain($nameserver)
   - getSessionCredentials()
   - setSessionCredentials($accessKey, $secretKey, $authChannel)
   - getGroupName()
   - setGroupName($groupName)
   - setNamesrvAddr($nameaddr)
   - getNamesrvAddr()
   - start()
   - push($topic, $tag, $body)

### PullConsumer
   - setInstanceName
   - setNamesrvDomain
   - setTopic
   - start
   - getQueues

### PushConsumer
   - setNamesrvDomain
   - setInstanceName
   - setTryLockTimeout
   - setConnectTimeout
   - setThreadCount
   - setListenerType
   - subscribe
   - start
   - shutdown
   - setCallback

### PullResult
   - getCount
   - getMessage
   - getPullStatus
   - getNextBeginOffset
   - getMinOffset
   - getMaxOffset 

### ConsumeStatus
   - CONSUME_SUCCESS
   - RECONSUME_LATER

### ConsumeType
   - CONSUME_ACTIVELY
   - CONSUME_PASSIVELY

### ConsumeFromWhere
   - CONSUME_FROM_LAST_OFFSET
   - CONSUME_FROM_LAST_OFFSET_AND_FROM_MIN_WHEN_BOOT_FIRST  (@Deprecated)
   - CONSUME_FROM_MIN_OFFSET (@Deprecated)
   - CONSUME_FROM_MAX_OFFSET (@Deprecated)
   - CONSUME_FROM_FIRST_OFFSET
   - CONSUME_FROM_TIMESTAMP

### MessageModel
   - BROADCASTING
   - CLUSTERING

### Message
   - toString()
   - getQueueId()
   - getBornTimestamp()
   - getBornHost()
   - getBornHostString()
   - getBornHostNameString()
   - getStoreTimestamp()
   - getStoreHost()
   - getStoreHostString()
   - getMsgId()
   - getOffsetMsgId()
   - getBodyCRC()
   - getQueueOffset()
   - getStoreSize()
   - getReconsumeTimes()
   - getPreparedTransactionOffset()
   - getProperty($name)
   - getTopic()
   - getTags()
   - getKeys()
   - getDelayTimeLevel()
   - getFlag()
   - getSysFlag()
   - getBody()

### MessageQueue
   - getMessageQueueOffset()
   - setMessageQueueOffset($offset)
   - pull($tag, $size = 32)

### MessageListenerType
   - messageListenerDefaultly
   - messageListenerOrderly
   - messageListenerConcurrently

### PullStatus
   - FOUND
   - NO_NEW_MSG
   - NO_MATCH_MSG
   - OFFSET_ILLEGAL
   - BROKER_TIMEOUT

### SessionCredentials
   - __construct($accessKey, $secretKey, $authChannel)
   - __destruct()
   - getAccessKey()
   - setAccessKey($accessKey)
   - getSecretKey()
   - setSecretKey($secretKey)
   - getSignature()
   - setSignature($signature)
   - getSignatureMethod()
   - setSignatureMethod($signatureMethod)
   - getAuthChannel()
   - setAuthChannel($authChannel)
   - isvalid()

