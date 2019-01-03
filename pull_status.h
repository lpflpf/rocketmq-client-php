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

#endif
