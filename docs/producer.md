---
layout: default
---

## RocketMQ::Producer
```
class Producer {
    function __construct($groupName)
    function getInstanceName()
    function setInstanceName($instanceName)
    function setNamesrvDomain($nameserver)
    function getSessionCredentials()
    function setSessionCredentials($accessKey, $secretKey, $authChannel)
    function getGroupName()
    function setGroupName($groupName)
    function setNamesrvAddr($nameaddr)
    function getNamesrvAddr()
    function start()
    function push($topic, $tag, $body)
}
```

