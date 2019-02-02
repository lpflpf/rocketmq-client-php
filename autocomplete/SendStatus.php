<?php

namespace RocketMQ;

class SendStatus{
    const SEND_OK;
    const SEND_FLUSH_DISK_TIMEOUT;
    const SEND_FLUSH_SLAVE_TIMEOUT;
    const SEND_SLAVE_NOT_AVAILABLE;
}
