#include "pull_result.h"		

PullResult::PullResult(rocketmq::PullResult result){
    this->result = result;
}

Php::Value PullResult::getPullStatus(){
    return this->result.pullStatus;
}

Php::Value PullResult::getNextBeginOffset(){
    return (int64_t)this->result.nextBeginOffset;
}

Php::Value PullResult::getMinOffset(){
    return (int64_t)this->result.minOffset;
}

Php::Value PullResult::getMaxOffset(){
    return (int64_t)this->result.maxOffset;
}

void registerPullResult(Php::Namespace &rocketMQNamespace){
    Php::Class<PullResult> pullResultClass("PullResult");

    pullResultClass.method<&PullResult::getCount>("getCount");
    pullResultClass.method<&PullResult::getMessage>("getMessage", {
            Php::ByVal("index", Php::Type::Numeric),
            });
    pullResultClass.method<&PullResult::getPullStatus>("getPullStatus");
    pullResultClass.method<&PullResult::getNextBeginOffset>("getNextBeginOffset");
    pullResultClass.method<&PullResult::getMinOffset>("getMinOffset");
    pullResultClass.method<&PullResult::getMaxOffset>("getMaxOffset");

    rocketMQNamespace.add(pullResultClass);
}
