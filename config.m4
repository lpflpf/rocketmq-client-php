PHP_ARG_ENABLE([rocketmq_client_php],
  [whether to enable rocketmq_client_php support],
  [AS_HELP_STRING([--enable-rocketmq_client_php],
    [Enable rocketmq_client_php support])],
  [no])

if test "$PHP_ROCKETMQ_CLIENT_PHP" != "no"; then
  AC_DEFINE(HAVE_ROCKETMQ_CLIENT_PHP, 1, [ Have rocketmq_client_php support ])



  CPPFLAGS="-lrocketmq -g -O0"
  dnl PHP_ADD_LIBRARY_WITH_PATH(rocketmq, /usr/local/lib, ROCKETMQ_SHARED_LIBADD)
  dnl PHP_ADD_LIBRARY(rocketmq)
  dnl PHP_SUBST(ROCKETMQ_SHARED_LIBADD)
  dnl PHP_NEW_EXTENSION(rocketmq_client_php, rocketmq_client_php.c message.c message_ext.c send_result.c producer.c batch_message.c mq_exception.c common.c message_queues.c, $ext_shared)
  PHP_ADD_EXTENSION_DEP(rocketmq_client_php, spl, true)
  PHP_NEW_EXTENSION(rocketmq_client_php, *.c, $ext_shared)
fi
