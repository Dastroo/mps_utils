//
// Created by dawid on 5/17/22.
//

#include "../include/Crypto.h"


#include <my_utils/Time.h>

#include <cryptopp/aes.h>
#include <cryptopp/base64.h>
#include <cryptopp/gcm.h>
#include <cryptopp/osrng.h>

#include "../include/Sha256.h"

std::string crypto::UUID() {
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);

    using namespace mutl::time;
    unsigned long long timestamp = now<nanoseconds>();

    return sha256(std::to_string(timestamp));
}

std::string crypto::sha256(const std::string &string) {
    SHA256_HASH sha256Hash;

    Sha256Calculate(string.c_str(), string.size(), &sha256Hash);

    char outputBuffer[64];
    for (int i = 0; i < SHA256_HASH_SIZE; i++)
        sprintf(outputBuffer + (i * 2), "%02x", sha256Hash.bytes[i]);

    outputBuffer[63] = 0;

    return outputBuffer;
}

/**
 * @brief
 * @param str
 * @param iv_out
 * @param key_out
 * @return cipher
 */
std::string crypto::encrypt(const std::string &str, std::string &iv_out, std::string &key_out) {
    try {
        CryptoPP::AutoSeededRandomPool prng;

        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        prng.GenerateBlock(key, key.size());

        CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
        prng.GenerateBlock(iv, iv.size());

        key_out = std::string(key.begin(), key.end());
        iv_out = std::string(iv.begin(), iv.end());

        CryptoPP::GCM<CryptoPP::AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        std::string cipher;
        CryptoPP::StringSource ss1(
                str, true,
                new CryptoPP::AuthenticatedEncryptionFilter(
                        e,
                        new CryptoPP::StringSink(cipher))// AuthenticatedEncryptionFilter
        );                                               // StringSource
        return cipher;
    } catch (CryptoPP::Exception &e) {
        throw std::runtime_error(__func__ + std::string(": ") + e.GetWhat());
    }
}

/// encrypt string and generate random iv (remember to save the iv_out somewhere) todo: change to WjCryptLib
std::string crypto::encrypt(const std::string &str, std::string &iv_out, const std::string &key_) {
    try {
        CryptoPP::AutoSeededRandomPool prng;

        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        key.Assign((unsigned char *) key_.c_str(), key_.size());

        CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
        prng.GenerateBlock(iv, iv.size());

        iv_out = std::string(iv.begin(), iv.end());

        CryptoPP::GCM<CryptoPP::AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        std::string cipher;
        CryptoPP::StringSource ss1(
                str, true,
                new CryptoPP::AuthenticatedEncryptionFilter(
                        e,
                        new CryptoPP::StringSink(cipher))// AuthenticatedEncryptionFilter
        );                                               // StringSource
        return cipher;
    } catch (CryptoPP::Exception &e) {
        throw std::runtime_error(__func__ + std::string(": ") + e.GetWhat());
    }
}
/// encrypt string and generate random iv (remember to save the iv_out somewhere)
std::string crypto::encrypt(const std::string &str, const std::string &iv_str, const std::string &key_) {
    try {
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        key.Assign((unsigned char *) key_.c_str(), key_.size());

        CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
        iv.Assign((unsigned char *) iv_str.c_str(), iv_str.size());

        CryptoPP::GCM<CryptoPP::AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        std::string cipher;
        CryptoPP::StringSource ss1(
                str, true,
                new CryptoPP::AuthenticatedEncryptionFilter(
                        e,
                        new CryptoPP::Base64Encoder(
                                new CryptoPP::StringSink(cipher)))// AuthenticatedEncryptionFilter
        );                                                        // StringSource
        return cipher;
    } catch (CryptoPP::Exception &e) {
        throw std::runtime_error(__func__ + std::string(": ") + e.GetWhat());
    }
}

std::string crypto::decrypt(const std::string &cipher, const std::string &iv_str, const std::string &key_) {
    try {
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        key.Assign((unsigned char *) key_.c_str(), key_.size());

        CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
        iv.Assign((unsigned char *) iv_str.c_str(), iv_str.size());

        CryptoPP::GCM<CryptoPP::AES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        // Recovered plain text
        std::string rpdata;
        CryptoPP::AuthenticatedDecryptionFilter df(
                d,
                new CryptoPP::StringSink(rpdata));// AuthenticatedDecryptionFilter

        /* The StringSource dtor will be called immediately
          after construction below. This will cause the
          destruction of objects it owns. To stop the
          behavior so we can get the decoding result from
          the DecryptionFilter, we must use a redirector
          or manually Put(...) into the filter without
          using a StringSource.
          std::string cipher_m = cipher;*/
        CryptoPP::StringSource ss2(
                cipher, true,
                new CryptoPP::Base64Decoder(new CryptoPP::Redirector(df /*, PASS_EVERYTHING */)));// StringSource

        // If the object does not throw, here's the only
        //  opportunity to check the data's integrity
        if (!df.GetLastResult())
            throw std::runtime_error(__func__ + std::string(": digest message was not valid"));
        return rpdata;
    } catch (CryptoPP::Exception &e) {
        throw std::runtime_error(__func__ + std::string(": ") + e.what());
    }
}

void crypto::encode_base64(const std::string &decoded, std::string &encoded_out) {
    CryptoPP::Base64Encoder encoder;
    encoder.Put((CryptoPP::byte*)decoded.data(), decoded.size());
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if (size) {
        encoded_out.resize(size);
        encoder.Get((CryptoPP::byte *) &encoded_out[0], encoded_out.size());
    }
}

void crypto::decode_base64(const std::string &encoded, std::string &decoded_out) {
    CryptoPP::Base64Decoder decoder;
    decoder.Put( (CryptoPP::byte*)encoded.data(), encoded.size() );
    decoder.MessageEnd();

    CryptoPP::word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        decoded_out.resize(size);
        decoder.Get((CryptoPP::byte*)&decoded_out[0], decoded_out.size());
    }
}
