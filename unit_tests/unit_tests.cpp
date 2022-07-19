//
// Created by dawid on 06.04.2022.
//

#include "../include/Crypto.h"
#include "doctest.h"
#include <cryptopp/aes.h>
#include <cryptopp/gcm.h>
#include <cryptopp/osrng.h>
#include <iostream>

//TEST_CASE(R"(test)") {
//    using namespace CryptoPP;
//
//    AutoSeededRandomPool prng;
//
//    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
//    prng.GenerateBlock(key, key.size());
//
//    byte iv[AES::BLOCKSIZE];
//    prng.GenerateBlock(iv, sizeof(iv));
//
//    const int TAG_SIZE = 12;
//
//    // Plain text
//    std::string pdata = "Authenticated Encryption";
//
//    // Encrypted, with Tag
//    std::string cipher, encoded;
//
//    // Recovered plain text
//    std::string rpdata;
//
//    /*********************************\
//\*********************************/
//
//    try {
//        GCM<AES>::Encryption e;
//        e.SetKeyWithIV(key, key.size(), iv, sizeof(iv));
//
//        StringSource ss1(pdata, true,
//                         new AuthenticatedEncryptionFilter(e,
//                                                           new StringSink(cipher), false, TAG_SIZE)// AuthenticatedEncryptionFilter
//        );                                                                                         // StringSource
//    } catch (CryptoPP::Exception &e) {
//        std::cerr << e.what() << std::endl;
//        exit(1);
//    }
//
//    /*********************************\
//\*********************************/
//
//    try {
//        GCM<AES>::Decryption d;
//        d.SetKeyWithIV(key, key.size(), iv, sizeof(iv));
//
//        AuthenticatedDecryptionFilter df(d,
//                                         new StringSink(rpdata),
//                                         AuthenticatedDecryptionFilter::Flags::DEFAULT_FLAGS, TAG_SIZE);// AuthenticatedDecryptionFilter
//
//        // The StringSource dtor will be called immediately
//        //  after construction below. This will cause the
//        //  destruction of objects it owns. To stop the
//        //  behavior so we can get the decoding result from
//        //  the DecryptionFilter, we must use a redirector
//        //  or manually Put(...) into the filter without
//        //  using a StringSource.
//        StringSource ss2(cipher, true,
//                         new Redirector(df /*, PASS_EVERYTHING */));// StringSource
//
//        // If the object does not throw, here's the only
//        //  opportunity to check the data's integrity
//        if (df.GetLastResult()) {
//            std::cout << "recovered text: " << rpdata << std::endl;
//        }
//    } catch (CryptoPP::Exception &e) {
//        std::cerr << e.what() << std::endl;
//        exit(1);
//    }
//}

TEST_CASE(R"(Crypto)") {



    SUBCASE(R"(encrypt)") {
        std::string message = "Authenticated Encryption";
        std::string cipher;
        const std::string &key = "this is my key16";
        const std::string &iv = "thisasdfjkgsdjkfhgjksdfgjksdfjkghsjkdfhg";

        cipher = crypto::encrypt(message, iv, key);
        crypto::encode_base64(cipher, cipher);
        crypto::decode_base64(cipher, cipher);
        CHECK_EQ(crypto::decrypt(cipher, iv, key), message);
    }

    SUBCASE(R"(decrypt)") {
    }
}

/*
TEST_CASE(R"()") {

}

SUBCASE(R"()") {

}
 */