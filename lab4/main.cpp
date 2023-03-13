#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void z1() {
	ifstream fin("FILE1.txt");
	if (!fin) {
		cout << "Не удалось открыть файл!";
		return;
	}
	string word, str;
	fin >> word;
	word.insert(0, " ");
	word.push_back(' ');
	cout << "Слово для поиска" << word;
	ofstream fout("FILE2.txt");
	while (!fin.eof()) {
		getline(fin, str);
		if (str.find(word) == string::npos)
			fout << str << endl;
	}
}
void z2() {
	string str;
	cin >> ws;
	getline(cin, str);
	ofstream fout("z2.txt");
	fout << str;
	fout.close();
	ifstream fin("z2.txt");
	while (!fin.eof()) {
		fin >> str;
		if (str.find("p") != string::npos)
			cout << str << endl;
	}
}

int main() {
	vector<void(*)()> choice = { z1, z2 };
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
		cout << endl;
		system("pause");
		system("cls");
	}

	return 0;
}