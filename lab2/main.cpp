#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;
typedef void(*func)();

enum { PARL = 0b0001, PRES = 0b0010, MONCH = 0b0100, RESPUB = 0b1000 };

struct State {
    string name;
    string capital;
    unsigned int population;
    unsigned int area;
    union {
        struct {
            unsigned parlament : 1;
            unsigned president : 1;
            unsigned monarch : 1;
            unsigned respublic : 1;
        };
        unsigned form;
    } stateForm;
};

void showState(State s) {
    cout << s.name << " площадью " << s.area << " и населением " << s.population <<
        " имеет столицу " << s.capital << ". По форме правления имеет ";
    if ((s.stateForm.form & (PARL | MONCH)) == (PARL | MONCH))
        cout << "парламентскую монархию";
    if ((s.stateForm.form & (PARL | RESPUB)) == (PARL | RESPUB))
        cout << "парламентскую республику";
    if ((s.stateForm.form & (PRES | MONCH)) == (PRES | MONCH))
        cout << "президентскую монархию";
    if ((s.stateForm.form & (PRES | RESPUB)) == (PRES | RESPUB))
        cout << "президентскую республику";
    cout << endl;
}
void addState(vector<State>& states) {
    State newState;
    setlocale(LC_CTYPE, "Rus");
    cout << "Введите название страны: ";
    cin >> ws;
    setlocale(LC_CTYPE, "C");
    getline(cin, newState.name);
    setlocale(LC_CTYPE, "Rus");
    cout << "Введите название столицы: ";
    cin >> ws;
    setlocale(LC_CTYPE, "C");
    getline(cin, newState.capital);
    setlocale(LC_CTYPE, "Rus");
    cout << "Введите численность населения: ";
    cin >> newState.population;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cin >> newState.population;
    }
    cout << "Введите площадь страны: ";
    cin >> newState.area;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cin >> newState.area;
    }
    cout << "Форма правления (монархия или республика, 0 или 1 соответственно)?: ";
    bool buff;
    cin >> ws;
    cin >> buff;
    if (buff)
        newState.stateForm.form = RESPUB;
    else
        newState.stateForm.form = MONCH;
    cout << "Парламентская или президентская (0 или 1 соответственно): ";
    cin >> buff;
    if (buff)
        newState.stateForm.form |= PRES;
    else
        newState.stateForm.form |= PARL;

    states.emplace_back(newState);
    showState(states.back());
}
void chooseState(vector<State>& states) {
    int searchArea; vector<State> findedStates;
    cout << "Введите искомую площадь: ";
    cin >> searchArea;
    copy_if(states.begin(), states.end(), back_inserter(findedStates), [&](State s) { return s.area >= searchArea; });
    if (!findedStates.empty()) {
        cout << "\nНайденные страны:\n";
        for (int i = 0; i < findedStates.size(); i++) {
            showState(findedStates[i]);
            cout << endl;
        }
    }
    else cout << "Не найдено совпадений\n";
}
void showAllStates(vector<State>& states) {
    if (states.empty()) {
        cout << "Пока что стран нет\n";
        return;
    }

    for (int i = 0; i < states.size(); i++) {
        cout << i + 1 << ". ";
        showState(states[i]);
        cout << endl;
    }
}
void deleteState(vector<State>& states) {
    string searchForDelete;
    cout << "Введите страну на бомбардировку: ";
    cin >> searchForDelete;
    auto it = find_if(states.begin(), states.end(),
        [&](const State& s) { return s.name == searchForDelete; });

    if (it != states.end()) {
        states.erase(it);
        cout << "Страны больше нет :)\n";
    }
    else {
        cout << "Страна на удаление не найдена\n";
    }
}

void mainTask1() {
    int enter = 0;
    vector<void(*)(vector<State>&)> choice = { addState, chooseState, showAllStates, deleteState };
    vector<State> states;

    while (true) {
        cout << "1. Добавить страну\n2. Выбор по занимаемой площади" << endl <<
            "3. Показать все страны" << endl <<
            "4. Удалить страну\nВыбрать действие: ";
        cin >> enter;
        if (enter == 0) break;
        if (enter > choice.size()) {
            cout << "Неверный ввод! Попробуйте ещё раз\n";
            continue;
        }
        system("cls");
        choice[enter - 1](states);
        system("pause");
        system("cls");
    }
}

struct Citizen {
    string fio;
    string birthday;
    string adress;
    bool sex;
};
void showCitizen(Citizen c) {
    if(!c.sex)
    cout << "Гражданка " << c.fio << ", родилась " << c.birthday << " проживающая по адресу: " <<
        c.adress << ".";
    else cout << "Гражданин " << c.fio << ", родился " << c.birthday << " проживающий по адресу: " <<
        c.adress << ".";
}
void addCitizen(vector<Citizen>& citizens) {
    Citizen newCitizen;
    setlocale(LC_CTYPE, "Rus");
    cout << "ФИО: ";
    cin >> ws;
    setlocale(LC_CTYPE, "C");
    getline(cin, newCitizen.fio);
    setlocale(LC_CTYPE, "Rus");
    cout << "Дата рождения: ";
    cin >> ws;
    setlocale(LC_CTYPE, "C");
    getline(cin, newCitizen.birthday);
    setlocale(LC_CTYPE, "Rus");
    cout << "Адресс проживания: ";
    cin >> ws;
    setlocale(LC_CTYPE, "C");
    getline(cin, newCitizen.adress);
    setlocale(LC_CTYPE, "Rus");
    cout << "Введите пол гражданина (женский/мужской, 0 или 1 соответственно): ";
    cin >> newCitizen.sex;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cin >> newCitizen.sex;
    }
    citizens.push_back(newCitizen);
    showCitizen(citizens.back());
}
void chooseCitizen(vector<Citizen>& c) {
    int searchYear;
    vector<Citizen> findedCitizens;
    cout << "Введите год рождения: ";
    cin >> searchYear;
    copy_if(c.begin(), c.end(), back_inserter(findedCitizens), [&](Citizen c) {
        return stoi(c.birthday.substr(6)) == searchYear;
    });
    if (!findedCitizens.empty()) {
        cout << "\nНайденные горожанины:\n";
        for (int i = 0; i < findedCitizens.size(); i++) {
            showCitizen(findedCitizens[i]);
            cout << endl;
        }
    }
    else cout << "Не найдено совпадений\n";
}
void showAllCitizens(vector<Citizen>& c) {
    if (c.empty()) {
        cout << "Пока что горожан нет\n";
        return;
    }

    for (int i = 0; i < c.size(); i++) {
        cout << i + 1 << ". ";
        showCitizen(c[i]);
        cout << endl;
    }
}

void mainTask2() {
    int enter = 0;
    vector<void(*)(vector<Citizen>&)> choice = { addCitizen, chooseCitizen, showAllCitizens };
    vector<Citizen> citizens;

    while (true) {
        cout << "1. Добавить горожанина\n2. Выбор по году рождения" << endl <<
            "3. Показать всех горожан" << endl <<
            "Выбрать действие: ";
        cin >> enter;
        if (enter == 0) break;
        if (enter > choice.size()) {
            cout << "Неверный ввод! Попробуйте ещё раз\n";
            continue;
        }
        system("cls");
        choice[enter - 1](citizens);
        system("pause");
        system("cls");
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<func> choice{
        mainTask1,
        mainTask2
    };
    int enter = 0;

    while (true) {
        setlocale(LC_ALL, "Rus");
        cout << "Доступные задания: ";
        for (int i = 0; i < choice.size(); i++) cout << i + 1 << " ";
        cout << endl;
        cin >> enter;
        while (cin.fail()) {
            cin.clear();
            cin.ignore();
            cin >> enter;
        }
        if (enter == 0) break;
        if (enter > choice.size()) {
            cout << "Неверный ввод! Попробуйте ещё раз\n";
            continue;
        }
        system("cls");
        choice[enter - 1]();
        system("pause");
        system("cls");
    }

    return 0;
}
