#ifndef ROCKETMQ_CLIENT_PHP_PULL_RESULT_H
#define ROCKETMQ_CLIENT_PHP_PULL_RESULT_H

class PullResult:public Php::Base {
	private:
		rocketmq::PullResult *result;
		int64_t position = 0;
	public :
		PullResult(rocketmq::PullResult *result){
			this->result = result;
		}

		Php::Value getPullStatus(){
			return this->result->pullStatus;
		}

		Php::Value getNextBeginOffset(){
			return (int64_t)this->result->nextBeginOffset;
		}

		Php::Value getMinOffset(){
			return (int64_t)this->result->minOffset;
		}

		Php::Value getMaxOffset(){
			return (int64_t)this->result->maxOffset;
		}

		Php::Value current(){
			return Php::Object("Message", new Message(this->result->msgFoundList[this->position]));
		}

		void rewind(){
			this->position = 0;
		}

		Php::Value key(){
			return this->position;
		}

		void next(){
			this->position += 1;
		}

		Php::Value valid(){
			return (unsigned int64_t)this->position < this->result->msgFoundList.size();
		}
};
#endif
