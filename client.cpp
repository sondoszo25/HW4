#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <regex.h>
#include <cstring>
#include "Myvector.h"
#include "Data.h"
#include "DefaultIOo.h"
#include <sstream>
#include <sys/stat.h>
#include <list>
#include <thread>
#include <fstream>
using namespace std;
/******************
 * Function Name: download
 * Input: list of strings & string
 * Output: void
 * Function Operation: for 5th command
 ******************/
void download(list<string> *classified, string path)
{
    int count = 1;
    string input;
    ofstream myfile;
    int flag = 1;
    myfile.open(path + "/results.txt");
    if (!(myfile.is_open()))
    {
        cout << "not open" << endl;
        flag = 0;
        return;
    }
    for (std::list<string>::iterator j = classified->begin(); j != classified->end(); ++j)
    {
        myfile << to_string(count) + "  " + *j << endl;
        count++;
    }
}

/******
 * Function Name: main
 * Input: string array length in argc, and the strings array from the command line in argv
 * Output: int
 * Function Operation: the function runs the client and connects with the server and exchange data
 ******/
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "invalid input run again" << endl;
        return 0;
    }
    const char *ip_address = argv[1];
    string moa;
    vector<double> v22;
    char delim22[1];
    delim22[0] = ',';
    MakeData data9(ip_address, delim22, v22, 5, moa);
    if (data9.makeInput() == 0)
    {
        cout << "invaild input ip" << endl;
        return 0;
    }
    int flag65 = 0;
    for (vector<double>::iterator i = data9.getVector().begin(); i != data9.getVector().end(); i++)
    {
        if (*i < 0 || *i > 255)
        {
            flag65 = 1;
            break;
        }
    }
    if (flag65)
    {
        cout << "invaild input ip" << endl;
        return 0;
    }
    int porttest;
    try
    {
        porttest = stod(argv[2]);
    }
    catch (exception e)
    {
        cout << "invalid input run again" << endl;
        return 0;
    }
    const int port_no = porttest;
    string moaa;
    vector<double> v222;
    char delim222[1];
    delim222[0] = ',';
    MakeData data99(argv[2], delim222, v222, 0, moaa);
    if (data99.makeInput() == 0)
    {
        cout << "invalid input run again" << endl;
        return 0;
    }
    if (port_no > 65535 || port_no < 0)
    {
        cout << "invalid input run again" << endl;
        return 0;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("error creating socket");
        return 0;
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("error connecting to server");
        close(sock);
        return 0;
    }
    string choice;
    SocketIO socket(sock);
    string inputlist;
    string input;
    int num;
    list<string> *classified = new list<string>;
    while (1)
    {
        inputlist = socket.read();
        if (!socket.getflag())
        {
            close(sock);
            break;
        }
        std::cout << inputlist << endl;
        getline(cin, choice);
        if (choice == "8")
        {
            break;
        }
        socket.write(choice);
        if (!socket.getflag())
        {
            close(sock);
            break;
        }
        else if (choice == "1")
        {
            classified->clear();
            input = socket.read();
            cout << input << endl;
            cin.clear();
            getline(cin, choice);
            ifstream ifs(choice);
            if (!ifs.is_open())
            {
                cout << "invalid input" << endl;
                socket.write("finish1");
            }
            else
            {
                string line;
                while (getline(ifs, line))
                {
                    socket.write(line);
                }
                socket.write("finish");
                input = socket.read();
                cout << input << endl;
            }
            input = socket.read();
            cout << input << endl;
            cin.clear();
            getline(cin, choice);
            ifstream ifss(choice);
            if (!ifss.is_open())
            {
                cout << "invalid input" << endl;
                socket.write("finish1");
                continue;
            }
            else
            {
                string line;
                while (getline(ifss, line))
                {
                    socket.write(line);
                }
                socket.write("finish");
                input = socket.read();
                cout << input << endl;
            }
        }
        else if (choice == "2")
        {
            input = socket.read();
            cout << input << endl;
            getline(cin, choice);
            socket.write(choice);
            if (choice.empty())
            {
                continue;
            }
            else
            {
                input = socket.read();
                if (input != "valid")
                {
                    cout << input << endl;
                }
                continue;
            }
        }
        else if (choice == "3")
        {
            classified->clear();
            while (1)
            {
                input = socket.read();
                if (input == "please upload data" || input == "classifying data complete")
                {
                    cout << input << endl;
                    break;
                }
                else
                {
                    classified->push_back(input);
                }
            }
        }
        else if (choice == "4")
        {
            int count = 1;
            while (1)
            {
                input = socket.read();
                if (input == "Done.")
                {
                    cout << input << endl;
                    break;
                }
                if (input == "please upload data" || input == "please classify the data")
                {
                    cout << input << endl;
                    break;
                }
                else
                {
                    cout << count << "  " << input << endl;
                    count++;
                }
            }
        }
        else if (choice == "5")
        {
            string path;
            getline(cin, path);
            input = socket.read();
            if (input == "Done.")
            {
                thread t(download, classified, path);
                t.detach();
            }
            else
            {
                cout << input << endl;
            }
        }
        else
        {
            input = socket.read();
            if (!socket.getflag())
            {
                close(sock);
                break;
            }
            std::cout << input << endl;
        }
    }
    free(classified);
    close(sock);
    return 0;
}