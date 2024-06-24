all: client server

client: client.cpp
	g++ client.cpp -o client -pthread

server: server.cpp
	g++ server.cpp -o server -pthread
