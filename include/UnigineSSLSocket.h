/* Copyright (C) 2005-2025, UNIGINE. All rights reserved.
*
* This file is a part of the UNIGINE 2 SDK.
*
* Your use and / or redistribution of this software in source and / or
* binary form, with or without modification, is subject to: (i) your
* ongoing acceptance of and compliance with the terms and conditions of
* the UNIGINE License Agreement; and (ii) your inclusion of this notice
* in any version of this software that you use or redistribute.
* A copy of the UNIGINE License Agreement is available by contacting
* UNIGINE. at http://unigine.com/
*/
// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include "UniginePtr.h"
#include "UnigineStreams.h"

namespace Unigine
{


class UNIGINE_API SSLSocket : public Socket
{
public:
	static bool convertible(Stream *obj) { return obj && obj->getType() == Stream::SSL_SOCKET; }

	enum SSL_CTX_METHOD
	{
		SSL_CTX_METHOD_TLS = 0,
		SSL_CTX_METHOD_TLS_1_0 = 1,
		SSL_CTX_METHOD_TLS_1_1 = 2,
		SSL_CTX_METHOD_TLS_1_2 = 3,
		SSL_CTX_METHOD_DTLS = 4,
		SSL_CTX_METHOD_DTLS_1 = 5,
		SSL_CTX_METHOD_DTLS_1_2 = 6,
	};

	enum SSL_HANDSHAKE
	{
		SSL_HANDSHAKE_ERROR_NONE = 0,	// openssl errors
		SSL_HANDSHAKE_ERROR_SSL = 1,
		SSL_HANDSHAKE_ERROR_WANT_READ = 2,
		SSL_HANDSHAKE_ERROR_WANT_WRITE = 3,
		SSL_HANDSHAKE_ERROR_WANT_X509_LOOKUP = 4,
		SSL_HANDSHAKE_ERROR_SYSCALL = 5,
		SSL_HANDSHAKE_ERROR_ZERO_RETURN = 6,
		SSL_HANDSHAKE_ERROR_WANT_CONNECT = 7,
		SSL_HANDSHAKE_ERROR_WANT_ACCEPT = 8,
		SSL_HANDSHAKE_ERROR_WANT_ASYNC = 9,
		SSL_HANDSHAKE_ERROR_WANT_ASYNC_JOB = 10,
		SSL_HANDSHAKE_ERROR_WANT_CLIENT_HELLO_CB = 11,
		SSL_HANDSHAKE_OK = 100,
		SSL_HANDSHAKE_FAILED = 101,
	};

	enum LOADER_TYPE
	{
		LOADER_TYPE_RSA_KEY = 3,
		LOADER_TYPE_X509_CERT = 1,
		LOADER_TYPE_X509_CACERT = 2,
	};
	static Ptr<SSLSocket> create();
	static Ptr<SSLSocket> create(Socket::SOCKET_TYPE socket_type, SSLSocket::SSL_CTX_METHOD ssl_method);
	void close();
	bool accept(const Ptr<Socket> &socket);
	bool connect();
	bool connect(size_t timeout_ms);
	SSLSocket::SSL_HANDSHAKE handshake();
	bool isCertificateVerified() const;
	bool load(SSLSocket::LOADER_TYPE loader_type, const char *path);
	bool parse(SSLSocket::LOADER_TYPE loader_type, const char *data);
	bool isAvailable() const;
	int pending() const;
	size_t read(void *ptr, size_t size, size_t nmemb) const;
	size_t write(const void *ptr, size_t size, size_t nmemb) const;
	size_t peek(void *ptr, size_t size, size_t nmemb) const;
};
typedef Ptr<SSLSocket> SSLSocketPtr;

} // namespace Unigine
