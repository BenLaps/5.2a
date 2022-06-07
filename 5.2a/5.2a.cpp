#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

enum Speciality { COMPUTER_SCIENCE, IT, APPLIED_MATHS };
string specialityStr[] = { "����'����� �����", "�����. �������㳿", "�����. ����������" };


struct Student
{
    char surname[100];
    int course;
    Speciality speciality;
    int physics;
    int maths;
    int it;
};

void enter_save(char* fname)
{
    int sp;
    ofstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "������� � ��������� ����� '" << fname << "'" << endl;
        return;
    }
    Student st;
    char ch;
    do
    {
        cout << endl;
        cout << "�������: "; cin.sync();
        cin >> st.surname;
        cout << "����: "; cin >> st.course;
        cout << "����i����i��� (0 - ����'����� �����, 1 - ����������� �������㳿, 2 - ��������� ����������): ";
        cin >> sp;
        st.speciality = static_cast<Speciality>(sp);
        cout << "��i��� � �i����: "; cin >> st.physics;
        cout << "��i��� � ����������: "; cin >> st.maths;
        cout << "������ � �����������: "; cin >> st.it;
        if (!f.write((char*)&st, sizeof(Student)))
        {
            cerr << "������� �������� �����." << endl;
        }
        cout << "����������? (Y/n) "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');

}

void ArithmeticMean(char* fname)
{
    ifstream f(fname, ios::binary & ios::beg);

    float markPhys = 0, markMaths = 0, markIT = 0;
    int i = 0;
    Student st;
    while (f.read((char*)&st, sizeof(Student)))
    {
        markPhys += st.physics;
        markMaths += st.maths;
        markIT += st.it;
        i++;
    }

    cout << "������� ��� � ������: " << markPhys / i << endl;
    cout << "������� ��� � ����������: " << markMaths / i << endl;
    cout << "������� ��� � �����������: " << markIT / i << endl;
}

int PhysicsFiveOrFour(char* fname)
{
    ifstream f(fname, ios::binary & ios::beg);

    int i = 0;
    Student st;
    while (f.read((char*)&st, sizeof(Student)))
    {
        if (st.physics == 5 || st.physics == 4)
            i++;
    }
    return i;
}

void load_print(char* fname)
{
    int i = 0;
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "������� �������� ����� '" << fname << "'" << endl;
        return;
    }

    cout << "========================================================================================="
        << endl;
    cout << "| � |    ��i�����   | ���� |  ����i����i���   | �i���� | ���������� | ����������� |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------"
        << endl;

    Student st;
    while (f.read((char*)&st, sizeof(Student)))
    {
        cout << "| " << setw(2) << right << i + 1 << "";
        cout << "| " << setw(14) << left << st.surname
            << "| " << setw(5) << right << st.course
            << "| " << setw(23) << left << specialityStr[st.speciality]
            << "| " << setw(7) << st.physics
            << "| " << setw(11) << left << st.maths
            << "| " << setw(12) << left << st.it << "| " << endl;
        ++i;
    }
    cout << "-----------------------------------------------------------------------------------------"
        << endl;
}

int main()
{
    char fname[100];
    char ch;
    do
    {
        cout << endl;
        cout << "�������:" << endl;
        cout << "[1] - ������ ���;" << endl;
        cout << "[2] - ������� ���;" << endl;
        cout << "[3] - ���� ������� ������ 4 ��� 5 � ������;" << endl;
        cout << "[4] - ���� ���������� ���� � ������� ��������;" << endl;
        cout << "[0] - �����." << endl << endl;
        cout << "��� ����: "; cin >> ch;
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "������ ����� �����: "; cin.getline(fname, sizeof(fname));
            enter_save(fname);
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "������ ����� �����: "; cin.getline(fname, sizeof(fname));
            load_print(fname);
            break;
        case '3':
            cout << endl;
            cout << "������ ����� �����: "; cin >> fname;
            cout << "ʳ������ ��������, �� �������� � ������ �5� ��� �4�: " << PhysicsFiveOrFour(fname) << endl;
            break;
        case '4':
            cout << endl;
            cout << "������ ����� �����: "; cin >> fname;
            ArithmeticMean(fname);
            break;
        default:
            cout << "�������! ";
        }
    } while (ch != '0');
    return 0;
}