<?php

namespace RocketMQ;

class PullStatus{
	const FOUND;
	const NO_METCHED_MSG;
	const OFFSET_ILLEGAL;
	const BROKER_TIMEOUT;
	const NO_NEW_MSG;
}
