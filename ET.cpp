#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

// temp variables
int t;
string temp;

// global dcl

// should have used class or struct :)
string remark;
string date;
string Time;
double amount;
string category;
int count;
string id;

int idTOcount()
{

    string tempstring;

    ifstream file("saves.csv");

    if (!file.is_open())
    {
        cout << "error" << endl;
    }

    string line, lastline;
    while (getline(file, line))
    {

        if (!line.empty())
        {

            lastline = line;
        }
    }
    if (lastline.empty())
    {
        return 0;
    }

    stringstream ss(lastline);
    string idStr;
    getline(ss, idStr, ',');
    return stoi(idStr);
}

// add expense function
int addE()
{ 

    // to store current time automaticaly

    time_t now = time(0);
    tm *localTime = localtime(&now);

    ofstream file("saves.csv", ios ::app);

    if (!file.is_open())
    {
        cout << "can't open file" << endl;
        return 1;
    }
    // running this first so it can get prev id before we enter ant values
    count = idTOcount();

    cout << "ENTER DETAILS" << endl;

    stringstream datestream, timestream;
    datestream << put_time(localTime, "%Y-%m-%d");
    timestream << put_time(localTime, "%H-%M-%S");

    date = datestream.str();
    Time = timestream.str();

    cout << "Date is set to current date: " << date << endl;

    cout << "Time is set to current local time: " << Time << endl;

    cout << "Enter category(one word)" << endl;
    cin >> category;

    cin.ignore();
    cout << "enter remark / name " << endl;
    getline(cin, remark);

    cout << "Enter Amount" << endl;
    cin >> amount;

    // to make id continious even after restarting our program

    count++;

    id = to_string(count);

    cout << "creating Id...." << endl
         << id << endl;

    file << id << "," << date << "," << Time << "," << category << "," << remark << "," << amount << endl;

    cout << " saving and exiting..." << endl;
    file.close();

    cout << "press any key to continue" << endl
         << "press 5 to exit" << endl;
    cin >> t;
    if (t == 5)
        exit(0);

    return count;
}

// view function
int viewE()
{
    ifstream file("saves.csv");

    if (!file.is_open())
    {
        cout << " file not found" << endl;
    }

    string line;

    // printing header

    cout << left
         << setw(15) << "Id"
         << setw(15) << "date"
         << setw(15) << "time"
         << setw(15) << "category"
         << setw(15) << "remark"
         << setw(15) << "amount"
         << endl;

    cout << string(85, '-') << endl;

    double total = 0.0;

    // printing table

    while (getline(file, line))
    {
        stringstream ss(line);
        string lastfield;

        while (getline(ss, temp, ','))
        {
            lastfield = temp;

            cout << left << setw(15) << temp;
        }

        try
        {
            total = total + stod(lastfield);
        }
        catch (...)
        {
            continue;
        }

        cout << endl;
    }

    cout << string(85, '-') << endl;

    cout << right << setw(75) << "Total : " << total << endl;

    file.close();

    cout << "press any key to continue" << endl
         << "press 5 to exit" << endl;
    cin >> t;
    if (t == 5)
        exit(0);

    return 0;
}

// edit / delete funtion(toughest fn for me)
int edel()
{

    ifstream file("saves.csv");

    if (!file.is_open())
    {
        cout << "file not found" << endl;
    }

    ofstream tempfile("temp.csv", ios::app);

    if (!tempfile.is_open())
    {
        cout << "Error" << endl;
    }

    string userid;
    string line;

    cout << "enter Id to edit or delete record" << endl;
    cin >> userid;

    bool found = false;

    while (getline(file, line))
    {

        stringstream ss(line);
        string amountStr;

        // storing values in their respective variables

        getline(ss, id, ',');
        getline(ss, date, ',');
        getline(ss, Time, ',');
        getline(ss, category, ',');
        getline(ss, remark, ',');
        getline(ss, amountStr, ',');

        if (id == userid)
        {
            if (!found)
            {
                amount = stod(amountStr);
                cout << string(85, '-') << endl;
                cout << left
                     << setw(15) << id
                     << setw(15) << date
                     << setw(15) << Time
                     << setw(15) << category
                     << setw(15) << remark
                     << setw(15) << amount
                     << endl;

                cout << string(85, '-') << endl;

                found = true;
            }

            cout << "To edit press :" << endl
                 << "1.category" << endl
                 << "2.remark" << endl
                 << "3.amount" << endl
                 << "4. delete" << endl;
            cin >> t;

            switch (t)
            {
            case 1:
            {
                cout << "enter to record" << endl;
                cin >> category;

                break;
            }
            case 2:
            {
                cout << "enter to record" << endl;
                cin >> remark;

                break;
            }
            case 3:
            {
                cout << "enter to record" << endl;
                cin >> amountStr;

                break;
            }
            case 4:
            {
                cout << "deleting...." << endl;
                continue;
                break;
            }

            default:
                cout << "invalid input" << endl;

                break;
            }
        }
        else
        {
            cout << "id doesn't exist\n";
        }

        tempfile << id << "," << date << "," << Time << "," << category << "," << remark << "," << amountStr << endl;
    }

    file.close();
    tempfile.close();

    remove("saves.csv");
    rename("temp.csv", "saves.csv");

    cout << "press any key to continue" << endl
         << "press 5 to exit" << endl;

    cin >> t;
    if (t == 5)
        exit(0);

    return 0;
}

// search function

int searchf()
{

    ifstream file("saves.csv");

    if (!file.is_open())
    {
        cout << "file not found" << endl;
        return 1;
    }

    string userCat;
    cout << " enter word to search" << endl;
    cin >> userCat;

    // false so we are assuming that we havent found the result it wil be wrong to assume that we already have ..
    bool found = false;

    string line; // temmp variable

    bool printed = false; // for header to print

    // reading values

    while (getline(file, line))
    {

        stringstream ss(line);

        string amountStr;

        // storing values in their respective variables

        getline(ss, id, ',');
        getline(ss, date, ',');
        getline(ss, Time, ',');
        getline(ss, category, ',');
        getline(ss, remark, ',');
        getline(ss, amountStr, ',');

        if (category == userCat)
        {
            found = true;

            amount = stod(amountStr);

            if (!printed)
            {
                // printing header

                cout << left
                     << setw(15) << "Id"
                     << setw(15) << "date"
                     << setw(15) << "time"
                     << setw(15) << "category"
                     << setw(15) << "remark"
                     << setw(15) << "amount"
                     << endl;
                printed = true;
            }

            cout << string(85, '-') << endl;
            cout << left
                 << setw(15) << id
                 << setw(15) << date
                 << setw(15) << Time
                 << setw(15) << category
                 << setw(15) << remark
                 << setw(15) << amount
                 << endl;

            cout << string(85, '-') << endl;
        }
    }

    if (!found)
    {
        cout << "Nothing or invaild word" << endl;
    }

    file.close();

    cout << "press any key to continue" << endl
         << "press 5 to exit" << endl;

    cin >> t;
    if (t == 5)
        exit(0);

    return 0;
}

// menu funtion
void menuf(int m)
{

    if (m < 5)
    {

        switch (m)
        {

        case 1:
        {
            addE();
            break;
        }

        case 2:
        {
            viewE();
            break;
        }

        case 3:
        {
            edel();
            break;
        }

        case 4:
        {
            searchf();
            break;
        }
        default:
            cout << "invalid input // Error 404" << endl;
        }
    }
}

int main()
{

    int m, i;

    // menu selector
    do
    {

        cout << "1. add expense" << "\n";
        cout << "2. view expense" << "\n";
        cout << "3. edit or delete expense" << "\n";
        cout << "4. search/filter" << "\n";
        cout << "5. exit" << "\n";

        cin >> m;

        menuf(m);

    } while (m < 5);

    return 0;
}
