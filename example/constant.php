<?php
namespace RocketMQ;

echo "\n";
echo "ConsumeFromWhere::LAST_OFFSET: " . ConsumeFromWhere::LAST_OFFSET . "\n";
echo "ConsumeFromWhere::LAST_OFFSET_AND_FROM_MIN_WHEN_BOOT_FIRST: " . ConsumeFromWhere::LAST_OFFSET_AND_FROM_MIN_WHEN_BOOT_FIRST . "\n";
echo "ConsumeFromWhere::MIN_OFFSET: " . ConsumeFromWhere::MIN_OFFSET . "\n";
echo "ConsumeFromWhere::MAX_OFFSET: " . ConsumeFromWhere::MAX_OFFSET . "\n";
echo "ConsumeFromWhere::FIRST_OFFSET: " . ConsumeFromWhere::FIRST_OFFSET . "\n";
echo "ConsumeFromWhere::TIMESTAMP: " . ConsumeFromWhere::TIMESTAMP . "\n";

echo "\n";
echo "ConsumeStatus::CONSUME_SUCCESS: " . ConsumeStatus::CONSUME_SUCCESS . "\n";
echo "ConsumeStatus::RECONSUME_LATER: " . ConsumeStatus::RECONSUME_LATER . "\n";

echo "\n";
echo "ELogLevel::FATAL: " . ELogLevel::FATAL . "\n";
echo "ELogLevel::ERROR: " . ELogLevel::ERROR . "\n";
echo "ELogLevel::WARN: " . ELogLevel::WARN . "\n";
echo "ELogLevel::INFO: " . ELogLevel::INFO . "\n";
echo "ELogLevel::DEBUG: " . ELogLevel::DEBUG . "\n";
echo "ELogLevel::TRACE: " . ELogLevel::TRACE . "\n";
echo "ELogLevel::LEVEL_NUM: " . ELogLevel::LEVEL_NUM . "\n";

echo "\n";
echo "MessageModel::BROADCASTING: " .MessageModel::BROADCASTING . "\n";
echo "MessageModel::CLUSTERING: " . MessageModel::CLUSTERING . "\n";

echo "\n";
echo "PullStatus::FOUND: " . PullStatus::FOUND . "\n";
echo "PullStatus::NO_MATCHED_MSG: " . PullStatus::NO_MATCHED_MSG . "\n";
echo "PullStatus::OFFSET_ILLEGAL: " . PullStatus::OFFSET_ILLEGAL . "\n";
echo "PullStatus::BROKER_TIMEOUT: " . PullStatus::BROKER_TIMEOUT . "\n";
echo "PullStatus::NO_NEW_MSG: " . PullStatus::NO_NEW_MSG . "\n";

echo "\n";
echo "SendStatus::OK: " . SendStatus::OK . "\n";
echo "SendStatus::FLUSH_DISK_TIMEOUT: " . SendStatus::FLUSH_DISK_TIMEOUT . "\n";
echo "SendStatus::FLUSH_SLAVE_TIMEOUT: " . SendStatus::FLUSH_SLAVE_TIMEOUT . "\n";
echo "SendStatus::SLAVE_NOT_AVAILABLE: " . SendStatus::SLAVE_NOT_AVAILABLE . "\n";

echo "\n";
echo "TraceModel::OPEN: " . TraceModel::OPEN . "\n";
echo "TraceModel::CLOSE: " . TraceModel::CLOSE. "\n";

echo "\n";
echo "TransactionStatus::COMMIT: " . TransactionStatus::COMMIT . "\n";
echo "TransactionStatus::ROLLBACK: " . TransactionStatus::ROLLBACK . "\n";
echo "TransactionStatus::UNKNOWN: " . TransactionStatus::UNKNOWN. "\n";