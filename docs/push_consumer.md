---
layout: default
---

## RocketMQ::PushConsumer
```php
class PushConsumer {
	public function __construct()
	public function doRebalance()
	public function persistConsumerOffset()
	public function persistConsumerOffsetByResetOffset()
	public function setNamesrvDomain($nameserver)
	public function setInstanceName($groupName)
	public function setTryLockTimeout($tryLockTimeout)
	public function setConnectTimeout($connectTimeout)
	public function setThreadCount($threadCount)
	public function setListenerType(int $listenerType)
	public function getConsumeType()
	public function getConsumeFromWhere()
	public function setConsumeFromWhere(int $setConsumeFromWhere)
	public function subscribe(string $topic, string $tag);
	public function start()
	public function shutdown()
	public function setCallback(Callable $callback);
}
```
