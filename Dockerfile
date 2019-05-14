FROM rocketmq-client-cpp:1.2.2 

WORKDIR /root/

RUN yum install -y libxml2-devel libcurl-devel which\
    && echo '185.85.0.29 www.php.net' >> /etc/hosts \
    && wget -O php.tar.gz 'https://www.php.net/distributions/php-7.1.29.tar.gz' \
    && mkdir /root/php/ /root/php-cpp/ /root/rocketmq-client-php\
    && tar xvf php.tar.gz -C /root/php/ --strip-components=1 \
    && cd /root/php \
    && ./configure --prefix=/usr/local/php/ && make && make install \
    && ln -s /usr/local/php/bin/php-config /usr/local/bin/ \
    && ln -s /usr/local/php/bin/php /usr/local/bin/ \
    && ln -s /usr/local/php/bin/phpize /usr/local/bin/ \
    && wget -O php-cpp.tar.gz https://github.com/CopernicaMarketingSoftware/PHP-CPP/archive/v2.1.4.tar.gz \
    && tar xvf php-cpp.tar.gz -C /root/php-cpp --strip-components=1 \
    && cd /root/php-cpp && make && make install \
    && wget -O /root/rocketmq-client-php.tar.gz 'https://github.com/lpflpf/rocketmq-client-php/archive/v0.1-beta.tar.gz' \
    && tar xvf /root/rocketmq-client-php.tar.gz -C /root/rocketmq-client-php --strip-components=1 \
    && cd /root/rocketmq-client-php/ \
    && make && make install \
    && cp /root/php/php.ini-development /usr/local/php/lib/php.ini \
    && echo "extension_dir=`/usr/local/php/bin/php-config --extension-dir`" >> /usr/local/php/lib/php.ini \
    && echo 'extension=rocketmq.so' >> /usr/local/php/lib/php.ini \
    && rm /root/php* /root/rocketmq* -rf
