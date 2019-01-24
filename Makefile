CPP             = g++
RM              = rm -f
CPP_FLAGS       = -Wall -c -I. -O2 -std=c++11

LIBRARY_DIR		= `php-config --extension-dir` 

LD              = g++
LD_FLAGS        = -Wall -shared -O2
RESULT          = rocketmq.so

DIR_SRC         = ./src

SOURCES			= $(wildcard ${DIR_SRC}/*.cc)
OBJECTS         = $(SOURCES:%.cc=%.o)

all:	${OBJECTS} ${RESULT}

${RESULT}: ${OBJECTS}
		${LD} ${LD_FLAGS} -o $@ ${OBJECTS} -lphpcpp -lrocketmq  -lz -lcurl -lpthread


${OBJECTS}: 
		${CPP} ${CPP_FLAGS} -fpic -o $@ ${@:%.o=%.cc}

install:
		cp -f ${RESULT} ${LIBRARY_DIR}

clean:
		${RM} *.obj *~* ${OBJECTS} ${RESULT}
