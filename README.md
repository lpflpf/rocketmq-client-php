# rocketmq-client-php

rocketMQ 的php客户端

# 项目说明

* 使用 php7.3 进行开发 （php5版本暂未进行测试）
* 基于 [rocketmq-client-php](https://github.com/apache/rocketmq-client-cpp)、 [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP) 开发
* Linux 环境 (暂未windows 测试)
* 其他依赖请参考 rocketmq-client-php & php-cpp


## 功能说明
*  通过pull的方式进行消费，将偏移量保存在server端。
*  消费不会产生阻塞，若消费完成，则程序结束。  
*  使用方法，请参考example/目录下样例。

## 安装方法

1. 安装rocketmq-client-php lib, 将生成 librocketmq.so, 和相应的include 文件。
2. 安装php-cpp lib, 将生成 libphpcpp.so，和相应的include 文件。
3. 配置php-config。(Makefile 中使用了`php-config --extension-dir` 查找扩展安装目录)
4. 执行： `make && make install`
5.  修改php.ini 文件，增加  
	`extension=rocketmq.so`  
6. 完成
