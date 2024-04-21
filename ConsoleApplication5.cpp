#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <format>
using namespace std;

string ConsertList[4] {"Егор крид", "Группа ленинград", "3 дня дождя", "Рамштайн"};

class User {
public:

	User(string login, string password, char c);
	void setLogin(string u);
	void setPassword(string p);
	void setAdmin(char c);

	string getLogin();
	string getPassword();
	void setSustain(bool s);
	bool checkIsLoggined();
	bool isAdmin();

private:

	string login;
	string password;
	bool is_loggined; 
	bool admin_rule;
};
User::User(string l, string p, char c) {
	setLogin(l);
	setPassword(p);
	setAdmin(c);

	is_loggined = false;
}
void User::setLogin(string u) {
	login = u;
}
void User::setPassword(string p) {
	password = p;
}
void User::setAdmin(char c) {
	if (c=='1') {admin_rule = 1; return; }
}
string User::getLogin(){
	return login;
}
string User::getPassword() {
	return password;
}
bool User::checkIsLoggined() {
	return is_loggined;
}
void User::setSustain(bool s) {
	is_loggined = s;
}
bool User::isAdmin() {
	return admin_rule;
}


class Terminal {
protected:
	void addUser(string l_and_p, string path);
	bool checkData(string l_and_p, string direct_path = "..\\ConsoleApplication5\\UsersInfo\\User_data.txt");
	map<string, string> Links {
		{"Егор крид", "..\\ConsoleApplication5\\Conserts\\EgorKrid.txt"} ,
		{"Группа ленинград", "..\\ConsoleApplication5\\Conserts\\Leningrad.txt"} ,
		{"3 дня дождя", "..\\ConsoleApplication5\\Conserts\\3DayRain.txt"} ,
		{"Рамштайн", "..\\ConsoleApplication5\\Conserts\\Ramshtain.txt"}
	};
};
void Terminal::addUser(string l_and_p, string direct_path) {
	ofstream out;
	out.open(direct_path, ios::app);
	if (out.is_open()) out << l_and_p;

}
bool Terminal::checkData(string l_and_p, string direct_path) {

	ifstream in;
	string to_read;
	in.open(direct_path, ios::app);

	if (in.is_open()) {

		try
		{
			while (std::getline(in, to_read)) {
				if (to_read == l_and_p) return 1;
			}
		}

		catch (const std::exception&)
		{
			cout << "Проблемы при чтении файла" << endl;
		}

	}
	else {
		cout << "Проблема при открытии файла. Проверьте путь к файлу или его наличие.";
	}
	return 0;
}


class usersManager : public Terminal {
public:
	bool Authorization(string lp, char c);
	void DeleteAccount(string lp);
	void LogOut();
};
bool usersManager::Authorization(string lp, char c) {
	switch (c)
	{
	case '1':

		if (!checkData(lp, "..\\ConsoleApplication5\\UsersInfo\\User_data.txt")) {
			addUser(lp, "..\\ConsoleApplication5\\UsersInfo\\User_data.txt");
			return 1;
			}
		cout << "Такой пользователь уже существует" << endl;
		break;
	default:

		if (checkData(lp)) return 1;
		cout << "Такого пользователя не существует" << endl;
		break;
	}
	return 0;
}
void usersManager::DeleteAccount(string lp) {
	rename("..\\ConsoleApplication5\\UsersInfo\\User_data.txt", "..\\ConsoleApplication5\\UsersInfo\\Old_data.txt");

	ofstream out;
	out.open("..\\ConsoleApplication5\\UsersInfo\\User_data.txt");
	cout << out.is_open();

	ifstream fst;
	fst.open("..\\ConsoleApplication5\\UsersInfo\\Old_data.txt");
	cout << fst.is_open();
	string to_read;
	while (getline(fst, to_read)) {
		if (to_read != lp) { out << to_read; out << '\n'; }
	}
	remove("..\\ConsoleApplication5\\UsersInfo\\Old_data.txt");
}
void LogOut(User user) {
	user.setSustain(false);
}


class ticketsManager : public Terminal {
public:
	void IssueTicket(User user, string path);
	void VerifyTickets(User user);
	void DencelOne(User user, const char* path1, const char* path2);
};
void ticketsManager::IssueTicket(User user, string path) {
	if (!checkData(user.getLogin() + user.getPassword(), path)) { addUser(user.getLogin() + user.getPassword(), path); return;}
	cout << "У вас уже имеется билет на этот концерт" << endl;
	
	
}
void ticketsManager::VerifyTickets(User user) {
	for (string s : ConsertList) {
		if (checkData(user.getLogin() + user.getPassword(), Links[s])) cout << s;
	}
	
}
void ticketsManager::DencelOne(User user, const char* path1, const char* path2) {


	rename(path1, path2);

	ofstream out;
	out.open(path1);
	cout << out.is_open();

	ifstream fst;
	fst.open(path2);
	cout << fst.is_open();
	cout << path1 << endl << path2 << endl;
	string to_read;
	while (getline(fst, to_read)) {
		if (to_read != user.getLogin() + user.getPassword()) { out << to_read; out << '\n'; }
	}
	remove(path2);
}

class user_func {
public:
	user_func() {
		cout << "Выберите действие: \n " <<
		"1. Приобрести билет на концерт" <<
		"2. Узнать активные билеты" <<
		"3. Совершить возврат билета" <<
		"4. Совершить возврат всех билетов" <<
		"5. Выйти из аккаунта" <<
		"6. Удалить аккаунт";
	}
private:
	void BuyTicket();
	void CheckTickets();
	void CancelOneTicket();
	void DeleteMyAccaount();
	void LeaveAccaount();
};


class admin_func {
public:
	admin_func(User user) {
		if (user.isAdmin()) {
			cout << "Выберите действие: \n " <<
				"1. Удалить пользователя из файла" <<
				"2. Добавить своего пользователя" <<
				"3. Изменить лоигн-пароль юзера" <<
				"4. Добавить концерт" <<
				"5. Удалить концерт" <<
				"6. Выйти с позиции администратора";
		}
	}
private:
	
};




int main() {
	char c = '1';
	string login = "qwe", password="werwe";

	usersManager UsersManager;
	ticketsManager TicketsManager;
	User user("", "", 'n');
	setlocale(LC_ALL, "ru");

	cout << "Приветствуем в приложении бронирования билетов. \n ";

	while (!user.checkIsLoggined()) {
		cout << "Выберите: 1 - регистрация. Любой другой символ - вход(Ввести цифру) \n";
	
		cout << "Введите имя пользователя: \n";

		cout << "Введите пароль: \n";

		user.setSustain(UsersManager.Authorization(login + password, c));
	}
	user.setLogin(login);
	user.setPassword(password);
	user.setAdmin(c);

}