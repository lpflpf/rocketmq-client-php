<?php

namespace RocketMQ;

class SendStatus{
    const SEND_OK = 0;
    const SEND_FLUSH_DISK_TIMEOUT = 1;
    const SEND_FLUSH_SLAVE_TIMEOUT = 2;
    const SEND_SLAVE_NOT_AVAILABLE = 3;
}
