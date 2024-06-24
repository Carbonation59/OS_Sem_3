#include <string>
#include <vector>
#include <iostream>

using namespace std;

//��������� ��������� ������� � ������� ����� - �����$����������$����� ��������$���������
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


//��������� ��������� �������
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


//�������� ��������� � ������� ��� ������� �����
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


//�������� ��������� � ������� ��� ������� �����
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


//�������� ����� �� ��������� ��� �������
string extract_login(string message){
    string login;
    int i = 0;
    while (message[i] != '$'){
        login.push_back(message[i]);
        i++;
    }
    return login;
}


//�������� ��������� ��� �������
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

//�������� ����� �������� ���������
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


//�������� ���������� ���������
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


//�������� ����� ���������
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
