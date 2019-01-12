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

## Example 

### Producer Example

```php
namespace RocketMQ;

$groupName = "testGroupName";
$instanceName = "testInstanceName";
$namesrvAddr = "127.0.0.1:9876";
$topic = "TestTopic";
$tag = "*";

$producer = new Producer($groupName);
$producer->setInstanceName($instanceName);
$producer->setNamesrvAddr($namesrvAddr);
$producer->start();
for ($i = 0;$i < 10000; $i ++){
	$producer->push($topic, $tag, "hello world $i");
	echo "push message $i" . "\n";
}
```

## [Usage](https://github.com/lpflpf/rocketmq-client-php/wiki/Usage)
