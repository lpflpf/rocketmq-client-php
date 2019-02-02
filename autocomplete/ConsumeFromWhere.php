<?php

namespace RocketMQ;

class ConsumeFromWhere {
	const CONSUME_FROM_LAST_OFFSET = 0;

	/**
	 * @deprecated
	 */

	const CONSUME_FROM_LAST_OFFSET_AND_FROM_MIN_WHEN_BOOT_FIRST = 1;

	const CONSUME_FROM_MIN_OFFSET = 2;
	const CONSUME_FROM_MAX_OFFSET = 3;

	const CONSUME_FROM_FIRST_OFFSET = 4;

	const CONSUME_FROM_TIMESTAMP = 5;

}
