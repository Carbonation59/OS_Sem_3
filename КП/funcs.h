#include <string>
#include <vector>
#include <iostream>

using namespace std;

//отправить сообщение серверу в удобной форме - логин$получатель$время ожидания$сообщение
void send_message_to_server(int fd, string curlogin, string user, int time, string message){
    string s_time;
    char k1;
    int q;
    while(time>0){
		q=time%10+'0';
		k1=q;
		s_time=k1 + s_time;
		time=time/10;
    }
    if(s_time.size()==0){
		s_time="0";
	}
    string text = curlogin + "$" + user + "$" + s_time + "$" + message;
    int k = text.size();
    write(fd, &k, sizeof(k));
    char messagec[k];
    for (int i = 0; i < k; i++){
        messagec[i] = text[i];
    }
    write(fd, messagec, k);
}


//отправить сообщение клиенту
void send_message_to_client(int fd, string message){
    string text = message;
    int k = text.size();
    write(fd, &k, sizeof(k));
    char messagec[k];
    for (int i = 0; i < k; i++){
        messagec[i] = text[i];
    }
    write(fd, messagec, k);
}


//получить сообщение в удобной для клиента форме
string recieve_message_client(int fd){
    int size;
    read(fd, &size, sizeof(size));
    char messagec[size];
    read(fd, messagec, size);
    string recv;
    for (int i = 0; i < size; i++){
        if (messagec[i] != '$'){
            recv.push_back(messagec[i]);
        }
        else{
			recv = recv + ": ";
		}
    }
    return recv;
}


//получить сообщение в удобной для сервера форме
string recieve_message_server(int fd){
    int size;
    read(fd, &size, sizeof(size));
    char messagec[size];
    read(fd, messagec, size);
    string recv;
    for (int i = 0; i < size; i++){
        recv.push_back(messagec[i]);
    }
    return recv;
}


//получить логин из сообщения для сервера
string extract_login(string message){
    string login;
    int i = 0;
    while (message[i] != '$'){
        login.push_back(message[i]);
        i++;
    }
    return login;
}


//получить сообщение для клиента
string extract_message(string message){
    string text, text1, text2;
    int i = 0;
    while (message[i] != '$'){
        text1.push_back(message[i]);
        i++;
    }
    i++;
    while (message[i] != '$'){
        i++;
    }
        i++;
        while (message[i] != '$'){
        i++;
    }
    while (i < message.size()){
        text2.push_back(message[i]);
        i++;
    }
    text = text1 + text2;
    return text;
}

//получить время отправки сообщения
string extract_time(string message){
    string text;
    int i = 0;
    while (message[i] != '$'){
        i++;
    }
    i++;
    while (message[i] != '$'){
        i++;
    }
    i++;
    while (message[i] != '$'){
        text.push_back(message[i]);
        i++;
    }
    return text;
}


//получить получателя сообщения
string extract_addressee(string message){
    string text;
    int i = 0;
    while (message[i] != '$'){
        i++;
    }
    i++;
    while (message[i] != '$'){
        text.push_back(message[i]);
        i++;
    }
    return text;
}


//получить текст сообщения
string extract_text(string message){
    string text;
    int i = 0;
    while (message[i] != '$'){
        i++;
    }
    i++;
        while (message[i] != '$'){
        i++;
    }
        i++;
    while (message[i] != '$'){
        i++;
    }
    i++;
    while (i < message.size()){
        text.push_back(message[i]);
        i++;
    }
    return text;
}
