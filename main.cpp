#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

class Appointment
{
  public:
    int charges;
    int date[3];
    int time[2];



    Appointment()
    {
        charges = 350;
    }

    int doc_ID;
    int pat_ID;
    void add_to_file();
    void del();

};

void Appointment::add_to_file()
{

}

class Doctor
{

    int dob[3];                      //all dates in DD/MM/YYYY
    char specialization[20];

public:

    char name[20];

    int ret_ID()
    {
        return ID;
    }

    int ID;
    int ID_gen();
    void create();
    void display();
    void del_from_file();

};

void Doctor::create()
{
    cout << "Enter name:" << endl;
    gets(name);

    cout << "Enter your date of birth (format: DD MM YYYY)" << endl;
    cin >> dob[0] >> dob[1] >> dob[2];

    cout << "Enter your specialization:" << endl;
    gets(specialization);
}

void Doctor::display()
{
     puts(name);
     cout << "   " << "Date of Birth: " << dob[0] << "/" << dob[1] << "/" << dob[2] << endl;
     cout << "   " << "Specialization: " << puts(specialization);
     cout << "   " << "ID: " << ID << endl;
}

class Patient
{
    int ID;
    char name[20];
    char address[30];
    int dob[3];
    //int admission_date[3];
    //int release_date[3];
    int no_of_days;
    int Room_no;

public:
    Patient()
    {
       // admission_date = release_date = 0;
        no_of_days = 0;                   //for patients only for consultation
        Room_no = 0;
    }

    int accomodation_charges()
    {
        return no_of_days*500;
    }

    int ret_ID()
    {
        return ID;
    }
    int ID_gen();
    void create();

};


void Patient::create()
{
    cout << "Enter your name: ";
    cin.getline(name, 20);

    cout << "Enter your Date of Birth: ";
    cin >> dob[0] >> dob[1] >> dob[2];

    cout << "Enter your home address: ";
    cin.getline(address, 30);
}

void home_sc();
void doc();
void patient();
Doctor sd(int, char[]);

int main()
{
    cout << "----------WELCOME----------" << "\n" << endl;

    home_sc();

    return 0;
}

void home_sc()
{
    int s;

    cout << "Log in as:" << endl;
    cout << "1. Doctor" << endl;
    cout << "2. Patient" << endl;
    cout << "0. Exit." << endl;

    cin >> s;

    switch(s)
    {
    case 1: doc(); break;

    case 2: patient(); break;

    default: break;

    }

}

Doctor sd(int p, char name[20])
{
    ifstream fin("Doctor", ios::in|ios::binary);

    Doctor doc1;
    int A[10];
    int i = 0;

    if(p == 0)
    {
        fin.seekg(0, ios::beg);
        while(!fin.eof())
        {
            fin.read((char*)&doc1, sizeof(doc1));

            if(!strcmp(doc1.name, name))
            {
                cout << i + 1 << ". ";
                doc1.display();

                A[i] = fin.tellg();

                cout << endl;
            }

        }

        cout << "Enter your preference: ";
        cin >> i;

        fin.seekg(A[i-1]);

        fin.read((char*)&doc1, sizeof(doc1));

        return doc1;
    }

    else if(p == 1)
    {

    }

    fin.close();
}

void add_doc();

void doc()
{
    int s;

    cout << "1. Add Doctor" << endl;
    cout << "2. Edit Doctor info" << endl;
    cout << "3. Remove Doctor" << endl;
    cout << "0. Log out" << endl;

    cin >> s;

    switch(s)
    {
        case 1: add_doc(); break;

        case 2: break;

        case 3:  break;

        default: home_sc(); break;
    }

    home_sc();
}

void add_doc()
{
    ofstream fout("Doctor", ios::out|ios::app|ios::binary);

    Doctor doc1;

    doc1.create();

    fout.write((char*)&doc1, sizeof(doc1));

    fout.close();
}

void new_app();

void patient()
{
    int s;

    cout << "1. Book an appointment" << endl;
    cout << "2. Cancel an existing appointment" << endl;
    cout << "3. Pay bills and leave" << endl;
    cout << "0. Log out" << endl;

    switch(s)
    {
        case 1: new_app(); break;

        case 2:

        case 3:

        default: home_sc();
    }
}

int check_app(int[], int[], int);

void create_app_pat(Doctor);

void new_app()
{
    int s;
    char name[20];
    Doctor doct;

    cout << "Find Doctor by:" << endl;
    cout << "1. Name" << endl;
    cout << "2. Specialization" << endl;
    cout << "0. Back" << endl;

    cin >> s;

    switch(s)
    {
        case 1: cin.getline(name, 20);
                doct = sd(0, name);
                create_app_pat(doct);
                break;

        case 2: cin.getline(name, 20);
                doct = sd(1, name);
                create_app_pat(doct);
                break;

        default: patient();

    }

}
    void create_app_pat(Doctor doct)
    {
        int date[3];
        int time[2];

        int i = 1;

        while(i)
        {
            cout << "Enter your preferred appointment date: ";
            cin >> date[0] >> date[1] >> date[2];

            cout << "Enter your preferred appointment time: ";
            cin >> time[0] >> time[1];

            i = check_app(date, time, doct.ID);

            if(i)
            cout << "Appointment already exists, Please enter a different date and time" << endl;

        }

        Patient pat;

        pat.create();

        ofstream fout1("Patient", ios::out | ios::app | ios::binary);

        fout1.write((char*)&pat, sizeof(pat));

        fout1.close();

        Appointment app;

        app.doc_ID = doct.ID;
        app.pat_ID = pat.ret_ID();

        ofstream fout2("Appointment", ios::out | ios::app | ios::binary);

        fout2.write((char*)&app, sizeof(app));

        fout2.close();

    }




int check_app(int date[3], int time[2], int ID)
{
    ifstream fin("Appointment", ios::in|ios::binary);

    fin.seekg(0);

    Appointment app1;

    int flag = 0;

    while(!fin.eof())
    {
        fin.read((char*)&app1, sizeof(app1));

        if(app1.doc_ID == ID && app1.date == date && app1.time == time)
        {
            flag = 1;
            break;
        }
    }

    fin.close();

    if(flag = 1)
        return 1;
    else
        return 0;

}

