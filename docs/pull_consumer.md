---
layout: default
---

## RocketMQ::PullConsumer
```php
class PullConsumer {
	public function __construct()
    public function setInstanceName($groupName)
	public function setNamesrvDomain($nameserver)
	public function setTopic($topic)
	public function start()
    /**
     * @return array(RocketMQ::MessageQueue)
     */
	public function getQueues()
}
```
