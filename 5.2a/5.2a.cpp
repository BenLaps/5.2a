#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

enum Speciality { COMPUTER_SCIENCE, IT, APPLIED_MATHS };
string specialityStr[] = { "Комп'ютерні науки", "Інфор. технології", "Прикл. математика" };


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
        cerr << "Помилка з відкриттям файлу '" << fname << "'" << endl;
        return;
    }
    Student st;
    char ch;
    do
    {
        cout << endl;
        cout << "Прізвище: "; cin.sync();
        cin >> st.surname;
        cout << "Курс: "; cin >> st.course;
        cout << "Спецiальнiсть (0 - Комп'ютерні науки, 1 - Інформаційні технології, 2 - Прикладна математика): ";
        cin >> sp;
        st.speciality = static_cast<Speciality>(sp);
        cout << "Оцiнка з фiзики: "; cin >> st.physics;
        cout << "Оцiнка з математики: "; cin >> st.maths;
        cout << "Оцінка з інформатики: "; cin >> st.it;
        if (!f.write((char*)&st, sizeof(Student)))
        {
            cerr << "Помилка відкриття файлу." << endl;
        }
        cout << "Продовжити? (Y/n) "; cin >> ch;
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

    cout << "Середній бал з фізики: " << markPhys / i << endl;
    cout << "Середній бал з математики: " << markMaths / i << endl;
    cout << "Середній бал з інформатики: " << markIT / i << endl;
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
        cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
        return;
    }

    cout << "========================================================================================="
        << endl;
    cout << "| № |    Прiзвище   | Курс |  Спецiальнiсть   | Фiзика | Математика | Інформатика |"
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
        cout << "Вибрати:" << endl;
        cout << "[1] - ввести дані;" << endl;
        cout << "[2] - вивести дані;" << endl;
        cout << "[3] - вивід кількості оцінок 4 або 5 з фізики;" << endl;
        cout << "[4] - вивід середнього балу з кожного предмету;" << endl;
        cout << "[0] - вийти." << endl << endl;
        cout << "Ваш вибір: "; cin >> ch;
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "Введіть назву файла: "; cin.getline(fname, sizeof(fname));
            enter_save(fname);
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "Введіть назву файла: "; cin.getline(fname, sizeof(fname));
            load_print(fname);
            break;
        case '3':
            cout << endl;
            cout << "Введіть назву файла: "; cin >> fname;
            cout << "Кількість студентів, які отримали з фізики “5” або “4”: " << PhysicsFiveOrFour(fname) << endl;
            break;
        case '4':
            cout << endl;
            cout << "Введіть назву файла: "; cin >> fname;
            ArithmeticMean(fname);
            break;
        default:
            cout << "Помилка! ";
        }
    } while (ch != '0');
    return 0;
}