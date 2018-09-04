//
// Created by onter on 18-8-31.
//

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>

using namespace muduo;
using namespace muduo::net;


const int kBufSize = 64*1024;
const char* g_file = NULL;

typedef boost::shared_ptr<FILE> FilePtr;

void onConnection(const TcpConnectionPtr& connection)
{
    FILE* fp = ::fopen(g_file, "rb");
    if (fp)
    {
        FilePtr ctx(fp, ::fclose);
        connection->setContext(ctx);
        char buf[kBufSize];
        size_t  nread = ::fread(buf, 1, sizeof buf, fp);
        connection->send(buf, nread);
    }
}

void onWriteComplete(const TcpConnectionPtr& connection)
{
    const FilePtr& fp = boost::any_cast<const FilePtr&>(connection->getContext());
    char buf[kBufSize];
    size_t nread = ::fread(buf,1, sizeof buf, get_pointer(fp));
    if (nread > 0)
    {
        connection->send(buf, nread);
    }
    else
    {
        connection->shutdown();
        LOG_INFO << "TcpServer -- done";
    }
}

int main(int argc, char* argv[])
{
    LOG_INFO << "pid = "<< getpid();
    if (argc > 1)
    {
        g_file = argv[1];

        EventLoop loop;
        InetAddress listenAddr(2021);
        TcpServer server(&loop, listenAddr, "FilerServer");
        server.setConnectionCallback(onConnection);
        server.setWriteCompleteCallback(onWriteComplete);
        server.start();
        loop.loop();
    }
}