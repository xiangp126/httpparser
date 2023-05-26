#include<iostream>
#include<string>
#include<unordered_map>

using std::string;
using std::unordered_map;
using std::stoi;
using std::cout;
using std::endl;

class HttpResponseParser {
public:
    HttpResponseParser() {
        httpVersion = "";
        statusCode = 0;
        reasonPhrase = "";
        validHeaders = 0;
        invalidHeaders = 0;
    }

    HttpResponseParser(const string &message) {
        // Parse the HTTP Response Message
        size_t statusLinePosEnd = message.find("\r\n");
        if (statusLinePosEnd == string::npos) {
            cout << "Invalid HTTP Response Message" << endl;
            return;
        }

        // Parse the status line
        string statusLine = message.substr(0, statusLinePosEnd);
        // Part1: The version of HTTP
        size_t httpVerPosEnd = statusLine.find(" ");
        if (httpVerPosEnd == string::npos) {
            cout << "Invalid HTTP response: Invalid status line" << endl;
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
            size_t headerPosEnd = message.find("\r\n", headersPosStart);
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

    string lookupHeaderValuebyName(const string &headerName) const {
        // lookup the header value by name in the unordered_map
        auto iter = headers.find(headerName);
        if (iter != headers.end()) {
            return iter->second;
        }
        return "";
    }

    // Output the headers
    void printHeaders() const {
        // cout << "Headers:" << endl;
        for (const auto &header : headers) {
            cout << header.first << ": " << header.second << endl;
        }
    }

    int getValidHeadersCount() const {
        return validHeaders;
    }

    int getInvalidHeadersCount() const {
        return invalidHeaders;
    }

    int getStatusCode() const {
        return statusCode;
    }

    int gethttpStatusCode() const {
        return statusCode;
    }

    string getHttpVersion() const {
        return httpVersion;
    }

    string getReasonPhrase() const {
        return reasonPhrase;
    }

private:
    // Structure of the HTTP Response Message
    string httpVersion;
    int statusCode;
    string reasonPhrase;
    unordered_map<string, string> headers;
    int validHeaders;
    int invalidHeaders;
};

int main() {
    // Example HTTP response
    string httpResponseString =
        "HTTP/1.0 200 OK\r\n"
        "cache-control: public\r\n"
        "content-length: 0\r\n"
        "content-type: image/svg+xml\r\n"
        "date: Tue, 22 Jun 2021 22:24:42 GMT\r\n"
        "\r\n";

    // Create an instance of HttpParser
    HttpResponseParser httpParser(httpResponseString);

    // Output the parsed data
    cout << "HTTP Version: " << httpParser.getHttpVersion() << endl;
    cout << "Status: " << httpParser.getStatusCode() << endl;
    // cout << "Reason Phrase: " << httpParser.getReasonPhrase() << endl;
    cout << "Number of valid headers: " << httpParser.getValidHeadersCount() << endl;
    cout << "Number of invalid headers: " << httpParser.getInvalidHeadersCount() << endl;

    // Output the header. Isn't required in the assignment, so comment it out
    // httpParser.printHeaders();

    // Lookup a header value by name. Isn't required in the assignment, so comment it out
    // string headerValue = httpParser.lookupHeaderValuebyName("date");
    // cout << "Content-Type header value: " << headerValue << endl;

    return 0;
}







