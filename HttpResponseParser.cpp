#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "HttpResponseParser.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::stoi;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

HttpResponseParser::HttpResponseParser() {
    httpVersion = "";
    statusCode = 0;
    reasonPhrase = "";
    validHeaders = 0;
    invalidHeaders = 0;
    validResponse = true;
}

HttpResponseParser::HttpResponseParser(const string &message) {
    validResponse = true;

    /*
     * Parse the HTTP Response Message
     * For Windows, the line separator is "\r\n"
     * But for Linux, the line separator is "\n"
     */
    // size_t statusLinePosEnd = message.find("\r\n");
    size_t statusLinePosEnd = message.find("\n");
    if (statusLinePosEnd == string::npos) {
        cout << "Invalid HTTP Response Message" << endl;
        validResponse = false; // Set validResponse to false
        return;
    }

    // Parse the status line
    string statusLine = message.substr(0, statusLinePosEnd);
    // Part1: The version of HTTP
    size_t httpVerPosEnd = statusLine.find(" ");
    if (httpVerPosEnd == string::npos) {
        cout << "Invalid HTTP response: Invalid status line" << endl;
        validResponse = false;
        return;
    }
    string httpVerString = statusLine.substr(0, httpVerPosEnd);
    size_t httpVerSeparatorPos = httpVerString.find("/");
    httpVersion = httpVerString.substr(httpVerSeparatorPos + 1);

    // Part2: The status code
    size_t statusCodePosStart = httpVerPosEnd + 1;
    size_t statusCodePosEnd = statusLine.find(" ", statusCodePosStart);
    if (statusCodePosEnd == string::npos) {
        cout << "Invalid HTTP response: Invalid status line" << endl;
        validResponse = false;
        return;
    }
    string statusCodeString = statusLine.substr(statusCodePosStart,
                                                statusCodePosEnd - statusCodePosStart);
    statusCode = stoi(statusCodeString);
    // Part3: The response phrase
    reasonPhrase = statusLine.substr(statusCodePosEnd + 1);

    // Parse the headers
    size_t headersPosStart = statusLinePosEnd + 2;
    validHeaders = 0;
    invalidHeaders = 0;
    while (headersPosStart < message.length()) {
        // one header per line
        size_t headerPosEnd = message.find("\n", headersPosStart);
        if (headerPosEnd == string::npos) {
            break;
        }
        string header = message.substr(headersPosStart,
                                       headerPosEnd - headersPosStart);
        size_t headerSeparatorPos = header.find(":");
        if (headerSeparatorPos != string::npos) {
            string headerName = header.substr(0, headerSeparatorPos);
            string headerValue = header.substr(headerSeparatorPos + 1);
            headers[headerName] = headerValue;
            ++validHeaders;
        } else {
            ++invalidHeaders;
        }
        // move to the next header
        headersPosStart = headerPosEnd + 2;
    }
}

bool HttpResponseParser::isvalidResponse() const {
    return validResponse;
}

string HttpResponseParser::lookupHeaderValueByName(const string &headerName) const {
    // lookup the header value by name in the unordered_map
    auto iter = headers.find(headerName);
    if (iter != headers.end()) {
        return iter->second;
    }
    return "";
}

// Output the headers
void HttpResponseParser::printHeaders() const {
    // cout << "Headers:" << endl;
    for (const auto &header : headers) {
        cout << header.first << ": " << header.second << endl;
    }
}

int HttpResponseParser::getValidHeadersCount() const {
    return validHeaders;
}

int HttpResponseParser::getInvalidHeadersCount() const {
    return invalidHeaders;
}

int HttpResponseParser::getStatusCode() const {
    return statusCode;
}

string HttpResponseParser::getHttpVersion() const {
    return httpVersion;
}

string HttpResponseParser::getReasonPhrase() const {
    return reasonPhrase;
}
