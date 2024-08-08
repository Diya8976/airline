#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Airline 
{
private:
    string Flight, Des, Dep;
    int Seats;

public:
    Airline(string flight, string des, string dep, int seats)
        : Flight(flight), Des(des), Dep(dep), Seats(seats) {}

    string getFlight() 
    {
        return Flight;
    }
    string getDes() 
    {
        return Des;
    }
    string getDep() 
    {
        return Dep;
    }
    int getSeats() 
    {
        return Seats;
    }

    void update(string flight, const string& passengerName) 
    {
        ifstream in("C:\\Users\\diya\\Desktop\\things\\projects\\Airline management system\\flight.txt");
        ofstream out("C:\\Users\\diya\\Desktop\\things\\projects\\Airline management system\\flight_temp.txt");

        if (!in || !out) 
        {
            cout << "Error: file can't open!" << endl;
            return;
        }

        string line;
        while (getline(in, line)) 
        {
            int pos = line.find(flight);
            if (pos != string::npos) 
            {
                int current = Seats - 1;
                Seats = current;
                stringstream ss;
                ss << current;
                string strCurrent = ss.str();

                int seatPos = line.find_last_of(':');
                line.replace(seatPos + 1, string::npos, strCurrent);
            }
            out << line << endl;
        }
        out.close();
        in.close();
        remove("C:\\Users\\diya\\Desktop\\things\\projects\\Airline management system\\flight.txt");
        rename("C:\\Users\\diya\\Desktop\\things\\projects\\Airline management system\\flight_temp.txt",
               "C:\\Users\\diya\\Desktop\\things\\projects\\Airline management system\\flight.txt");

        // Log the reservation
        ofstream log("C:\\Users\\diya\\Desktop\\things\\projects\\Airline management system\\reservations.txt", ios::app);
        if (!log) 
        {
            cout << "Error: could not open reservations log file!" << endl;
        } 
        else 
        {
            log << "Passenger: " << passengerName << ", Flight: " << flight << endl;
            log.close();
        }

        cout << "Seat reservation successful!" << endl;
    }

    static void Display() 
    {
        ifstream in("C:\\Users\\diya\\Desktop\\things\\projects\\Airline management system\\flight.txt");
        if (!in) 
        {
            cout << "Error: file can't open!" << endl;
        } 
        else 
        {
            string line;
            while (getline(in, line)) 
            {
                cout << line << endl;
            }
            in.close();
        }
    }

    static void DisplayReservations() 
    {
        ifstream in("C:\\Users\\diya\\Desktop\\things\\projects\\Airline management system\\reservations.txt");
        if (!in) 
        {
            cout << "Error: file can't open!" << endl;
        } 
        else 
        {
            string line;
            while (getline(in, line)) 
            {
                cout << line << endl;
            }
            in.close();
        }
    }
};

int main() 
{
    Airline flight1("F101", "UAE", "England", 50);
    Airline flight2("F102", "UAE", "USA", 40);
    Airline flight3("F103", "UAE", "Canada", 2);
    Airline flight4("F104", "UAE", "India", 50);
    Airline flight5("F105", "UAE", "West Indies", 40);
    Airline flight6("F106", "UAE", "Netherlands", 2);

    ofstream out("C:\\Users\\diya\\Desktop\\things\\projects\\Airline management system\\flight.txt");
    if (!out) 
    {
        cout << "Error: file can't open!" << endl;
    } 
    else 
    {
        out << flight1.getFlight() << ":" << flight1.getDes() << ":" << flight1.getDep() << ":" << flight1.getSeats() << endl;
        out << flight2.getFlight() << ":" << flight2.getDes() << ":" << flight2.getDep() << ":" << flight2.getSeats() << endl;
        out << flight3.getFlight() << ":" << flight3.getDes() << ":" << flight3.getDep() << ":" << flight3.getSeats() << endl;
        out << flight4.getFlight() << ":" << flight4.getDes() << ":" << flight4.getDep() << ":" << flight4.getSeats() << endl;
        out << flight5.getFlight() << ":" << flight5.getDes() << ":" << flight5.getDep() << ":" << flight5.getSeats() << endl;
        out << flight6.getFlight() << ":" << flight6.getDes() << ":" << flight6.getDep() << ":" << flight6.getSeats() << endl;
        cout << "Data saved successfully" << endl;
        out.close();
    }

    bool exit = false;
    while (!exit) 
    {
        system("cls");
        cout << "\t Welcome to Airline Reservation System" << endl;
        cout << "\t *************************************" << endl;
        cout << "\t 1. Reserve A Seat." << endl;
        cout << "\t 2. View Reservations." << endl;
        cout << "\t 3. Exit." << endl;
        cout << "\t Enter your choice: ";

        int val;
        cin >> val;

        if (val == 1) 
        {
            system("cls");
            Airline::Display();
            string flight;
            cout << "Enter flight no: ";
            cin >> flight;

            cout << "Enter your name: ";
            string passengerName;
            cin >> passengerName;

            if (flight == flight1.getFlight() && flight1.getSeats() > 0) 
            {
                flight1.update(flight, passengerName);
            } 
            else if (flight == flight2.getFlight() && flight2.getSeats() > 0) 
            {
                flight2.update(flight, passengerName);
            } 
            else if (flight == flight3.getFlight() && flight3.getSeats() > 0) 
            {
                flight3.update(flight, passengerName);
            }
            else if (flight == flight4.getFlight() && flight4.getSeats() > 0) 
            {
                flight4.update(flight, passengerName);
            }
            else if (flight == flight5.getFlight() && flight5.getSeats() > 0) 
            {
                flight5.update(flight, passengerName);
            }
            else if (flight == flight6.getFlight() && flight6.getSeats() > 0) 
            {
                flight6.update(flight, passengerName);   
            } 
            else 
            {
                cout << "Sorry, seats not available!" << endl;
            }
            Sleep(5000);
        } 
        else if (val == 2) 
        {
            system("cls");
            Airline::DisplayReservations();
            system("pause");
        } 
        else if (val == 3) 
        {
            system("cls");
            exit = true;
            cout << "Good luck" << endl;
            Sleep(3000);
        }
    }

    return 0;
}

