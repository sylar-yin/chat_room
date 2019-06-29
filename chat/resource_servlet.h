#ifndef __SYLAR_HTTP_RESOURCE_SERVLET_H__
#define __SYLAR_HTTP_RESOURCE_SERVLET_H__

#include "sylar/http/servlet.h"

namespace sylar {
namespace http {

class ResourceServlet :public sylar::http::Servlet {
public:
    typedef std::shared_ptr<ResourceServlet> ptr;
    ResourceServlet(const std::string& path);
    virtual int32_t handle(sylar::http::HttpRequest::ptr request
                   , sylar::http::HttpResponse::ptr response
                   , sylar::http::HttpSession::ptr session) override;

private:
    std::string m_path;
};

}
}

#endif
