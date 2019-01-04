#include "pull_result.h"		

PullResult::PullResult(rocketmq::PullResult *result){
	this->result = result;
}

Php::Value PullResult::getPullStatus(){
	return this->result->pullStatus;
}

Php::Value PullResult::getNextBeginOffset(){
	return (int64_t)this->result->nextBeginOffset;
}

Php::Value PullResult::getMinOffset(){
	return (int64_t)this->result->minOffset;
}

Php::Value PullResult::getMaxOffset(){
	return (int64_t)this->result->maxOffset;
}

Php::Value PullResult::current(){
	return Php::Object("Message", new Message(this->result->msgFoundList[this->position]));
}

void PullResult::rewind(){
	this->position = 0;
}

Php::Value PullResult::key(){
	return this->position;
}

void PullResult::next(){
	this->position += 1;
}

Php::Value PullResult::valid(){
	return (unsigned int64_t)this->position < this->result->msgFoundList.size();
}

