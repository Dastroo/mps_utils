//
// Created by dawid on 19.07.22.
//

#pragma once

#include <cstdint>

enum user_flags : uint32_t {
    ///direct authenticationAPI target
    AUTH = 0,// TODO: check how bit operation work with 0

    // ACCOUNT TYPES
    ///registered account
    BASIC = 1 << 0,
    ///verified account (with email and phone nr)
    VERIFIED = 1 << 1,
    ///payed or test account with extra privileges
    VIP = 1 << 2,

    // TRAITS
    ///verified email
    EMAIL = 1 << 3,
    ///verified phone number
    PHONE_NR = 1 << 4,
    ///crypto address set
    XNO = 1 << 5
};