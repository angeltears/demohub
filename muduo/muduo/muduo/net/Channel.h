//
// Created by onter on 18-8-21.
//

#ifndef MUDUO_CHANNEL_HPP
#define MUDUO_CHANNEL_HPP


#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "../base/Timestamp.h"
namespace jmuduo
{
    namespace net
    {
        class EventLoop;

        /**
         * a selectable I/O channel
         *
         * this class doesn't own the file descriptor
         * the file descriptor could be a socket
         **/
        class Channel : boost::noncopyable
        {
        public:
            typedef boost::function<void()> EventCallback;
            typedef boost::function<void(Timestamp)> ReadEventCallback;

            Channel(EventLoop* loop, int fd);
            ~Channel();

            void handleEvent(Timestamp receiveTime);
            void setReadCallback(const ReadEventCallback& cb)
            { readCallback_ = cb; }
            void setWriteCallback(const EventCallback& cb)
            { writeCallback_ = cb; }
            void setCloseCallback(const EventCallback& cb)
            { closeCallback_ = cb; }
            void setErrorCallback(const EventCallback& cb)
            { errorCallback_ = cb; }
#ifdef __GXX_EXPERIMENTAL_CXX0X__               /// use c11 to reduce copy cost
            void setReadCallback(ReadEventCallback&& cb)
            { readCallback_ = std::move(cb); }
            void setWriteCallback(EventCallback&& cb)
            { writeCallback_ = std::move(cb); }
            void setCloseCallback(EventCallback&& cb)
            { closeCallback_ = std::move(cb); }
            void setErrorCallback(EventCallback&& cb)
            { errorCallback_ = std::move(cb); }
#endif

            /// Tie this channel to the owner object managed by shared_ptr,
            /// prevent the owner object being destroyed in handleEvent.
            void tie(const boost::shared_ptr<void>&);
            int fd() const
            { return fd_; }
            int events() const
            { return events_; }
            void set_revents(int revt)        /// used by pollers
            { revents_ = revt; }
            bool isNoneEvent() const
            { return events_ == kNoneEvent; }

            void enableReading()
            { events_ |= kReadEvent; update(); }
            void disableReading()
            { events_ &= ~kReadEvent; update(); }
            void enableWriting()
            { events_ |= kWriteEvent; update(); }
            void disableWriting()
            { events_ &= ~kWriteEvent; update(); }
            void disableAll()
            { events_ = kNoneEvent; update(); }
            bool isWriting() const
            { return events_ & kWriteEvent; }
            bool isReading() const
            { return events_ & kReadEvent; }

            /// for Poller
            int index()
            { return index_; }
            void set_index(int idx)
            { index_ = idx; }

            /// for debug
            string reventsToString() const;
            string eventToString() const;

            void doNotLogHup()
            { logHup_ = false; }
            EventLoop* ownerLoop()
            { return loop_; }

            void remove();
        private:
            static string eventsToString(int fd, int ev);

            void update();
            void handleEvnetWithGuard(Timestamp receiveTime);
            static const int kNoneEvent;   /// nothing flag
            static const int kReadEvent;   /// read event flag
            static const int kWriteEvent;  /// write event flag

            EventLoop* loop_;   /// has the eventloop pointer to callback funciton
            const int  fd_;
            int        events_;
            int        revents_;      /// it's the received event types of epoll or epoll
            int        index_;         ///  will be user in fds_(Poller)
            bool       logHup_;

            boost::weak_ptr<void> tie_;
            bool tied_;
            bool eventHandling_;
            bool addedToLoop_;
            ReadEventCallback   readCallback_;
            EventCallback       writeCallback_;
            EventCallback       closeCallback_;
            EventCallback       errorCallback_;
        };
    }
}


#endif //MUDUO_CHANNEL_HPP
