#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <vector>
#include <fcntl.h>
#include "funcs.h"
#include <thread>

using namespace std;

//функция приёма сообщений (для потока)
void func(int fd_recv, string login){
    while (true){
        string reply = recieve_message_client(fd_recv);
        cout << reply << "\n";
        cout.flush();
        cout << login << ">";
        cout.flush();
    }
}

int main(){
    //подключение к входному FIFO сервера
    int fd_send = open("input", O_RDWR);
    if (fd_send == -1){
        cout << "ERROR: MAIN FIFO WAS NOT OPENED\n";
        exit(1);
    }

    //подготовка - инструкции, ввод логина
    cout << "Welcome to Sdacha_KP.\nTo create accounts launch ./server and insert logins.\n Than relaunch this application and enter your login.\n";
    cout << "Input: LOGIN TIME MESSAGE. Example: anton 5 hey, how are you?\n";
    cout << "Insert your login: ";
    string login;

    //подключение к персональному именованному пайпу
    int fd_recv = -1;
    while (fd_recv == -1){
        cin >> login;
        fd_recv = open(login.c_str(), O_RDWR);
        if (fd_recv == -1){
            cout << "Wrong login!\nInsert your login: ";
        }
    };

    //вход успешен, запуск потока принятия сообщений от сервера
    string adressee, message;
    cout << "Congrats! You have signed in Sdacha_KP. Now you can send messages!\n";
    thread thr_recieve(func, fd_recv, login);

    //запуск цикла отправки сообщений на сервер
    while (true){
        cout << login << "> ";
        cin >> adressee;
        if (adressee == "quit")
			break;
		int time;
		cin >> time;
		while(time<0){
			cout << "Time must be positive or 0\n";
			cin >> time;
		}
        getline(cin, message);
        send_message_to_server(fd_send, login, adressee, time, message);
    }
    thr_recieve.detach();
}