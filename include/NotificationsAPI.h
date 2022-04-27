//
// Created by dawid on 22.04.22.
//

#pragma once

#include <sstream>

namespace mps {

    class NotificationsAPI {
        inline static const char *TAG = "NotificationsAPI";

        const int connect_timeout = 3; // in seconds

    public:
        bool connect(const std::string &service);

        bool disconnect(const std::string &service);

        std::string notify_clients(const std::string &service, const std::string &title, const std::string &body);

        std::string services(int client_id);

        std::string service_on(const std::string &service, int client_id, const std::string &firebase_token);

        std::string service_off(const std::string &service, int client_id);

        std::string services_off(int client_id);

        std::string update_firebase_token(int client_id, const std::string &firebase_token);

    private:
        [[nodiscard]] std::string get(const std::string &target, const std::string &params) const;

        [[nodiscard]] std::string post(const std::string &target, const std::string &params) const;
    };

} // mps
