
#ifndef ROCKETMQ_CLIENT_PHP_MESSAGE_H
#define ROCKETMQ_CLIENT_PHP_MESSAGE_H
#include<phpcpp.h>
#include<iostream>
#include<rocketmq/MQMessageExt.h>

class Message: public Php::Base {
	private:
		rocketmq::MQMessageExt message;
	public:
		virtual void __construct(){}
		virtual void __destruct(){}
		virtual ~Message(){}
		Message(rocketmq::MQMessageExt message){
			this->message = message;
		}

		Php::Value getQueueId(){
			return this->message.getQueueId();
		};
		Php::Value getBornTimestamp(){
			return (int64_t)this->message.getBornTimestamp();
		}
		Php::Value getBornHost(){
			return this->message.getBornHost().sa_data;
		}
		Php::Value getBornHostString(){
			return this->message.getBornHostString();
		}
		Php::Value getBornHostNameString(){
			return this->message.getBornHostNameString();
		}
		Php::Value getStoreTimestamp(){
			return (int64_t)this->message.getStoreTimestamp();
		}
		Php::Value getStoreHost(){
			return this->message.getStoreHost().sa_data;
		}
		Php::Value getStoreHostString(){
			return this->message.getStoreHostString();
		}
		Php::Value getMsgId(){
			return this->message.getMsgId();
		}
		Php::Value getOffsetMsgId(){
			return this->message.getOffsetMsgId();
		}
		Php::Value getBodyCRC(){
			return this->message.getBodyCRC();
		}
		Php::Value getQueueOffset(){
			return (int64_t)this->message.getQueueOffset();
		}
		Php::Value getCommitLogOffset(){
			return (int64_t)this->message.getCommitLogOffset();
		}
		Php::Value getStoreSize(){
			return this->message.getStoreSize();
		}
		Php::Value getReconsumeTimes(){
			return this->message.getReconsumeTimes();
		}
		Php::Value getPreparedTransactionOffset(){
			return (int64_t)this->message.getPreparedTransactionOffset();
		}

		Php::Value getProperty(Php::Parameters &param){
			Php::Value tmp = param[0];
			std::string name = tmp;
			return this->message.getProperty(name);
		}
		Php::Value getTopic(){
			return this->message.getTopic();
		}
		Php::Value getTags(){
			return this->message.getTags();
		}
		Php::Value getKeys(){
			return this->message.getKeys();
		}
		Php::Value getDelayTimeLevel(){
			return this->message.getDelayTimeLevel();
		}
		Php::Value getFlag(){
			return this->message.getFlag();
		}
		Php::Value getSysFlag(){
			return this->message.getSysFlag();
		}
		Php::Value getBody(){
			return this->message.getBody();
		}

		Php::Value toString();

};

#endif
