#include "stdafx.h"
#include "socket.hpp"

WebSocketManager::WebSocketManager() {}

WebSocketManager::~WebSocketManager() {
    Stop();
}

void WebSocketManager::Start() {
    if (m_server) return; 

    m_server = std::make_unique<ix::WebSocketServer>(8080, "0.0.0.0");

    m_server->setOnClientMessageCallback([this](std::shared_ptr<ix::ConnectionState> connectionState, ix::WebSocket& webSocket, const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            try {
                nlohmann::json message = nlohmann::json::parse(msg->str);
                // OutputDebugStringA(("[vTEFS] websocket message:\n" + msg->str).c_str());
                Dispatch(message["event"], message["payload"]);
            }
            catch (...) {
                OutputDebugStringA("[vTEFS] websocket message in incorrect format\n");
            }
            
            // echo
            // webSocket.send(msg->str);
        }
    });

    auto res = m_server->listen();
    if (res.first) {
        m_server->start();
    }
    else {
        m_server.reset();
    }
}

void WebSocketManager::Stop() {
    if (m_server) {
        m_server->stop();
        m_server.reset();
    }
}

void WebSocketManager::BroadcastEvent(std::string eventName, std::string payload) {
    if (!m_server) return;

    nlohmann::json message;

    message["event"] = eventName;
    message["payload"] = payload;
    for (auto&& client : m_server->getClients()) {
        if (client->getReadyState() == ix::ReadyState::Open) {
            client->send(message.dump());
        }
    }
}

void WebSocketManager::Subscribe(const std::string& eventType, std::function<void(const std::string& payload)> callback) {
    std::lock_guard<std::mutex> lock(m_subscribersMutex);
    m_subscribers[eventType].push_back(callback);
}

void WebSocketManager::Dispatch(const std::string& eventType, const std::string& payload) {
    std::lock_guard<std::mutex> lock(m_subscribersMutex);
    auto it = m_subscribers.find(eventType);
    if (it != m_subscribers.end()) {
        for (const auto& callback : it->second) {
            callback(payload);
        }
    }
}