#ifndef ROCKETMQ_CLIENT_PHP_PULL_RESULT_H_
#define ROCKETMQ_CLIENT_PHP_PULL_RESULT_H_

#include <rocketmq/PullResult.h>
#include <phpcpp.h>
#include "message_ext.h"
#define PULL_RESULT_CLASS_NAME   NAMESPACE_NAME"\\PullResult"

class PullResult: public Php::Base, public Php::Countable, public Php::Traversable
{
    private:
        rocketmq::PullResult result;
    public :
        ~PullResult(){ }
        PullResult(rocketmq::PullResult result);

        Php::Value getMessage(Php::Parameters &param);

        Php::Value getNextBeginOffset();

        Php::Value getMinOffset();

        Php::Value getMaxOffset();

        Php::Value getPullStatus();

        virtual long count() override;

        virtual Php::Iterator *getIterator() override;
};

void registerPullResult(Php::Namespace &rocketMQNamespace);
#endif
