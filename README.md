# rocketmq-client-php

A Php Client for Apache RocketMQ.

# dependence
* [rocketmq-client-cpp](https://github.com/apache/rocketmq-client-cpp)
* [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP)
* linux environment.
* >= php7

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
   - setInstanceName
   - setNamesrvDomain
   - start
   - push
