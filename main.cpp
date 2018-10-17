#include <iostream>
#include <fstream>
#include <process.h>
#include <string>
#include <stdio.h>

using namespace std;

class Appointment
{
    int ID;
    int charges;
    int doc_ID;
    int pat_ID;
    int date[3];
    int time[2];

public:

    Appointment()
    {
        charges = 350;
    }

    int ID_gen();
    void del();

};

void app_chk(int[]);

class Doctor
{
    int ID;
    char name[20];
    int dob[3];                      //all dates in DD/MM/YYYY
    char specialization[20];

public:

    int ID_gen();
    void create();
    void display();
    void add_to_file();
    void del_from_file();

};

void Doctor::create()
{
    cout << "Enter name:" << endl;
    cin.getline(name, 20);

    cout << "Enter your date of birth (format: DD MM YYYY)" << endl;
    cin >> dob[0] >> dob[1] >> dob[2];

    cout << "Enter your specialization:" << endl;
    cin.getline(specialization, 20);
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

    default: exit(0);

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
                cout << i + 1 << ". "; puts(doc1.name);
                cout << "   " << "Date of Birth: " << doc1.dob[0] << "/" << doc1.dob[1] << "/" << doc1.dob[2] << endl;
                cout << "   " << "Specialization: " << puts(doc1.specialization);
                cout << "   " << "ID: " << doc1.ID << endl;

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


}

void add_doc();
void add_pat();

void doc()
{
    int s;

    cout << "1. Add Doctor" << endl;
    cout << "2. Edit Doctor info" << endl;
    cout << "3. Remove Doctor" << endl;
    cout << "0. Log out" << endl;

    switch(s)
    {
        case 1: add_doc(); break;

        case 2:  break;

        case 3: del();

        default: home_sc();
    }
}

void add_doc()
{
    ofstream fout("Doctor", ios::out|ios::app|ios::binary);

    Doctor doc1;

    doc1::create();

    fout.write((char*)&doc1, sizeof(doc1));

    fout.close();
}

void add_pat()
{
    Patient pat;

    pat::create();

    ofstream fout("Patient", ios::out|ios::app|ios::binary);

    fout.write((char*)&pat, sizeof(pat));

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

        case 2: Appointment::del(); break;

        case 3:

        default: home_sc();
    }
}

void new_app()
{
    int s;
    char name[20];
    Doctor doct;
    void func(Doctor);

    cout << "Find Doctor by:" << endl;
    cout << "1. Name" << endl;
    cout << "2. Specialization" << endl;
    cout << "0. Back" << endl;

    cin >> s;

    switch(s)
    {
        case 1: cin.getline(name, 20);
                doct = sd(0, name);
                func(doct);
                break;

        case 2: cin.getline(name, 20);
                doct = sd(1, name);
                func(doct);
                break;

        default: patient();

    }

    void func(Doctor doct)
    {
        ofstream fout("Appointment", ios::out|ios::app|ios::binary);

        int date[3];

        cout << "Enter your preferred appointment date: ";
        cin >> date[0] >> date[1] >> date[2];



    }


}


