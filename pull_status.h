#ifndef ROCKETMQ_CLIENT_PHP_PULL_STATUS_H
#define ROCKETMQ_CLIENT_PHP_PULL_STATUS_H

#include "common.h"

class PullStatus : public Php::Base
{
	//  FOUND,
	//  NO_NEW_MSG,
	//  NO_MATCHED_MSG,
	//  OFFSET_ILLEGAL,
	//  BROKER_TIMEOUT  // indicate pull request timeout or received NULL response
};

void registerPullStatus(Php::Namespace &rocketMQNamespace){
		// class PullStatus
		Php::Class<PullStatus> pullStatusClass("PullStatus");
		pullStatusClass.constant("FOUND", (int)rocketmq::FOUND);
		pullStatusClass.constant("NO_MATCHED_MSG", (int)rocketmq::NO_MATCHED_MSG);
		pullStatusClass.constant("OFFSET_ILLEGAL", (int)rocketmq::OFFSET_ILLEGAL);
		pullStatusClass.constant("BROKER_TIMEOUT", (int)rocketmq::BROKER_TIMEOUT);
		pullStatusClass.constant("NO_NEW_MSG", (int)rocketmq::NO_NEW_MSG);

		rocketMQNamespace.add(pullStatusClass);
}
#endif
