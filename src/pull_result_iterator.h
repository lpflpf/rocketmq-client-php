#ifndef ROCKETMQ_CLIENT_PHP_PULL_RESULT_ITERATOR_H_
#define ROCKETMQ_CLIENT_PHP_PULL_RESULT_ITERATOR_H_

#include <phpcpp.h>
#include "pull_result.h"

class PullResultIterator : public Php::Iterator
{
    private:
        std::vector<rocketmq::MQMessageExt> &_vec;
        std::vector<rocketmq::MQMessageExt>::const_iterator _iter;
    public :
        PullResultIterator(PullResult *obj, std::vector<rocketmq::MQMessageExt> &vec)
            : Php::Iterator(obj), _vec(vec), _iter(vec.begin()) { }

        virtual ~PullResultIterator(){}

        virtual bool valid(){
            return this->_iter != this->_vec.end();
        }

        Php::Value key(){
            return this->_iter - this->_vec.begin();
        }

        void rewind(){
            this-> _iter = this->_vec.begin();
        }

        void next(){
            this->_iter ++;
        }

        Php::Value current(){
            return Php::Object(MESSAGE_EXT_CLASS_NAME, new MessageExt(*_iter));
        }
};

#endif
