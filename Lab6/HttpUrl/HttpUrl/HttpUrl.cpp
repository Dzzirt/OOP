#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

using namespace std;

enum ParsingState
{
	PROTOCOL_,
	SPECIAL_SYMBOLS_,
	DOMAIN_,
	PORT_,
	DOCUMENT_
};

CHttpUrl::CHttpUrl(string const& url)
{
	if (url.empty())
	{
		throw CUrlParsingError("Input URL is empty");
	}
	Initialize(ParseUrl(url));
}

CHttpUrl::CHttpUrl(string const& domain, string const& document,
	Protocol protocol , unsigned short port) : m_protocol(protocol), m_port(port), m_document(document)
{
	if (domain.find_first_of(" \t") != string::npos)
	{
		throw invalid_argument("Domain can't contain a whitespace characters");
	}
	if (domain.empty())
	{
		throw invalid_argument("Domain shouldn't be empty");
	}
	if (m_document[0] != '/' && !m_document.empty())
	{
		m_document.insert(0, string("/"));
	}
	m_domain = domain;
}

void CHttpUrl::Initialize(UrlParts const& urlParts)
{
	m_domain = urlParts[DOMAIN_];
	m_document = urlParts[DOCUMENT_];
	auto port = urlParts[PORT_];
	urlParts[PROTOCOL_] == "http" ? m_protocol = HTTP : m_protocol = HTTPS;
	if (port.empty())
	{
		m_protocol == HTTP ? m_port = DefaultHttpPort : m_port = DefaultHttpsPort;
	}
	else
	{
		m_port = stoi(port);
	}
}

string CHttpUrl::GetURL() const
{
	string portOutput = ":" + to_string(m_port);
	if ((m_protocol == HTTP && m_port == DefaultHttpPort) || (m_protocol == HTTPS && m_port == DefaultHttpsPort))
	{
		portOutput.clear();
	}
	return ToString(m_protocol) + "://" + m_domain + portOutput + m_document;
}

string CHttpUrl::GetDomain() const
{
	return m_domain;
}

string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}


UrlParts CHttpUrl::ParseUrl(string const& url)
{
	UrlParts urlParts = {"", "", "", "", ""};

	ParsingState state = PROTOCOL_;
	for (size_t i = 0; i < url.length(); i++)
	{
		if (state == PROTOCOL_)
		{
			if (url[i] == ':')
			{

				urlParts[SPECIAL_SYMBOLS_] += url[i];
				state = SPECIAL_SYMBOLS_;
			}
			else
			{
				urlParts[PROTOCOL_] += url[i];
			}
		}
		else if (state == SPECIAL_SYMBOLS_)
		{
			if (url[i] != '/')
			{
				state = DOMAIN_;
				urlParts[DOMAIN_] += url[i];
			}
			else
			{
				urlParts[SPECIAL_SYMBOLS_] += url[i];
			}
		}
		else if (state == DOMAIN_)
		{
			if (url[i] == ':')
			{
				state = PORT_;
			}
			else if (url[i] == '/')
			{
				state = DOCUMENT_;
				urlParts[DOCUMENT_] += '/';
			}
			else
			{
				urlParts[DOMAIN_] += url[i];
			}
		}
		else if (state == PORT_)
		{
			if (url[i] == '/')
			{
				state = DOCUMENT_;
				urlParts[DOCUMENT_] += '/';
			}
			else
			{
				urlParts[PORT_] += url[i];
			}
		}
		else
		{
			urlParts[DOCUMENT_] += url[i];
		}
	}
	Validate(urlParts);
	return urlParts;
}

void CHttpUrl::Validate(UrlParts const& urlParts)
{
	string specSymb = urlParts[SPECIAL_SYMBOLS_];
	string protocol = urlParts[PROTOCOL_];
	string domain = urlParts[DOMAIN_];
	string port = urlParts[PORT_];
	string document = urlParts[DOCUMENT_];

	if (protocol != "http" && protocol != "https")
	{
		throw CUrlParsingError("Incorrect protocol. Available protocols : HTTP, HTTPS");
	}
	if (specSymb != "://")
	{
		throw CUrlParsingError(":// should be between protocol and domain");
	}
	if (domain.empty())
	{
		throw CUrlParsingError("Domain shouldn't be empty");
	}
	if (domain.find_first_of(" \t\n\v\f\r") != string::npos)
	{
		throw CUrlParsingError("Domain can't contain a whitespace characters");
	}
	if (!port.empty())
	{
		if (port.find_first_not_of("0123456789") != string::npos)
		{
			throw CUrlParsingError("Port should be digit value");
		}
		if (stoi(port) > USHRT_MAX)
		{
			throw CUrlParsingError("Port must be the less than 65535");
		}
	}
}

string CHttpUrl::ToString(Protocol protocol)
{
	if (protocol == HTTP)
	{
		return "http";
	}
	else
	{
		return "https";
	}
}