#ifndef HTTP_RESPONSE_PARSER_H
#define HTTP_RESPONSE_PARSER_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

class HttpResponseParser {
public:
    HttpResponseParser();
    HttpResponseParser(const string& message);

    string lookupHeaderValueByName(const string& headerName) const;
    string getHttpVersion() const;
    string getReasonPhrase() const;
    void printHeaders() const;
    int getValidHeadersCount() const;
    int getInvalidHeadersCount() const;
    int getStatusCode() const;
    bool isvalidResponse() const;

private:
    string httpVersion;
    int statusCode;
    string reasonPhrase;
    unordered_map<string, string> headers;
    int validHeaders;
    int invalidHeaders;
    bool validResponse;
};

#endif // HTTP_RESPONSE_PARSER_H
