FROM centos

WORKDIR /root/

RUN buildDeps="gcc-c++ cmake automake autoconf libtool bzip2-devel wget tar unzip make zlib-devel" \
    && yum install -y $buildDeps \
    && mkdir -p /root/rocketmq-cpp/ \
    && wget -O rocketmq.tar.gz 'https://github.com/apache/rocketmq-client-cpp/archive/1.2.2.tar.gz' \
    && tar xvf rocketmq.tar.gz -C /root/rocketmq-cpp/ --strip-components=1 \
    && cd /root/rocketmq-cpp/ \
    && sh build.sh \
    && yum clean all \
    && mkdir -p /usr/include/rocketmq \
    && cp /root/rocketmq-cpp/bin/librocketmq.* /usr/lib64/ -rf \
    && cp /root/rocketmq-cpp/include/* /usr/include/rocketmq/ -rf \
    && cp /root/rocketmq-cpp/bin/include/* /usr/include/ -rf \
    && cp /root/rocketmq-cpp/bin/lib/* /usr/lib64/ -rf \
    && rm -rf /root/rocketmq*
