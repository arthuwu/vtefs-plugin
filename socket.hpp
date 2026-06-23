#pragma once
#include <memory>
#include <string>
#include <mutex>
#include <vector>
#include <ixwebsocket/IXWebSocketServer.h>
#include <nlohmann/json.hpp>

class WebSocketManager {
public:
    WebSocketManager();
    ~WebSocketManager();

    void Start();
    void Stop();
    void BroadcastEvent(std::string eventName, std::string payload);
    void Subscribe(const std::string& eventType, std::function<void(const std::string& payload)> callback);

private:
    std::unique_ptr<ix::WebSocketServer> m_server;

    std::mutex m_subscribersMutex;
    std::map<std::string, std::vector<std::function<void(const std::string& payload)>>> m_subscribers;

    void Dispatch(const std::string& eventType, const std::string& payload);
};