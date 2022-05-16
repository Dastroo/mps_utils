//
// Created by dawid on 22.04.22.
//

#ifdef REDHAT
#include <json/writer.h>
#endif
#ifdef DEBIAN
#include <jsoncpp/json/writer.h>
#endif

#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <log_helper/Log.h>

#include "../include/ParameterBuilder.h"
#include "../include/NotificationsAPI.h"

namespace mps {

    bool NotificationsAPI::connect(const std::string &service) {
        Json::Value request;
        request["service"] = service;
        std::string params = Json::FastWriter().write(request);
        params.pop_back();
        return !post("/connect", params).empty();
    }

    bool NotificationsAPI::disconnect(const std::string &service) {
        Json::Value request;
        request["service"] = service;
        std::string params = Json::FastWriter().write(request);
        params.pop_back();
        return !post("/disconnect", params).empty();
    }

    std::string
    NotificationsAPI::notify_clients(const std::string &service, const std::string &title, const std::string &body) {
        Json::Value request;
        request["service"] = service;
        request["title"] = title;
        request["body"] = body;
        return post("/notify_clients", Json::FastWriter().write(request));
    }

    std::string NotificationsAPI::services(int client_id) {
        ParameterBuilder builder;
        builder.add_param("client_id", client_id);
        return get("/services", builder.build());
    }

    std::string
    NotificationsAPI::service_on(const std::string &service, int client_id, const std::string &firebase_token) {
        Json::Value jv;
        jv["client_id"] = client_id;
        jv["service"] = service;
        jv["firebase_token"] = firebase_token;
        std::string params = Json::FastWriter().write(jv);
        params.pop_back();
        return post("/service_on", params);
    }

    std::string NotificationsAPI::service_off(const std::string &service, int client_id) {
        Json::Value jv;
        jv["client_id"] = client_id;
        jv["service"] = service;
        std::string params = Json::FastWriter().write(jv);
        params.pop_back();
        return post("/service_off", params);
    }

    std::string NotificationsAPI::services_off(int client_id) {
        Json::Value jv;
        jv["client_id"] = client_id;
        std::string params = Json::FastWriter().write(jv);
        params.pop_back();
        return post("/services_off", params);
    }

    std::string
    NotificationsAPI::update_firebase_token(int client_id, const std::string &firebase_token) {
        Json::Value jv;
        jv["client_id"] = client_id;
        jv["firebase_token"] = firebase_token;
        std::string params = Json::FastWriter().write(jv);
        params.pop_back();
        return post("/update_firebase_token", params);
    }

    std::string NotificationsAPI::get(const std::string &target, const std::string &params) const {
        try {
            curlpp::Easy request;

            //  --request GET
            request.setOpt<curlpp::options::HttpGet>(true);

            //  -G url
            std::string url = "localhost:1618" + target + params;
            request.setOpt<curlpp::options::Url>(url);

            request.setOpt<curlpp::options::ConnectTimeout>(connect_timeout);

            //  get result as string
            std::ostringstream os;
            request.setOpt<curlpp::options::WriteStream>(&os);

            request.perform();

            return os.str();
        } catch (curlpp::RuntimeError &e) {
            Log::e(TAG, "get", "runtime error: " + (std::string) e.what());
            return {};
        } catch (curlpp::LogicError &e) {
            Log::e(TAG, "get", "logic error: " + (std::string) e.what());
            return {};
        }
    }

    std::string NotificationsAPI::post(const std::string &target, const std::string &params) const {
        try {
            curlpp::Easy request;

            //  -G url
            std::string url = "localhost:1618" + target;
            request.setOpt<curlpp::options::Url>(url);

            //  -d parameters'
            request.setOpt<curlpp::options::PostFields>(params);
            request.setOpt<curlpp::options::PostFieldSize>((long) params.size());

            request.setOpt<curlpp::options::ConnectTimeout>(connect_timeout);

            //  get result as string
            std::ostringstream os;
            request.setOpt<curlpp::options::WriteStream>(&os);

            request.perform();

            return os.str();
        } catch (curlpp::RuntimeError &e) {
            Log::e(TAG, "post", "runtime error: " + (std::string) e.what());
            return {};
        } catch (curlpp::LogicError &e) {
            Log::e(TAG, "post", "logic error: " + (std::string) e.what());
            return {};
        }
    }

} // mps