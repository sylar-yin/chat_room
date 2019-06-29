#include "my_module.h"
#include "sylar/config.h"
#include "sylar/log.h"
#include "sylar/application.h"
#include "sylar/http/ws_server.h"

#include "resource_servlet.h"
#include "chat_servlet.h"
#include "sylar/env.h"

namespace chat {

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

MyModule::MyModule()
    :sylar::Module("chat_room", "1.0", "") {
}

bool MyModule::onLoad() {
    SYLAR_LOG_INFO(g_logger) << "onLoad";
    return true;
}

bool MyModule::onUnload() {
    SYLAR_LOG_INFO(g_logger) << "onUnload";
    return true;
}

//static int32_t handle(sylar::http::HttpRequest::ptr request
//                       , sylar::http::HttpResponse::ptr response
//                       , sylar::http::HttpSession::ptr session) {
//    SYLAR_LOG_INFO(g_logger) << "handle";
//    response->setBody("handle");
//    return 0;
//}

bool MyModule::onServerReady() {
    SYLAR_LOG_INFO(g_logger) << "onServerReady";
    std::vector<sylar::TcpServer::ptr> svrs;
    if(!sylar::Application::GetInstance()->getServer("http", svrs)) {
        SYLAR_LOG_INFO(g_logger) << "no httpserver alive";
        return false;
    }

    for(auto& i : svrs) {
        sylar::http::HttpServer::ptr http_server =
            std::dynamic_pointer_cast<sylar::http::HttpServer>(i);
        if(!i) {
            continue;
        }
        auto slt_dispatch = http_server->getServletDispatch();

        sylar::http::ResourceServlet::ptr slt(new sylar::http::ResourceServlet(
                    sylar::EnvMgr::GetInstance()->getCwd()
        ));
        slt_dispatch->addGlobServlet("/html/*", slt);
        SYLAR_LOG_INFO(g_logger) << "addServlet";
    }

    svrs.clear();
    if(!sylar::Application::GetInstance()->getServer("ws", svrs)) {
        SYLAR_LOG_INFO(g_logger) << "no ws alive";
        return false;
    }

    for(auto& i : svrs) {
        sylar::http::WSServer::ptr ws_server =
            std::dynamic_pointer_cast<sylar::http::WSServer>(i);

        sylar::http::ServletDispatch::ptr slt_dispatch = ws_server->getWSServletDispatch();
        ChatWSServlet::ptr slt(new ChatWSServlet);
        slt_dispatch->addServlet("/sylar/chat", slt);
    }
    return true;
}


bool MyModule::onServerUp() {
    SYLAR_LOG_INFO(g_logger) << "onServerUp";
    return true;
}

}

extern "C" {

sylar::Module* CreateModule() {
    sylar::Module* module = new chat::MyModule;
    SYLAR_LOG_INFO(chat::g_logger) << "CreateModule " << module;
    return module;
}

void DestoryModule(sylar::Module* module) {
    SYLAR_LOG_INFO(chat::g_logger) << "CreateModule " << module;
    delete module;
}

}
