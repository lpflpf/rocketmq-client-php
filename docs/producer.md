---
layout: default
---

## RocketMQ::Producer
```php
class Producer {
    public function __construct($groupName)
    public function getInstanceName()
    public function setInstanceName($instanceName)
    public function setNamesrvDomain($nameserver)
    public function getSessionCredentials()
    public function setSessionCredentials($accessKey, $secretKey, $authChannel)
    public function getGroupName()
    public function setGroupName($groupName)
    public function setNamesrvAddr($nameaddr)
    public function getNamesrvAddr()
    public function start()
    public function push($topic, $tag, $body)
}
```

[back](./)
