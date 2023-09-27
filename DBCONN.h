#ifndef DBCONN
#define DBCONN
#include<iostream>
#include<string>
#include<mysql.h>
using namespace std;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;

            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost", "root", "", "device_mgmt", 3306, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            system("pause");
            
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
};
#endif


