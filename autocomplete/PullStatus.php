<?php

namespace RocketMQ;

class PullStatus{
	const FOUND = 0;
	const NO_METCHED_MSG = 1;
	const OFFSET_ILLEGAL = 2;
	const BROKER_TIMEOUT = 3;
	const NO_NEW_MSG = 4;
}
