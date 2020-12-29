
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>

#include <algorithm>
using namespace std;


enum StudentSpec : unsigned short
{
	StudentSpec_ComputerScience = 0, 
	StudentSpec_Informatics, 
	StudentSpec_MathematicsEconomics, 
	StudentSpec_Fiz_Inf, 
	StudentSpec_Trud 
};

struct Student {
	char lastname[120]; 
	unsigned short course; 
	StudentSpec spec; 

	unsigned short mark_physics; 
	unsigned short mark_math; 
	union
	{
		unsigned short programming; 
		unsigned short numerical_methods; 
		unsigned short pedagogy; 
	};
};

void writeStudent(fstream& f, const int& index, const Student& st) 
{
	f.clear();
	f.seekp(index * sizeof(Student));
	f.write((char*)&st, sizeof(Student));
}

void readStudent(fstream& f, const int& index, Student &st) {
	f.clear();
	f.seekg(index * sizeof(Student));
	f.read((char*)&st, sizeof(Student));
}

void swapStudents(fstream& f, const int& i1, const int& i2) {
	Student st1, st2;
	readStudent(f, i1, st1);
	readStudent(f, i2, st2);
	writeStudent(f, i1, st2);
	writeStudent(f, i2, st1);
}

void studentFactory(fstream &f, const int& count) {
	int prof;
	Student tmp;
	for (int i = 0; i < count; i++)
	{
		cin.ignore(INT_MAX, '\n');
		cout << "Студент № " << i + 1 << ":" << endl;
		cout << "прізвище: ";
		cin.getline(tmp.lastname, 119);
		cout << "курс  : ";
		do
		{
			if (cin.fail()) {
				cin.clear(); 
				cin.ignore(INT_MAX, '\n'); 
			}
			cin >> tmp.course;
		} while (cin.fail() || tmp.course <= 0 || tmp.course > 6);
		cout << "Спеціальності:\n0 - Комп'ютерні науки\n1 - Інформатика\n2 - Математика та економіка \n3 - Фізика та інформатика\n4 - Трудове навчання\n";
		do
		{
			if (cin.fail()) {
				cin.clear(); 
				cin.ignore(INT_MAX, '\n'); 
			}
			cin >> (unsigned short &)tmp.spec;
		} while (cin.fail() || tmp.spec < 0 || tmp.spec > 4);
		switch (tmp.spec)
		{
		case StudentSpec_ComputerScience:
			cout << "Оцінка з програмування: ";
			break;
		case StudentSpec_Informatics:
			cout << "Оцінка з чисельних методів: ";
			break;
		case StudentSpec_MathematicsEconomics:
		case StudentSpec_Fiz_Inf:
		case StudentSpec_Trud:
			cout << "Оцінка з педагогіки: ";
		}
		do
		{
			if (cin.fail()) {
				cin.clear(); 
				cin.ignore(INT_MAX, '\n'); 
			}
			cin >> tmp.programming;
		} while (cin.fail() || tmp.programming < 0 || tmp.programming > 5);
		cout << "Оцінка з фізики : ";
		do
		{
			if (cin.fail()) {
				cin.clear(); 
				cin.ignore(INT_MAX, '\n'); 
			}
			cin >> tmp.mark_physics;
		} while (cin.fail() || tmp.mark_physics < 0 || tmp.mark_physics > 5);
		cout << "Оцінка з математики: ";
		do
		{
			if (cin.fail()) {
				cin.clear(); 
				cin.ignore(INT_MAX, '\n');
			}
			cin >> tmp.mark_math;
		} while (cin.fail() || tmp.mark_math < 0 || tmp.mark_math > 5);
		f.write((char*)&tmp, sizeof(Student));
	}
}

void drawStudents(fstream &f)
{
	cout << "===================================================================================================================" << endl;
	cout << "| № | Прізвище | Курс | Спеціальність          | Фізика | Математика | Програмування | Чисельні методи |Педагогіка|" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	Student tmp;	
	int i = 0;
	f.clear();
	f.seekg(0);
	while (!f.eof()) {
		f.read((char*)&tmp, sizeof(Student));
		if (f.eof())
			break;
		cout << "| " << setw(2) << ++i
			<< "| " << setw(9) << tmp.lastname
			<< "| " << setw(5) << tmp.course;

		switch (tmp.spec)
		{
		case StudentSpec_ComputerScience:
			cout << "| " << setw(23) << "Комп'ютерні науки";
			break;
		case StudentSpec_Informatics:
			cout << "| " << setw(23) << "Інформатика";
			break;
		case StudentSpec_MathematicsEconomics:
			cout << "| " << setw(23) << "Математика й економіка";
			break;
		case StudentSpec_Fiz_Inf:
			cout << "| " << setw(23) << "Фізика та інформатика";
			break;
		case StudentSpec_Trud:
			cout << "| " << setw(23) << "Трудове навчання";
			break;
		}
		cout << "| " << setw(7) << tmp.mark_physics
			<< "| " << setw(11) << tmp.mark_math;

		switch (tmp.spec)
		{
		case StudentSpec_ComputerScience:
			cout << "| " << setw(14) << tmp.programming
				<< "| " << setw(16) << " "
				<< "| " << setw(8) << " ";
				cout << " | ";
			break;
		case StudentSpec_Informatics:
			cout << "| " << setw(14) << " "
				<< "| " << setw(16) << tmp.programming
				<< "| " << setw(8) << " ";
			cout << " | ";
			break;
		case StudentSpec_MathematicsEconomics:
		case StudentSpec_Fiz_Inf:
		case StudentSpec_Trud:
			cout << "| " << setw(14) << " "
				<< "| " << setw(16) << " "
				<< "| " << setw(8) << tmp.programming;
			cout << " | ";
		}
		cout << endl;
	}
	cout << "===================================================================================================================" << endl;
}

void indexed_sort(fstream &sourse, fstream &out)
{
	Student tmp[2];
	int i_tmp[2];
	out.clear();
	sourse.clear();
	out.seekp(0);
	sourse.seekg(0);
	int size = 0;
	while (!sourse.eof()) {
		sourse.read((char*)&tmp[0], sizeof(Student));
		if (sourse.eof())
			break;
		out.write((char*)&size, sizeof(int));
		size++;
	}
	sourse.clear();
	sourse.seekg(0);
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i; j < size - i - 1; ++j)
		{
			out.seekg(j * sizeof(int));
			out.read((char*)&i_tmp[0], sizeof(int));
			readStudent(sourse, i_tmp[0], tmp[0]);

			out.seekg((j+1) * sizeof(int));
			out.read((char*)&i_tmp[1], sizeof(int));
			readStudent(sourse, i_tmp[1], tmp[1]);

			int avarage1 = (tmp[0].mark_math + tmp[0].mark_physics + tmp[0].programming) / 3;
			int avarage2 = (tmp[1].mark_math + tmp[1].mark_physics + tmp[1].programming) / 3;
			if (avarage1 > avarage2 ||
				(avarage1 == avarage2 && tmp[0].spec > tmp[1].spec) ||
				(avarage1 == avarage2 && tmp[0].spec == tmp[1].spec && string(tmp[0].lastname) > string(tmp[1].lastname)))
			{
				out.seekp(j * sizeof(int));
				out.write((char*)&i_tmp[1], sizeof(int));
				out.seekp((j+1) * sizeof(int));
				out.write((char*)&i_tmp[0], sizeof(int));
			}
		}
	}
}

void sort_students(fstream& f)
{
	Student tmp[2];
	f.clear();
	f.seekg(0, ios::end);
	int size = f.tellg()/sizeof(Student);
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = i; j < size - i - 1; ++j)
		{
			readStudent(f, j, tmp[0]);
			readStudent(f, j+1, tmp[1]);

			int avarage1 = (tmp[0].mark_math + tmp[0].mark_physics + tmp[0].programming) / 3;
			int avarage2 = (tmp[1].mark_math + tmp[1].mark_physics + tmp[1].programming) / 3;
			if (avarage1 > avarage2 ||
				(avarage1 == avarage2 && tmp[0].spec > tmp[1].spec) ||
				(avarage1 == avarage2 && tmp[0].spec == tmp[1].spec && string(tmp[0].lastname) < string(tmp[1].lastname)))
				swapStudents(f, j, j + 1);
		}
	}
}

void print_indexed_sort(fstream& f, fstream& indexed)
{
	cout << "===================================================================================================================" << endl;
	cout << "| № | Прізвище | Курс | Спеціальність          | Фізика | Математика | Програмування | Чисельні методи |Педагогіка|" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	Student tmp;
	int tmp_i = 0;
	indexed.clear();
	indexed.seekg(0);
	while (!indexed.eof()) {
		indexed.read((char*)&tmp_i, sizeof(int));
		if (indexed.eof())
			break;
		readStudent(f, tmp_i, tmp);
		cout << "| " << setw(2) << tmp_i
			<< "| " << setw(9) << tmp.lastname
			<< "| " << setw(5) << tmp.course;

		switch (tmp.spec)
		{
		case StudentSpec_ComputerScience:
			cout << "| " << setw(23) << "Комп'ютерні науки";
			break;
		case StudentSpec_Informatics:
			cout << "| " << setw(23) << "Інформатика";
			break;
		case StudentSpec_MathematicsEconomics:
			cout << "| " << setw(23) << "Математика та економіка";
			break;
		case StudentSpec_Fiz_Inf:
			cout << "| " << setw(23) << "Фізика та інформатика";
			break;
		case StudentSpec_Trud:
			cout << "| " << setw(23) << "Трудове навчання";
			break;
		}
		cout << "| " << setw(7) << tmp.mark_physics
			<< "| " << setw(11) << tmp.mark_math;

		switch (tmp.spec)
		{
		case StudentSpec_ComputerScience:
			cout << "| " << setw(14) << tmp.programming
				<< "| " << setw(16) << " "
				<< "| " << setw(8) << " ";
			cout << " | ";
			break;
		case StudentSpec_Informatics:
			cout << "| " << setw(14) << " "
				<< "| " << setw(16) << tmp.programming
				<< "| " << setw(8) << " ";
			cout << " | ";
			break;
		case StudentSpec_MathematicsEconomics:
		case StudentSpec_Fiz_Inf:
		case StudentSpec_Trud:
			cout << "| " << setw(14) << " "
				<< "| " << setw(16) << " "
				<< "| " << setw(8) << tmp.programming;
			cout << " | " ;
		}
		cout << endl;

	}
	cout << "===================================================================================================================" << endl;
}

int BinSearch(fstream& f, const string &lastname, const StudentSpec& spec, const float &av)
{ 
	f.clear();
	f.seekg(0, ios::end);
	int L = 0, R = f.tellg() / sizeof(Student) - 1, m, avarage[2] = {av, 0};
	Student tmp;
	do {
		m = (L + R) / 2;
		readStudent(f, m, tmp);

		avarage[1] = round((tmp.mark_math + tmp.mark_physics + tmp.programming) / 3);
		
		if (lastname == string(tmp.lastname) &&
			avarage[0] == avarage[1] &&
			spec == tmp.spec)
			return m;

		if (avarage[0] > avarage[1] ||
			(avarage[0] == avarage[1] && spec > tmp.spec) ||
			(avarage[0] == avarage[1] && spec == tmp.spec && lastname > string(tmp.lastname)))
			L = m + 1;
		else 
			R = m - 1;
	} while (L <= R);
	return -1;
}


void main() {
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 
	cout.setf(ios_base::left);

	unsigned int state = 1, count = 3;
	fstream f;
	bool indexed_cout = false;
	char message[256] = { 0 };
	string name_of_file;
	cout << "ім'я файлу: "; cin >> name_of_file;
	f.open(name_of_file, ios::binary | ios::in | ios::out);
	if (!f.is_open()) {
		f.open(name_of_file, ios::binary | ios::in | ios::out | ios::trunc);
		if (!f.is_open()) {
			cout << "неможливо відкрити файл!" << endl;
			return;
		}
	}
	else f.seekp(0, ios::end);
	cout << "кількість студентів: ";
	do
	{
		if (cin.fail()) {
			cin.clear(); 
			cin.ignore(INT_MAX, '\n'); 
		}
		cin >> count;
	} while (cin.fail() || count < 0 || count > 30);
	studentFactory(f, count);
	int found;

	do {
		if (!indexed_cout)
			drawStudents(f);
		else {
			string fn;
			cout << "ім'я файлу: "; cin >> fn;
			fstream fi(fn, ios::binary | ios::in | ios::trunc | ios::out);
			if (fi.is_open()) {
				indexed_sort(f, fi);
				print_indexed_sort(f, fi);
				fi.close();
			}
			else cout << "Неможливо відкрити файл для індексного сортування";
			indexed_cout = false;
		}
		if (message[0] != '\0') {
			cout << message << endl;
			message[0] = '\0';
		}
		cout << "[1] Sort" << endl
			<< "[2] Indexed sort" << endl
			<< "[3] Сout original" << endl
			<< "[4] Bin search" << endl
			<< "[0] Exit" << endl;
		do
		{
			if (cin.fail()) {
				cin.clear(); 
				cin.ignore(INT_MAX, '\n'); 
			}
			cin >> state;
		} while (cin.fail());
		switch (state)
		{
		case 1:
			sort_students(f);
			sprintf_s(message, 255, "Успішно посортовано за прізвищем");
			break;
		case 2:
			indexed_cout = true;
			sprintf_s(message, 255, "Успішне індексне сортування");
			break;
		case 3:
			break;
		case 4: {
			string lastname;
			StudentSpec spec;
			float avarage;

			cout << "прізвище: ";
			cin.ignore(INT_MAX, '\n');
			getline(cin, lastname);
			cout << "Спеціальності:\n0 - Комп'ютерні науки\n1 - Інформатика\n2 - Математика та економіка\n3 - Фізика та інформатика\n4 - Трудове навчання\n";
			do
			{
				if (cin.fail()) {
					cin.clear(); 
					cin.ignore(INT_MAX, '\n'); 
				}
				cin >> (unsigned short&)spec;
			} while (cin.fail() || spec < 0 || spec > 4);
			cout << "середній бал: ";
			do
			{
				if (cin.fail()) {
					cin.clear(); 
					cin.ignore(INT_MAX, '\n'); 
				}
				cin >> avarage;
			} while (cin.fail() || avarage < 0 || avarage > 5);

			if ((found = BinSearch(f, lastname, spec, avarage)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;

	
			
		}break;
		default:
			sprintf_s(message, 255, "Неправильна дія!");
		}
	} while (state > 0);
	f.close();
}