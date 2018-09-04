//
// Created by onter on 18-9-4.
//

#ifndef EXAMPLES_CODEC_H
#define EXAMPLES_CODEC_H

#include <muduo/base/Types.h>
#include <muduo/net/Buffer.h>

#include <boost/noncopyable.hpp>

namespace pubsub
{
    using muduo::string;
    enum ParseResult
    {
        kError,
        kSuccess,
        kContinue,
    };
    ParseResult parseMessage(muduo::net::Buffer* buf,
                             string * cmd,
                             string * topic,
                             string * content);
}



#endif //EXAMPLES_CODEC_H
