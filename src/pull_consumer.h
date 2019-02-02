#ifndef ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H_
#define ROCKETMQ_CLIENT_PHP_PULL_CONSUMER_H_

#include "common.h"
#include <rocketmq/DefaultMQPullConsumer.h>
#include "message.h"
#include "message_queue.h"


class PullConsumer:public Php::Base
{
    private:
        std::string topicName;
        rocketmq::DefaultMQPullConsumer *consumer;
        std::vector<rocketmq::MQMessageQueue> mqs;
    public:
        PullConsumer(){
            this->consumer = nullptr;
        }
        virtual ~PullConsumer(){
            if (nullptr != this->consumer){
                delete(this->consumer);
            }
        }
        virtual void __construct(Php::Parameters &params);

        void start();

        Php::Value getQueues();

        Php::Value getNamesrvDomain();
        void setNamesrvDomain(Php::Parameters &param);

        Php::Value getNamesrvAddr();
        void setNamesrvAddr(Php::Parameters &param);

        void setInstanceName(Php::Parameters &param);

        void setTopic(Php::Parameters &param);

        void setGroup(Php::Parameters &param);

        Php::Value pull(Php::Parameters &param);
        Php::Value pullBlockIfNotFound(Php::Parameters &param);

        void setSessionCredentials(Php::Parameters &param);
        Php::Value getSessionCredentials();

        void updateConsumeOffset(Php::Parameters &params);
        void removeConsumeOffset(Php::Parameters &params);

        Php::Value fetchConsumeOffset(Php::Parameters &params);

        Php::Value getMessageModel();
        void setMessageModel(Php::Parameters &params);

        // void setTcpTransportPullThreadNum(int num);
        void setTcpTransportPullThreadNum(Php::Parameters &param);

        // const int getTcpTransportPullThreadNum() const;
        Php::Value getTcpTransportPullThreadNum();

        // void setTcpTransportConnectTimeout(uint64_t timeout);  // ms
        void setTcpTransportConnectTimeout(Php::Parameters &param);
        // const uint64_t getTcpTransportConnectTimeout() const;
        Php::Value getTcpTransportConnectTimeout();

        // void setTcpTransportTryLockTimeout(uint64_t timeout);  // ms
        void setTcpTransportTryLockTimeout(Php::Parameters &param);
        // const uint64_t getTcpTransportConnectTimeout() const;
        Php::Value getTcpTransportTryLockTimeout();

        //void setUnitName(std::string unitName);
        void setUnitName(Php::Parameters &param);
        //const std::string& getUnitName();
        Php::Value getUnitName();


};

void registerPullConsumer(Php::Namespace &rocketMQNamespace);

#endif
