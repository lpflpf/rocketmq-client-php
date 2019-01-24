#ifndef ROCKETMQ_CLIENT_PHP_PULL_RESULT_H
#define ROCKETMQ_CLIENT_PHP_PULL_RESULT_H

#include <rocketmq/PullResult.h>
#include <phpcpp.h>
#include "message_ext.h"
#define PULL_RESULT_CLASS_NAME   NAMESPACE_NAME"\\PullResult"

class PullResult: public Php::Base
{
    private:
        rocketmq::PullResult result;
        int64_t position = 0;
    public :
        ~PullResult(){ }
        PullResult(rocketmq::PullResult result);
        Php::Value getCount(){
            return (int64_t)this->result.msgFoundList.size();
        }

        Php::Value getMessage(Php::Parameters &param){
            Php::Value idx_val = param[0];
            int idx = idx_val;

            if (idx < (int)this->result.msgFoundList.size()){
                Php::Value msg(Php::Object(MESSAGE_EXT_CLASS_NAME, new MessageExt(this->result.msgFoundList[idx])));
                return msg;
            }
            return nullptr;
        }

        Php::Value getNextBeginOffset();

        Php::Value getMinOffset();

        Php::Value getMaxOffset();

        Php::Value getPullStatus();
};

void registerPullResult(Php::Namespace &rocketMQNamespace);
#endif
