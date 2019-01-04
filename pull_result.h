#ifndef ROCKETMQ_CLIENT_PHP_PULL_RESULT_H
#define ROCKETMQ_CLIENT_PHP_PULL_RESULT_H

#include <rocketmq/PullResult.h>
#include <phpcpp.h>
#include "message.h"

class PullResult:public Php::Base {
	private:
		rocketmq::PullResult *result;
		int64_t position = 0;
	public :
		PullResult(rocketmq::PullResult *result);

		Php::Value getPullStatus();

		Php::Value getNextBeginOffset();

		Php::Value getMinOffset();

		Php::Value getMaxOffset();

		Php::Value current();

		void rewind();

		Php::Value key();

		void next();

		Php::Value valid();
};
#endif
