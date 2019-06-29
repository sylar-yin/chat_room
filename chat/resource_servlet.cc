#include "resource_servlet.h"
#include "sylar/log.h"
#include <iostream>
#include <fstream>

namespace sylar {
namespace http {

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

ResourceServlet::ResourceServlet(const std::string& path)
    :Servlet("ResourceServlet")
    ,m_path(path) {
}

int32_t ResourceServlet::handle(sylar::http::HttpRequest::ptr request
                           , sylar::http::HttpResponse::ptr response
                           , sylar::http::HttpSession::ptr session) {
    auto path = m_path + "/" + request->getPath();
    SYLAR_LOG_INFO(g_logger) << "handle path=" << path;
    if(path.find("..") != std::string::npos) {
        response->setBody("invalid path");
        response->setStatus(sylar::http::HttpStatus::NOT_FOUND);
        return 0;
    } 
    std::ifstream ifs(path);
    if(!ifs) {
        response->setBody("invalid file");
        response->setStatus(sylar::http::HttpStatus::NOT_FOUND);
        return 0;
    }

    std::stringstream ss;
    std::string line;
    while(std::getline(ifs, line)) {
        //SYLAR_LOG_INFO(g_logger) << line;
        ss << line << std::endl;
    }

    response->setBody(ss.str());
    response->setHeader("content-type", "text/html;charset=utf-8");
    return 0;
}

}
}
