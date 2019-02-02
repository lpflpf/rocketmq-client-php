#ifndef ROCKETMQ_CLIENT_PHP_PRODUCER_H_
#define ROCKETMQ_CLIENT_PHP_PRODUCER_H_
#include "common.h"
#include <rocketmq/DefaultMQProducer.h>

class Producer : public Php::Base
{
    private:
        rocketmq::DefaultMQProducer *producer;

    public:
        Producer() { }

        virtual ~Producer() { }

        void __construct(Php::Parameters &param);

        void setInstanceName(Php::Parameters &param);
        Php::Value getInstanceName();

        void setNamesrvAddr(Php::Parameters &param);
        Php::Value getNamesrvAddr();

        Php::Value getNamesrvDomain();
        void setNamesrvDomain(Php::Parameters &param);

        Php::Value getTopicMessageQueueInfo(Php::Parameters &param);

        Php::Value getMQClientId();

        void setGroupName(Php::Parameters &param);
        Php::Value getGroupName();

        void start();

        Php::Value send(Php::Parameters &params);

        void setSessionCredentials(Php::Parameters &param);
        Php::Value getSessionCredentials();

        Php::Value getRetryTimes();
        void setRetryTimes(Php::Parameters &param);

        //int getSendMsgTimeout() const;
        Php::Value getSendMsgTimeout();

        //void setSendMsgTimeout(int sendMsgTimeout);
        void setSendMsgTimeout(Php::Parameters &param);

        //int getCompressMsgBodyOverHowmuch() const;
        Php::Value getCompressMsgBodyOverHowmuch();
        //void setCompressMsgBodyOverHowmuch(int compressMsgBodyOverHowmuch);
        void setCompressMsgBodyOverHowmuch(Php::Parameters &param);

        //int getCompressLevel() const;
        Php::Value getCompressLevel();
        //void setCompressLevel(int compressLevel);
        void setCompressLevel(Php::Parameters &param);

        //int getMaxMessageSize() const;
        Php::Value getMaxMessageSize();
        //void setMaxMessageSize(int maxMessageSize);
        void setMaxMessageSize(Php::Parameters &param);

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

        virtual void __destruct(){
            if (this->producer != nullptr){
                producer->shutdown();
                delete(this->producer);
            }
        }
};

void registerProducer(Php::Namespace &rocketMQNamespace);

#endif
