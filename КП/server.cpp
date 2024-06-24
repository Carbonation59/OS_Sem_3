#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <vector>
#include <string>
#include <fcntl.h>
#include "funcs.h"
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>
#include <thread>

using namespace std;


typedef struct{
        string m;
		int fd;
		int time;
} vec_el;

vector<vec_el> vector_mes;


void func(vector<int> fd){
	while(true){
		if(vector_mes.size()!=0){
			sort(vector_mes.begin(),vector_mes.end(),
				[](const vec_el a, const vec_el b){
					return a.time<b.time;
			});
			for(int i=0;i<vector_mes.size();i++){
				if(vector_mes[i].time==0){
					send_message_to_client(fd[vector_mes[i].fd], vector_mes[i].m);
				}
				vector_mes[i].time--;
			}
			for(int i=0;i<vector_mes.size();i++){
				if(vector_mes[i].time==-1){
					vector_mes.erase(vector_mes.begin());
				}
			}
		}
		if(vector_mes.size()!=0){
			sleep(1);
		}
	}
}

int in(vector<string> logins, string str){
    for (int i = 0; i < logins.size(); i++){
        if (logins[i] == str)
            return i;
    }
    return -1;
}

int main(){
    vector<string> logins;
    string command;
    string login;

    //ввод логинов
    cout << "Enter all user's logins. Insert 'end' to stop:\n";
    while (true){
        cin >> login;
		if(login == "end"){
			break;
		}
        vector<string> vec;
        vec.push_back(login);
        if (in(logins, login) == -1)
            logins.push_back(login);
        else
            cout << "already exists!";
    }
    //создание выходных FIFO для всех логинов
    for (int i = 0; i < logins.size(); i++){
        if (mkfifo(logins[i].c_str(), 0777) == -1){
            if (errno != EEXIST){
                cout << "FIFO WAS NOT CREATED";
                exit(1);
            }
        }
    }
    //создание входного FIFO
    if (mkfifo("input", 0777) == -1){
        cout << "MAIN INPUT FIFO WAS NOT CREATED";
        exit(1);
    }
    int fd_pub = open("input", O_RDWR);
    if (fd_pub == -1){
        cout << "INPUT FIFO WAS NOT OPENED";
        exit(1);
    }

    //открытие всех FIFO на запись
	vector<int> fd(logins.size());
    for (int i = 0; i < logins.size(); i++){
        fd[i] = open(logins[i].c_str(), O_RDWR);
    }

	thread thr_recieve(func, fd);
    while (true){
        string message;
        message = recieve_message_server(fd_pub);
        cout << message << "\n";
        string s_usr = extract_login(message);          //от кого
        string s_adressee = extract_addressee(message); //кому
		string s_time = extract_time(message);          //время
        string s_message = extract_message(message);    //что
        int fd_repl = in(logins, s_adressee);                //id получателя
        int fd_usr = in(logins, s_usr);                      //id отправителя
        int pos = -1;
		int time = stoi(s_time.data());
		vec_el q_mes;
		q_mes.m=s_message;
		q_mes.time=time;
		q_mes.fd=fd_repl;
		if (in(logins, s_adressee) == -1){
				send_message_to_client(fd[fd_usr], "Login does not exists!\n");
		} else{
				vector_mes.push_back(q_mes);
				//send_message_to_client(fd[fd_repl], s_message);
		}
	}
}
