#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<sstream>
#include<fstream>

#include "HttpResponseParser.h"

using std::string;
using std::unordered_map;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::stoi;
using std::cout;
using std::endl;

void handleHttpResponse(const string &httpResponseString) {
    // Create an instance of HttpParser
    HttpResponseParser httpParser(httpResponseString);

    // Output the parsed data
    if ((httpParser.isvalidResponse())) {
        cout << "HTTP Response is valid" << endl;
    } else {
        cout << "HTTP Version: " << httpParser.getHttpVersion() << endl;
        cout << "Status: " << httpParser.getStatusCode() << endl;
        // cout << "Reason Phrase: " << httpParser.getReasonPhrase() << endl;
        cout << "Number of valid headers: " << httpParser.getValidHeadersCount() << endl;
        cout << "Number of invalid headers: " << httpParser.getInvalidHeadersCount() << endl;

        // Output the header. Isn't required in the assignment, so comment it out
        // httpParser.printHeaders();

        // Lookup a header value by name.
        // Isn't required in the assignment, so comment it out
        // string headerValue = httpParser.lookupHeaderValuebyName("date");
        // cout << "Content-Type header value: " << headerValue << endl;
    }

    cout << endl;
}

int main() {
    // Example HTTP response
#if 0
    string httpResponseString =
        "HTTP/1.0 200 OK\n"
        "cache-control: public\n"
        "content-length: 0\n"
        "content-type: image/svg+xml\n"
        "date: Tue, 22 Jun 2021 22:24:42 GMT\n"
        "\n";
#endif

    // Read the HTTP response from a file
    const string filename = "ut.txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return {};
    }

    // vector<string> blocks;
    string line;
    stringstream blockStream;

    while (getline(file, line)) {
        if (line.empty()) {
            // Reached a blank line, we got a whole http response block.
            // blocks.push_back(blockStream.str());
            handleHttpResponse(blockStream.str());
            blockStream.str(""); // Clear the block stream
        } else {
            // Append the current line to the block
            blockStream << line << endl;
        }
    }

    file.close();

    return 0;
}
