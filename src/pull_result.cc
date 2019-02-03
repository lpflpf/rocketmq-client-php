#include "pull_result.h"		
#include "pull_result_iterator.h"

Php::Value PullResult::getMessage(Php::Parameters &param){
    Php::Value idx_val = param[0];
    int idx = idx_val;

    if (idx < (int)this->result.msgFoundList.size()){
        Php::Value msg(Php::Object(MESSAGE_EXT_CLASS_NAME, new MessageExt(this->result.msgFoundList[idx])));
        return msg;
    }
    return nullptr;
}

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

long PullResult::count() { 
    return this->result.msgFoundList.size();
}

Php::Iterator* PullResult::getIterator(){
    return new PullResultIterator(this, this->result.msgFoundList);
}

void registerPullResult(Php::Namespace &rocketMQNamespace){
    Php::Class<PullResult> pullResultClass("PullResult");

    pullResultClass.method<&PullResult::getMessage>("getMessage", { Php::ByVal("index", Php::Type::Numeric), });
    pullResultClass.method<&PullResult::getPullStatus>("getPullStatus");
    pullResultClass.method<&PullResult::getNextBeginOffset>("getNextBeginOffset");
    pullResultClass.method<&PullResult::getMinOffset>("getMinOffset");
    pullResultClass.method<&PullResult::getMaxOffset>("getMaxOffset");

    rocketMQNamespace.add(pullResultClass);
}
