### HTTP Parser - The Code Assignment

#### Usage
```bash
make
g++ -std=c++11 -Wall -c -o obj/HttpResponseParser.o HttpResponseParser.cpp
g++ -std=c++11 -Wall -c -o obj/main.o main.cpp
g++ -std=c++11 -Wall -o bin/main obj/HttpResponseParser.o obj/main.o

./bin/main
```
