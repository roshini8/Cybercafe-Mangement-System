#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<iomanip>
#include<windows.h>
#include<stdlib.h>
#include<mysql.h>
#include<ctime>
#include<chrono>
#include<conio.h>
#include<thread>        
#include<vector>
#include<cstdlib>
#include<fstream>
#include<regex>
#include<sstream>
#include <mysql/jdbc.h>
#include "DBCONN.h"

using namespace std;

//clock times
int qstate;
char mem_opt;

time_t now = time(0);
tm* ltm = localtime(&now);
time_t current = time(0);
string present = to_string(ltm->tm_mday) + "/" + to_string(ltm->tm_mon + 1) + "/" + "20" + to_string(ltm->tm_year - 100);
string time1 = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
string today = "20" + to_string(ltm->tm_year - 100) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday);
string student = "20" + to_string(ltm->tm_year - 100) + "-" + to_string(ltm->tm_mon + 4) + "-" + to_string(ltm->tm_mday);
string end_date = "20" + to_string(ltm->tm_year - 100) + "-" + to_string(ltm->tm_mon + 4) + "-" + to_string(ltm->tm_mday);
string real = to_string(ltm->tm_mday) + "-" + to_string(ltm->tm_mon+1) + "-" + "20" + to_string(ltm->tm_year - 100);

//GLOBAL DECLARATIONS
int main();
void AdminRegistration();
void MemberRegistration();
void StaffRegistration();
void AdminLogin();
void MemberLogin();
void StaffLogin();
void UserManagement();
void Admin();
void Staff();
void Member();
void ShowAdmin();
void UpdateAdmin();
void DeleteAdmin();
void ShowStaff();
void UpdateStaff();
void DeleteStaff();
void ShowMember();
void UpdateMember();
void DeleteMember();
void LoginMenu();
void AdminMenu();
void StaffMenu(string);
void MemberMenu(string);
void AddDevice();
void ShowDevice();
void UpdateDevice();
void DeleteDevice();
void DeviceEntry();
void AddMaintenance(string);
void ShowMaintenance(string);
void UpdateMaintenance(string);
void DeleteMaintenance(string);
void Maintenance(std::string);
void Device_checker();
void MemberBook(string);
void Report();
void calculation(string);
void PaymentHistory(string);
void qrcode();
void check_time(string);
void Device_checker();
void Invoice(string booking_id, string payment_id);
void Membership_renew(string);
void creditcard();


void PaymentHistory(string member_id)
{
    system("color 0D");
    string search_query = "select payment.payment_id,payment.booking_id,booking.duration,payment.price,payment.payment_date from PAYMENT join booking on booking.booking_id = payment.booking_id where booking.member_id ='" + member_id + "' ";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << "\n\t----------------------------------------------------------------------------------------------" << endl;
        cout << "\t \t \t PAYMENT INFORMATION " << endl;
        cout << "\t------------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t" << setw(9) << "Payment Id" << setw(14) << "Booking Id" << setw(14) << "Duration" << setw(14) << "Price" << setw(15) << "Payment Date" << endl;
        cout << "\t-----------------------------------------------------------------------------------------------" << endl;
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) > 0)
        {
            while ((row = mysql_fetch_row(res)))
            {
                cout << "\t\t\t" << "|" << row[0] << setw(14) << row[1] << setw(15) << row[2] << setw(16) << row[3] << setw(18) << row[4] << "|" << "\t\t\t" << endl;
            }

            int payopt;
        pay:
            cout << "\n\t\t\t[1] Search on a specific date";
            cout << "\n\t\t\t[2] Exit";
            cout << "\n\t\t\tPlease Enter an option:";
            cin >> payopt;
            if (payopt == 1)
            {
                string paymentdate;
                cout << "\n\t\t\tPlease Enter the date (YYYY-M-D): ";
                cin >> paymentdate;
                string search_query = "select payment.payment_id,payment.booking_id,booking.duration,payment.price,payment.payment_date from PAYMENT join booking on booking.booking_id = payment.booking_id where member_id ='" + member_id + "' and payment_date ='" + paymentdate + "'";
                const char* q = search_query.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate)
                {
                    res = mysql_store_result(conn);
                    if (mysql_num_rows(res) > 0)
                    {
                        while ((row = mysql_fetch_row(res)))
                        {
                            cout << "\n\t----------------------------------------------------------------------------------------------" << endl;
                            cout << "\t \t \t PAYMENT INFORMATION " << endl;
                            cout << "\t------------------------------------------------------------------------------------------------" << endl;
                            cout << "\t\t\t" << setw(9) << "Payment Id" << setw(14) << "Booking Id" << setw(14) << "Duration" << setw(14) << "Price" << setw(15) << "Payment Date" << endl;
                            cout << "\t-----------------------------------------------------------------------------------------------" << endl;
                            cout << "\t\t\t" << "|" << row[0] << setw(14) << row[1] << setw(15) << row[2] << setw(16) << row[3] << setw(18) << row[4] << "|" << "\t\t\t" << endl;
                            
                        }
                        cout << "\n\t\t\t";
                        system("pause");
                        MemberMenu(member_id);
                    }
                    else
                    {
                        cout << "\n\t\t\tNo payment history found for the specified date." << endl;
                        cout << "\t\t\t";
                        system("pause");
                        MemberMenu(member_id);
                    }
                }
            }
            else if (payopt == 2)
            {
                MemberMenu(member_id);
            }
            else
            {
                cout << "\n\t\t\t Please Enter a valid option..";
                goto pay;
            }
        }
        else
        {
            cout << "\n\t\t\tNo payment history found for the member ID." << endl;
            cout << "\t\t\t";
            system("pause");
            goto pay;
        }
    }
}


void Invoice(string booking_id, string payment_id)
{
    system("color 0D");
    string insert_query = "insert into Invoice ( payment_id, Invoice_date,Invoice_time) values ('" + payment_id + "','" + today + "','" + time1 + "')";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    {
        //cout << "\n\t\t\tInvoice updated";
        string invoice_query = "select booking.Member_id ,booking.Booking_id, Booking.Start_time, Booking.End_time, Booking.Duration, Payment.Price,Invoice.Invoice_Number,Invoice.Invoice_date,Invoice.Invoice_time from booking LEFT Join Payment on booking.Booking_id = payment.Booking_id Right Join Invoice on Invoice.Payment_id = Payment.Payment_id where payment.Booking_id =  '" + booking_id + "'";
        const char* q = invoice_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        if (!qstate)
        {

            while ((row = mysql_fetch_row(res)))
            {

                string f1 = row[0];//member_id
                string f2 = row[1];//booking_id
                string f3 = row[2];//start_time
                string f4 = row[3];//end_time
                string f5 = row[4];//duration
                string f6 = row[5];//price
                
                string name = payment_id + ".txt";
                ofstream file(name);

                file << "\n\t\t RH CYBERCAFE MANAGEMENT SYSTEM\t\t";
                file << setw(15) << "\n\t\t\t  Invoice";
                file << "\n\nInvoice No :" << row[6];
                file << "\n\nInvoice Date:" << row[7];
                file << "\n\nTime:" << row[8];
                file << "\n\nMemberId :" << row[0];
                

                file << "\n\n\n------------------------------------------------------------------";
                file << setw(10) << "\n BookingID   |" << setw(10) << " StartTime   |" << setw(10) << "EndTime      |" << setw(10) << " Duration    |" << setw(10) << " Amount  |";
                file << "\n------------------------------------------------------------------\n";
                file << setw(10) << f2 << setw(12) << f3 << setw(14) << f4 << setw(14) << f5 << setw(14) << f6;


                for (int i = 0; i < 10; i++)
                {

                    file << "\n";
                    file << setw(14) << "|" << setw(14) << "|" << setw(14) << "|" << setw(14) << "|" << setw(10) << "|";
                }
                file << "\n------------------------------------------------------------------";
                file.close();
                int opt;

            payment:
                cout << "\n\t\t\tWould you like to pay using QR or credit card payment";
                cout << "\n\t\t\t1.QR PAYMENT" << endl;
                cout << "\t\t\t2.CREDIT CARD PAYMENT" << endl;
                
                cout << "\t\t\tPlease Enter your choice (1/2): ";
                cin >> opt;
                if (opt == 1)
                {
                   
                    cout << "\n";
                    qrcode();
                    cout << "\t\t\t";
                    system("pause");
                }
                else if (opt == 2)
                {
                    creditcard();
                    cout << "\t\t\t";
                    system("pause");
                }
                else
                {
                    cout << "\t\t\tPlease choose a valid choice of payment";
                    goto payment;
                }
            }


        }
    }
    

}

void qrcodes()// qr code for staff payment
{
    system("color 0C");
    const int size = 11;
    const char* code[size] = {
        "\t\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB   \xDB\xDB\xDB\xDB\xDB",
        "\t\t\t\xDB     \xDB   \xDB    ",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB \xDB \xDB \xDB\xDB",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB   \xDB \xDB\xDB",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB \xDB \xDB \xDB\xDB",
        "\t\t\t\xDB     \xDB \xDB    \xDB",
        "\t\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB ",
        "\t\t\t              ",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB \xDB \xDB \xDB\xDB",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB   \xDB \xDB\xDB",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB \xDB \xDB \xDB\xDB"
    };

    for (int i = 0; i < size; i++) {

        cout << code[i] << std::endl;
    }


}
void qrcode()// qr code for member payment
{
    system("color 0D");
    const int size = 11;
    const char* code[size] = {
        "\t\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB   \xDB\xDB\xDB\xDB\xDB",
        "\t\t\t\xDB     \xDB   \xDB    ",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB \xDB \xDB \xDB\xDB",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB   \xDB \xDB\xDB",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB \xDB \xDB \xDB\xDB",
        "\t\t\t\xDB     \xDB \xDB    \xDB",
        "\t\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB ",
        "\t\t\t              ",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB \xDB \xDB \xDB\xDB",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB   \xDB \xDB\xDB",
        "\t\t\t\xDB \xDB\xDB\xDB \xDB \xDB \xDB \xDB\xDB"
    };

    for (int i = 0; i < size; i++) {

        cout <<  code[i] << std::endl;
    }
    
    
}

void creditcard() // Function for credit card validation for member payment
{
    system("color 0D"); // Set console color to black background and light purple text

cr: // Label for goto statement

    long long creditnum; // Variable to store credit card number

    do
    {
        cout << "\t\t\tEnter the credit card number : ";
        cin >> creditnum;
    } while (creditnum <= 0); // Prompt user to enter credit card number until a positive number is entered

    long long pcc = creditnum; // Copy of credit card number for further processing
    int sum = 0; // Variable to store sum of digits
    int count1 = 0; // Variable to count the number of digits
    long long divisor = 10; // Variable used to extract first digit(s)
    char types[20]; // Array to store credit card type

    // Calculate sum of alternate digits starting from the last digit
    while (pcc > 0)
    {
        int lastdigit = pcc % 10; // Extract last digit
        sum = sum + lastdigit; // Add last digit to the sum
        pcc = pcc / 100; // Move to the next pair of digits (skipping one digit)
    }

    pcc = creditnum / 10; // Remove the last digit to prepare for the next calculation

    // Calculate sum of doubled digits and add individual digits to the sum
    while (pcc > 0)
    {
        int lastsecdigit = pcc % 10; // Extract last second digit
        int db = lastsecdigit * 2; // Double the last second digit
        sum = sum + (db % 10) + (db / 10); // Add individual digits of the doubled number to the sum
        pcc = pcc / 100; // Move to the next pair of digits (skipping one digit)
    }

    pcc = creditnum; // Restore the original credit card number for further processing

    // Count the number of digits in the credit card number
    while (pcc != 0)
    {
        pcc = pcc / 10; // Remove the last digit
        count1++; // Increment digit count
    }

    // Calculate the divisor to extract first digit(s)
    for (int i = 0; i < count1 - 2; i++)
    {
        divisor = divisor * 10;
    }

    int firstdigit = creditnum / divisor; // Extract the first digit
    int firsttwo = creditnum / (divisor / 10); // Extract the first two digits

    if (sum % 10 == 0) // Check if sum of digits is divisible by 10
    {
        if (firstdigit == 4 && (count1 == 13 || count1 == 16)) // Check for VISA card conditions
        {
            cout << "\t\t\tValid \n";
            cout << "\t\t\tCard Type : ";
            strcpy(types, "VISA CARD");
        }
        else if ((firsttwo == 34 || firsttwo == 37) && count1 == 15) // Check for American Express card conditions
        {
            cout << "\t\t\tValid \n";
            cout << "\t\t\tCard Type : ";
            strcpy(types, "AMERICAN EXPRESS CARD");
        }
        else if ((50 < firsttwo && firsttwo < 56) && count1 == 16) // Check for Mastercard conditions
        {
            cout << "\t\t\tValid \n";
            cout << "\t\t\tCard Type : ";
            strcpy(types, "MASTERCARD");
        }
        else // If none of the conditions are met, the card is valid but the type is not identified
        {
            cout << "\t\t\tValid \n";
        }
    }
    else // If the sum is not divisible by 10, the card is invalid
    {
        strcpy(types, "INVALID");
        cout << "\t\t\tUnsuccessful Payment!! \n\t\t\tPlease try again..";
        goto cr; // Go back to the label 'cr' to prompt for credit card number again
    }

    cout << types; // Print the credit card type
}


void Membership_renew(string Member_id)
{
    int opt;
    system("color 0D");
    string plan[3] = { "BASIC","PREMIUM","STUDENT" };
    string findbymemtype_query = "select Member_type,Member_end from Member where Member_id = '" + Member_id + "'";
    const char* qt = findbymemtype_query.c_str();
    qstate = mysql_query(conn, qt);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        
        while ((row = mysql_fetch_row(res)))
        {
            std::stringstream ss;
            ss << "20" << std::setfill('0') << std::setw(2) << (ltm->tm_year - 100) << "-"
                << std::setfill('0') << std::setw(2) << (ltm->tm_mon + 1) << "-"
                << std::setfill('0') << std::setw(2) << ltm->tm_mday;
            std::string today1 = ss.str();

            if (today1 >= row[1])
            {
                if (row[0] == plan[0])
                {
                    double price1 = 100;
                    string basic_days = "20" + to_string(ltm->tm_year - 99) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday);

                    string updaterenewb_query = "update Member set Member_end = '" + basic_days + "'";
                    const char* q = updaterenewb_query.c_str();
                    qstate = mysql_query(conn, q);
                    res = mysql_store_result(conn);
                    if (!qstate)
                    {
                        cout << "\t\t\tMEMBERSHIP RENEWED FOR 1 year";
                        string findbymemtype_query = "select Member_end from Member where Member_id = '" + Member_id + "'";
                        const char* qt = findbymemtype_query.c_str();
                        qstate = mysql_query(conn, qt);
                        res = mysql_store_result(conn);
                        if (!qstate)
                        {
                            while ((row = mysql_fetch_row(res)))
                            {
                                
                                cout << "\n\t\t\tYour End date of membership has been updated to " << row[0];
                                cout << "\n\t\t\tYour payment for the membership renewal is RM 100";
                               
                            payment:
                                cout << "\n\t\t\tWould you like to pay using QR or credit card payment";
                                cout << "\n\t\t\t1.QR PAYMENT" << endl;
                                cout << "\t\t\t2.CREDIT CARD PAYMENT" << endl;

                                cout << "\t\t\tPlease Enter your choice (1/2): ";
                                cin >> opt;
                                if (opt == 1)
                                {

                                    cout << "\n";
                                    qrcode();
                                    
                                    string payment_id;
                                    string findbypaymentno_query = "select MAX(NO) from payment";
                                    const char* qn = findbypaymentno_query.c_str();
                                    qstate = mysql_query(conn, qn);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        while ((row = mysql_fetch_row(res)))
                                        {
                                            int paymentid_increment = stoi(row[0]) + 1;
                                            payment_id = "P0" + to_string(paymentid_increment);
                                            
                                            string insert_query = "insert into Payment(Payment_id,Price,Payment_date) values('" + payment_id + "','" + to_string(price1) + "','" + today + "')";
                                            const char* q = insert_query.c_str();
                                            qstate = mysql_query(conn, q);
                                            if (!qstate)
                                            {
                                                cout << "\n\t\t\tPayment updated";
                                            }

                                        }
                                    }
                                   
                                }
                                else if (opt == 2)
                                {
                                    creditcard();
                                    string payment_id;
                                    string findbypaymentno_query = "select MAX(NO) from payment";
                                    const char* qn = findbypaymentno_query.c_str();
                                    qstate = mysql_query(conn, qn);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        while ((row = mysql_fetch_row(res)))
                                        {
                                            int paymentid_increment = stoi(row[0]) + 1;
                                            payment_id = "P0" + to_string(paymentid_increment);

                                            string insert_query = "insert into Payment(Payment_id,Price,Payment_date) values('" + payment_id + "','" + to_string(price1) + "','" + today + "')";
                                            const char* q = insert_query.c_str();
                                            qstate = mysql_query(conn, q);
                                            if (!qstate)
                                            {
                                                cout << "\n\t\t\tPayment updated";
                                            }

                                        }
                                    }
                                    
                                   
                                }
                                else
                                {
                                    cout << "\t\t\tPlease choose a valid choice of payment";
                                    goto payment;
                                }
                            }
                        }
                        cout << "\n\t\t\t";
                        system("pause");
                        MemberMenu(Member_id);
                    }

                }
                else if (row[0] == plan[1])
                {
                    string premium_days = "20" + to_string(ltm->tm_year - 98) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday);
                    string updaterenewp_query = "update Member set Member_end = '" + premium_days + "'";
                    const char* q = updaterenewp_query.c_str();
                    qstate = mysql_query(conn, q);
                    res = mysql_store_result(conn);
                    if (!qstate)
                    {
                        double price2 = 200;
                        cout << "\t\t\tMEMBERSHIP RENEWED FOR 2 years";
                        string findbymemtype_query = "select Member_end from Member where Member_id = '" + Member_id + "'";
                        const char* qt = findbymemtype_query.c_str();
                        qstate = mysql_query(conn, qt);
                        res = mysql_store_result(conn);
                        if (!qstate)
                        {
                            while ((row = mysql_fetch_row(res)))
                            {
                                cout << "\n\t\t\tYour End date of membership has been updated to " << row[0];
                                cout << "\n\t\t\tYour payment for the membership renewal is RM 100";

                            payment1:
                                cout << "\n\t\t\tWould you like to pay using QR or credit card payment";
                                cout << "\n\t\t\t1.QR PAYMENT" << endl;
                                cout << "\t\t\t2.CREDIT CARD PAYMENT" << endl;

                                cout << "\t\t\tPlease Enter your choice (1/2): ";
                                cin >> opt;
                                if (opt == 1)
                                {

                                    cout << "\n";
                                    qrcode();

                                    string payment_id;
                                    string findbypaymentno_query = "select MAX(NO) from payment";
                                    const char* qn = findbypaymentno_query.c_str();
                                    qstate = mysql_query(conn, qn);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        while ((row = mysql_fetch_row(res)))
                                        {
                                            int paymentid_increment = stoi(row[0]) + 1;
                                            payment_id = "P0" + to_string(paymentid_increment);

                                            string insert_query = "insert into Payment(Payment_id,Price,Payment_date) values('" + payment_id + "','" + to_string(price2) + "','" + today + "')";
                                            const char* q = insert_query.c_str();
                                            qstate = mysql_query(conn, q);
                                            if (!qstate)
                                            {
                                                cout << "\n\t\t\tPayment updated";
                                            }

                                        }
                                    }

                                }
                                else if (opt == 2)
                                {
                                    creditcard();
                                    string payment_id;
                                    string findbypaymentno_query = "select MAX(NO) from payment";
                                    const char* qn = findbypaymentno_query.c_str();
                                    qstate = mysql_query(conn, qn);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        while ((row = mysql_fetch_row(res)))
                                        {
                                            int paymentid_increment = stoi(row[0]) + 1;
                                            payment_id = "P0" + to_string(paymentid_increment);

                                            string insert_query = "insert into Payment(Payment_id,Price,Payment_date) values('" + payment_id + "','" + to_string(price2) + "','" + today + "')";
                                            const char* q = insert_query.c_str();
                                            qstate = mysql_query(conn, q);
                                            if (!qstate)
                                            {
                                                cout << "\n\t\t\tPayment updated";
                                            }

                                        }
                                    }
                                   

                                }
                                else
                                {
                                    cout << "\t\t\tPlease choose a valid choice of payment";
                                    goto payment1;
                                }
                            }
                        }
                        cout << "\n\t\t\t";
                        system("pause");
                        MemberMenu(Member_id);
                    }
                }
                else if (row[0] == plan[2])
                {
                    double price3 = 50;
                    int month = ltm->tm_mon + 7;
                    int year = ltm->tm_year - 100;

                    if (month > 12)
                    {
                        string student_days1 = "20" + to_string(ltm->tm_year - 99) + "-" + to_string(ltm->tm_mon - 3) + "-" + to_string(ltm->tm_mday);
                        string updaterenews_query = "update Member set Member_end = '" + student_days1 + "'";
                        const char* q = updaterenews_query.c_str();
                        qstate = mysql_query(conn, q);
                        res = mysql_store_result(conn);
                        if (!qstate)
                        {
                            cout << "\t\t\tMEMBERSHIP RENEWED FOR 6 months";
                            string findbymemtype_query = "select Member_end from Member where Member_id = '" + Member_id + "'";
                            const char* qt = findbymemtype_query.c_str();
                            qstate = mysql_query(conn, qt);
                            res = mysql_store_result(conn);
                            if (!qstate)
                            {
                                while ((row = mysql_fetch_row(res)))
                                {
                                    cout << "\n\t\t\tYour End date of membership has been updated to " << row[0];
                                    cout << "\n\t\t\tYour payment for the membership renewal is RM 100";

                                payment3:
                                    cout << "\n\t\t\tWould you like to pay using QR or credit card payment";
                                    cout << "\n\t\t\t1.QR PAYMENT" << endl;
                                    cout << "\t\t\t2.CREDIT CARD PAYMENT" << endl;

                                    cout << "\t\t\tPlease Enter your choice (1/2): ";
                                    cin >> opt;
                                    if (opt == 1)
                                    {

                                        cout << "\n";
                                        qrcode();

                                        string payment_id;
                                        string findbypaymentno_query = "select MAX(NO) from payment";
                                        const char* qn = findbypaymentno_query.c_str();
                                        qstate = mysql_query(conn, qn);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            while ((row = mysql_fetch_row(res)))
                                            {
                                                int paymentid_increment = stoi(row[0]) + 1;
                                                payment_id = "P0" + to_string(paymentid_increment);

                                                string insert_query = "insert into Payment(Payment_id,Price,Payment_date) values('" + payment_id + "','" + to_string(price3) + "','" + today + "')";
                                                const char* q = insert_query.c_str();
                                                qstate = mysql_query(conn, q);
                                                if (!qstate)
                                                {
                                                    cout << "\n\t\t\tPayment updated";
                                                }

                                            }
                                        }

                                    }
                                    else if (opt == 2)
                                    {
                                        creditcard();
                                        string payment_id;
                                        string findbypaymentno_query = "select MAX(NO) from payment";
                                        const char* qn = findbypaymentno_query.c_str();
                                        qstate = mysql_query(conn, qn);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            while ((row = mysql_fetch_row(res)))
                                            {
                                                int paymentid_increment = stoi(row[0]) + 1;
                                                payment_id = "P0" + to_string(paymentid_increment);

                                                string insert_query = "insert into Payment(Payment_id,Price,Payment_date) values('" + payment_id + "','" + to_string(price3) + "','" + today + "')";
                                                const char* q = insert_query.c_str();
                                                qstate = mysql_query(conn, q);
                                                if (!qstate)
                                                {
                                                    cout << "\n\t\t\tPayment updated";
                                                }

                                            }
                                        }
                                        

                                    }
                                    else
                                    {
                                        cout << "\t\t\tPlease choose a valid choice of payment";
                                        goto payment3;
                                    }

                                }
                            }
                            cout << "\n\t\t\t";
                            system("pause");
                            MemberMenu(Member_id);
                        }
                    }
                    else
                    {
                        string student_days = "20" + to_string(ltm->tm_year - 100) + "-" + to_string(ltm->tm_mon + 7) + "-" + to_string(ltm->tm_mday);
                        string updaterenews_query = "update Member set Member_end = '" + student_days + "'";
                        const char* q = updaterenews_query.c_str();
                        qstate = mysql_query(conn, q);
                        res = mysql_store_result(conn);
                        if (!qstate)
                        {
                            cout << "\t\t\tMEMBERSHIP RENEWED FOR 6 months";
                            string findbymemtype_query = "select Member_end from Member where Member_id = '" + Member_id + "'";
                            const char* qt = findbymemtype_query.c_str();
                            qstate = mysql_query(conn, qt);
                            res = mysql_store_result(conn);
                            if (!qstate)
                            {
                                while ((row = mysql_fetch_row(res)))
                                {
                                    cout << "\n\t\t\tYour End date of membership has been updated to " << row[0];
                                }
                            }
                            cout << "\n\t\t\t";
                            system("pause");
                            MemberMenu(Member_id);
                        }
                    }

                }
                else
                {
                    cout << "\t\t\tConnection Failed!!";
                }
            }
            else
            {
                string findbymemtype_query = "select Member_end from Member where Member_id = '" + Member_id + "'";
                const char* qt = findbymemtype_query.c_str();
                qstate = mysql_query(conn, qt);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    while ((row = mysql_fetch_row(res)))
                    {
                        cout << "\n\t\t\tYour End date of membership is " << row[0];
                        string date1 = row[0];

                        string membership_query = "select member_id, (DATEDIFF('" + date1 + "','" + today + "')),member_end from member where member_id ='" + Member_id + "' ";
                        const char* qn = membership_query.c_str();
                        qstate = mysql_query(conn, qn);
                        res = mysql_store_result(conn);
                        if (!qstate)
                        {
                            while ((row = mysql_fetch_row(res)))
                            {
                                if (stoi(row[1]) > 0)
                                {
                                    cout << "\n\t\t\tMember ID:" << row[0];
                                    cout << "\n\t\t\tMembership expires in " << row[1] << "days" << endl;
                                    cout << "\t\t\t";
                                    system("pause");
                                    MemberMenu(Member_id);
                                }

                            }
                        }
                        else
                        {
                            cout << "\t\t\tConnection failed!!" << endl;
                           

                        }
                    }
                }

            }
        }
    }
}

void Invoice_p(string booking_id, string payment_id)
{
    system("color 0D");
    string insert_query = "insert into Invoice ( payment_id, Invoice_date,Invoice_time) values ('" + payment_id + "','" + today + "','" + time1 + "')";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);
    {
        //cout << "\n\t\t\tInvoice updated";
        string invoice_query = "select booking.Member_id ,booking.Booking_id, Booking.Start_time, Booking.End_time, Booking.Duration, Payment.Price,Invoice.Invoice_Number,Invoice.Invoice_date,Invoice.Invoice_time from booking LEFT Join Payment on booking.Booking_id = payment.Booking_id Right Join Invoice on Invoice.Payment_id = Payment.Payment_id where payment.Booking_id =  '" + booking_id + "'";
        const char* q = invoice_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        if (!qstate)
        {

            while ((row = mysql_fetch_row(res)))
            {

                string f1 = row[0];//member_id
                string f2 = row[1];//booking_id
                string f3 = row[2];//start_time
                string f4 = row[3];//end_time
                string f5 = row[4];//duration
                string f6 = row[5];//price

                string name = payment_id + ".txt";
                ofstream file(name);

                file << "\n\t\t RH CYBERCAFE MANAGEMENT SYSTEM\t\t";
                file << setw(15) << "\n\t\t\t  Invoice";
                file << "\n\nInvoice No :" << row[6];
                file << "\n\nInvoice Date:" << row[7];
                file << "\n\nTime:" << row[8];
                file << "\n\nMemberId :" << row[0];

                
                file << "\n\n\n------------------------------------------------------------------";
                file << setw(10) << "\n BookingID   |" << setw(10) << " StartTime   |" << setw(10) << "EndTime      |" << setw(10) << " Duration    |" << setw(10) << " Amount  |";
                file << "\n------------------------------------------------------------------\n";
                file << setw(10) << f2 << setw(12) << f3 << setw(14) << f4 << setw(14) << f5 << setw(14) << f6;

                string invoice_query = "select booking.Member_id,Member.Member_points from booking LEFT Join Member on booking.Member_id = Member.Member_id where booking.Member_id =  '" + f1 + "'";
                const char* q = invoice_query.c_str();
                qstate = mysql_query(conn, q);
                res = mysql_store_result(conn);
                if (!qstate)
                {

                    while ((row = mysql_fetch_row(res)))
                    {
                        file << "\n\nCurrent Member Points :" << row[1];
                    }
                }

                for (int i = 0; i < 10; i++)
                {

                    file << "\n";
                    file << setw(14) << "|" << setw(14) << "|" << setw(14) << "|" << setw(14) << "|" << setw(10) << "|";
                }
                file << "\n------------------------------------------------------------------";
                file.close();
                
            }


        }
    }

}



string hours[14] = { "09:00:00","10:00:00","11:00:00","12:00:00","13:00:00",
                      "14:00:00","15:00:00","16:00:00","17:00:00","18:00:00",
                      "19:00:00","20:00:00","21:00:00","22:00:00" };


void Student_Membership_payment(string booking_id, string payment_id, string member_id)
{
    system("color 0D");
    char mem_opt;
    string num1 = "09:00:00";
    int num2 = stoi(num1);

    string num3 = "14:00:00";
    int num4 = stoi(num3);

    string num5 = "22:00:00";
    int num6 = stoi(num5);

    string num7 = "18:00:00";
    int num8 = stoi(num7);
    cout << "\n\t\t\t*********************************************************************************" << endl;
    cout << "\n\t\t\t\t\t PAYMENT FOR THE BOOKING" << endl;
    cout << "\n\t\t\t*********************************************************************************" << endl;

    string findbytime_query = "SELECT Booking.Device_id,Booking.Start_time,Booking.End_time,Booking.Duration from Booking where Booking_id = '" + booking_id + "'";
    const char* q = findbytime_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while (row = mysql_fetch_row(res))
        {

            if ((stoi(row[1]) == num2 && stoi(row[2]) == num4))
            {
                
                cout <<"\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price1 = 15.00;
                double discount_price1 = 0.85 * price1;
                cout << "\n\t\t\tPrice : RM" << discount_price1;
                string duration1 = row[3];//5
               
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                              
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n) : ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";

                                        Invoice(booking_id, payment_id);

                                        MemberMenu(member_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice(booking_id, payment_id);
                                            MemberMenu(member_id);
                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }
                                        
                                        
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {

                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {

                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                                
                            }
                        }
                    }


                

            }
            else if (stoi(row[1]) >= num2 && stoi(row[2]) <= num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price2 = 5.00;
                double total_price = price2 * stoi(row[3]);
                double discount_price2 = 0.85 * total_price;
                cout << "\n\t\t\tPrice : RM" << discount_price2;
                string duration2 = row[3];
               
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                       
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n) : ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points =  stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\t\t\tThe points have been deducted as a payment";
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice(booking_id, payment_id);
                                            MemberMenu(member_id);
                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }


                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                

            }
            else if (stoi(row[1]) == num8 && stoi(row[2]) == num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price3 = 10.00;
                double discount_price3 = 0.85 * price3;
                cout << "\n\t\t\tPrice : RM" << discount_price3;
                string duration3 = row[3];//4
                
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points =  stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice(booking_id, payment_id);
                                            MemberMenu(member_id);
                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }


                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }

                            }
                        }
                    }


                        

                    

                
            }
            else
            {
                cout << "\t\t\tConnection failed!!";
            }

        }
    }
}

void Premium_Membership_payment(string booking_id, string payment_id, string member_id)
{
    system("color 0D");
    char mem_opt;
    string num1 = "09:00:00";
    int num2 = stoi(num1);

    string num3 = "14:00:00";
    int num4 = stoi(num3);

    string num5 = "22:00:00";
    int num6 = stoi(num5);

    string num7 = "18:00:00";
    int num8 = stoi(num7);
    cout << "\n\t\t\t*********************************************************************************" << endl;
    cout << "\n\t\t\t\t\t PAYMENT FOR THE BOOKING" << endl;
    cout << "\n\t\t\t*********************************************************************************" << endl;

    string findbytime_query = "SELECT Booking.Device_id,Booking.Start_time,Booking.End_time,Booking.Duration from Booking where Booking_id = '" + booking_id + "'";
    const char* q = findbytime_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while (row = mysql_fetch_row(res))
        {

            if ((stoi(row[1]) == num2 && stoi(row[2]) == num4))
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price1 = 15.00;
                double discount_price1 = 0.7 * price1;
                cout << "\n\t\t\tPrice : RM" << discount_price1;
                string duration1 = row[3];//5
               
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qe = points_query.c_str();
                    qstate = mysql_query(conn, qe);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected (y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points =  stoi(row[0]) -100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 40;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            
                                            Invoice(booking_id, payment_id);
                                            MemberMenu(member_id);
                                          
                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }

                                        
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 40;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {

                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                

            }
            else if (stoi(row[1]) >= num2 && stoi(row[2]) <= num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price2 = 5.00;
                double total_price = price2 * stoi(row[3]);
                double discount_price2 = 0.7 * total_price;
                cout << "\n\t\t\tPrice : RM" << discount_price2;
                string duration2 = row[3];
                
                   
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qn = points_query.c_str();
                    qstate = mysql_query(conn, qn);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected (y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) -100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);

                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 40;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            
                                            Invoice(booking_id, payment_id);
                                            MemberMenu(member_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }


                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 40;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                

            }
            else if (stoi(row[1]) == num8 && stoi(row[2]) == num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price3 = 10.00;
                double discount_price3 = 0.7 * price3;
                cout << "\n\t\t\tPrice : RM" << discount_price3;
                string duration3 = row[3];//4
                
                    
                    string pointsp_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qn = pointsp_query.c_str();
                    qstate = mysql_query(conn, qn);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected (y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 40;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {

                                            Invoice(booking_id, payment_id);
                                            MemberMenu(member_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }


                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 40;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {

                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                
            }
            else
            {
                cout << "\t\t\tConnection failed!!";
            }

        }
    }
}

void Basic_Membership_payment(string booking_id,string payment_id,string member_id)
{
    system("color 0D");
    char mem_opt;
    string num1 = "09:00:00";
    int num2 = stoi(num1);

    string num3 = "14:00:00";
    int num4 = stoi(num3);

    string num5 = "22:00:00";
    int num6 = stoi(num5);

    string num7 = "18:00:00";
    int num8 = stoi(num7);
    cout << "\n\t\t\t*********************************************************************************" << endl;
    cout << "\n\t\t\t\t\t PAYMENT FOR THE BOOKING" << endl;
    cout << "\n\t\t\t*********************************************************************************" << endl;

    string findbytime_query = "SELECT Booking.Device_id,Booking.Start_time,Booking.End_time,Booking.Duration from Booking where Booking_id = '" + booking_id + "'";
    const char* q = findbytime_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while (row = mysql_fetch_row(res))
        {

            if ((stoi(row[1]) == num2 && stoi(row[2]) == num4))
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price1 = 15.00;
                double discount_price1 = 0.8 * price1;//12
                cout << "\n\t\t\tPrice : RM" << discount_price1;
                string duration1 = row[3];//5
                
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice(booking_id, payment_id);
                                            MemberMenu(member_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                    

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                

            }
            else if (stoi(row[1]) >= num2 && stoi(row[2]) <= num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price2 = 5.00;
                double total_price = price2 * stoi(row[3]);
                double discount_price2 = 0.8 * total_price;//4
                cout << "\n\t\t\tPrice : RM" << discount_price2;
                string duration2 = row[3];
                
                   
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {
                        

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice(booking_id, payment_id);
                                            MemberMenu(member_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                

            }
            else if (stoi(row[1]) == num8 && stoi(row[2]) == num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price3 = 10.00;
                double discount_price3 = 0.8 * price3;//8
                cout << "\n\t\t\tPrice : RM" << discount_price3;
                string duration3 = row[3];//4
                
                   
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\t\t\tThe points have been deducted as a payment";
                                        Invoice(booking_id, payment_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice(booking_id, payment_id);
                                            MemberMenu(member_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice(booking_id, payment_id);
                                        MemberMenu(member_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                
            }
            else
            {
                cout << "\t\t\tConnection failed!!";
            }

        }
    }
}

void payment(string member_id, string booking_id)
{
    system("color 0D");
    
    string payment_id;
    string findbypaymentno_query = "select MAX(NO) from payment";
    const char* qn = findbypaymentno_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while ((row = mysql_fetch_row(res)))
        {
            int paymentid_increment = stoi(row[0]) + 1;
            payment_id = "P0" + to_string(paymentid_increment);
            string plan[3] = { "BASIC","PREMIUM","STUDENT" };
            string findbymemtype_query = "select Member_type from Member where Member_id= '" + member_id + "'";
            const char* qn = findbymemtype_query.c_str();
            qstate = mysql_query(conn, qn);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                while ((row = mysql_fetch_row(res)))
                {

                    if (row[0] == plan[0])//Basic Membership
                    {
                        Basic_Membership_payment(booking_id, payment_id, member_id);
                    }
                    else if (row[0] == plan[1])//Premium Membership
                    {
                        Premium_Membership_payment(booking_id, payment_id, member_id);
                    }
                    else if (row[0] == plan[2])//Student Membership
                    {
                        Student_Membership_payment(booking_id, payment_id, member_id);
                    }
                    else
                    {
                        cout << "\t\t\tConnection failed!!";
                    }

                }

            }
        }
    }

}




void Device_checker()
{
    system("color 0D");
    int qstate;
    string AVAIL = "AVAILABLE";
    string findbyname_query = "select * from Device where Device_Status like '%" + AVAIL + "%'";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    cout << "\t\t\tDevices available\n\n";
    // Get the number of rows in the result set
    int numDevices = mysql_num_rows(res);

    if (numDevices > 0)
    {
        // Dynamically allocate an array to store the device names
        string* devices = new string[numDevices];
        string* deviceNames = new string[numDevices]; // Array to store device names

        int i = 0;
        while ((row = mysql_fetch_row(res)))
        {
            devices[i] = row[0]; // Store the device ID in the array
            deviceNames[i] = row[1]; // Store the device name in the array
            i++;
        }

        // Print the device names
        for (int i = 0; i < numDevices; i++)
        {
            cout << "\t\t\t" << devices[i] << "|" << deviceNames[i] << endl;
        }

        // Deallocate the dynamically allocated arrays
        delete[] devices;
        delete[] deviceNames;
    }
    else
    {
        cout << "Sorry..There are no available devices..." << endl;
    }
}




/*int lastBookingid()
{
    string findbyid_query = "select MAX(Booking_id) from Booking";
    const char* q = findbyid_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        while ((row = mysql_fetch_row(res)))
        {

            return;
        }
    }
}
*/

bool isNotPreviousDate(int year, int month, int day)
{
    // Get the current system time
    std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // Convert the current system time to struct tm
    std::tm* now = std::localtime(&currentTime);

    // Check if the input date is not a previous date
    if (year > now->tm_year + 1900) {
        return true;
    }
    else if (year == now->tm_year + 1900) {
        if (month > now->tm_mon + 1) {
            return true;
        }
        else if (month == now->tm_mon + 1) {
            if (day >= now->tm_mday) {
                return true;
            }
        }
    }

    return false;
}

std::string combineDate(int year, int month, int day) {
    // Convert year, month, and day to a string format
    std::string yearStr = std::to_string(year);
    std::string monthStr = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
    std::string dayStr = (day < 10) ? "0" + std::to_string(day) : std::to_string(day);

    // Combine year, month, and day into a single date string
    std::string booking_date = yearStr + "-" + monthStr + "-" + dayStr;

    return booking_date;
}


//Pre Booking for Device Booking
void MemberBook(string Member_id)
{


    system("color 0D");
    int qstate;

    string booking_id;
    string find_member_end_query = "SELECT Member_end FROM member WHERE Member_id = '" + Member_id + "'";
    const char* qme = find_member_end_query.c_str();
    qstate = mysql_query(conn, qme);
    res = mysql_store_result(conn);
    if (qstate == 0 && mysql_num_rows(res) > 0) {
        row = mysql_fetch_row(res);
        string member_end_date = row[0];
        //cout << member_end_date;
        // Compare member_end with today's date
        struct tm member_end_tm = {};
        istringstream member_end_ss(member_end_date);
        member_end_ss >> get_time(&member_end_tm, "%Y-%m-%d");

        time_t now = time(nullptr);
        struct tm* ltm = localtime(&now);
        int current_year = 1900 + ltm->tm_year;
        int current_month = 1 + ltm->tm_mon;
        int current_day = ltm->tm_mday;
        string today_date = to_string(current_year) + "-" + to_string(current_month) + "-" + to_string(current_day);
        //cout << today_date;

        struct tm today_tm = {};
        istringstream today_ss(today_date);
        today_ss >> get_time(&today_tm, "%Y-%m-%d");

        if (mktime(&member_end_tm) < mktime(&today_tm)) {
            cout << "\n\t\t\tPlease renew your membership before making a booking." << endl;
            cout << "\t\t\t";
            system("pause");
            MemberMenu(Member_id);
            return;
        }
    }

    string findbyname_query = "select MAX(NO) from booking";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {

        while ((row = mysql_fetch_row(res)))
        {

            string duration;
            string Device_id, time;
            int end_time;
            string end_time2;
            
            int year, month, day;
            int booking_increment = stoi(row[0]) + 1;
            booking_id = "B0" + to_string(booking_increment);
        DATE:
            cout << "\n\t\t\tPlease Enter your booking date which is today's date or future date(YYYY M D):";
            cin >> year >> month >> day;

            if (!isNotPreviousDate(year, month, day))
            {
                std::cout << "\n\t\t\tError: Entered date is a previous date.Please Enter a present date or future date" << std::endl;
                goto DATE;
            }
            // Combine year, month, and day into a single date string
            std::string booking_date1 = combineDate(year, month, day);
            
           
            std::stringstream ss;
            ss << "20" << std::setfill('0') << std::setw(2) << (ltm->tm_year - 100) << "-"
                << std::setfill('0') << std::setw(2) << (ltm->tm_mon + 1) << "-"
                << std::setfill('0') << std::setw(2) << ltm->tm_mday;
            std::string today1 = ss.str();

            if (booking_date1 == today1)
            {
               

                Device_checker();
                cout << endl;
            devs:
                cout << "\n\t\t\tChoose your device : ";
                cin >> Device_id;
                string finddevice_query = "select device_id from device where device_id = '" + Device_id + "'";
                const char* qd = finddevice_query.c_str();
                qstate = mysql_query(conn, qd);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    if (mysql_num_rows(res) <= 0)
                    {
                        cout << "\n\t\t\tNo such devices available\n\t\t\t";
                        system("pause");
                        goto devs;
                    }
                }
                cout << "\t\t\tAvailable times are : \n";
                string findbydevice_query = "select time_table.time from time_table WHERE NOT EXISTS(SELECT * FROM BOOKING WHERE  booking.Booking_date = '" + booking_date1 + "' and booking.Device_id='" + Device_id + "' and time_table.time_stamp = booking.start_time_stamp)having time_table.time>'" + time1 + "' and time_table.time<'22:00:00'order by time_table.time asc";
                const char* q = findbydevice_query.c_str();
                qstate = mysql_query(conn, q);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    while ((row = mysql_fetch_row(res)))
                    {
                        cout << "\t\t\t" << row[0] << endl;
                    }
                }
            ti:
                cout << "\n\t\t\tChoose your time(ex:09:00:00) : ";
                cin >> time;
                string findtime = "select time from time_table where time = '" +time+"'";
                const char* qt = findtime.c_str();
                qstate = mysql_query(conn, qt);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    if (mysql_num_rows(res) <= 0)
                    {
                        cout << "\n\t\t\tNo such time available\n\t\t\tPlease enter in correct format(09:00:00)\n\t\t\t";
                        system("pause");
                        goto ti;
                    }
                }
            durs:
                cout << "\n\t\t\tChoose your duration(minimum 1 hour) : ";
                cin >> duration;
                if (time == "21:00:00" && duration > "1")
                {
                    cout << "\n\t\t\tThe duration is only allowed 1 hour duration...Thank you!!";
                    goto durs;

                }
                end_time = stoi(time) + stoi(duration);
                end_time2 = to_string(end_time) + ":00:00";

                string findbytime_query = "select time_stamp from time_table where time like '%" + time + "%' ";
                const char* d = findbytime_query.c_str();
                qstate = mysql_query(conn, d);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    while ((row = mysql_fetch_row(res)))
                    {

                        string slot = row[0];
                        string findbytime_query = "select time_stamp from time_table where time like '%" + end_time2 + "%' ";
                        const char* d = findbytime_query.c_str();
                        qstate = mysql_query(conn, d);
                        res = mysql_store_result(conn);

                        if (!qstate)
                        {
                            while ((row = mysql_fetch_row(res)))
                            {

                                string endtimeslot = row[0];
                                string insert_query = "insert into Booking(Booking_id ,Member_id, Device_id, Booking_date,Start_time,End_time,Duration,start_time_stamp,end_time_stamp) values ('" + booking_id + "','" + Member_id + "','" + Device_id + "','" + booking_date1 + "','" + time + "','" + end_time2 + "','" + duration + "', '" + slot + "','" + endtimeslot + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                res = mysql_store_result(conn);

                                if (!qstate)
                                {


                                    cout << "\t\t\tDatabase has been updated";
                                    payment(Member_id, booking_id);



                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed" << endl;
                                    MemberMenu(Member_id);

                                }
                            }

                        }
                        else
                        {
                            cout << "Connection failed" << endl;
                            MemberMenu(Member_id);

                        }




                    }


                }

                
                
            }
            else
            {
               
                Device_checker();
                cout << endl;
                cout << "\n\t\t\tChoose your device : ";
                cin >> Device_id;
                cout << "\t\t\tAvailable times are : \n";
                string findbydevice_query = "select time_table.time from time_table WHERE NOT EXISTS(SELECT * FROM BOOKING WHERE  booking.Booking_date = '" + booking_date1 + "' and booking.Device_id='" + Device_id + "'  and time_table.time_stamp = booking.start_time_stamp) having(time_table.time<'22:00:00') ORDER BY time_table.time ASC ";
                const char* q = findbydevice_query.c_str();
                qstate = mysql_query(conn, q);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    while ((row = mysql_fetch_row(res)))
                    {
                        cout << "\t\t\t"<<row[0] << endl;
                    }
                }
                cout << "\n\t\t\tChoose your time(ex:09:00:00) : ";
                cin >> time;
                cout << "\n\t\t\tChoose your duration : ";
                cin >> duration;
                end_time = stoi(time) + stoi(duration);
                end_time2 = to_string(end_time) + ":00:00";

                string findbytime_query = "select time_stamp from time_table where time like '%" + time + "%' ";
                const char* d = findbytime_query.c_str();
                qstate = mysql_query(conn, d);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    while ((row = mysql_fetch_row(res)))
                    {

                        string slot = row[0];
                        string findbytime_query = "select time_stamp from time_table where time like '%" + end_time2 + "%' ";
                        const char* d = findbytime_query.c_str();
                        qstate = mysql_query(conn, d);
                        res = mysql_store_result(conn);

                        if (!qstate)
                        {
                            while ((row = mysql_fetch_row(res)))
                            {

                                string endtimeslot = row[0];
                                string insert_query = "insert into Booking(Booking_id ,Member_id, Device_id, Booking_date,Start_time,End_time,Duration,start_time_stamp,end_time_stamp) values ('" + booking_id + "','" + Member_id + "','" + Device_id + "','" + booking_date1 + "','" + time + "','" + end_time2 + "','" + duration + "', '" + slot + "','" + endtimeslot + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                res = mysql_store_result(conn);

                                if (!qstate)
                                {


                                    cout << "\t\t\tDatabase has been updated";
                                    payment(Member_id, booking_id);



                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed" << endl;
                                    MemberMenu(Member_id);

                                }
                            }

                        }
                        else
                        {
                            cout << "Connection failed" << endl;
                            MemberMenu(Member_id);

                        }




                    }


                }


            }


        }
    }
    else
    {
        cout << "Connection failed" << endl;
        MemberMenu(Member_id);
    }
}

void check_canceltime()
{
    system("color 0D");
    string start_time;
    string checktime_query = "select Start_time from Booking ";
    const char* qr = checktime_query.c_str();
    qstate = mysql_query(conn, qr);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << row[0] << endl;
            if (time1 > row[0])
            {
                cout << "\t\t\tSorry..The time had been exceeded...You are not allowed to cancel the booking";
            }

        }
    }
}




void MemberLogin()
{
    system("color 0D");
    int option;
    char Flag;
    int qstate;
    system("cls");
c:
    cout << "\n\t\t\t  RH CYBERCAFE MANAGEMENT SYSTEM\t\t\t \n" << endl;
    cout << "\t\t\t=============MEMBER LOGIN==================\t\t\t " << endl;
    string  Member_id, Member_pass;

    cout << "\t\t\tMember ID : ";
    cin >> Member_id;
    if (Member_id == "0")
    {
        goto c;
    }
    cout << "\t\t\tPassword : ";
    int i = 0;
    char a;
    for (i = 0;;)
    {
        a = _getch();
        
        if (a >= 'a' && a <= 'z' || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
        {

            Member_pass += a;
            ++i;
            cout << "*";

        }
        if (a == '\b' && i >= 1)
        {
            cout << "\b \b";
            --i;
        }
        if (a == '\r')
        {
            break;
        }

    }

    if (Member_pass == "0")
    {
        cout << "\n\t\t\tInvalid Password";
        goto c;
    }
    string checkUser_query = "select Member_id from Member where Member_id like BINARY '" + Member_id + "' and Member_pass like BINARY '" + Member_pass + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);
    res = mysql_store_result(conn);
    do
    {
        if ((row = mysql_fetch_row(res)))
        {

            cout << "\n\t\t\t[Login Successful]...\n";
            cout << "\t\t\t";
            system("pause");
            system("cls");
            MemberMenu(Member_id);
        }
        else
        {
            cout << "\n\n\t\t\tYou have entered  a wrong password or id.\n\t\t\tPress 'Y' to try again:";
            cin >> Flag;
            if (Flag == 'y' || Flag == 'Y')
            {
                cout << "\n\t\t\t[1] RETURN TO LOGIN" << endl;
                cout << "\t\t\t[2] FORGOT PASSWORD" << endl;
                cout << "\t\t\tPlease Enter your choice (1/2): ";
                cin >> option;
                if (option == 1)
                {
                    system("cls");
                    goto c;
                }
                else if (option == 2)
                {
                    string Member_ic;
ft:
                    cout << "\t\t\tEnter Member IC Number/Phone Number :";
                    cin >> Member_ic;
                    string search_query = " select Member_id,Member_name,Member_ic,Member_pass,Member_phone from Member where Member_ic ='" + Member_ic + "' or Member_phone ='" + Member_ic + "' ";
                    const char* q = search_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (qstate)
                    {
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res))
                        {

                            cin.ignore(1, '\n');
                            string Member_newpass;
                            cout << "\t \t \t \t\t\tPlease Insert the new Member Password : ";
                            getline(cin, Member_newpass);
                            string update_query = "update Member set Member_pass  = '" + Member_newpass + "' where Member_ic = '" + Member_newpass + "'";
                            const char* q = update_query.c_str();
                            qstate = mysql_query(conn, q);
                            cout << " ";
                            cout << "\t\t\tSuccesfully modified the password" << endl;
                            main();
                        }
                    }
                    else
                    {
                        cout << "\n\t\t\tInvalid IC Number/Phone Number";
                        goto ft;
                    }
                }
                else
                {
                    cout << "\t\t\tInvalid option";
                    goto c;
                }
            }
            else
            {
                system("cls");
                LoginMenu();
            }
        }
    }
    while (qstate);
}

//Add Member Details
void MemberRegistration()
{
    system("cls");
    system("color 0D");
    cout << "\t\t\t Welcome to Member Registration Portal \t\t\t\n";
    int qstate;
    string Member_name = "";
    string Member_ic = "";
    string Member_phone = "";
    string Member_pass;
    string Member_id = "";
    cin.ignore(1, '\n');
NAME:
    cout << "\t\t\tEnter Member Name: ";
    getline(cin, Member_name);
    if (Member_name == "0")
    {
        goto NAME;
    }
    else if (Member_name.size() > 50)
    {
        cout << "\n\t\t\t\t MAX CHARACTER IS 50" << endl;
        goto NAME;
    }
    else if (Member_name.size() == 0)
    {
        cout << "\n\t\t\t\t INVALID CHARACTER SIZE" << endl;
        goto NAME;
    }
IC:

    cout << "\t\t\tEnter Identification Card Number: ";
    getline(cin, Member_ic);
    for (int i = 0; i < Member_ic.length(); i++)
    {
        if (!isdigit(Member_ic[i]) || Member_ic.length() < 12 || Member_ic.length() > 12)
        {
            cout << "\t\t\tInvalid Identification Card Number\n";
            goto IC;
        }
    }
    string checkUserc_query = "select Member_ic from Member where Member_ic = '" + Member_ic + "'";
    const char* cui = checkUserc_query.c_str();
    qstate = mysql_query(conn, cui);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t Identification Card Number registered earlier...\n";
        goto IC;
    }
PH:
    cout << "\t\t\tEnter Member Phone Number: ";

    getline(cin, Member_phone);
    for (int i = 0; i < Member_phone.length(); i++)
    {
        if (!isdigit(Member_phone[i]) || (Member_phone.length() < 10 || Member_phone.length() > 11))
        {
            cout << "\t\t\tInvalid Phone Number\n ";
            goto PH;
        }
    }
    string checkUserp_query = "select Member_phone from Member where Member_phone = '" + Member_phone + "'";
    const char* cup = checkUserp_query.c_str();
    qstate = mysql_query(conn, cup);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t Phone Number have been registered earlier..\n";
        goto PH;
    }
ID:
    cout << "\t\t\tEnter a Member id  : ";
    getline(cin, Member_id);
    string checkUseri_query = "select Member_id from Member where Member_id = '" + Member_id + "'";
    const char* cud = checkUseri_query.c_str();
    qstate = mysql_query(conn, cud);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t Member ID registered earlier...\n";
        goto ID;
    }
PASS:

    bool upper_case = false; //saves the result if upper-case characters were found.
    bool lower_case = false; //same for lower-case
    bool number_case = false; //...

    std::regex upper_case_expression{ "[A-Z]+" }; //here is the very simple expression for upper_case search
    std::regex lower_case_expression{ "[a-z]+" }; //for lower-case
    std::regex number_expression{ "[0-9]+" }; //...

    bool done = false; //let's assume we're not done

    do
    { //do ask-for-password as long were not done

        cout << "\t\t\tEnter Member Password(The password must be between 5 - 10 and should have uppercase,lowercase and numbers): ";
        getline(std::cin, Member_pass); //get input

        if (Member_pass.length() <= 5 && Member_pass.length() >= 10) { //too short!
            std::cout << "\t\t\tInvalid password! Try again . . .\n\n";

        }
        else
        {

            upper_case = std::regex_search(Member_pass, upper_case_expression); //save the result, if the expression was found.
            lower_case = std::regex_search(Member_pass, lower_case_expression); //....
            number_case = std::regex_search(Member_pass, number_expression);


            //like: sum_of_positive_results = 1 + 0 + 1  (true/false as an integer)
            int sum_of_positive_results = upper_case + lower_case + number_case;

            if (sum_of_positive_results < 3) { //not enough booleans were true!
                std::cout << "\t\t\tInvalid password! Try again . . .\n\n";
                cout << "\t\t\t*THE PASSWORD SHOULD HAVE UPPERCASE,LOWERCASE,NUMBERS \n\n";
            }
            else { //otherwise it's valid!
                std::cout << "\t\t\tThat's a valid Password!" << std::endl;
                done = true;
            }
        }


    } while (!done);

    if (Member_pass == "0")
    {
        goto PASS;
    }
    time_t now = time(0);
    tm* ltm = localtime(&now);
    time_t current = time(0);
    
    string Member_type1 = "BASIC";
    string Member_type2 = "PREMIUM";
    string Member_type3 = "STUDENT";
    char stdopt;
    cout << "\n\n\t\t\tSTUDENT MEMBERSHIP PLAN BENEFITS\n";
    cout << "\t\t\t---------------------------------------------------------------------------------------\n";
    printf("\t\t\t| %-30s | %-50s |\n", "Membership Plan ", "STUDENT");
    printf("\t\t\t| %-30s | %-50s |\n", "Benefits", "#Gain 15% discount for each device booking");
    printf("\t\t\t| %-30s | %-50s |\n", "     ", "#20 points per booking");
    printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Each registration will be valid for 3 months");
    printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Membership Renewal for 6 months with RM 50");
    printf("\t\t\t---------------------------------------------------------------------------------------\n");
    cout << "\t\t\tAre you a student(y/n):";
    cin >> stdopt;
    if (stdopt == 'y' || stdopt == 'Y')
    {
        string checkUser_query = "select * from Member where Member_id = '" + Member_id + "' and Member_pass = '" + Member_pass + "' and Member_ic = '" + Member_ic + "'";
        const char* cq = checkUser_query.c_str();
        qstate = mysql_query(conn, cq);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                cout << "\t\t\tId has been taken please retry ";
                MemberRegistration();
            }
            else
            {
                
                string insert_query = "insert into Member (Member_name, Member_ic, Member_phone, Member_id, Member_pass,Member_start,Member_end,Member_type) values ('" + Member_name + "','" + Member_ic + "','" + Member_phone + "','" + Member_id + "','" + Member_pass + "','" + today + "','" + end_date + "','" + Member_type3 + "')";
                const char* q = insert_query.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate)
                {
                    cout << endl << "\n\t\t\tSuccessfully Registered.\n" << endl;
                    cout << "\t\t\t";
                    system("pause");
                    main();
                }
            }
        }
    }
    else
    {
        opt:
        cout << "\n\n\t\t\tMEMBERSHIP PLANS\n";
        cout << "\t\t\t---------------------------------------------------------------------------------------\n";
        printf("\t\t\t| %-30s | %-50s |\n", "Membership Plan ", "BASIC");
        printf("\t\t\t| %-30s | %-50s |\n", "Benefits", "#Gain 20% discount for each device booking");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#20 points per booking");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Each registration will be valid for 3 months");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Membership Renewal for 1 years with RM 100");
        cout << endl;
        printf("\t\t\t| %-30s | %-50s |\n", "Membership Plan ", "PREMIUM");
        printf("\t\t\t| %-30s | %-50s |\n", "Benefits", "#Gain 30% discount for each device booking");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#40 points per booking");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Each registration will be valid for 3 months");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Membership Renewal for 2 years with RM 200");
        printf("\t\t\t---------------------------------------------------------------------------------------\n");
        int qstate;
        int mem_option;
        cout << "\t\t\tPlease Choose a membership plan\n";
        cout << "\t\t\t1.Basic Membership\n";
        cout << "\t\t\t2.Premium Membership : ";
        cin >> mem_option;
        if (mem_option == 1)
        {
            string checkUser_query = "select * from Member where Member_id = '" + Member_id + "' and Member_pass = '" + Member_pass + "' and Member_ic = '" + Member_ic + "'";
            const char* cq = checkUser_query.c_str();
            qstate = mysql_query(conn, cq);
            if (!qstate)
            {
                res = mysql_store_result(conn);
                if (res->row_count == 1)
                {
                    cout << "\t\t\tId has been taken please retry ";
                    MemberRegistration();
                }
                else
                {
                    string insert_query = "insert into Member (Member_name, Member_ic, Member_phone, Member_id, Member_pass,Member_start,Member_end,Member_type) values ('" + Member_name + "','" + Member_ic + "','" + Member_phone + "','" + Member_id + "','" + Member_pass + "','" + today + "','" + end_date + "','" + Member_type1 + "')";
                    const char* q = insert_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (!qstate)
                    {
                        cout << endl << "\n\t\t\tSuccessfully Registered.\n" << endl;
                        cout << "\t\t\t";
                        system("pause");
                        main();
                    }
                }
            }
            else
            {
                cout << "\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;
                MemberRegistration();
            }
        }
        if (mem_option == 2)
        {
            string checkUser_query = "select * from Member where Member_id = '" + Member_id + "' and Member_pass = '" + Member_pass + "' and Member_ic = '" + Member_ic + "'";
            const char* cq = checkUser_query.c_str();
            qstate = mysql_query(conn, cq);
            if (!qstate)
            {
                res = mysql_store_result(conn);
                if (res->row_count == 1)
                {
                    cout << "\t\t\tId has been taken please retry ";
                    MemberRegistration();
                }
                else
                {
                    string insert_query = "insert into Member (Member_name, Member_ic, Member_phone, Member_id, Member_pass,Member_start,Member_end,Member_type) values ('" + Member_name + "','" + Member_ic + "','" + Member_phone + "','" + Member_id + "','" + Member_pass + "','" + today + "','" + end_date + "','" + Member_type2 + "')";
                    const char* q = insert_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (!qstate)
                    {
                        cout << endl << "\n\t\t\tSuccessfully Registered.\n" << endl;
                        cout << "\t\t\t";
                        system("pause");
                        main();
                    }
                }
            }
            else
            {
                cout << "\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;
                MemberRegistration();
            }
        }
        else
        {
            cout << "\t\t\tPlease choose the membership plan either from 1 or 2";
            goto opt;
        }
        
    }
}



void MemberMenu(string Member_id)
{
set:
    system("cls");
    system("color 0D");
    int choice;
    cout << "\n\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\t|                          MEMBER MENU                         |\t\t\t" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|\t\t\t" << endl;
    cout << "\t\t\t|  [1] MEMBERSHIP RENEWAL                                      |\t\t\t" << endl;
    cout << "\t\t\t|  [2] MEMBER BOOKING                                          |\t\t\t" << endl;
    cout << "\t\t\t|  [3] PAYMENT HISTORY                                         |\t\t\t" << endl;
    cout << "\t\t\t|  [0] EXIT                                                    |\t\t\t" << endl;
    cout << "\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\tPlease Enter your choice (0 - 3) : ";
    cin >> choice;
    switch (choice)
    {
    case 1:Membership_renew(Member_id);
        break;
    case 2:MemberBook(Member_id);
        break;
    case 3:PaymentHistory(Member_id);
        break;
    case 0:LoginMenu();
        break;


    default:
        cout << "\t\t\tPlease choose between 0 to 3."<<endl;
        cout << "\t\t\t";

        system("pause");
        system("cls");
        goto set;
        break;

    }

}

//Mimic barcode to show the customers and the usage is normally barcode will be storing the payment details
void barcode(string payment_id)
{
    system("color 0C");
    const string bars[] = { "101001101101", "110100101011", "101100101011", "110110010101", "101001101011",
                       "110100110101", "101100110101", "101001011011", "110100101101", "101100101101",
                       "110101001011", "101101001011", "110110100101", "101011001011", "110101100101",
                       "101101100101", "101010011011", "110101001101", "101101001101", "101011001101",
                       "110101010011", "101101010011", "110110101001", "101011010011", "110101101001",
                       "101101101001", "101010110011", "110101011001", "101101011001", "101011011001",
                       "110010101011", "100110101011", "110011010101", "100101101011", "110010110101",
                       "100110110101", "100101011011", "110010101101", "100110101101", "101011110101" };

    const int barCount = 43;
    string code = payment_id; // PUT PAYMENT ID HERE
    cout << "\n\t\t\tBarcode for Payment No. : " << code << endl;
    cout << "\t\t\t--------------------------" << endl;

    // Convert each character to its corresponding bar pattern
    string barcode;
    for (char c : code) {
        int index = (c >= '0' && c <= '9') ? c - '0' : (c - 'A' + 8); 
        barcode += bars[index] + "0"; // Add a space between characters
    }

    for (int k = 0; k < 7; k++) // Adjust the height of the barcode
    {
        cout << "\t\t\t"; // Three tabs before printing the barcode
        for (int i = 0; i < barcode.length(); i++)
        {
            if (barcode[i] == '1')
            {
                cout << "\xDB"; // Print a full block for bars
            }
            else
            {
                cout << " "; // Print a space for spaces
            }
        }
        cout << endl;
    }

}

void balance_calculation(string payment_id,string booking_id)
{
    system("color 0C");
    double price;
    string findbypay_query = "select price from payment where payment_id = '"+ payment_id+"'";
    const char* q = findbypay_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {

        while ((row = mysql_fetch_row(res)))
        {
            cout << "\n\t\t\tEnter the payment done by the customer :";
            cin >> price;
            double balance = price - stod(row[0]);
            cout << balance<<fixed<<setprecision(2)<<endl;

        }
    }
}

void Invoice_allocate(string booking_id, string payment_id)
{

    string Staff_id;
    system("color 0C");
    int opt;
    cout << "\n\t\t\tPayment Methods:";
    cout << "\n\t\t\t [1] QR PAYMENT ";
    cout << "\n\t\t\t [2] Cash Payment";
    cout << "\n\t\t\tPlease Enter customer's choice of payment (1/2):";
    cin >> opt;
    if (opt == 1)
    {
        
        string insert_query = "insert into Invoice ( payment_id, Invoice_date,Invoice_time) values ('" + payment_id + "','" + today + "','" + time1 + "')";
        const char* q = insert_query.c_str();
        qstate = mysql_query(conn, q);
        {
            //cout << "\n\t\t\tInvoice updated";
            string invoice_query = "select booking.Member_id ,booking.Booking_id, Booking.Start_time, Booking.End_time, Booking.Duration, Payment.Price,Invoice.Invoice_Number,Invoice.Invoice_date,Invoice.Invoice_time from booking LEFT Join Payment on booking.Booking_id = payment.Booking_id Right Join Invoice on Invoice.Payment_id = Payment.Payment_id where payment.Booking_id =  '" + booking_id + "'";
            const char* q = invoice_query.c_str();
            qstate = mysql_query(conn, q);
            res = mysql_store_result(conn);
            if (!qstate)
            {

                while ((row = mysql_fetch_row(res)))
                {

                    string f1 = row[0];//member_id
                    string f2 = row[1];//booking_id
                    string f3 = row[2];//start_time
                    string f4 = row[3];//end_time
                    string f5 = row[4];//duration
                    string f6 = row[5];//price

                    string name = payment_id + ".txt";
                    ofstream file(name);

                    file << "\n\t\t RH CYBERCAFE MANAGEMENT SYSTEM\t\t";
                    file << setw(15) << "\t\t\t  Invoice";
                    file << "\n\nInvoice No :" << row[6];
                    file << "\n\nInvoice Date:" << row[7];
                    file << "\n\nTime:" << row[8];
                    file << "\n\nMemberId :" << row[0];


                    file << "\n-------------------------------------";
                    //file << setw(10) << "\n BookingID   |" << setw(10) << " StartTime   |" << setw(10) << "EndTime      |" << setw(10) << " Duration    |" << setw(10) << " Amount  |";
                    file << setw(10) << "\n BookingID   | " << setw(10) << f2 << setw(2) << "|";
                    file << setw(10) << "\n StartTime   | " << setw(10) << f3 << setw(2) << "|";
                    file << setw(10) << "\n EndTime     | " << setw(10) << f4 << setw(2) << "|";
                    file << setw(10) << "\n Duration    | " << setw(10) << f5 << setw(2) << "|";
                    file << setw(10) << "\n Amount      | " << setw(10) << f6 << setw(2) << "|";


                    for (int i = 0; i < 10; i++)
                    {

                        file << "\n";
                        file << setw(14) << "|" << setw(13) << "|";
                    }
                    file << "\n-------------------------------------";
                    file.close();
                    cout << "\n";
                    qrcodes();
                    cout << "\t\t\t";
                    system("pause");
                    StaffMenu(Staff_id);
                }


            }
        }

        
    }
    else if(opt == 2)
    {
        
        double price;
        string findbypay_query = "select price from payment where payment_id = '" + payment_id + "'";
        const char* q = findbypay_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        if (!qstate)
        {

            while ((row = mysql_fetch_row(res)))
            {
                cout << "\n\t\t\tEnter the payment done by the customer :";
                cin >> price;
                double balance = price - stod(row[0]);
                cout <<"\n\t\t\tBalance:" << balance << fixed << setprecision(2) << endl;
                cout << "\t\t\t";
                barcode(payment_id);//Mimic barcode to show the customers and the usage is normally barcode will be storing the payment details
                string insert_query = "insert into Invoice ( payment_id, Invoice_date,Invoice_time) values ('" + payment_id + "','" + today + "','" + time1 + "')";
                const char* q = insert_query.c_str();
                qstate = mysql_query(conn, q);
                {
                    //cout << "\n\t\t\tInvoice updated";
                    string invoice_query = "select booking.Member_id ,booking.Booking_id, Booking.Start_time, Booking.End_time, Booking.Duration, Payment.Price,Invoice.Invoice_Number,Invoice.Invoice_date,Invoice.Invoice_time from booking LEFT Join Payment on booking.Booking_id = payment.Booking_id Right Join Invoice on Invoice.Payment_id = Payment.Payment_id where payment.Booking_id =  '" + booking_id + "'";
                    const char* q = invoice_query.c_str();
                    qstate = mysql_query(conn, q);
                    res = mysql_store_result(conn);
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {

                            string f1 = row[0];//member_id
                            string f2 = row[1];//booking_id
                            string f3 = row[2];//start_time
                            string f4 = row[3];//end_time
                            string f5 = row[4];//duration
                            string f6 = row[5];//price

                            string name = payment_id + ".txt";
                            ofstream file(name);

                            file << "\n\t\t RH CYBERCAFE MANAGEMENT SYSTEM\t\t";
                            file << setw(15) << "\n\t\t\t  Invoice";
                            file << "\n\nInvoice No :" << row[6];
                            file << "\n\nInvoice Date:" << row[7];
                            file << "\n\nTime:" << row[8];
                            file << "\n\nMemberId :" << row[0];


                            file << "\n\n\n-------------------------------------";
                            //file << setw(10) << "\n BookingID   |" << setw(10) << " StartTime   |" << setw(10) << "EndTime      |" << setw(10) << " Duration    |" << setw(10) << " Amount  |";
                            file << setw(10) << "\n BookingID   | " << setw(10) << f2 << setw(2) << "|";
                            file << setw(10) << "\n StartTime   | " << setw(10) << f3 << setw(2) << "|";
                            file << setw(10) << "\n EndTime     | " << setw(10) << f4 << setw(2) << "|";
                            file << setw(10) << "\n Duration    | " << setw(10) << f5 << setw(2) << "|";
                            file << setw(10) << "\n Amount      | " << setw(10) << f6 << setw(2) << "|";
                            file << setw(10) << "\n Cash        | " << setw(10) << price <<setw(2) << "|";
                            file << setw(10) << "\n Balance     | " << setw(10) << balance << setw(2) << "|";
                           
                            //file << setw(10) << f2 << setw(12) << f3 << setw(14) << f4 << setw(14) << f5 << setw(14) << f6;


                            for (int i = 0; i < 10; i++)
                            {

                                file << "\n";
                                file << setw(14) << "|" << setw(13) << "|" ;
                            }
                            file << "\n-------------------------------------";
                            file.close();

                            
                            cout << "\t\t\t";
                            system("pause");
                            StaffMenu(Staff_id);
                        }


                    }
                }
            }
        
        }

       
    }
    

}

void Student_payment(string booking_id, string payment_id, string member_id)
{
    system("color 0C");
    char mem_opt;
    string Staff_id;
    string num1 = "09:00:00";
    int num2 = stoi(num1);

    string num3 = "14:00:00";
    int num4 = stoi(num3);

    string num5 = "22:00:00";
    int num6 = stoi(num5);

    string num7 = "18:00:00";
    int num8 = stoi(num7);
    cout << "\n\t\t\t*********************************************************************************" << endl;
    cout << "\n\t\t\t\t\t PAYMENT FOR THE BOOKING" << endl;
    cout << "\n\t\t\t*********************************************************************************" << endl;

    string findbytime_query = "SELECT Booking.Device_id,Booking.Start_time,Booking.End_time,Booking.Duration from Booking where Booking_id = '" + booking_id + "'";
    const char* q = findbytime_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while (row = mysql_fetch_row(res))
        {

            if ((stoi(row[1]) == num2 && stoi(row[2]) == num4))
            {
                
                cout <<"\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price1 = 15.00;
                double discount_price1 = 0.85 * price1;
                cout << "\n\t\t\tPrice : RM" << discount_price1;
                string duration1 = row[3];//5
               
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                              
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n) : ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                        
                                        StaffMenu(Staff_id);

                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice_allocate(booking_id, payment_id);
                                            StaffMenu(Staff_id);
                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }
                                        
                                        
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {

                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {

                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                                
                            }
                        }
                    }


                

            }
            else if (stoi(row[1]) >= num2 && stoi(row[2]) <= num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price2 = 5.00;
                double total_price = price2 * stoi(row[3]);
                double discount_price2 = 0.85 * total_price;
                cout << "\n\t\t\tPrice : RM" << discount_price2;
                string duration2 = row[3];
               
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                       
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) -  100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\t\t\tThe points have been deducted as a payment";
                                        
                                        StaffMenu(Staff_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice_allocate(booking_id, payment_id);
                                            StaffMenu(Staff_id);
                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }


                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                

            }
            else if (stoi(row[1]) == num8 && stoi(row[2]) == num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price3 = 10.00;
                double discount_price3 = 0.85 * price3;
                cout << "\n\t\t\tPrice : RM" << discount_price3;
                string duration3 = row[3];//4
                
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                       
                                        StaffMenu(Staff_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice_allocate(booking_id, payment_id);
                                            StaffMenu(Staff_id);
                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }


                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }

                            }
                        }
                    }


                        

                    

                
            }
            else
            {
                cout << "\t\t\tConnection failed!!";
            }

        }
    }
}

void Premium_payment(string booking_id, string payment_id, string member_id)
{
    system("color 0C");
    char mem_opt;
    string Staff_id;
    string num1 = "09:00:00";
    int num2 = stoi(num1);

    string num3 = "14:00:00";
    int num4 = stoi(num3);

    string num5 = "22:00:00";
    int num6 = stoi(num5);

    string num7 = "18:00:00";
    int num8 = stoi(num7);
    cout << "\n\t\t\t*********************************************************************************" << endl;
    cout << "\n\t\t\t\t\t PAYMENT FOR THE BOOKING" << endl;
    cout << "\n\t\t\t*********************************************************************************" << endl;

    string findbytime_query = "SELECT Booking.Device_id,Booking.Start_time,Booking.End_time,Booking.Duration from Booking where Booking_id = '" + booking_id + "'";
    const char* q = findbytime_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while (row = mysql_fetch_row(res))
        {

            if ((stoi(row[1]) == num2 && stoi(row[2]) == num4))
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price1 = 15.00;
                double discount_price1 = 0.7 * price1;
                cout << "\n\t\t\tPrice : RM" << discount_price1;
                string duration1 = row[3];//5
               
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qe = points_query.c_str();
                    qstate = mysql_query(conn, qe);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                       
                                        StaffMenu(Staff_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 40;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            
                                            Invoice_allocate(booking_id, payment_id);
                                            StaffMenu(Staff_id);
                                          
                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }

                                        
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 40;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {

                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                

            }
            else if (stoi(row[1]) >= num2 && stoi(row[2]) <= num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price2 = 5.00;
                double total_price = price2 * stoi(row[3]);
                double discount_price2 = 0.7 * total_price;
                cout << "\n\t\t\tPrice : RM" << discount_price2;
                string duration2 = row[3];
                
                   
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qn = points_query.c_str();
                    qstate = mysql_query(conn, qn);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                        
                                        StaffMenu(Staff_id);

                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 40;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            
                                            Invoice_allocate(booking_id, payment_id);
                                            StaffMenu(Staff_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }


                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 40;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        
                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                

            }
            else if (stoi(row[1]) == num8 && stoi(row[2]) == num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price3 = 10.00;
                double discount_price3 = 0.7 * price3;
                cout << "\n\t\t\tPrice : RM" << discount_price3;
                string duration3 = row[3];//4
                
                    
                    string pointsp_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qn = pointsp_query.c_str();
                    qstate = mysql_query(conn, qn);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                       
                                        StaffMenu(Staff_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 40;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {

                                            Invoice_allocate(booking_id, payment_id);
                                            StaffMenu(Staff_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }


                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 40;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {

                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }


                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                
            }
            else
            {
                cout << "\t\t\tConnection failed!!";
            }

        }
    }
}

void Basic_payment(string booking_id,string payment_id,string member_id)
{
    system("color 0C");
    char mem_opt;
    string Staff_id;
    string num1 = "09:00:00";
    int num2 = stoi(num1);

    string num3 = "14:00:00";
    int num4 = stoi(num3);

    string num5 = "22:00:00";
    int num6 = stoi(num5);

    string num7 = "18:00:00";
    int num8 = stoi(num7);
    cout << "\n\t\t\t*********************************************************************************" << endl;
    cout << "\n\t\t\t\t\t PAYMENT FOR THE BOOKING" << endl;
    cout << "\n\t\t\t*********************************************************************************" << endl;

    string findbytime_query = "SELECT Booking.Device_id,Booking.Start_time,Booking.End_time,Booking.Duration from Booking where Booking_id = '" + booking_id + "'";
    const char* q = findbytime_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while (row = mysql_fetch_row(res))
        {

            if ((stoi(row[1]) == num2 && stoi(row[2]) == num4))
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price1 = 15.00;
                double discount_price1 = 0.8 * price1;//12
                cout << "\n\t\t\tPrice : RM" << discount_price1;
                string duration1 = row[3];//5
                
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n) : ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                       
                                        StaffMenu(Staff_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice_allocate(booking_id, payment_id);
                                            StaffMenu(Staff_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                    

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price1) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                

            }
            else if (stoi(row[1]) >= num2 && stoi(row[2]) <= num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price2 = 5.00;
                double total_price = price2 * stoi(row[3]);
                double discount_price2 = 0.8 * total_price;//4
                cout << "\n\t\t\tPrice : RM" << discount_price2;
                string duration2 = row[3];
                
                   
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {
                        

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n): ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tThe points have been deducted as a payment";
                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice_allocate(booking_id, payment_id);
                                            StaffMenu(Staff_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price2) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                

            }
            else if (stoi(row[1]) == num8 && stoi(row[2]) == num6)
            {
                cout << "\t\t\t" << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                double price3 = 10.00;
                double discount_price3 = 0.8 * price3;//8
                cout << "\n\t\t\tPrice : RM" << discount_price3;
                string duration3 = row[3];//4
                
                   
                    string points_query = "select member_points from Member where Member_id ='" + member_id + "' ";
                    const char* qp = points_query.c_str();
                    qstate = mysql_query(conn, qp);
                    res = mysql_store_result(conn);
                    int mem_points;
                    if (!qstate)
                    {

                        while ((row = mysql_fetch_row(res)))
                        {
                            if (stoi(row[0]) >= 100)
                            {
                                
                                cout << "\n\n\t\t\tAvailable points collected:" << row[0] << endl;
                                cout << "\t\t\tWould you like to redeem the points collected(y/n) : ";
                                cin >> mem_opt;
                                if (mem_opt == 'y' || mem_opt == 'Y')
                                {
                                    mem_points = stoi(row[0]) - 100;
                                    string updatemempoints_query = "update Member set Member_points ='" + to_string(mem_points) + "' where Member_id = '" + member_id + "' ";
                                    const char* qr = updatemempoints_query.c_str();
                                    qstate = mysql_query(conn, qr);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        cout << "\t\t\tThe points have been deducted as a payment";
                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);
                                    }
                                }
                                else if (mem_opt == 'n' || mem_opt == 'N')
                                {
                                    string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                    const char* q = insert_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    if (!qstate)
                                    {
                                        cout << "\n\t\t\tPayment updated";
                                        mem_points = stoi(row[0]) + 20;
                                        string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                        const char* q = update_query.c_str();
                                        qstate = mysql_query(conn, q);
                                        res = mysql_store_result(conn);
                                        if (!qstate)
                                        {
                                            Invoice_allocate(booking_id, payment_id);
                                            StaffMenu(Staff_id);

                                        }
                                        else
                                        {
                                            cout << "\t\t\tConnection failed!!";
                                        }
                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }

                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                            else
                            {
                                string insert_query = "insert into Payment(Payment_id,Booking_id,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + to_string(discount_price3) + "','" + today + "')";
                                const char* q = insert_query.c_str();
                                qstate = mysql_query(conn, q);
                                if (!qstate)
                                {
                                    cout << "\n\t\t\tPayment updated";
                                    mem_points = stoi(row[0]) + 20;
                                    string update_query = "update Member set Member_points = '" + to_string(mem_points) + "'where Member_id = '" + member_id + "' ";
                                    const char* q = update_query.c_str();
                                    qstate = mysql_query(conn, q);
                                    res = mysql_store_result(conn);
                                    if (!qstate)
                                    {
                                        Invoice_allocate(booking_id, payment_id);
                                        StaffMenu(Staff_id);

                                    }
                                    else
                                    {
                                        cout << "\t\t\tConnection failed!!";
                                    }
                                }
                                else
                                {
                                    cout << "\t\t\tConnection failed!!";
                                }
                            }
                        }
                    }


                        

                    

                
            }
            else
            {
                cout << "\t\t\tConnection failed!!";
            }

        }
    }
}
void payment_allocate(string member_id,string booking_id)
{
    system("color 0C");
    string payment_id;
    string findbypaymentno_query = "select MAX(NO) from payment";
    const char* qn = findbypaymentno_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while ((row = mysql_fetch_row(res)))
        {
            int paymentid_increment = stoi(row[0]) + 1;
            payment_id = "P0" + to_string(paymentid_increment);
            string plan[3] = { "BASIC","PREMIUM","STUDENT" };
            string findbymemtype_query = "select Member_type from Member where Member_id= '" + member_id + "'";
            const char* qn = findbymemtype_query.c_str();
            qstate = mysql_query(conn, qn);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                while ((row = mysql_fetch_row(res)))
                {

                    if (row[0] == plan[0])//Basic Membership
                    {
                        Basic_payment(booking_id, payment_id, member_id);
                    }
                    else if (row[0] == plan[1])//Premium Membership
                    {
                        Premium_payment(booking_id, payment_id, member_id);
                    }
                    else if (row[0] == plan[2])//Student Membership
                    {
                        Student_payment(booking_id, payment_id, member_id);
                    }
                    else
                    {
                        cout << "\t\t\tConnection failed!!";
                    }

                }

            }
        }
    }
}

//BACK UP PAYMENT
/*void calculation(string member_id, string booking_id)
{

    string start_time, end_time;

    int qstate;

    double price;
    string total_price;
    string payment_id;
    string findbypaymentno_query = "select MAX(NO) from payment";
    const char* qn = findbypaymentno_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {
        while ((row = mysql_fetch_row(res)))
        {
            int paymentid_increment = stoi(row[0]) + 1;
            payment_id = "P0" + to_string(paymentid_increment);

            string num1 = "09:00:00";
            int num2 = stoi(num1);

            string num3 = "14:00:00";
            int num4 = stoi(num3);

            string num5 = "22:00:00";
            int num6 = stoi(num5);

            string num7 = "18:00:00";
            int num8 = stoi(num7);
            cout << "\n*********************************************************************************" << endl;
            cout << "\n\t\t\t\t\t PAYMENT FOR THE BOOKING" << endl;
            cout << "\n*********************************************************************************" << endl;

            string findbytime_query = "SELECT Booking.Device_id,Booking.Start_time,Booking.End_time,Booking.Duration from Booking where Booking_id = '" + booking_id + "'";
            const char* q = findbytime_query.c_str();
            qstate = mysql_query(conn, q);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                while (row = mysql_fetch_row(res))
                {

                    if ((stoi(row[1]) >= num2 && stoi(row[2]) <= num4))
                    {
                        cout << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                        total_price = 5.00;
                        cout << "RM" << 5.00;


                    }
                    else if (stoi(row[1]) > num2 && stoi(row[2]) <= num6)
                    {
                        cout << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                        price = 3.00;
                        total_price = 3.00 * stoi(row[3]);

                        cout << "RM" << total_price;
                    }
                    else if (stoi(row[1]) >= num8 && stoi(row[2]) <= num6)
                    {
                        cout << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << endl;
                        price = 6.00;
                        total_price = 6.00 * stoi(row[3]);
                        cout << "RM" << total_price;
                    }
                    string duration2 = row[3];
                    string insert_query = "insert into Payment(Payment_id,Booking_id,Duration,Price,Payment_date) values('" + payment_id + "','" + booking_id + "','" + duration2 + "','" + total_price + "','" + today + "')";
                    const char* q = insert_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (!qstate)
                    {
                        cout << "\nPayment updated";
                        Invoice(booking_id, payment_id);

                    }
                }
            }
        }

    }


}

*/

void MemberAllocate()
{
    system("color 0C");
    int qstate;
    


    

    string booking_id;
    string Member_id;
    string Staff_id;
    string findbyname_query = "select MAX(NO) from booking";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);

    if (!qstate)
    {

        while ((row = mysql_fetch_row(res)))
        {
            string duration;
            string Device_id, time;
            int end_time;
            string end_time2;

            int booking_increment = stoi(row[0]) + 1;

            booking_id = "B0" + to_string(booking_increment);
        mem:
            cout << "\t\t\tPlease Enter the Member id:";
            cin >> Member_id;
            string find_member_end_query = "SELECT Member_end FROM member WHERE Member_id = '" + Member_id + "'";
            const char* qme = find_member_end_query.c_str();
            qstate = mysql_query(conn, qme);
            res = mysql_store_result(conn);
            if (qstate == 0 && mysql_num_rows(res) > 0) {
                row = mysql_fetch_row(res);
                string member_end_date = row[0];
                //cout << member_end_date;
                // Compare member_end with today's date
                struct tm member_end_tm = {};
                istringstream member_end_ss(member_end_date);
                member_end_ss >> get_time(&member_end_tm, "%Y-%m-%d");

                
                struct tm* ltm = localtime(&now);
                int current_year = 1900 + ltm->tm_year;
                int current_month = 1 + ltm->tm_mon;
                int current_day = ltm->tm_mday;
                string today_date = to_string(current_year) + "-" + to_string(current_month) + "-" + to_string(current_day);
                //cout << today_date;

                struct tm today_tm = {};
                istringstream today_ss(today_date);
                today_ss >> get_time(&today_tm, "%Y-%m-%d");

                if (mktime(&member_end_tm) < mktime(&today_tm)) {
                    cout << "\n\t\t\tPlease renew your membership before making a booking." << endl;
                    cout << "\t\t\t";
                    system("pause");
                    MemberMenu(Member_id);
                    return;
                }
            }

            string findmember_query = "select member_id from member where member_id = '" + Member_id + "'";
            const char* qm = findmember_query.c_str();
            qstate = mysql_query(conn, qm);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                if (mysql_num_rows(res) <= 0)
                {
                    cout << "\n\t\t\tNo such members registered\n\t\t\t";
                    system("pause");
                    goto mem;
                }
            }
            string AVAIL = "AVAILABLE";

            string findbya_query = "select * from Device where Device_Status = '" + AVAIL + "'";
            const char* qA = findbya_query.c_str();
            qstate = mysql_query(conn, qA);
            res = mysql_store_result(conn);
            cout << "\t\t\tDevices available\n\n";
            if (!qstate)
            {
                while ((row = mysql_fetch_row(res)))
                {

                    cout << "\t\t\t" << row[0]<<"|"<<row[1];
                    cout << endl;

                }
            }
            else
            {
                cout << "Sorry..There is no available devices...";
            }

        dev:
            cout << "\n\t\t\tChoose your device : ";
            cin >> Device_id;
            string finddevice_query = "select device_id from device where device_id = '" + Device_id + "'";
            const char* qd = finddevice_query.c_str();
            qstate = mysql_query(conn, qd);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                if (mysql_num_rows(res) <= 0)
                {
                    cout << "\n\t\t\tNo such devices available\n\t\t\t";
                    system("pause");
                    goto dev;
                }
            }
            cout << "\t\t\tAvailable times are : \n";
            string findbydevice_query = "select time_table.time from time_table WHERE NOT EXISTS(SELECT * FROM BOOKING WHERE  booking.Booking_date = '" + today + "' and booking.Device_id='" + Device_id + "' and time_table.time_stamp = booking.start_time_stamp)having time_table.time>'" + time1 + "' and time_table.time<'22:00:00'ORDER BY time_table.time ASC";
            const char* q = findbydevice_query.c_str();
            qstate = mysql_query(conn, q);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                while ((row = mysql_fetch_row(res)))
                {
                    cout <<"\t\t\t" << row[0] << endl;
                }
            }
            
        time:
            cout << "\n\t\t\tChoose your time(ex:09:00:00) : ";
            cin >> time;
            string findtime = "select time from time_table where time = '" + time + "'";
            const char* qt = findtime.c_str();
            qstate = mysql_query(conn, qt);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                if (mysql_num_rows(res) <= 0)
                {
                    cout << "\n\t\t\tNo such time available\n\t\t\tPlease enter in correct format(09:00:00)\n\t\t\t";
                    system("pause");
                    goto time;
                }
            }
        dur:
            cout << "\n\t\t\tChoose your duration(minimum 1 hour) : ";
            cin >> duration;
            if (time == "21:00:00" && duration >"1")
            {
                cout << "\n\t\t\tThe duration is only allowed 1 hour duration...Thank you!!";
                goto dur;

            }
            end_time = stoi(time) + stoi(duration);
            end_time2 = to_string(end_time) + ":00:00";

            string findbytime_query = "select time_stamp from time_table where time like '%" + time + "%' ";
            const char* d = findbytime_query.c_str();
            qstate = mysql_query(conn, d);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                while ((row = mysql_fetch_row(res)))
                {

                    string slot = row[0];
                    string findbytime_query = "select time_stamp from time_table where time like '%" + end_time2 + "%' ";
                    const char* d = findbytime_query.c_str();
                    qstate = mysql_query(conn, d);
                    res = mysql_store_result(conn);

                    if (!qstate)
                    {
                        while ((row = mysql_fetch_row(res)))
                        {
                            string endtimeslot = row[0];
                            string insert_query = "insert into Booking(Booking_id ,Member_id, Device_id, Start_time,End_time,Duration,Booking_date,start_time_stamp,end_time_stamp) values ('" + booking_id + "','" + Member_id + "','" + Device_id + "','" + time + "','" + end_time2 + "','" + duration + "','" + today + "', '" + slot + "','" + endtimeslot + "')";
                            const char* q = insert_query.c_str();
                            qstate = mysql_query(conn, q);
                            res = mysql_store_result(conn);

                            if (!qstate)
                            {
                                payment_allocate(Member_id, booking_id);
                                cout << "\t\t\tDatabase has been updated";




                            }
                            else
                            {
                                cout << "\t\t\tConnection failed" << endl;
                                StaffMenu(Staff_id);

                            }
                        }

                    }
                    else
                    {
                        cout << "\t\t\tConnection failed" << endl;
                        StaffMenu(Staff_id);

                    }




                }


            }

        }
    }
}
void SearchBooking(string Staff_id)
{
    system("color 0C");
    string Booking_date;
    string search_query = "select Booking_id,Member_id,Device_id,Booking_date,Start_time,End_time from booking";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        cout << "----------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\t \t \t \t\t\t\t BOOKING INFORMATION " << endl;
        cout << "----------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t" << setw(9) << "Booking_id" << setw(14) << "Member_id" << setw(14) << "Device_id" << setw(14) << "Booking_Date " << setw(14) << "Start_time" << setw(14) << "End_time" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------" << endl;
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "\t\t\t" << "|" << row[0] << setw(14) << row[1] << setw(15) << row[2] << setw(16) << row[3] << setw(17) << row[4] << setw(16) << row[5] << "|" << endl;
        }
        int option;
        cout << " " << endl;
        cout << "\t\t\t[1] Search Booking " << endl;
        cout << "\t\t\t[2] Staff Menu" << endl;
        cout << "\t\t\tPlease Enter an option (1/2) : ";
        cin >> option;
        if (option == 1)
        {
        opt:
            cout << "\t\t\tPlease Enter the Booking date to search(YYYY-MM-DD): ";
            cin >> Booking_date;

            string search_query = "SELECT Booking_id,Member_id,Device_id,Booking_date,Start_time,End_time from booking where Booking_date like '" + Booking_date + "' ";
            const char* qm = search_query.c_str();
            qstate = mysql_query(conn, qm);
            if (!qstate)
            {
                res = mysql_store_result(conn);
                if (mysql_num_rows(res) > 0)
                {
                    while (row = mysql_fetch_row(res))
                    {
                        cout << "\t\t\t" << setw(6) << row[0] << setw(14) << row[1] << setw(15) << row[2] << setw(16) << row[3] << setw(17) << row[4] << setw(16) << row[5] << endl;
                       
                    }
                    cout << "\t\t\t";
                    system("pause");
                    StaffMenu(Staff_id); // Moved outside the while loop
                }
                else
                {
                    cout << "\n\t\t\tNo Data is available for the date entered" << endl;
                    cout << "\t\t\t";
                    system("pause");
                    system("cls");
                    goto opt;
                }
            }
            else
            {
                cout << "\n\t\t\tQuery Execution Problem" << endl;
                cout << "\t\t\t";
                system("pause");
                goto opt;
            }
        }
        else
        {
            StaffMenu(Staff_id);
        }
    }
}


void AddMaintenance(string Staff_id)
{
    system("color 0C");
    int qstate;
    string Maintenance_id ;
    string Device_id;
   
    string Maintenance_Date;
    string Remarks;

    cin.ignore(1, '\n');
    string findbyname_query = "select MAX(NO) from Staff_Device";
    const char* qn = findbyname_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);


    if (!qstate)
    {

        while ((row = mysql_fetch_row(res)))
        {

            int maintenance_increment = stoi(row[0]) + 1;
            Maintenance_id = "M0" + to_string(maintenance_increment);
        dev:
            cout << "\t\t\tEnter the Device id :";
            getline(cin, Device_id);
            string checkdev_query = "select Device_id from Device where Device_id = '" + Device_id + "'";;
            const char* Q = checkdev_query.c_str();
            qstate = mysql_query(conn, Q);
            res = mysql_store_result(conn);
            if (!qstate)
            {

                string checkstaf_query = "select * from Staff where Staff_id = '" + Staff_id + "'";
                const char* Q = checkstaf_query.c_str();
                qstate = mysql_query(conn, Q);
                res = mysql_store_result(conn);
                if (!qstate)
                {
                    cout << "\t\t\tEnter Maintenance Date(YYYY-MM-DD) : ";
                    getline(cin, Maintenance_Date);
                remark:
                    cout << "\t\t\tEnter Remarks about  the Maintenance(max 30 words): ";
                    getline(cin, Remarks);
                    if (Remarks.length() < 30)
                    {
                        
                        string insert_query = "insert into staff_device(StaffDevice_id,Device_id,Staff_id,Staffdevice_date, Remarks) values ('" + Maintenance_id + "','" + Device_id + "','" + Staff_id + "','" + Maintenance_Date + "','" + Remarks + "')";
                        const char* q = insert_query.c_str();
                        qstate = mysql_query(conn, q);
                        if (!qstate)
                        {
                            cout << endl << "\t\t\tSuccessfully stored in database." << endl;
                            cout << "\t\t\t";
                            system("pause");
                            Maintenance(Staff_id);
                        }
                        else
                        {
                            cout << "\t\t\tPlease try again:)" << endl;
                            AddMaintenance(Staff_id);
                        }

                    }
                    else
                    {
                        cout << "\t\t\tYou have reached maximum words limit(maximum 30 words)";
                        goto remark;
                        cout << "\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;

                    }
                }
                else
                {
                    cout << "\t\t\tPlease try again:)" << endl;
                    AddMaintenance(Staff_id);
                }
            }
            else
            {
                cout << "\t\t\tPlease try again:)" << endl;
                goto dev;
            }
        }
    }
}
void ShowMaintenance(string Staff_id)
{
    system("color 0C");
    int qstate;
    system("cls");
    string Maintenance_id;
    string Device_id;
   
    qstate = mysql_query(conn, "select * from Staff_Device ");
    cout << "\t \t \t\t\t\t DEVICE MAINTENANCE INFORMATION";
    cout << " " << endl;
    cout << "\t\t\t" << setw(9) << "Maintenance_id" << setw(14) << "Device_id" << setw(15) << "Staff_id" << setw(19) << "Staffdevice_date" << setw(18) << "Remarks" << endl;

    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "\t\t\t"<<setw(6) << row[1] << setw(18) << row[2] << setw(19) << row[3] << setw(17) << row[4] << setw(24) << row[5] << endl;

        }
    }
    int option;
    cout << " " << endl;
    cout << "\t\t\t[1] Search Maintenance " << endl;
    cout << "\t\t\t[2] Maintenance Menu" << endl;
    cout << "\t\t\tPlease Enter an option (1/2) : ";
    cin >> option;
    if (option == 1)
    {
        cout << "\t\t\tPlease Enter the Maintenance id to search: ";
        cin >> Maintenance_id;
        string search_query = "select * from Staff_Device where StaffDevice_id like BINARY  '" + Maintenance_id + "' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "\t\t\t" << setw(6) << row[1] << setw(18) << row[2] << setw(19) << row[3] << setw(17) << row[4] << setw(24) << row[5] << endl;
            
        }
        cout << "\t\t\t";
        system("pause");
        Maintenance(Staff_id);
    }
    else
    {
        Maintenance( Staff_id);
    }


}

void UpdateMaintenance(string Staff_id)
{
    system("color 0C");
    system("cls");
    string Maintenance_id, Device_name, Device_Status;
    int o;
    cout << "\t\t\t---------------------- MODIFY DEVICE MAINTENANCE ----------------------" << endl;
    cout << "\t\t\tEnter Maintenance id : ";
    cin >> Maintenance_id;
    string search_query = " select *  from Staff_Device where StaffDevice_id = '" + Maintenance_id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {

        cout << " " << endl;
        cout << " \t \t \t \t Current Details of the Device Maintenance \t \t \t " << endl;
        cout << " \t \t \t \t     Device Maintenance Id : " << row[0] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t     Device ID : " << row[1] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t     Staff ID : " << row[2] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t     Maintenance ID : " << row[3] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t [1] Remarks : " << row[5] << endl;
        cout << " \t \t \t \t [2] Exit " << endl;




        cout << " \t \t \t \t Choose an option to modify:";
        cin >> o;
        cin.ignore(1, '\n');

        if (o == 1)
        {

            string Maintenace_Remarks;
            cout << "\t \t \t \t Please Enter the Maintenance Remarks : ";
            getline(cin, Maintenace_Remarks);
            string update_query = "update Staff_device set Remarks  = '" + Maintenace_Remarks + "' where StaffDevice_id = '" + Maintenance_id + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << " ";
            cout << "\t \t \t \tSuccesfully modified the Remarks" << endl;
            cout << "\n\t \t \t \t";
            system("pause");
            Maintenance(Staff_id);
        }
        else if (o == 2)
        {

            cout << "\t\t\tReturning back to Device Entry Menu....";
            system("cls");
            Maintenance(Staff_id);
        }
        else
            cout << "\t\t\tPlease Enter a valid option whether 1 OR 2 " << endl;
        UpdateMaintenance(Staff_id);

    }
}

void DeleteMaintenance(string Staff_id)
{
    system("color 0C");
    string Maintenance_id;
    char del_opt;
    system("cls");
    cout << "\t\t\tPlease Enter the Maintenance id : ";
    cin >> Maintenance_id;
    string search_query = "select * from Staff_Device where StaffDevice_id like '%" + Maintenance_id + "%' ";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    cout << "\t \t \t\t\t\tDEVICE MAINTENANCE INFORMATION " << endl;
    cout << "\t\t\t" << setw(9) << "Maintenance_id" << setw(14) << "Device_id" << setw(15) << "Staff_id" << setw(19) << "Staffdevice_date" << setw(18) << "Remarks" << endl;
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t" << setw(6) << row[1] << setw(18) << row[2] << setw(19) << row[3] << setw(17) << row[4] << setw(24) << row[5] << endl;

    }
    do
    {
        cout << "\t\t\tAre you sure to delete this Maintenance? (y/n) :";
        cin >> del_opt;
        if (del_opt == 'Y' || del_opt == 'y')
        {
            string delete_query = "delete from Staff_Device where StaffDevice_id = '" + Maintenance_id + "' ";
            const char* q = delete_query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate)
            {
                cout << "\t\t\tDeleted Succesfully!!";
                cout << "\n\t\t\t";
                system("pause");
                ShowMaintenance(Staff_id);

            }
            else
            {
                cout << "\t\t\tQuery Execution Problem! " << mysql_errno(conn) << endl;
            }
        }
        else
            cout << "\t\t\tReturning to Maintenance Menu..." << endl;
        cout << "\t\t\t";
        system("pause");
        Maintenance(Staff_id);

    } while (del_opt != 'y' && del_opt != 'Y' && del_opt != 'n' && del_opt != 'N');


}

void Maintenance(string Staff_id)
{
    system("color 0C");
    int menu_opt;
    system("cls");
    cout << "\n\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t|                       DEVICE MAINTENANCE MENU:               |" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|" << endl;
    cout << "\t\t\t|  [1] ADD MAINTENANCE                                         |" << endl;
    cout << "\t\t\t|  [2] SHOW MAINTENANCE                                        |" << endl;
    cout << "\t\t\t|  [3] UPDATE MAINTENANCE                                      |" << endl;
    cout << "\t\t\t|  [4] DELETE MAINTENANCE                                      |" << endl;
    cout << "\t\t\t|  [0] EXIT                                                    |" << endl;
    cout << "\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\tPlease Enter your choice (0 - 4): ";
    cin >> menu_opt;
    switch (menu_opt)
    {
    case 1:AddMaintenance(Staff_id);
        break;
    case 2:ShowMaintenance(Staff_id);
        break;
    case 3:UpdateMaintenance(Staff_id);
        break;
    case 4:DeleteMaintenance(Staff_id);
        break;
    case 0:StaffMenu(Staff_id);
        break;
    default:
        cout << "\t\t\tPlease choose 0 to 4 ." << endl;
        cout << "\t\t\t";
        system("pause");
        system("cls");
        Maintenance(Staff_id);
    }


}

void ViewDevice(string Staff_id)
{
    system("color 0C");
    int qstate;
    system("cls");
    string Device_id;
    qstate = mysql_query(conn, "select * from Device ");
    cout << "\t \t \t \t\t\tDEVICE INFORMATION";
    cout << " " << endl;
    cout << "\t\t\t" << setw(9) << "Device_id" << setw(14) << "Device_name" << setw(15) << "Device_Status" << endl;

    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "\t\t\t" << setw(6) << row[0] << setw(15) << row[1] << setw(15) << row[2] << endl;
        }
    }
    int option;
    cout << " " << endl;
    cout << "\t\t\t[1] Search Device " << endl;
    cout << "\t\t\t[2] Staff Menu" << endl;
    cout << "\t\t\tPlease Enter an option (1/2): ";
    cin >> option;
    if (option == 1)
    {
        cout << "\t\t\tPlease Enter the Device id to search: ";
        cin >> Device_id;
        string search_query = "select Device_id ,Device_name,Device_Status from Device where Device_id like '%" + Device_id + "%' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0)
            {
                while (row = mysql_fetch_row(res))
                {
                    cout << "\t\t\t" << setw(6) << row[0] << setw(15) << row[1] << setw(16) << row[2] << endl;
                    cout << "\n\t\t\t";
                    system("pause");
                }
                StaffMenu(Staff_id);
            }
            else
            {
                cout << "\n\t\t\tNo Data is available for the device ID entered" << endl;
                cout << "\t\t\t";
                system("pause");
                ViewDevice(Staff_id);
            }
        }
    }
    else
    {
        StaffMenu(Staff_id);
    }
}


void StaffLogin()
{
    system("color 0C");
    int option;
    char Flag;
    system("cls");
b:
    cout << "\n\t\t\t\t RH CYBERCAFE MANAGEMENT SYSTEM \t \n" << endl;
    cout << "\t\t\t=============STAFF LOGIN================== " << endl;
    string Staff_id, password;

    cout << "\t\t\tStaff ID : ";
    cin >> Staff_id;
    if (Staff_id == "0")
    {
        goto b;
    }
    cout << "\t\t\tStaff Password : ";
    
    int i = 0;
    char a;
    for (i = 0;;)
    {
        a = _getch();
        if (a >= 'a' && a <= 'z' || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
        {

            password += a;
            ++i;
            cout << "*";

        }
        if (a == '\b' && i >= 1)
        {
            cout << "\b \b";
            --i;
        }
        if (a == '\r')
        {
            break;
        }

    }
    if (password == "0")
    {
        cout << "\t\t\tInvalid Password";
        goto b;
    }

    
    string checkUser_query = "select Staff_id from Staff where Staff_id like BINARY '" + Staff_id + "' and Staff_pass like BINARY '" + password + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
            cout << "\n\t\t\t[Login Successful]...\n";
            cout<<"\t\t\t";
            system("pause");
            system("cls");
            StaffMenu(Staff_id);
        }
        else
        {
            cout << "\n\t\t\tYou have entered  a wrong password or id\n\t\t\t.Press 'Y' to try again:";
            cin >> Flag;
            if (Flag == 'y' || Flag == 'Y')
            {
                cout << "\n\t\t\t[1] RETURN TO LOGIN" << endl;
                cout << "\t\t\t[2] FORGOT PASSWORD" << endl;
                cout << "\t\t\tPlease Enter your Choice (1/2) : ";
                cin >> option;
                if (option == 1)
                {
                    system("cls");
                    goto b;
                }
                else if (option == 2)
                {
                    string Staff_phone, Staff_ic;
ft:
                    cout << "\t\t\tEnter Admin IC Number/Phone Number :";
                    cin >> Staff_ic;
                    string search_query = " select Staff_id,Staff_name,Staff_ic,Staff_pass,Staff_phone from Staff where Staff_ic ='" + Staff_ic + "' or Staff_phone = '" + Staff_ic + "' ";
                    const char* q = search_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (qstate)
                    {
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res))
                        {

                            cin.ignore(1, '\n');
                            string Staff_newpass;
                            cout << "\t \t \t \t\t\tPlease Insert the new Admin Password : ";
                            getline(cin, Staff_newpass);
                            string update_query = "update Staff set Staff_pass  = '" + Staff_newpass + "' where Staff_ic = '" + Staff_ic + "'";
                            const char* q = update_query.c_str();
                            qstate = mysql_query(conn, q);
                            cout << " ";
                            cout << "\t\t\tSuccesfully modified the password" << endl;
                            main();
                        }
                    }
                    else
                    {
                        cout << "\n\t\t\tInvalid IC Number/Phone Number";
                        goto ft;
                    }
                }
            }
            else
            {
                system("cls");
                LoginMenu();
            }
        }
    }
}
void membercheck()
{
m:
    system("color 0C");
    string Staff_id;
    string member_id;
    cout << "\t\t\tPlease Enter Member ID to search :";
    cin >> member_id;
    int qstate;
    string member_query = "select * from member where member_id ='" + member_id + "'";
    const char* qn = member_query.c_str();
    qstate = mysql_query(conn, qn);
    res = mysql_store_result(conn);
    if (!qstate)
    {

        while ((row = mysql_fetch_row(res)))
        {
            
            cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
            printf("| % -20s | % -20s | % -13s | % -15s | % -13s | % -15s | % -10s |  \n", "Name", "Identification Card", "Phone", "Member from", "Member to", "Points Earned", "Membership");
            printf("| % -20s | % -20s | % -13s | % -15s | % -13s | % -15s | % -10s | \n", row[1], row[2], row[4], row[5], row[6], row[7], row[8]);

            printf("------------------------------------------------------------------------------------------------------------------------------------\n");
            //to find the difference between two dates which memberstart date and end date
            string date1 = row[6];
            
            string membership_query = "select member_id, (DATEDIFF('" + date1 + "','" + today + "')),member_end from member where member_id ='" + member_id + "' ";
            const char* qn = membership_query.c_str();
            qstate = mysql_query(conn, qn);
            res = mysql_store_result(conn);
            if (!qstate)
            {
                while ((row = mysql_fetch_row(res)))
                {
                    if (stoi(row[1])> 0)
                    {
                        cout << "\t\t\tMember ID:" << row[0];
                        cout << "\n\t\t\tMembership expires in " << row[1] << "days" << endl;
                        cout << "\t\t\t";
                        system("pause");
                        StaffMenu(Staff_id);
                    }
                    else
                    {
                        cout << "\t\t\tMember ID:" << row[0];
                        cout << "\n\t\t\tYour last date of membership is on " << row[2];
                        cout << "\n\t\t\tPlease extend your membership" << endl;
                        cout << "\t\t\t";
                        system("pause");
                        StaffMenu(Staff_id);
                    }
                }
            }
            else
            {
                cout << "\t\t\tConnection failed!!" << endl;
                goto m;
            }
        }
    }
    else
    {
        cout << "\t\t\tInvalid Member ID";
        goto m;
    }
}

void CancelBook(string Staff_id)
{
    system("color 0D");
    string Member_id;
    string Booking_id;
    char del_opt;
    system("cls");
    cout << "\t\t\tPlease Enter the Member id :";
    cin >> Member_id;
    cout << "\t\t\tPlease Enter the Booking id : ";
    cin >> Booking_id;
    string search_query = "select Booking.Booking_id,Booking.Member_id,Booking.Device_id,Booking.Booking_date,Booking.Start_time,Booking.End_time,Payment.payment_id from Booking JOIN Payment on Payment.Booking_id = Booking.Booking_id WHERE Booking.Booking_id ='" + Booking_id + "' AND Member_id = '" + Member_id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    cout << "\t \t \t\t\t\tBOOKING INFORMATION " << endl;
    cout << "\t\t\t" << setw(9) << "Booking_id" << setw(14) << "Member_id" << setw(15) << "Device_id" << setw(16) << "Booking Date" << setw(17) << "Start Time" << setw(18) << "End time" << endl;
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << setw(6) << row[0] << setw(15) << row[1] << setw(15) << row[2] << setw(16) << row[3] << setw(15) << row[4] << setw(17) << row[5] <<
            endl;
    }
    do
    {
        string start_time;
        string checktime_query = "select Start_time from Booking ";
        const char* qr = checktime_query.c_str();
        qstate = mysql_query(conn, qr);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                if (row[0] > today)
                {


                    cout << "\t\t\tAre you sure to delete this Booking? (y/n) :";
                    cin >> del_opt;
                    if (del_opt == 'Y' || del_opt == 'y')
                    {
                        string delete_query = "delete * from Booking join payment on payment.booking_id = booking.booking_id where Booking_id = '" + Booking_id + "' ";
                        const char* q = delete_query.c_str();
                        qstate = mysql_query(conn, q);
                        if (!qstate)
                        {

                            cout << "\t\t\tCanceled Succesfully!!";
                            StaffMenu(Staff_id);
                        }
                        else
                        {
                            cout << "\t\t\tQuery Execution Problem! " << mysql_errno(conn) << endl;
                        }
                    }
                    else
                    {
                        StaffMenu(Staff_id);
                    }
                }
            }

        }
        else
        {
            StaffMenu(Staff_id);
        }

    } while (del_opt != 'y' && del_opt != 'Y' && del_opt != 'n' && del_opt != 'N');
}

void StaffMenu(string Staff_id)
{
    system("cls");
    system("color 0C");
    int choice;
    cout << "\n\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\t|                          STAFF MENU                          |\t\t\t" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|\t\t\t" << endl;
    cout << "\t\t\t|  [1] DEVICE MAINTENANCE                                      |\t\t\t" << endl;
    cout << "\t\t\t|  [2] VIEW DEVICE                                             |\t\t\t" << endl;
    cout << "\t\t\t|  [3] DISPLAY BOOKING                                         |\t\t\t" << endl;
    cout << "\t\t\t|  [4] MEMBER DEVICE ALLOCATION                                |\t\t\t" << endl;
    cout << "\t\t\t|  [5] MEMBER CHECKING                                         |\t\t\t" << endl;
    cout << "\t\t\t|  [0] EXIT                                                    |\t\t\t" << endl;
    cout << "\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\tPlease Enter your choice (0 - 5) : ";
    cin >> choice;
    switch (choice)
    {

    case 1:Maintenance(Staff_id);//Maintenance Entry
        break;
    case 2:ViewDevice(Staff_id);//View Device Details and Availabality Status
        break;
    case 3:SearchBooking(Staff_id);//Search Booking
        break;
    case 4:MemberAllocate();//Allocate Device
        break;
    case 5:membercheck();//check membership for members
        break;
    case 0:LoginMenu();
        break;
        

    default:
        cout << "\n\t\t\tPlease choose between 0 to 5.";
        cout << "\n\t\t\t";
        system("pause");
        system("cls");
        StaffMenu(Staff_id);
        break;

    }

}




void dailyReport()
{
    string date;
    cout << "\n\t\t\tPlease Enter a date (YYYY-MM-DD) :";
    cin >> date;
    string date_query = "select payment.payment_id, payment.payment_date, payment.Booking_id, booking.Duration, Payment.Price as Subtotal from payment join booking on booking.booking_id = payment.booking_id where payment_date = '" + date + "'";
    const char* q = date_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        
        res = mysql_store_result(conn);
        if (mysql_num_rows(res)>0)
        {
            

            cout << "\n\n\t\t\t------------------------------------------------------------------------\n";
            printf("\t\t\t| %-10s | %-10s | %-10s | %-8s | %-10s |\n", "Payment ID", "Payment Date", "Booking ID", "Duration", "Cost");
            while (row = mysql_fetch_row(res))
            {
                printf("\t\t\t| %-10s | %-12s | %-10s | %-8s | %-10s |\n", row[0], row[1], row[2], row[3], row[4]);
            }
            printf("\t\t\t---------------------------------------------------------------------\n");
            cout << "\t\t\t";

            string dates_query = "select payment.payment_id, payment.payment_date,  Payment.Price as Subtotal from payment where payment_date = '" + date + "' and Booking_id is NULL";
            const char* qsi = dates_query.c_str();
            qstate = mysql_query(conn, qsi);
            if (!qstate)
            {

                res = mysql_store_result(conn);
                if (mysql_num_rows(res) > 0)
                {

                    cout << "\n\n\t\t\t------------------------------------------------------------------------\n";
                    printf("\t\t\t| %-10s | %-10s | %-10s |\n", "Payment ID", "Payment Date", "Cost");
                    while (row = mysql_fetch_row(res))
                    {
                        printf("\t\t\t| %-10s | %-12s | %-10s |\n", row[0], row[1], row[2]);
                    }
                    printf("\t\t\t---------------------------------------------------------------------\n");
                    cout << "\t\t\t";

                }
                else
                {
                    cout << "\t\t\tThere is no additional data for the member renewal payment";
                }
            }
           
            string search_query = "select sum(Price) FROM PAYMENT where Payment_date ='" + date + "'";
            const char* qs = search_query.c_str();
            qstate = mysql_query(conn, qs);
            if (!qstate)
            {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res))
                {
                    cout << endl;

                    cout << "\t\t\t Total Amount of Sales on " << date << " : RM " << fixed << setprecision(2) << row[0];
                    cout << "\n\t\t\t";
                    system("pause");
                    Report();
                }

            }
            
        }
        else
        {
            
            int opt;
            system("cls");
        d:
            cout << "\t\t\tNo data Available for the date";
            cout << "\n\t\t\t [1] Search Another date";
            cout << "\n\t\t\t [2] Admin Menu";
            cout << "\n\t\t\t Please Enter your choice(1/2):";
            cin >> opt;
            if (opt == 1)
            {
                string date1;
                cout << "\n\t\t\tPlease Enter a date to search (YYYY-MM-DD):";
                cin >> date1;
                string date1_query = "select payment.payment_id, payment.payment_date, payment.Booking_id, booking.Duration, Payment.Price as Subtotal from payment join booking on booking.booking_id = payment.booking_id where payment_date = '" + date1 + "'";
                const char* qd = date1_query.c_str();
                qstate = mysql_query(conn, qd);
                if (!qstate)
                {
                    cout << "\n\n\t\t\t---------------------------------------------------------------------\n";
                    printf("\t\t\t|%-10s |%-10s|%-10s |%-8s|%-10s|\n", "Payment ID", "Payment Date", "Booking ID", "Duration", "Cost");
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res))
                    {
                        printf("\t\t\t|%-10s |%-12s|%-10s |%-8s |%-10s|\n", row[0], row[1], row[2], row[3], row[4]);
                    }
                    printf("\t\t\t---------------------------------------------------------------------\n");
                    cout << "\t\t\t";

                    string search1_query = "select sum(Price) FROM PAYMENT where Payment_date ='" + date1 + "'";
                    const char* qs1 = search1_query.c_str();
                    qstate = mysql_query(conn, qs1);
                    if (!qstate)
                    {
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res))
                        {
                            cout << endl;

                            cout << "\t\t\t Total Amount of Sales on " << date1 << " : RM " << fixed << setprecision(2) << row[0];
                            cout << "\n\t\t\t";
                            system("pause");
                            Report();
                        }
                    }
                }

            }
            else if (opt == 2)
            {
                AdminMenu();

            }
            else
            {
                cout << "\n\t\t\tPlease Enter a valid option";
                goto d;
            }
        }
    }   
    
   

}

void monthlybarchart(int data[], int numColumns, std::string deviceNames[])
{


    int max = data[0];
    for (int i = 1; i < numColumns; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }

    // Draw the vertical bar chart
    for (int row = max; row > 0; row--) {
        for (int col = 0; col < numColumns; col++) {
            if (data[col] >= row) {
                std::cout << "  * ";
            }
            else {
                std::cout << "    ";
            }
        }
        std::cout << std::endl;
    }

    // Draw the x-axis
    for (int i = 0; i < numColumns; i++) {
        std::cout << "----";
    }
    std::cout << std::endl;

    // Draw the sport names
    for (int i = 0; i < numColumns; i++) {
        std::cout << " " << deviceNames[i] << " ";
    }
    std::cout << std::endl;
}

void monthlyReport()
{
    system("color 0B");
    system("cls");
    string month;


    double price = 0.00;
    double average = 0.00;
month:
    cout << "\n\t\t\t**************************************************************************************" << endl;
    cout << "\t\t\t\t\t RH CYBERCAFE MANAGEMENT SYSTEM \t\n" << endl;
    cout << "\t\t\t\t\t MONTHLY SALES REPORT" << endl;
    cout << "\t\t\t****************************************************************************************" << endl;
    cout << "\t\t\t [1] January   [4] April  [7] July       [10] October" << endl;
    cout << "\t\t\t [2] February  [5] May    [8] August     [11] November" << endl;
    cout << "\t\t\t [3] March     [6] May    [9] September  [12] December" << endl;
    cout << "\t\t\t****************************************************************************************" << endl;
    cout << "\t\t\t\t\tMONTH : ";
    cin >> month;
    
    string search_query = "select sum(Price) FROM PAYMENT where MONTH(Payment_date) ='" + month + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << endl;
            
            cout << "\t\t\t Total Amount of Monthly Sales : RM " << fixed << setprecision(2) << row[0];
        }
    }
    else
    {
        cout << "\n\t\t\t Please Enter a valid option from (1 to 12) according to month to be searched...Thank you" << endl;
        goto month;
    }

   

    string average_query = "select avg(price) from payment where MONTH(Payment_date) ='" + month + "'";
    const char* qavg = average_query.c_str();
    qstate = mysql_query(conn, qavg);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            average = atof(row[0]);
        }
        cout << "\n\t\t\t Average Amount of Monthly Sales : RM " << fixed << setprecision(2) << average;
    }
    else
    {
        cout << "\n\t\t\t Please Enter a valid option from (1 to 12) according to month to be searched...Thank you" << endl;
        goto month;
    }

    string count_query = "select count(*) from payment where MONTH(Payment_date) ='" + month + "'";
    const char* qc = count_query.c_str();
    qstate = mysql_query(conn, qc);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            do {

                if (month == "1")
                {
                    cout << "\n\t\t\t Number of Sales in January : " << row[0] << endl;
                }
                else if (month == "2")
                {
                    cout << "\n\t\t\t Number of Sales in February : " << row[0] << endl;
                }
                else if (month == "3")
                {
                    cout << "\n\t\t\t Number of Sales in March : " << row[0] << endl;
                }
                else if (month == "4")
                {
                    cout << "\n\t\t\t Number of Sales in April : " << row[0] << endl;
                }
                else if (month == "5")
                {
                    cout << "\n\t\t\t Number of Sales in May : " << row[0] << endl;
                }
                else if (month == "6")
                {
                    cout << "\n\t\t\t Number of Sales in June : " << row[0] << endl;
                }
                else if (month == "7")
                {
                    cout << "\n\t\t\t Number of Sales in July : " << row[0] << endl;
                }
                else if (month == "8")
                {
                    cout << "\n\t\t\t Number of Sales in August : " << row[0] << endl;

                }
                else if (month == "9")
                {
                    cout << "\n\t\t\t Number of Sales in September : " << row[0] << endl;
                }
                else if (month == "10")
                {
                    cout << "\n\t\t\t Number of Sales in October : " << row[0] << endl;
                }
                else if (month == "11")
                {
                    cout << "\n\t\t\t Number of Sales in November : " << row[0] << endl;
                }
                else if (month == "12")
                {
                    cout << "\n\t\t\t Number of Sales in December : " << row[0] << endl;
                }
                else
                {
                    cout << "\n\t\t\t Please Enter a valid option from (1 to 12) according to month to be searched...Thank you" << endl;
                    goto month;
                }


            } while (month != "1" && month != "2" && month != "3" && month != "4" && month != "5" && month != "6" && month != "7" && month != "8" && month != "9" && month != "10" && month != "11" && month != "12");

        }
    }
    string devices_query = "SELECT Booking.Device_id,count(Booking.Device_id),SUM(Payment.Price),SUM(PAYMENT.PRICE) * 100 /(select SUM(Price) from Payment WHERE MONTH(PAYMENT_DATE) ='" + month + "')FROM PAYMENT JOIN Booking on Payment.Booking_id = Booking.booking_id join device on Booking.Device_id = Device.Device_id WHERE MONTH(PAYMENT_DATE) = '" + month + "'GROUP BY Booking.Device_id";
    const char* qti = devices_query.c_str();
    qstate = mysql_query(conn, qti);
    if (!qstate)
    {
       

        cout << "\n\t\t\t--------------------------------------------------------------------------------------------------\n";
        cout << "\n\t\t\tFrequency of device booked per month" << endl;
        cout << "\n\t\t\t--------------------------------------------------------------------------------------------------\n";
        printf("\t\t\t| %-10s | %-20s | %-21s |\n ", "Device ID", "Sales per device","Profit Percentage( % )");
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            
                
                    
                    
            
            
            
            printf("\t\t\t| %-10s | %-20s | %-20s |\n ", row[0], row[2], row[3]);
            

        }
        printf("\t\t\t--------------------------------------------------------------------------------------------------\n");
       
        
    }

    string renewal_query = "SELECT PAYMENT.PAYMENT_ID,PAYMENT.Booking_id,Payment.Price from payment where payment.Booking_id IS NULL and Month(Payment_date) = '" + month + "'";
    const char* qtt = renewal_query.c_str();
    qstate = mysql_query(conn, qtt);
    if (!qstate)
    {


        cout << "\n\t\t\t--------------------------------------------------------------------------------------------------\n";
        cout << "\n\t\t\tFrequency of Renewal of the Members of the month" << endl;
        cout << "\n\t\t\t--------------------------------------------------------------------------------------------------\n";
        printf("\t\t\t| %-10s | %-20s | \n ", "Payment ID", "Renewal Sales");
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {







            printf("\t\t\t| %-10s | %-20s | \n ", row[0], row[2]);


        }
        printf("\t\t\t--------------------------------------------------------------------------------------------------\n");


    }
    string device_query = "select booking.device_id,count(booking.device_id) from booking join device on booking.device_id = device.device_id join payment on payment.booking_id = booking.booking_id where month(payment.payment_date) = '" + month + "'group by booking.device_id order by count(booking.device_id) desc";
    const char* qt = device_query.c_str();
    qstate = mysql_query(conn, qt);
    if (!qstate)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
            SetConsoleTextAttribute(hConsole, 15);
            cout << "\n\n\t\t\t--------------------------------------------------------------------------------------------------";
            cout << "\n\t\t\tFrequency of Booked Devices" << endl;
            cout << "\t\t\t--------------------------------------------------------------------------------------------------\n";
            printf("\t\t\t| %-10s | %-30s |\n ", "Device ID", "Frequency of booked Devices");
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {

                float tfreq = 0.0;
                
                tfreq += stof(row[1]);
                printf( "\t\t\t| % -10s : ", row[0]);
                

                for (int i = 0; i < tfreq; i++)
                {
                    cout << " \xFE ";
                }
                cout << row[1] << endl;




            }
        
    }
    
    string times_query = "select booking.start_time_stamp,time_table.time,count(booking.start_time_stamp) from booking join time_table on time_table.time_stamp = booking.start_time_stamp join payment on payment.booking_id = booking.booking_id where month(payment.payment_date) = '" + month + "' group by booking.start_time_stamp order by count(booking.start_time_stamp) desc;";
    const char* qd = times_query.c_str();
    qstate = mysql_query(conn, qd);
    if (!qstate)
    {
        system("color 0B");
        cout << "\n\n\t\t\tFrequency of time booked per month" << endl;
        cout << "\n\t\t\t-------------------------------------------------\n";
        printf("\t\t\t| %-20s | %-30s |\n ", " Time", "Frequency of booked Times");
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            printf("\t\t\t| %-20s | %-30s | \n", row[1], row[2]);
        }
        printf("\t\t\t-------------------------------------------------\n");
    }
rep:
    char repopt;
    cout << "\n\t\t\tWould you like to view all the bookings per month (y/n) :";
    cin >> repopt;
    if (repopt == 'y' || repopt == 'Y')
    {
        system("color 0B");
        string report_query = "select Payment.payment_date,Booking.Member_id,Payment.Booking_id,Payment.price from booking join payment on booking.booking_id = payment.booking_id where month(payment.payment_date) ='" + month + "'order by Payment.Booking_id";
        const char* qr = report_query.c_str();
        qstate = mysql_query(conn, qr);
        if (!qstate)
        {
            cout << "\t\t\t--------------------------------------------------------\n";
            printf("\t\t\t| %-10s | %-10s | %-10s |%-10s |\n", "Date", "Member ID", "Booking ID", "Price");
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                
                printf("\t\t\t| %-10s | %-10s | %-10s |%-10s |\n", row[0], row[1], row[2], row[3]);
            }
            printf("\t\t\t-------------------------------------------------------\n");

            system("color 0B");

            char monthopt;
            cout << "\n\t\t\t Would you like to research about another month?(y/n) :";
            cin >> monthopt;
            if (monthopt == 'y' || monthopt == 'Y')
            {
                
                goto month;
            }
            else
            {
                Report();
            }

        }
        


    }
   else if (repopt == 'n' || repopt == 'N')
   {
        char monthopt;
        cout << "\n\t\t\t Would you like to research about another month?(y/n) :";
        cin >> monthopt;
        if (monthopt == 'y' || monthopt == 'Y')
        {
           
            goto month;
        }
        else
        {
            Report();
        }
   }
   else
    {
        cout << "\n\t\t\tPlease Enter a valid opt either y or n";
        goto rep;
    }

}

void BookingReport()//Details of all bookings 
{
    system("color 0B");

    cout << "\n\t\t\t*********************************************************************************************\t\t\n";
    cout << "\n\t\t\t\t\t  RH CYBERCAFE MANAGEMENT SYSTEM";
    cout << "\n\t\t\t\t\t\tBOOKING REPORT";
    cout << "\n\t\t\t*********************************************************************************************\t\t";

    string search_query = "SELECT Device_id,COUNT(Device_id) AS FREQUENCY from Booking group by Device_id order BY COUNT(Device_id); ";
    const char* qd = search_query.c_str();
    qstate = mysql_query(conn, qd);
    if (!qstate)
    {
        cout << "\n\n\t\t\t*********************************************************************************************\t\t";
        cout << "\n\t\t\t\t\t\t MOST FREQUENTLY USED DEVICES" << endl;
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            
            printf("\t\t\t\t\t\t | %-15s | %-5s |\n", row[0], row[1]);
        }
    }
    else
    {
        cout << "\t\t\tQuery Execution Problem. Please try again..." << mysql_errno(conn) << endl;
    }

    string searchT_query = "SELECT Member_id,COUNT(Device_id) AS 'FREQUENCY OF DEVICE USAGE BY THE MEMBERS'from Booking group BY Member_id";
    const char* qt = searchT_query.c_str();
    qstate = mysql_query(conn, qt);
    if (!qstate)
    {
        cout << "\n\t\t\t\t\t\t FREQUENCY OF DEVICE USAGE BY THE MEMBER" << endl;
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            
            
            printf("\t\t\t\t\t\t | %-15s | %-5s |\n", row[0], row[1]);
        }
    }
    else
    {
        cout << "\t\t\tQuery Execution Problem. Please try again..." << mysql_errno(conn) << endl;
    }
    string searchd_query = "select Device_id,round(avg(Duration),4) as 'AVERAGE DURATION OF DEVICE USAGE'from Booking group by Device_id order by avg(Duration) ASC; ";
    const char* qa = searchd_query.c_str();
    qstate = mysql_query(conn, qa);
    if (!qstate)
    {
        cout << "\n\t\t\t\t\t\t AVERAGE DURATION OF DEVICE BOOKING" << endl;
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            
            
            printf("\t\t\t\t\t\t | %-15s | %-5s |\n", row[0], row[1]);
            
        }

    }
    cout << "\n\t\t\t***********************************************************************************************\t\t";
    cout << "\n\t\t\t";
    system("pause");
    Report();
}


void ViewBooking()
{
    system("color 0B");
    system("cls");
    string search_query = "select Booking_id,Member_id,Device_id,Booking_date,Start_time,End_time from Booking";
    const char* qb = search_query.c_str();
    qstate = mysql_query(conn, qb);
    if (!qstate)
    {
        string Booking_id;
        cout << "\n\t\t\t------------------------------------------------------------------------------------------------" << endl;
        cout << "\t \t \t \t\t\t\t BOOKING INFORMATION " << endl;
        cout << "\t\t\t-------------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t" << setw(9) << "Booking_id" << setw(14) << "Member_id" << setw(14) << "Device_id" << setw(14) << "Booking_Date " << setw(14) << "Start_time" << setw(14) << "End_time" << endl;
        cout << "\t\t\t------------------------------------------------------------------------------------------------\n" << endl;
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "\t\t\t" << "|" << row[0] << setw(14) << row[1] << setw(15) << row[2] << setw(16) << row[3] << setw(17) << row[4] << setw(16) << row[5] << "|" << endl;
        }
        int option;
        cout << " " << endl;
        cout << "\t\t\t[1] Search Booking " << endl;
        cout << "\t\t\t[2] Booking Report " << endl;
        cout << "\t\t\t[3] Admin Menu" << endl;
        cout << "\t\t\tPlease Enter an option (1 -3) : ";
        cin >> option;
        if (option == 1)
        {
            int opt;
            cout << "\t\t\t[1] Search Using Booking id  " << endl;
            cout << "\t\t\t[2] Search Using Booking Date " << endl;
            cout << "\t\t\tPlease Enter an option (1/2) : ";
            cin >> opt;
            if (opt == 1)
            {
                cout << "\t\t\tPlease Enter the Booking id to search: ";
                cin >> Booking_id;
                string search_query = "select Booking_id ,Member_id,Device_id,Booking_Date,Start_time,End_time from Booking where Booking_id like '%" + Booking_id + "%' ";
                const char* q = search_query.c_str();
                qstate = mysql_query(conn, q);
                res = mysql_store_result(conn);
                if (mysql_num_rows(res) > 0) {
                    while (row = mysql_fetch_row(res))
                    {
                        cout << "\t\t\t" << setw(6) << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(16) << row[3] << setw(17) << row[4] << setw(18) << row[5] << endl;
                        cout << "\t\t\t";
                        system("pause");
                        Report();
                    }
                }
                else {
                    cout << "\n\t\t\tNo data available for the Booking ID entered" << endl;
                    cout << "\t\t\t";
                    system("pause");
                    ViewBooking();
                }
            }
            else if (opt == 2)
            {
                string Booking_date;
                cout << "\t\t\tPlease Enter the Booking date to search(YYYY-MM-DD): ";
                cin >> Booking_date;
                string search_query = "select Booking_id ,Member_id,Device_id,Booking_Date,Start_time,End_time from Booking where Booking_id = '" + Booking_date + "' ";
                const char* q = search_query.c_str();
                qstate = mysql_query(conn, q);
                res = mysql_store_result(conn);
                if (mysql_num_rows(res) > 0) {
                    while (row = mysql_fetch_row(res))
                    {
                        cout << "\t\t\t" << setw(6) << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(16) << row[3] << setw(17) << row[4] << setw(18) << row[5] << endl;
                        cout << "\t\t\t";
                        system("pause");
                        Report();
                    }
                }
                else {
                    cout << "\n\t\t\tNo data available for the Booking date entered" << endl;
                    cout << "\t\t\t";
                    system("pause");
                    ViewBooking();
                }
            }
        }
        else if (option == 2)
        {
            BookingReport();
        }
        else
        {

            AdminMenu();
        }
    }
    else
    {
        cout << "\t\t\tQuery Execution Problem. Please try again..." << mysql_errno(conn) << endl;
    }
}



void MaintenanceReport()
{
    system("color 0B");
    
    cout << "\n\n\t\t\t***********************************************************************************************\t\t";
    cout << "\n\t\t\t\t\t  RH CYBERCAFE MANAGEMENT SYSTEM";
    cout << "\n\t\t\t\t\t\tMAINTENANCE REPORT";
    cout << "\n\t\t\t************************************************************************************************\t\t\n";

    string search_query = "select count(*) from Staff_device";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\n\t\t\t\t\tNumber of Maintenance: " << row[0] << endl;
    }
    string searchf_query = "select Device_id,COUNT(device_id) FROM Staff_device group by device_id; ";
    const char* qf = searchf_query.c_str();
    qstate = mysql_query(conn, qf);
    cout << "\n\t\t\t\t\tFrequency of Device Maintenance Done : " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        
        cout << "\t\t\t"<<setw(15) << "|" << row[0] << "\t\t|" << row[1] << "\t|\t\t" << endl;
        

    }
    cout << "\t\t\t------------------------------------------------------------" << endl;
    string searchst_query = "select staff_id,count(Staff_id) from Staff_device group by staff_id order by count(Staff_id) desc ";
    const char* qs = searchst_query.c_str();
    qstate = mysql_query(conn, qs);
    cout << "\n\t\t\t\t\tFrequency of  Staff Handled Maintenance : " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        
        printf("\t\t\t\t      | %-15s | %-5s |\n", row[0] ,row[1]);
       
        
    }
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\n\t\t\t";
    system("pause");
    Report();
}
void ViewMaintenance()
{
    system("color 0B");
    string search_query = "select StaffDevice_id,Staff_id,Device_id,Staffdevice_date,Remarks from staff_device";
    const char* qb = search_query.c_str();
    qstate = mysql_query(conn, qb);
    if (!qstate)
    {
        string Device_id;
        cout << "\n\t\t\t******************************************************************************************" << endl;
        cout << "\t \t \t \t \t\t\tMAINTENANCE INFORMATION " << endl;
        cout << "\t\t\t******************************************************************************************" << endl;
        cout << "\t\t\t" << setw(10) << "StaffDevice_id" << setw(12) << "Staff_id" << setw(15) << "Device_id" << setw(21) << "Staffdevice_Date " << setw(13) << "Remarks" << endl;
        cout << "\t\t\t------------------------------------------------------------------------------------------" << endl;
        res = mysql_store_result(conn);
        if (mysql_num_rows(res) > 0)
        {
            while (row = mysql_fetch_row(res))
            {
                cout << "\t\t\t" << "|" << row[0] << setw(19) << row[1] << setw(17) << row[2] << setw(19) << row[3] << setw(22) << row[4] << setw(8) << "|" << endl;
            }
            cout << "\t\t\t------------------------------------------------------------------------------------------" << endl;
            int option;
            cout << " " << endl;
            cout << "\t\t\t[1] Search Maintenance " << endl;
            cout << "\t\t\t[2] Maintenance Report " << endl;
            cout << "\t\t\t[3] Admin Menu" << endl;
            cout << "\t\t\tPlease Enter an option (1 - 3): ";
            cin >> option;
            if (option == 1)
            {
                system("cls");
                cout << "\t\t\tPlease Enter the Device id to search: ";
                cin >> Device_id;
                string search_query = "select StaffDevice_id,Staff_id,Device_id,Staffdevice_date,Remarks from staff_device where Device_id like '%" + Device_id + "%' ";
                const char* q = search_query.c_str();
                qstate = mysql_query(conn, q);
                res = mysql_store_result(conn);
                if (mysql_num_rows(res) > 0)
                {
                    while (row = mysql_fetch_row(res))
                    {
                        cout << "\t\t\t" << setw(6) << row[0] << setw(15) << row[1] << setw(16) << row[2] << setw(17) << row[3] << setw(18) << row[4] << endl;
                        cout << "\t\t\t";
                        system("pause");
                        Report();
                    }
                }
                else
                {
                    cout << "\t\t\tNo maintenance information found for the specified device ID." << endl;
                    cout << "\t\t\t";
                    system("pause");
                    AdminMenu();
                }
            }
            else if (option == 2)
            {
                MaintenanceReport();
            }
            else
            {
                system("cls");
                AdminMenu();
            }
        }
        else
        {
            cout << "\n\t\t\tNo maintenance information found." << endl;
            cout << "\t\t\t";
            system("pause");
            AdminMenu();
        }
    }
    else
    {
        cout << "\t\t\tQuery Execution Problem. Please try again..." << mysql_errno(conn) << endl;
    }
}



void Report()
{
    system("cls");
    system("color 0B");
    int menu_opt;
    cout << "\n\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\t|                       REPORTS MENU:                          |\t\t\t" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|\t\t\t" << endl;
    cout << "\t\t\t|  [1] MONTHLY REPORT                                          |\t\t\t" << endl;
    cout << "\t\t\t|  [2] DAILY SALES REPORT                                      |\t\t\t" << endl;
    cout << "\t\t\t|  [3] VIEW DEVICE MAINTENANCE                                 |\t\t\t" << endl;
    cout << "\t\t\t|  [4] VIEW BOOKING                                            |\t\t\t" << endl;
    cout << "\t\t\t|  [0] EXIT                                                    |\t\t\t" << endl;
    cout << "\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\tPlease Enter your choice (0 - 4): " ;
    cin >> menu_opt;
    switch (menu_opt)
    {

    case 1:monthlyReport();
       break;

    case 2:dailyReport();
        break;

    case 3:ViewMaintenance();
        break;
    case 4:ViewBooking();
        break;
    case 0:AdminMenu();
        break;

    default:
        cout << "\t\t\tPlease choose 0 to 4 !!\n";
        cout << "\t\t\t";
        system("pause");
        system("cls");
        Report();

    }

}


void AddDevice()
{
    system("color 0B");
    int qstate;
    string Device_id = "";
    string Device_name = "";
    string Device_Status = "";

    cin.ignore(1, '\n');
    cout << "\t\t\tEnter Device_id: ";
    getline(cin, Device_id);
    cout << "\t\t\tEnter Device Name : ";
    getline(cin, Device_name);
    cout << "\t\t\tEnter Status: ";
    getline(cin, Device_Status);
    string checkUser_query = "select * from Device where Device_id = '" + Device_id + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "\t\t\tId has been taken please retry ";
            cout << "\t\t\t";
            system("pause");
            AddDevice();
        }
        else
        {

            string insert_query = "insert into Device (Device_id, Device_name, Device_Status) values ('" + Device_id + "','" + Device_name + "','" + Device_Status + "')";
            const char* q = insert_query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate)
            {
                cout << endl << "\t\t\tSuccessfully stored in database." << endl;
                cout << "\t\t\t";
                system("pause");
                DeviceEntry();
            }
            else
            {
                cout << "\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;
            }
        }
    }
    else
    {
        cout << "\n\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;

    }


}

void ShowDevice()
{
    system("color 0B");
    int qstate;
    system("cls");
    string Device_id;
    qstate = mysql_query(conn, "select * from Device ");
    cout << "\t \t \t\t\t\t DEVICE INFORMATION";
    cout << " " << endl;
    cout << "\t\t\t"<<setw(9) << "Device_id" << setw(14) << "Device_name" << setw(15) << "Device_Status" << endl;

    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout <<"\t\t\t" << setw(6) << row[0] << setw(15) << row[1] << setw(15) << row[2] << endl;
        }
    }
    int option;
    cout << " " << endl;
    cout << "\t\t\t[1] Search Device " << endl;
    cout << "\t\t\t[2] Device Entry Menu" << endl;
    cout << "\t\t\tPlease Enter an option (1/2): ";
    cin >> option;
    if (option == 1)
    {
        cout << "\t\t\tPlease Enter the Device id to search: ";
        cin >> Device_id;
        string search_query = "select Device_id ,Device_name,Device_Status from Device where Device_id like '%" + Device_id + "%' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "\t\t\t" << setw(6) << row[0] << setw(15) << row[1] << setw(16) << row[2] << endl;
            cout << "\t\t\t";
            system("pause");
            DeviceEntry();
        }
    }
    else
    {
        DeviceEntry();
    }
}


void UpdateDevice()
{
    system("color 0B");
    system("cls");
    string Device_id, Device_name, Device_Status;
    int o;
    cout << "\n\t\t\t---------------------- MODIFY DEVICE ----------------------" << endl;
    cout << "\t\t\tEnter Device id : ";
    cin >> Device_id;
    string search_query = " select Device_id,Device_name,Device_Status from Device where Device_id = '" + Device_id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << " " << endl;
        cout << " \t \t \t \t Current Details of the Device \t \t \t " << endl;
        cout << " \t \t \t \t     Device Id : " << row[0] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t [1] Device Name : " << row[1] << endl;
        cout << " \t \t \t \t [2] Device Status : " << row[2] << endl;
        cout << " \t \t \t \t [3] Exit " << endl;
        cout << " \t \t \t \t Choose an option to modify:";
        cin >> o;
        cin.ignore(1, '\n');

        if (o == 1)
        {

            string Device_newname;
            cout << "\n\t \t \t Please Insert the new Device name : ";
            getline(cin, Device_newname);
            string update_query = "update Device set Device_name  = '" + Device_newname + "' where Device_id = '" + Device_id + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << " ";
            cout << "\n\t\t\tSuccesfully modified the details" << endl;
            cout << "\t\t\t";
            system("pause");
            DeviceEntry();
        }
        else if (o == 2)
        {

            string Device_newstatus;
            cout << "\n\t \t \t Please Update the  Device status : ";
            getline(cin, Device_newstatus);
            string update_query = "update Device set Device_Status  = '" + Device_newstatus + "' where Device_id = '" + Device_id + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << " ";
            cout << "\n\t\t\tSuccesfully modified the details" << endl;
            cout << "\t\t\t";
            system("pause");
            DeviceEntry();
        }
        else if (o == 3)
        {
            
            cout << "\n\t\t\t";
            system("pause");
            system("cls");
            DeviceEntry();

        }
        else
            cout << "\t\t\tPlease Enter a valid option from 1 to 3 " << endl;
        UpdateDevice();

    }
}

void DeleteDevice()
{
    system("color 0B");
    string Device_id;
    char del_opt;
    system("cls");
    cout << "\t\t\tPlease Enter the Device id : ";
    cin >> Device_id;
    string search_query = "select Device_id ,Device_name,Device_Status from Device where Device_id like '%" + Device_id + "%' ";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    cout << "\t \t \t\t\t\tDEVICE INFORMATION " << endl;
    cout << "\t\t\t" << setw(9) << "Device_id" << setw(17) << "Device_name" << setw(18) << "Device_Status " << endl;
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t" << setw(6) << row[0] << setw(22) << row[1] << setw(14) << row[2] << endl;
    }
    do
    {
        cout << "\t\t\tAre you sure to delete this device? (y/n) :";
        cin >> del_opt;
        if (del_opt == 'Y' || del_opt == 'y')
        {
            string delete_query = "delete from Device where Device_id = '" + Device_id + "' ";
            const char* q = delete_query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate)
            {
                cout << "\n\t\t\tDeleted Succesfully!!";
                cout << "\n\t\t\t";
                system("pause");
                DeviceEntry();
            }
            else
            {
                cout << "\t\t\tQuery Execution Problem! " << mysql_errno(conn) << endl;
            }
        }
        else
        {
            cout << "\t\t\tWrong Input ...Please enter either y or n\n ";
            cout << "\t\t\t";
            system("pause");
            DeviceEntry();
        }

    } while (del_opt != 'y' && del_opt != 'Y' && del_opt != 'n' && del_opt != 'N');
}


void DeviceEntry()
{
    system("color 0B");
    int menu_opt;
    system("cls");
    cout << "\n\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\t|                       DEVICE ENTRY MENU:                     |\t\t\t" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|\t\t\t" << endl;
    cout << "\t\t\t|  [1] ADD DEVICE                                              |\t\t\t" << endl;
    cout << "\t\t\t|  [2] SHOW DEVICE                                             |\t\t\t" << endl;
    cout << "\t\t\t|  [3] UPDATE DEVICE                                           |\t\t\t" << endl;
    cout << "\t\t\t|  [4] DELETE DEVICE                                           |\t\t\t" << endl;
    cout << "\t\t\t|  [5] EXIT                                                    |\t\t\t" << endl;
    cout << "\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\tPlease Enter your choice (1 - 5): ";
    cin >> menu_opt;
    switch (menu_opt)
    {
    case 1:AddDevice();
        break;

    case 2:ShowDevice();
        break;

    case 3:UpdateDevice();
        break;

    case 4:DeleteDevice();
        break;

    case 5:AdminMenu();
        break;

    default:
        cout << "\t\t\tPlease choose 1 to 5 .";
        cout << "\t\t\t";
        system("pause");
        system("cls");
        DeviceEntry();
    }
}

//Add Member Details
void MemberRegistrations()
{
    
    system("cls");
    system("color 0B");
    cout << "\t\t\t Welcome to Member Registration \t\t\t\n";
    int qstate;
    string Member_name = "";
    string Member_ic = "";
    string Member_phone = "";
    string Member_pass;
    string Member_id = "";
    cin.ignore(1, '\n');
NAME:
    cout << "\t\t\tEnter Member Name: ";
    getline(cin, Member_name);
    if (Member_name == "0")
    {
        goto NAME;
    }
    else if (Member_name.size() > 50)
    {
        cout << "\t\t\t\t MAX CHARACTER IS 50" << endl;
        goto NAME;
    }
    else if (Member_name.size() == 0)
    {
        cout << "\t\t\t\t INVALID CHARACTER SIZE" << endl;
        goto NAME;
    }
IC:

    cout << "\t\t\tEnter Identification Card Number: ";
    getline(cin, Member_ic);
    for (int i = 0; i < Member_ic.length(); i++)
    {
        if (!isdigit(Member_ic[i]) || Member_ic.length() != 12)
        {
            cout << "\t\t\tInvalid Identification Card Number\n";
            goto IC;
        }
    }
    string checkUserc_query = "select Member_ic from Member where Member_ic = '" + Member_ic + "'";
    const char* cui = checkUserc_query.c_str();
    qstate = mysql_query(conn, cui);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t Identification Card Number registered earlier...\n";
        goto IC;
    }
PH:
    cout << "\t\t\tEnter Member Phone Number: ";

    getline(cin, Member_phone);
    for (int i = 0; i < Member_phone.length(); i++)
    {
        if (!isdigit(Member_phone[i]) || (Member_phone.length() < 10 || Member_phone.length() > 11))
        {
            cout << "\t\t\tInvalid Phone Number ";
            goto PH;
        }
    }
    string checkUserp_query = "select Member_phone from Member where Member_phone = '" + Member_phone + "'";
    const char* cup = checkUserp_query.c_str();
    qstate = mysql_query(conn, cup);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t Phone Number have been registered earlier..\n";
        goto PH;
    }
ID:
    cout << "\t\t\tEnter a Member id  : ";
    getline(cin, Member_id);
    string checkUseri_query = "select Member_id from Member where Member_id = '" + Member_id + "'";
    const char* cud = checkUseri_query.c_str();
    qstate = mysql_query(conn, cud);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t Member ID registered earlier...\n";
        goto ID;
    }
PASS:

    bool upper_case = false; //saves the result if upper-case characters were found.
    bool lower_case = false; //same for lower-case
    bool number_case = false; //...

    std::regex upper_case_expression{ "[A-Z]+" }; //here is the very simple expression for upper_case search
    std::regex lower_case_expression{ "[a-z]+" }; //for lower-case
    std::regex number_expression{ "[0-9]+" }; //...

    bool done = false; //let's assume we're not done

    do
    { //do ask-for-password as long were not done

        cout << "\t\t\tEnter Member Password: ";
        getline(std::cin, Member_pass); //get input

        if (Member_pass.length() <= 5 && Member_pass.length() >= 10) { //too short!
            std::cout << "\t\t\tInvalid password! Try again . . .\n\n";

        }
        else
        {

            upper_case = std::regex_search(Member_pass, upper_case_expression); //save the result, if the expression was found.
            lower_case = std::regex_search(Member_pass, lower_case_expression); //....
            number_case = std::regex_search(Member_pass, number_expression);


            //like: sum_of_positive_results = 1 + 0 + 1  (true/false as an integer)
            int sum_of_positive_results = upper_case + lower_case + number_case;

            if (sum_of_positive_results < 3) { //not enough booleans were true!
                std::cout << "\t\t\tInvalid password! Try again . . .\n\n";
                cout << "\t\t\t*THE PASSWORD SHOULD HAVE UPPERCASE,LOWERCASE,NUMBERS \n\n";
            }
            else { //otherwise it's valid!
                std::cout << "\t\t\tThat's a valid Password!" << std::endl;
                done = true;
            }
        }


    } while (!done);

    if (Member_pass == "0")
    {
        goto PASS;
    }
    time_t now = time(0);
    tm* ltm = localtime(&now);
    time_t current = time(0);

    string Member_type1 = "BASIC";
    string Member_type2 = "PREMIUM";
    string Member_type3 = "STUDENT";
    char stdopt;
    cout << "\n\n\t\t\tSTUDENT MEMBERSHIP PLAN BENEFITS\n";
    cout << "\t\t\t---------------------------------------------------------------------------------------\n";
    printf("\t\t\t| %-30s | %-50s |\n", "Membership Plan ", "STUDENT");
    printf("\t\t\t| %-30s | %-50s |\n", "Benefits", "#Gain 15% discount for each device booking");
    printf("\t\t\t| %-30s | %-50s |\n", "     ", "#20 points per booking");
    printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Each registration will be valid for 3 months");
    printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Membership Renewal for 6 months with RM 50");
    printf("\t\t\t---------------------------------------------------------------------------------------\n");
    cout << "\t\t\tAre you a student(y/n):";
    cin >> stdopt;
    if (stdopt == 'y' || stdopt == 'Y')
    {
        string checkUser_query = "select * from Member where Member_id = '" + Member_id + "' and Member_pass = '" + Member_pass + "' and Member_ic = '" + Member_ic + "'";
        const char* cq = checkUser_query.c_str();
        qstate = mysql_query(conn, cq);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            if (res->row_count == 1)
            {
                cout << "\t\t\tId has been taken please retry ";
                MemberRegistrations();
            }
            else
            {

                string insert_query = "insert into Member (Member_name, Member_ic, Member_phone, Member_id, Member_pass,Member_start,Member_end,Member_type) values ('" + Member_name + "','" + Member_ic + "','" + Member_phone + "','" + Member_id + "','" + Member_pass + "','" + today + "','" + end_date + "','" + Member_type3 + "')";
                const char* q = insert_query.c_str();
                qstate = mysql_query(conn, q);
                if (!qstate)
                {
                    cout << endl << "\n\t\t\tSuccessfully Registered.\n" << endl;
                    cout << "\t\t\t";
                    system("pause");
                    Member();
                }
            }
        }
    }
    else
    {
    opt:
        cout << "\n\n\t\t\tMEMBERSHIP PLANS\n";
        cout << "\t\t\t---------------------------------------------------------------------------------------\n";
        printf("\t\t\t| %-30s | %-50s |\n", "Membership Plan ", "BASIC");
        printf("\t\t\t| %-30s | %-50s |\n", "Benefits", "#Gain 20% discount for each device booking");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#20 points per booking");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Each registration will be valid for 3 months");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Membership Renewal for 1 year with RM 100");
        cout << endl;
        printf("\t\t\t| %-30s | %-50s |\n", "Membership Plan ", "PREMIUM");
        printf("\t\t\t| %-30s | %-50s |\n", "Benefits", "#Gain 30% discount for each device booking");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#40 points per booking");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Each registration will be valid for 3 months");
        printf("\t\t\t| %-30s | %-50s |\n", "     ", "#Membership Renewal for 2 years with RM 200");
        printf("\t\t\t---------------------------------------------------------------------------------------\n");
        int qstate;
        int mem_option;
        cout << "\t\t\tPlease Choose a membership plan\n";
        cout << "\t\t\t1.Basic Membership\n";
        cout << "\t\t\t2.Premium Membership :";
        cin >> mem_option;
        if (mem_option == 1)
        {
            string checkUser_query = "select * from Member where Member_id = '" + Member_id + "' and Member_pass = '" + Member_pass + "' and Member_ic = '" + Member_ic + "'";
            const char* cq = checkUser_query.c_str();
            qstate = mysql_query(conn, cq);
            if (!qstate)
            {
                res = mysql_store_result(conn);
                if (res->row_count == 1)
                {
                    cout << "\t\t\tId has been taken please retry ";
                    MemberRegistrations();
                    Member();
                }
                else
                {
                    string insert_query = "insert into Member (Member_name, Member_ic, Member_phone, Member_id, Member_pass,Member_start,Member_end,Member_type) values ('" + Member_name + "','" + Member_ic + "','" + Member_phone + "','" + Member_id + "','" + Member_pass + "','" + today + "','" + end_date + "','" + Member_type1 + "')";
                    const char* q = insert_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (!qstate)
                    {
                        cout << endl << "\n\t\t\tSuccessfully Registered.\n" << endl;
                        cout << "\t\t\t";
                        system("pause");
                        Member();
                    }
                }
            }
            else
            {
                cout << "\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;
                MemberRegistrations();
            }
        }
        if (mem_option == 2)
        {
            string checkUser_query = "select * from Member where Member_id = '" + Member_id + "' and Member_pass = '" + Member_pass + "' and Member_ic = '" + Member_ic + "'";
            const char* cq = checkUser_query.c_str();
            qstate = mysql_query(conn, cq);
            if (!qstate)
            {
                res = mysql_store_result(conn);
                if (res->row_count == 1)
                {
                    cout << "\t\t\tId has been taken please retry ";
                    MemberRegistrations();
                }
                else
                {
                    string insert_query = "insert into Member (Member_name, Member_ic, Member_phone, Member_id, Member_pass,Member_start,Member_end,Member_type) values ('" + Member_name + "','" + Member_ic + "','" + Member_phone + "','" + Member_id + "','" + Member_pass + "','" + today + "','" + end_date + "','" + Member_type2 + "')";
                    const char* q = insert_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (!qstate)
                    {
                        cout << endl << "\n\t\t\tSuccessfully Registered.\n" << endl;
                        cout << "\t\t\t";
                        system("pause");
                        Member();
                    }
                }
            }
            else
            {
                cout << "\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;
                MemberRegistrations();
            }
        }
        else
        {
            cout << "\t\t\tPlease choose the membership plan either from 1 or 2";
            goto opt;
        }

    }
}

void ShowMember()
{
    system("color 0B");
    int qstate;
    system("cls");
    string Member_id;
    qstate = mysql_query(conn, "select * from Member");
    cout << "\t \t \t \t\t\tMEMBER INFORMATION";
    cout << " " << endl;
    printf("\t\t| % -30s | % -20s | % -13s | % -15s | % -13s | % -15s | % -10s |  \n", "Name", "Identification Card", "Phone", "Member from", "Member to", "Points Earned", "Membership");

    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {

            printf("\t\t| % -30s | % -20s | % -13s | % -15s | % -13s | % -15s | % -10s | \n", row[1], row[2], row[4], row[5], row[6], row[7], row[8]);
        }
    }
    int option;
    cout << " " << endl;
    cout << "\t\t\t[1] Search Member " << endl;
    cout << "\t\t\t[2] User Management Menu" << endl;
    cout << "\t\t\tPlease Enter an option (1/2): ";
    cin >> option;
    if (option == 1)
    {
        cout << "\t\t\tPlease Enter the Member id to search: ";
        cin >> Member_id;
        string search_query = "select Member_id ,Member_name,Member_ic,Member_pass,Member_phone from Member where Member_id = '" + Member_id + "' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << " \t \t \t \t     Member Id : " << row[0] <<  endl;
            cout << " \t \t \t \t     Member Name : " << row[1] <<  endl;
            cout << " \t \t \t \t     Member IC Number : " << row[2]<< endl;
            cout << " \t \t \t \t     Member Phone Number : " << row[4] << endl;
            cout << "\t\t\t";
            system("pause");
            Member();
        }
    }
    else
    {
        UserManagement();
    }
}


void UpdateMember()
{
    system("color 0B");
    system("cls");
    string Member_id, Member_name, Member_ic, Member_pass, Member_phone;
    int o;
    cout << "\n\t\t\t---------------------- MODIFY MEMBER ----------------------" << endl;
    cout << "\t\t\tEnter Member id : ";
    cin >> Member_id;
    string search_query = " select Member_id,Member_name,Member_ic,Member_pass,Member_phone,Member_type from Member where Member_id = '" + Member_id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << " " << endl;
        cout << " \t \t \t \t Current Details of the Member \t \t \t " << endl;
        cout << " \t \t \t \t     Member Id : " << row[0] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t     Member Name : " << row[1] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t     Member IC Number : " << row[2] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t [1] Member Password : " << row[3] << endl;
        cout << " \t \t \t \t [2] Member Phone Number : " << row[4] << endl;
        cout << " \t \t \t \t [3] Member Type : " << row[5] << endl;
        cout << " \t \t \t \t [0] Exit " << endl;
        cout << " \t \t \t \t Choose an option to modify:";
        cin >> o;
        cin.ignore(1, '\n');

        if (o == 1)
        {

            string Member_newpass;
            cout << "\t \t \t Please Insert the new Member Password : ";
            getline(cin, Member_newpass);
            string update_query = "update Member set Member_pass  = '" + Member_newpass + "' where Member_id = '" + Member_id + "'";
            const char* qp = update_query.c_str();
            qstate = mysql_query(conn, qp);
            cout << " ";
            cout << "\n\t\t\tSuccesfully modified the details" << endl;
            cout << "\n\t\t\t";
            system("pause");
            Member();
        }
        else if (o == 2)
        {

            string Member_newphone;
            cout << "\t \t \t Please Insert the new phone number   : ";
            getline(cin, Member_newphone);
            string update_query = "update Member set Member_phone  = '" + Member_newphone + "' where Member_id = '" + Member_id + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << " ";
            cout << "\n\t\t\tSuccesfully modified the details" << endl;
            cout << "\n\t\t\t";
            system("pause");
            Member();
        }
        
        else if(o==3)
        {
            string Member_newtype;
            cout << "\t \t \t Please Insert the new membership type(Basic/Premium)   : ";
            getline(cin, Member_newtype);
            string update_query = "update Member set Member_type  = '" + Member_newtype + "' where Member_id = '" + Member_id + "'";
            const char* qr = update_query.c_str();
            qstate = mysql_query(conn, qr);
            cout << " ";
            cout << "\n\t\t\tSuccesfully modified the details" << endl;
            cout << "\n\t\t\t";
            system("pause");
            Member();
        }
        else if (o == 0)
        {
            cout << " \n\t \t \t \t [Returning to Member Management Menu]" << endl;
            cout << " \n\t \t \t \t ";
            system("pause");
            system("cls");
            Member();

        }
        else
        {
            cout << "\n \t \t \t \t Please Enter a valid option from 0 to 3 " << endl;
            UpdateMember();
        }
    }
}

void DeleteMember()
{
    system("color 0B");
    string Member_id;
    char del_opt;
b:
    system("cls");
    cout << "\t\t\tPlease Enter the Member id : ";
    cin >> Member_id;
    string search_query = "select * from Member where Member_id = '" + Member_id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {


        
            cout << "\t \t \t\t\t\tMEMBER INFORMATION " << endl;
            cout << "\t\t\t" << setw(9) << "Member_id" << setw(19) << "Member_name" << setw(17) << "Member_ic" << setw(18) << "Member_phone" << setw(15) << "Member_start" << setw(15) << "Member_end" << setw(15) << "Member_points" << setw(15) << "Member_type" << endl;
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "\t\t\t" << setw(6) << row[0] << setw(22) << row[1] << setw(15) << row[2] << setw(16) << row[4] << setw(16) << row[5] << setw(15) << row[6] << setw(15) << row[7] << setw(15) << row[8] << endl;
            }
            do
            {
                cout << "\t\t\tAre you sure to delete this Member? (y/n) :";
                cin >> del_opt;
                if (del_opt == 'Y' || del_opt == 'y')
                {
                    string delete_query = "delete from Member where Member_id = '" + Member_id + "' ";
                    const char* q = delete_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (!qstate)
                    {
                        cout << "\n\t\t\tDeleted Succesfully!!\n";
                        cout << "\n\t\t\t";
                        system("pause");
                        ShowMember();
                    }
                    else
                    {
                        cout << "\n\t\t\tQuery Execution Problem! " << mysql_errno(conn) << endl;
                    }
                }
                else
                {
                    Member();
                }

            } while (del_opt != 'y' && del_opt != 'Y' && del_opt != 'n' && del_opt != 'N');
        
    }
}



void Member()
{
    system("color 0B");
    system("cls");
    int option;
    cout << "\n\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\t|                    MEMBER MANAGEMENT MENU                    |\t\t\t" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|\t\t\t" << endl;
    cout << "\t\t\t|  [1] MEMBER REGISTRATION                                     |\t\t\t" << endl;
    cout << "\t\t\t|  [2] SHOW MEMBER                                             |\t\t\t" << endl;
    cout << "\t\t\t|  [3] UPDATE MEMBER                                           |\t\t\t" << endl;
    cout << "\t\t\t|  [4] DELETE MEMBER                                           |\t\t\t" << endl;
    cout << "\t\t\t|  [0] EXIT                                                    |\t\t\t" << endl;
    cout << "\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\tPlease Enter your choice (0 - 4): ";
    cin >> option;
    switch (option)
    {
    case 1:MemberRegistrations();
        break;

    case 2:ShowMember();
        break;

    case 3:UpdateMember();
        break;

    case 4:DeleteMember();
        break;
    case 0:UserManagement();
        break;
    default:
        cout << "\t\t\tPlease choose between 0 to 2.Press Enter to Continue...";

        system("cls");
        Member();
        break;


    }

}

//Add Staff Details
void StaffRegistration()
{
    system("color 0B");
    int qstate;
    string Staff_name = "";
    string Staff_ic = "";
    string Staff_phone = "";
    string Staff_pass = "";
    string Staff_id = "";
    cin.ignore(1, '\n');
NAME:
    cout << "\t\t\tEnter Staff Name: ";
    getline(cin, Staff_name);
    if (Staff_name == "0")
    {
        goto NAME;
    }
    else if (Staff_name.size() > 50)
    {
        cout << "\n\t\t\t\t MAX CHARACTER IS 50" << endl;
        goto NAME;
    }
    else if (Staff_name.size() == 0)
    {
        cout << "\n\t\t\t\t INVALID CHARACTER SIZE" << endl;
        goto NAME;
    }
IC:
    cout << "\t\t\tEnter Identification Card Number: ";
    getline(cin, Staff_ic);
    for (int i = 0; i < Staff_ic.length(); i++)
    {
        if (!isdigit(Staff_ic[i]) || Staff_ic.length() < 12|| Staff_ic.length() > 12)
        {
            cout << "\t\t\tInvalid id\n";
            goto IC;
        }

    }
    string checkUseri_query = "select Staff_ic from Staff where Staff_ic = '" + Staff_ic + "'";
    const char* cui = checkUseri_query.c_str();
    qstate = mysql_query(conn, cui);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\t\t\t Identification Card Number registered earlier...\n";
        goto IC;
    }
PH:
    cout << "\t\t\tEnter Staff Phone No: ";
    getline(cin, Staff_phone);
    if (Staff_phone == "0")
    {
        goto PH;
    }
    string checkUserp_query = "select Staff_phone from Staff where Staff_phone = '" + Staff_phone + "'";
    const char* cup = checkUserp_query.c_str();
    qstate = mysql_query(conn, cup);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << "\n\t\t\t Phone Number registered earlier...\n";
        goto IC;
    }

    for (int i = 0; i < Staff_phone.length(); i++)
    {
        if (!isdigit(Staff_phone[i]) || (Staff_phone.length() < 10 || Staff_phone.length() > 11))
        {
            cout << "\n\t\t\tInvalid Phone Number...PLease try again";
            goto PH;
        }
    }
ID:
    cout << "\t\t\tEnter a Staff id  : ";
    getline(cin, Staff_id);
    if (Staff_id.size() == 0)
    {
        cout << "\n\t\t\t\tInvalid Staff ID" << endl;
        goto ID;
    }
    string findbyID_query = "select * from Staff where Staff_id = '" + Staff_id + "'";
    const char* qn = findbyID_query.c_str();
    qstate = mysql_query(conn, qn);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "\n\t\t\t\tId has been taken\n";
            goto ID;
        }
    }
    else
    {
        goto PASS;
    }
PASS:


    bool upper_case = false; //saves the result if upper-case characters were found.
    bool lower_case = false; //same for lower-case
    bool number_case = false; //...
    bool special_char = false;
    std::regex upper_case_expression{ "[A-Z]+" }; //here is the very simple expression for upper_case search
    std::regex lower_case_expression{ "[a-z]+" }; //for lower-case
    std::regex number_expression{ "[0-9]+" }; //...
    std::regex special_char_expression{ "[_@!?]+" };
    bool done = false; //let's assume we're not done

    do
    { //do ask-for-password as long were not done

        cout << "\t\t\tEnter Staff Password (The password must be between 5 - 10 and should have uppercase,lowercase and numbers): ";
        getline(std::cin, Staff_pass); //get input

        if (Staff_pass.length() <= 5 && Staff_pass.length() >= 10) { //too short or too long!!!
            std::cout << "\t\t\t\tInvalid password size! Try again . . .\n\n";

        }
        else
        {

            upper_case = std::regex_search(Staff_pass, upper_case_expression); //save the result, if the expression was found.
            lower_case = std::regex_search(Staff_pass, lower_case_expression); //....
            number_case = std::regex_search(Staff_pass, number_expression);
          

            //like: sum_of_positive_results = 1 + 0 + 1 + 1 (true/false as an integer)
            int sum_of_positive_results = upper_case + lower_case + number_case ;

            if (sum_of_positive_results < 3) { //not enough booleans were true!
                std::cout << "\t\t\t\tInvalid password! Try again . . .\n\n";
                cout << "\t\t\t\t*THE PASSWORD SHOULD HAVE UPPERCASE,LOWERCASE,NUMBERS \n\n";
            }
            else { //otherwise it's valid!
                std::cout << "\t\t\tThat's a valid Password!" << std::endl;
                done = true;
            }
        }


    } while (!done);

    if (Staff_pass == "0")
    {
        goto PASS;
    }
    string checkUserip_query = "select * from Staff where Staff_id = '" + Staff_id + "' and Staff_pass = '" + Staff_pass + "'";
    const char* cuc = checkUserip_query.c_str();
    qstate = mysql_query(conn, cuc);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "\t\t\t\tId has been taken please retry ";
            StaffRegistration();
        }
        else
        {

            string insert_query = "insert into Staff (Staff_name, Staff_ic, Staff_phone, Staff_id, Staff_pass) values ('" + Staff_name + "','" + Staff_ic + "','" + Staff_phone + "','" + Staff_id + "','" + Staff_pass + "')";
            const char* q = insert_query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate)
            {
                cout << endl << "\n\t\t\tSuccessfully stored in database." << endl;
                cout << "\t\t\t";
                system("pause");
                Staff();
            }
            else
            {
                cout << "\n\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;
                StaffRegistration();
            }
        }
    }
    else
    {
        cout << "\n\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;
    }
}


void ShowStaff()
{
    system("color 0B");
    int qstate;
    system("cls");
    string Staff_id;
    qstate = mysql_query(conn, "select staff_id,staff_name,staff_ic,staff_phone from Staff ");
    cout << "\t \t \t \t\t\tSTAFF INFORMATION";
    cout << " " << endl;
    cout <<"\t\t\t"<< setw(9) << "Staff_id" << setw(22) << "Staff_name" << setw(23) << "Staff_ic" << setw(24) << "Staff_phone" << endl;

    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "\t\t\t" << setw(10) << row[0] << setw(27) << row[1] << setw(20) << row[2] << setw(20) << row[3] << "\t\t\t" << endl;
        }
    }
    int option;
    cout << " " << endl;
    cout << "\t\t\t[1] Search Staff " << endl;
    cout << "\t\t\t[2] UserManagement Menu" << endl;
    cout << "\t\t\tPlease Enter an option (1/2): ";
    cin >> option;
    if (option == 1)
    {
        cout << "\t\t\tPlease Enter the Staff id to search: ";
        cin >> Staff_id;
        string search_query = "select Staff_id ,Staff_name,Staff_ic,Staff_phone from Staff where Staff_id = '" + Staff_id + "' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << " \t \t \t \t     Staff Id : " << row[0] << endl;
            cout << " \t \t \t \t     Staff Name : " << row[1] <<  endl;
            cout << " \t \t \t \t     Staff IC Number : " << row[2] <<  endl;
            cout << " \t \t \t \t     Staff Phone Number : " << row[3] << endl;
            cout << "\n\t\t\t";
            system("pause");
            Staff();
        }
    }
    else
    {
        Staff();
    }
}


void UpdateStaff()
{
    system("color 0B");
    system("cls");
    string Staff_id, Staff_name, Staff_ic, Staff_pass, Staff_phone;
    int o;
    cout << "\n\t\t\t---------------------- MODIFY STAFF ----------------------" << endl;
    cout << "\t\t\tEnter Staff id : ";
    cin >> Staff_id;
    string search_query = " select Staff_id,Staff_name,Staff_ic,Staff_pass,Staff_phone from Staff where Staff_id = '" + Staff_id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << " " << endl;
        cout << " \t \t \t \t Current Details of the Staff \t \t \t " << endl;
        cout << " \t \t \t \t     Staff Id : " << row[0] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t     Staff Name : " << row[1] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t     Staff IC Number : " << row[2] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t [1] Staff Password : " << row[3] << endl;
        cout << " \t \t \t \t [2] Staff Phone Number : " << row[4] << endl;
        cout << " \t \t \t \t [0] Exit " << endl;
        cout << " \t \t \t \t Choose an option to modify:";
        cin >> o;
        cin.ignore(1, '\n');

        if (o == 1)
        {

            string Staff_newpass;
            cout << "\t \t \t Please Insert the new Staff Password : ";
            getline(cin, Staff_newpass);
            string update_query = "update Staff set Staff_pass  = '" + Staff_newpass + "' where Staff_id = '" + Staff_id + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << " ";
            cout << "\t\t\tSuccesfully modified the details" << endl;
            cout << "\t\t\t";
            system("pause");
            Staff();
        }
        else if (o == 2)
        {

            string Staff_newphone;
            cout << "\t \t \t Please Insert the new phone number   : ";
            getline(cin, Staff_newphone);
            string update_query = "update Staff set Staff_phone  = '" + Staff_newphone + "' where Staff_id = '" + Staff_id + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << " ";
            cout << "\t\t\tSuccesfully modified the details" << endl;
            cout << "\t\t\t";
            system("pause");
            Staff();
        }
       
        else if(o==0)
        {
            cout << " \t \t \t \t [Returning to Staff Management Menu]" << endl;
            cout << " \t \t \t \t ";
            system("pause");
            system("cls");
            Staff();
        }
        else
        {
            cout << " \t \t \t \t Please Enter a valid option from 0 to 2 " << endl;
            cout << " \t \t \t \t ";
            system("pause");
            UpdateStaff();
        }
    }
}

void DeleteStaff()
{
    system("color 0B");
    string Staff_id;
    char del_opt;
s:
    system("cls");
    cout << "\t\t\tPlease Enter the Staff id : ";
    cin >> Staff_id;
    string search_query = "select Staff_id ,Staff_name,Staff_ic,Staff_pass,Staff_phone from Staff where Staff_id = '" + Staff_id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {


        res = mysql_store_result(conn);
        if (mysql_num_rows(res) > 0)
        {
            cout << "\t \t \t\t\t\tSTAFF INFORMATION " << endl;
            cout << "\t\t\t" << setw(9) << "Staff_id" << setw(14) << "Staff_name" << setw(15) << "Staff_ic" << setw(16) << "Staff_pass" << setw(15) << "Staff_phone" << endl;
            
            while (row = mysql_fetch_row(res))
            {
                cout <<"\t\t\t" << setw(6) << row[0] << setw(15) << row[1] << setw(15) << row[2] << setw(16) << row[3] << setw(15) << row[4] << endl;
            }
            do
            {
                cout << "\t\t\tAre you sure to delete this Staff? (y/n) :";
                cin >> del_opt;
                if (del_opt == 'Y' || del_opt == 'y')
                {
                    string delete_query = "delete from Staff where Staff_id = '" + Staff_id + "' ";
                    const char* q = delete_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (!qstate)
                    {
                        cout << "\t\t\tDeleted Succesfully!!\n";
                        cout << "\t\t\t";
                        system("pause");
                        Staff();
                    }
                    else
                    {
                        cout << "\t\t\tQuery Execution Problem! " << mysql_errno(conn) << endl;
                    }
                }
                else
                {
                    UserManagement();
                }

            } while (del_opt != 'y' && del_opt != 'Y' && del_opt != 'n' && del_opt != 'N');
        }
        else
        {
            cout << "\n\t\t\tPlease Enter a valid Staff ID" << endl;
            system("pause");
            goto s;
        }
    }
}
void Staff()
{
    system("cls");
    system("color 0B");
    int option;
    cout << "\n\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\t|                    STAFF MANAGEMENT MENU                     |\t\t\t" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|\t\t\t" << endl;
    cout << "\t\t\t|  [1] STAFF REGISTRATION                                      |\t\t\t" << endl;
    cout << "\t\t\t|  [2] SHOW STAFF                                              |\t\t\t" << endl;
    cout << "\t\t\t|  [3] UPDATE STAFF                                            |\t\t\t" << endl;
    cout << "\t\t\t|  [4] DELETE STAFF                                            |\t\t\t" << endl;
    cout << "\t\t\t|  [0] EXIT                                                    |\t\t\t" << endl;
    cout << "\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\tPlease Enter your choice (0 - 4): ";
    cin >> option;
    switch (option)
    {
    case 1:StaffRegistration();
        break;

    case 2:ShowStaff();
        break;

    case 3:UpdateStaff();
        break;

    case 4:DeleteStaff();
        break;
    case 0:UserManagement();
        break;
    default:
        cout << "\t\t\tPlease choose between 0 to 2.Press Enter to Continue...";

        system("cls");
        Staff();
        break;


    }

}

//Add Admin Details
void AdminRegistration()
{
    system("color 0B");
    int qstate;
    string Admin_name = "";
    string Admin_ic = "";
    string Admin_phone = "";
    string Admin_pass = "";
    string Admin_id = "";

    cin.ignore(1, '\n');//ignores line or whitespace

NAME:
    cout << "\t\t\tEnter the Admin Name: ";
    getline(cin, Admin_name);
    if (Admin_name == "0")
    {
        goto NAME;
    }
    else if (Admin_name.size() > 50)
    {
        cout << "\t\t\t\t MAX CHARACTER IS 50" << endl;
        goto NAME;
    }
    else if (Admin_name.size() == 0)
    {
        cout << "\t\t\t\t INVALID CHARACTER SIZE" << endl;
        goto NAME;
    }
IC:
    cout << "\t\t\tEnter Identification Card Number: ";
    getline(cin, Admin_ic);
    for (int i = 0; i < Admin_ic.length(); i++)
    {
        if (!isdigit(Admin_ic[i]) || Admin_ic.length() < 12|| Admin_ic.length() > 12)
        {
            cout << "Invalid id\n";
            goto IC;
        }

    }
    string findbyIC_query = "select Admin_ic from Admin where Admin_ic = '" + Admin_ic + "'";
    const char* qc = findbyIC_query.c_str();
    qstate = mysql_query(conn, qc);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "Phone Number have been registered \n";
            goto IC;
        }
    }
    else
    {
        goto PH;
    }

PH:
    cout << "\t\t\tEnter Admin Phone No: ";
    getline(cin, Admin_phone);
    if (Admin_phone == "0")
    {
        goto PH;
    }
    for (int i = 0; i < Admin_phone.length(); i++)
    {
        if (!isdigit(Admin_phone[i]) || (Admin_phone.length() < 10 || Admin_phone.length() > 11))
        {
            cout << "Invalid Phone Number...PLease try again";
            goto PH;
        }
    }
    string findbyp_query = "select Admin_phone from Admin where Admin_phone = '" + Admin_phone + "'";
    const char* qp = findbyp_query.c_str();
    qstate = mysql_query(conn, qp);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "Phone Number have been registered \n";
            goto PH;
        }
    }
    else
    {
        goto ID;
    }
ID:
    cout << "\t\t\tEnter a admin id  : ";
    getline(cin, Admin_id);
    if (Admin_id.size() == 0)
    {
        cout << "Invalid Admin ID" << endl;
        goto ID;
    }
    string findbyID_query = "select * from Admin where Admin_id = '" + Admin_id + "'";
    const char* qn = findbyID_query.c_str();
    qstate = mysql_query(conn, qn);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "Id has been taken\n";
            goto ID;
        }
    }
    else
    {

        goto PASS;
    }

PASS:

    bool upper_case = false; //saves the result if upper-case characters were found.
    bool lower_case = false; //same for lower-case
    bool number_case = false; //...
    bool special_char = false;
    std::regex upper_case_expression{ "[A-Z]+" }; //here is the very simple expression for upper_case search
    std::regex lower_case_expression{ "[a-z]+" }; //for lower-case
    std::regex number_expression{ "[0-9]+" }; //...
    std::regex special_char_expression{ "[_@!?]+" };
    bool done = false; //let's assume we're not done

    do
    { //do ask-for-password as long were not done

        cout << "\t\t\tEnter Admin Password(The password must be between 5 - 10 and should have uppercase,lowercase and numbers): ";
        getline(std::cin, Admin_pass); //get input

        if (Admin_pass.length() <= 5 && Admin_pass.length() >= 10) { //too short or too long!!!
            std::cout << "\t\t\tInvalid password size! Try again . . .\n\n";

        }
        else
        {

            upper_case = std::regex_search(Admin_pass, upper_case_expression); //save the result, if the expression was found.
            lower_case = std::regex_search(Admin_pass, lower_case_expression); //....
            number_case = std::regex_search(Admin_pass, number_expression);
           
            //like: sum_of_positive_results = 1 + 0 + 1 + 1 (true/false as an integer)
            int sum_of_positive_results = upper_case + lower_case + number_case ;

            if (sum_of_positive_results < 3) { //not enough booleans were true!
                std::cout << "\t\t\tInvalid password! Try again . . .\n\n";
                cout << "\t\t\t*THE PASSWORD SHOULD HAVE UPPERCASE,LOWERCASE,NUMBERS  \n\n";
            }
            else { //otherwise it's valid!
                std::cout << "\t\t\tThat's a valid Password!" << std::endl;
                done = true;
            }
        }


    } while (!done);
    if (Admin_pass == "0")
    {
        goto PASS;
    }
    string checkUser_query = "select * from Admin where Admin_id = '" + Admin_id + "' and Admin_pass = '" + Admin_pass + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "\t\t\tId has been taken please retry ";
            AdminRegistration();
        }
        else
        {

            string insert_query = "insert into Admin (Admin_name, Admin_ic, Admin_phone, Admin_id, Admin_pass) values ('" + Admin_name + "','" + Admin_ic + "','" + Admin_phone + "','" + Admin_id + "','" + Admin_pass + "')";
            const char* q = insert_query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate)
            {
                cout << endl << "\t\t\tSuccessfully stored in database." << endl;
                cout << "\t\t\t";
                system("pause");
                Admin();
            }
            else
            {
                cout << "\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;
                AdminRegistration();

            }
        }
    }
    else
    {
        cout << "\t\t\tQuery Execution Problem!!" << mysql_errno(conn) << endl;
        AdminRegistration();
    }
}


void ShowAdmin()
{
    system("color 0B");
    int qstate;
    system("cls");
    string Admin_id;
    qstate = mysql_query(conn, "select Admin_id,Admin_name,Admin_ic,Admin_phone from Admin ");
    cout << "\t \t \t \t\t\tADMIN INFORMATION";
    cout << " " << endl;
    cout << "\t\t\t" << setw(9) << "Admin ID" << setw(19) << "Admin Name" << setw(19) << "Admin IC" << setw(24) << "Admin Phone" << endl;

    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "\t\t\t"<<setw(10) << row[0] << setw(20) << row[1] << setw(20) << row[2] << setw(20) << row[3]  << "\t\t\t"<<endl;
        }
    }
    int option;
    cout << " " << endl;
    cout << "\t\t\t[1] Search Admin " << endl;
    cout << "\t\t\t[2] User Management Menu" << endl;
    cout << "\t\t\tPlease Enter an option(1/2) : ";
    cin >> option;
    if (option == 1)
    {
        cout << "\t\t\tPlease Enter the Admin id to search: ";
        cin >> Admin_id;
        string search_query = "select Admin_id ,Admin_name,Admin_ic,Admin_phone from Admin where Admin_id = '" + Admin_id + "' ";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << " \t \t \t \t     Admin Id : " << row[0] <<  endl;
            cout << " \t \t \t \t     Admin Name : " << row[1] <<endl;
            cout << " \t \t \t \t     Admin IC Number : " << row[2] << endl;
            cout << " \t \t \t \t     Admin Phone Number : " << row[3] << endl;
            cout << "\t\t\t";
            system("PAUSE");
            Admin();
        }
    }
    else
    {
        system("cls");
        UserManagement();
    }
}


void UpdateAdmin()
{
    system("color 0B");
    system("cls");
    string Admin_id, Admin_name, Admin_ic, Admin_pass, Admin_phone;
    int o;
    cout << "\n\t\t\t---------------------- MODIFY ADMIN ----------------------" << endl;
    cout << "\t\t\tEnter Admin id : ";
    cin >> Admin_id;
    string search_query = " select Admin_id,Admin_name,Admin_ic,Admin_pass,Admin_phone from Admin where Admin_id = '" + Admin_id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        cout << " " << endl;
        cout << " \t \t \t \t Current Details of the Admin \t \t \t " << endl;
        cout << " \t \t \t \t     Admin Id : " << row[0] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t     Admin Name : " << row[1] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t     Admin IC Number : " << row[2] << "<UNEDITABLE>" << endl;
        cout << " \t \t \t \t [1] Admin Password : " << row[3] << endl;
        cout << " \t \t \t \t [2] Admin Phone Number : " << row[4] << endl;
        cout << " \t \t \t \t [0] Exit " << endl;
        cout << " \t \t \t \t Choose an option to modify:";
        cin >> o;
        cin.ignore(1, '\n');

        if (o == 1)
        {

            string Admin_newpass;
            cout << "\t \t \t Please Insert the new Admin Password : ";
            getline(cin, Admin_newpass);
            string update_query = "update Admin set Admin_pass  = '" + Admin_newpass + "' where Admin_id = '" + Admin_id + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << " ";
            cout << "\t\t\t Succesfully modified the details" << endl;
            cout << "\t\t\t ";
            system("pause");
            Admin();
        }
        else if (o == 2)
        {

            string Admin_newphone;
            cout << "\t \t \t Please Insert the new phone number   : ";
            getline(cin, Admin_newphone);
            string update_query = "update Admin set Admin_phone  = '" + Admin_newphone + "' where Admin_id = '" + Admin_id + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
            cout << " ";
            cout << "\t\t\tSuccesfully modified the details" << endl;
            cout << "\t\t\t";
            system("pause");
            Admin();
        }
        else if (o == 0)
        {
            cout << " \t \t \t \t [Returning to Admin Management Menu]"<<endl;
            cout << " \t \t \t \t ";
            system("pause");
            system("cls");
            Admin();
        }
        else
        cout << " \t \t \t \t Please Enter a valid option from 1 to 3 " << endl;
        cout << " \t \t \t \t ";
        system("pause");
        UpdateAdmin();

    }
}

void DeleteAdmin()
{
    system("color 0B");
    string Admin_id;
    char del_opt;
a:
    system("cls");
    cout << "\t\t\tPlease Enter the Admin id : ";
    cin >> Admin_id;
    string search_query = "select Admin_id ,Admin_name,Admin_ic,Admin_pass,Admin_phone from Admin where Admin_id = '" + Admin_id + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
    if (!qstate)
    {


        res = mysql_store_result(conn);
        if (mysql_num_rows(res) > 0)
        {
            cout << "\t \t \tADMIN INFORMATION " << endl;
            cout << "\t\t\t" << setw(9) << "Admin_id" << setw(14) << "Admin_name" << setw(15) << "Admin_ic" << setw(16) << "Admin_pass" << setw(15) << "Admin_phone" << endl;
           
            while (row = mysql_fetch_row(res))
            {
                cout << "\t\t\t" << setw(6) << row[0] << setw(15) << row[1] << setw(15) << row[2] << setw(16) << row[3] << setw(15) << row[4] << endl;
            }
            do
            {
                cout << "\t\t\tAre you sure to delete this Admin? (y/n) :";
                cin >> del_opt;
                if (del_opt == 'Y' || del_opt == 'y')
                {
                    string delete_query = "delete from Admin where Admin_id = '" + Admin_id + "' ";
                    const char* q = delete_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (!qstate)
                    {
                        cout << "\t\t\tDeleted Succesfully!!\n";
                        cout << "\n\t\t\t";
                        system("pause");
                        Admin();

                    }
                    else
                    {
                        cout << "\t\t\tQuery Execution Problem! " << mysql_errno(conn) << endl;
                        Admin();
                    }
                }
                else
                {
                    Admin();
                }

            } while (del_opt != 'y' && del_opt != 'Y' && del_opt != 'n' && del_opt != 'N');

        }
        else
        {
            cout << "\n\t\t\tPlease Enter a valid Admin ID" << endl;
            system("pause");
            goto a;
        }
    }

        
}
void Admin()
{
    system("cls");
    system("color 0B");
    int option;
    cout << "\n\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\t|                    ADMIN MANAGEMENT MENU                     |\t\t\t" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|\t\t\t" << endl;
    cout << "\t\t\t|  [1] ADMIN REGISTRATION                                      |\t\t\t" << endl;
    cout << "\t\t\t|  [2] SHOW ADMIN                                              |\t\t\t" << endl;
    cout << "\t\t\t|  [3] UPDATE ADMIN                                            |\t\t\t" << endl;
    cout << "\t\t\t|  [4] DELETE ADMIN                                            |\t\t\t" << endl;
    cout << "\t\t\t|  [0] EXIT                                                    |\t\t\t" << endl;
    cout << "\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\tPlease Enter your choice (0 - 4) : ";
    cin >> option;
    switch (option)
    {
    case 1:AdminRegistration();
        break;

    case 2:ShowAdmin();
        break;

    case 3:UpdateAdmin();
        break;

    case 4:DeleteAdmin();
        break;
    case 0:UserManagement();
        break;
    default:
        cout << "\t\t\tPlease choose between 0 to 2.\n";
        cout << "\t\t\t";
        system("pause");
        system("cls");
        Admin();
        break;


    }

}
void UserManagement()
{
    system("cls");
    system("color 0B");
    int option;
    cout << "\n\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\t|                    USER MANAGEMENT MENU                      |\t\t\t" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|\t\t\t" << endl;
    cout << "\t\t\t|  [1] ADMIN MANAGEMENT                                        |\t\t\t" << endl;
    cout << "\t\t\t|  [2] STAFF MANAGEMENT                                        |\t\t\t" << endl;
    cout << "\t\t\t|  [3] MEMBER MANAGEMENT                                       |\t\t\t" << endl;
    cout << "\t\t\t|  [4] EXIT                                                    |\t\t\t" << endl;
    cout << "\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\tPlease Enter your choice (1 -4) : ";
    cin >> option;
    switch (option)
    {
    case 1: Admin();
        break;

    case 2: Staff();
        break;

    case 3:Member();
        break;

    case 4:
        cout << "\t\t\tReturning to Admin Menu..." << endl;
        AdminMenu();
    default:
        cout << "\t\t\tPlease choose between 1 to 4...";
        cout<<"\n\t\t\t";
        system("pause");
        system("cls");
        UserManagement();
        break;
    }
}

void AdminMenu()
{
    system("cls");
    system("color 0B");
    int choice;
    cout << "\n\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\t|                          ADMIN MENU                          |\t\t\t" << endl;
    cout << "\t\t\t|--------------------------------------------------------------|\t\t\t" << endl;
    cout << "\t\t\t|  [1] USER MANAGEMENT                                         |\t\t\t" << endl;
    cout << "\t\t\t|  [2] DEVICE ENTRY                                            |\t\t\t" << endl;
    cout << "\t\t\t|  [3] REPORTS                                                 |\t\t\t" << endl;
    cout << "\t\t\t|  [4] EXIT                                                    |\t\t\t" << endl;
    cout << "\t\t\t----------------------------------------------------------------\t\t\t" << endl;
    cout << "\t\t\tPlease Enter your choice (1 - 4): ";
    cin >> choice;
    switch (choice)
    {

    case 1:UserManagement();
        break;
    case 2:DeviceEntry();
        break;
   
    case 3:Report();
        break;
    
    case 4:LoginMenu();
        break;

    default:
        cout << "\n\t\t\tPlease choose between 1 to 4...\n";
        cout << "\t\t\t";
       
        system("pause");
        system("cls");
        AdminMenu();
        break;

    }
}


//Admin Login 
void AdminLogin()
{
    system("color 0B");
    int option;
    char Flag;
    
a:
    system("cls");
    cout << "\n\t\t\t RH CYBERCAFE MANAGEMENT SYSTEM \t\t\t \n" << endl;
    cout << "\t\t\t=============ADMIN LOGIN================== \t\t\t" << endl;
    string username, password;
b:
    cout << "\t\t\tADMIN ID : ";
    cin >> username;
    if (username == "0")
    {
        goto b;
    }
    cout << "\t\t\tAdmin Password : ";
    int i = 0;
    char a;
    for (i = 0;;)
    {
        a = _getch();
        if (a >= 'a' && a <= 'z' || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
        {

            password += a;
            ++i;
            cout << "*";

        }
        if (a == '\b' && i >= 1)
        {
            cout << "\b \b";
            --i;
        }
        if (a == '\r')
        {
            break;
        }

    }
    if (password == "0")
    {
         cout << "\n\t\t\tInvalid Password";
        goto a;
    }


    //Check Admin username and password
    string checkUser_query = "select Admin_id from Admin where Admin_id like BINARY '" + username + "' and Admin_pass like BINARY '" + password + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);
    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
                cout << "\n\t\t\t[Login Successful]...\t\t\t\n";
            cout << "\t\t\t";
            system("pause");
            system("cls");
            AdminMenu();

        }
        else
        {
            cout << "\n\t\t\tYou have entered a wrong password or id.\n\t\t\tPress '(Y/y)' to try again:";
            cin >> Flag;
            if (Flag == 'y' || Flag == 'Y')
            {

                cout << "\n\t\t\t[1] RETURN TO LOGIN" << endl;
                cout << "\t\t\t[2] FORGOT PASSWORD" << endl;
                cout << "\t\t\tPlease Enter your choice (1/2) : ";
                cin >> option;
                if (option == 1)
                {
                    system("cls");
                    goto a;
                }
                else if (option == 2)
                {
                    string Admin_phone, Admin_ic;
ft:
                    cout << "\t\t\tEnter Admin IC Number/Phone Number :";
                    cin >> Admin_ic;
                    string search_query = " select Admin_id,Admin_name,Admin_ic,Admin_pass,Admin_phone from Admin where Admin_ic ='" + Admin_ic + "' or Admin_phone ='" + Admin_ic + "'  ";
                    const char* q = search_query.c_str();
                    qstate = mysql_query(conn, q);
                    if (qstate)
                    {
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res))
                        {

                            cin.ignore(1, '\n');
                            string Admin_newpass;
                            cout << "\t\t\tPlease Insert the new Admin Password : ";
                            getline(cin, Admin_newpass);
                            string update_query = "update Admin set Admin_pass  = '" + Admin_newpass + "' where Admin_ic = '" + Admin_newpass + "'";
                            const char* q = update_query.c_str();
                            qstate = mysql_query(conn, q);
                            cout << " ";
                            cout << "\t\t\tSuccesfully modified the password" << endl;
                            LoginMenu();
                        }
                    }
                    else
                    {
                        cout << "\n\t\t\tInvalid IC Number/Phone Number";
                        goto ft;
                    }
                }

            }
            else
            {
                system("cls");
                LoginMenu();
            }


        }
    }

}

void LoginMenu()
{
    system("cls");
    system("color 0B");
    int role;
    cout << "\n\t\t\t RH CYBERCAFE MANAGEMENT SYSTEM \t\t\t \n" << endl;
    cout << "\n\t\t\t ROLE OPTION :\t\t\t \n" << endl;
    cout << "\t\t\t1 - ADMIN\t\t\t" << endl;
    cout << "\t\t\t2 - STAFF\t\t\t" << endl;
    cout << "\t\t\t3 - MEMBER\t\t\t" << endl;
    cout << "\t\t\t4 - EXIT   \t\t\t" << endl;
    cout << "\t\t\tPlease Enter your Choice (1 -4) :";
    cin >> role;
    switch (role)
    {
    case 1:AdminLogin();
        break;

    case 2:StaffLogin();
        break;

    case 3:MemberLogin();
        break;

    case 4:
        cout << "\t\t\tReturning to Login Menu..." << endl;
        main();

    default:
        cout << "\t\t\tPlease choose between 1 to 4.\n";
        cout << "\t\t\t";
        system("pause");
        system("cls");
        LoginMenu();
        break;
    }
}

int main()
{
    
   
    system("color 0B");
    db_response::ConnectionFunction();
    cout << time1 << endl;
    cout << real << endl;
    
   
    int choice = 0;
    cout << "\t\t\t===========================================================\t\t\t" << endl;
    cout << "\t\t\t|            RH CYBERCAFE MANAGEMENT SYSTEM               |\t\t\t" << endl;
    cout << "\t\t\t===========================================================\t\t\t" << endl;
    cout << "\t\t\t|1.LOGIN                                                  |\t\t\t" << endl;
    cout << "\t\t\t|2.MEMBER REGISTRATION                                    |\t\t\t" << endl;
    cout << "\t\t\t|3.EXIT                                                   |\t\t\t" << endl;
    cout << "\t\t\t===========================================================\t\t\t" << endl;
    cout << "\t\t\t Please Enter your choice (1 - 3):";
   
    cin >> choice;

    switch (choice)
    {
    case 1:LoginMenu();
        break;
    case 2:MemberRegistration();
        break;

    case 3:
        cout << "Program Exiting..." << endl;
        exit(0);

    default:
        cout << "\t\t\tPlease choose a choice between 1 to 3.\n";
        cout << "\t\t\t";
        system("pause");
        system("cls");
        main();
        break;

    }

}