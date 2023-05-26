### HTTP Parser - The Code Assignment
Read the HTTP response from the file `ut.txt` and parse it to get the status code, headers and body.

**The code is written in C++11 and well tested on Linux.**

#### Usage
```bash
make
g++ -std=c++11 -Wall -c -o obj/HttpResponseParser.o HttpResponseParser.cpp
g++ -std=c++11 -Wall -c -o obj/main.o main.cpp
g++ -std=c++11 -Wall -o bin/httpparser obj/HttpResponseParser.o obj/main.o

./bin/httpparser
HTTP Version: 1.0
Status: 200
Number of valid headers: 4
Number of invalid headers: 0

HTTP Version: 1.1
Status: 302
Number of valid headers: 3
Number of invalid headers: 1

HTTP Version: 2.0
Status: 404
Number of valid headers: 3
Number of invalid headers: 2

Invalid HTTP response: Invalid status line

Invalid HTTP response: Invalid status line

```

But if you want to test it on Windows, you need to modify the code a little bit.

Because
```
For Windows, the line separator is "\r\n"
But for Linux, the line separator is "\n"
```

The code needs to be modified to run on Windows.

```cpp
size_t statusLinePosEnd = message.find("\n");
```

should be changed to

```cpp
size_t statusLinePosEnd = message.find("\r\n");
```


