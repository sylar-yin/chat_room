#ifndef __CHAT_CHAT_SERVLET_H__
#define __CHAT_CHAT_SERVLET_H__

#include "sylar/http/ws_servlet.h"

namespace chat {

class ChatWSServlet : public sylar::http::WSServlet {
public:
    typedef std::shared_ptr<ChatWSServlet> ptr;
    ChatWSServlet();
    virtual int32_t onConnect(sylar::http::HttpRequest::ptr header
                              ,sylar::http::WSSession::ptr session) override;
    virtual int32_t onClose(sylar::http::HttpRequest::ptr header
                             ,sylar::http::WSSession::ptr session) override;
    virtual int32_t handle(sylar::http::HttpRequest::ptr header
                           ,sylar::http::WSFrameMessage::ptr msg
                           ,sylar::http::WSSession::ptr session) override;
};

}

#endif
