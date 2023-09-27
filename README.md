# Cybercafe-Mangement-System

RH-Cybercafe-Management-

Simple Cybercafe Managment System Project was started by Roshini for Workshop 1

Cybercafe Management For Members To Book Various Devices Accordingly

Three scope of users

    Admin
    Staff
    Member

Simple implementation of Database System with MYSQL

Features includes

    Booking a device
    Adding devices
    QR Code generation (mock cashless payment)
    Bar Code generation (mock)
    Receipt Generation (File Handling)
    Various Payment Methods:Credit card validation, QR Payment and Cash Payment
    Time selection
    Device Selection
    Password reset for all user scopes according to ID/Phone Number
    Registration for all users scope
    CRUD features according to rights of users
    Report Generation by month and by date

Instructions:

1. Download and Extract the file named Workshop1.
2. Open XAMPP and start and open the localhost.
3. Upload the database named 'device_mgmt' in localhost
4. Find the workshop.cpp and DBCONN.h file.
5. Make sure the DBCONN.h(conn = mysql_real_connect(conn, "localhost", "root", "", "device_mgmt", 3306, NULL, 0);)
5. Debug the workshop.cpp and now you will be in the seeing the console application of RH Cybercafe Management System
