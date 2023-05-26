### HTTP Parser - The Code Assignment
Read the HTTP response from the file `ut.txt` and parse it to get the status code, headers and body.

#### Usage
```bash
make
g++ -std=c++11 -Wall -c -o obj/HttpResponseParser.o HttpResponseParser.cpp
g++ -std=c++11 -Wall -c -o obj/main.o main.cpp
g++ -std=c++11 -Wall -o bin/httpparser obj/HttpResponseParser.o obj/main.o

./bin/httpparser
```
