CPP             = g++
RM              = rm -f
CPP_FLAGS       = -Wall -c -I. -O2 -std=c++11

#Edit these lines to correspond with your own directories
LIBRARY_DIR		= `php-config --extension-dir` 

LD              = g++
LD_FLAGS        = -Wall -shared -O2
RESULT          = rocketmq.so

SOURCES			= $(wildcard *.cpp)
OBJECTS         = $(SOURCES:%.cpp=%.o)

all:	${OBJECTS} ${RESULT}

${RESULT}: ${OBJECTS}
		${LD} ${LD_FLAGS} -o $@ ${OBJECTS} -lphpcpp -lrocketmq  -lz -lcurl -lpthread

clean:
		${RM} *.obj *~* ${OBJECTS} ${RESULT}

${OBJECTS}: 
		${CPP} ${CPP_FLAGS} -fpic -o $@ ${@:%.o=%.cpp}

install:
		cp -f ${RESULT} ${LIBRARY_DIR}
#		cp -f ${PHPINIFILE}	${PHP_CONFIG_DIR}
