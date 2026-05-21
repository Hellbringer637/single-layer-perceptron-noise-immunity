#include <iostream>
#include <windows.h>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//Вводные
	vector<vector<int>> numbers = {
		{1, 1, 1, 1, 1, 1, 0, 0, 0}, //0
		{0, 0, 0, 1, 1, 0, 1, 0, 0}, //1
		{0, 0, 1, 1, 0, 1, 0, 0, 1}, //2
		{0, 0, 1, 0, 0, 0, 1, 1, 1}, //3
		{0, 1, 0, 1, 1, 0, 0, 1, 0}, //4
		{0, 1, 1, 0, 1, 1, 0, 1, 0}, //5
		{1, 0, 0, 0, 1, 1, 1, 1, 0}, //6
		{1, 0, 1, 0, 0, 0, 1, 0, 0}, //7
		{1, 1, 1, 1, 1, 1, 0, 1, 0}, //8
		{0, 1, 1, 1, 0, 0, 0, 1, 1}  //9
	};
	//   0  1  2  3  4  5  6  7  8

	int Threshold_Value = 31;

	//Таблица
	vector<vector<int>> table;
	int random_count;
	vector<int> numbers_of_random;

	for (int a = 0; a < 500; a++) {
		random_count = rand() % 10;
		numbers_of_random.push_back(random_count);

		table.push_back(numbers[random_count]);
	}

	//Таблица помех
	vector<vector<int>> mistake_table;
	vector<int> null = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int a = 0; a < 500; a++) {
		mistake_table.push_back(null);
	}

	//Условие
	vector<int> Sum;
	Sum.reserve(500);
	int sum = 0;
	int sum_count = 0;

	for (int mistake = 0; mistake < 10; mistake++) {
		if (mistake > 0) {
			cout << " " << endl;
		}
		cout << "КОЛИЧЕСТВО ВНЕСЕННЫХ ПОМЕХ: " << mistake << endl << endl;
		vector<int> changes;
		int Changes = 0;
		int Epoha = 0;
		bool While = true;
		vector<int> Weight_Vector = { 5, 7, 3, 1, 4, 2, 6, 9, 8 };

		//Внесение помех
		if (mistake > 0) {
			for (int X = 0; X < 500; X++) {
				random_count = rand() % 10;
				bool Mistake = true;

				//Проверка на то, создалась ли помеха на том месте, где уже есть другая помеха
				while (Mistake) {
					//Помеха уже существует
					if ((random_count == 9) or (mistake_table[X][random_count] == 1)) {
						random_count = rand() % 10;
					}
					//Помеха еще не создана
					else {
						mistake_table[X][random_count] += 1;
						Mistake = false;

						//Помеха в основной таблице
						if (table[X][random_count] == 0)
							table[X][random_count] += 1;
						else
							table[X][random_count] -= 1;
					}
				}
			}
		}

		while (While) {

			//Суммирование
			for (int d = 0; d < 500; d++) {
				for (int a = 0; a < 9; a++) {
					if (table[d][a] == 1) {
						sum += Weight_Vector[a];
					}
					sum_count++;
				}

				if (sum_count % 9 == 0) {
					Sum.push_back(sum);
					sum = 0;

					//Найдена та самая цифра
					if (numbers_of_random[d] == 3) {

						//Сумма < или = порогового значения
						if (Sum[d] <= Threshold_Value) {
							for (int e = 0; e < 9; e++) {
								if (table[d][e] == 1)
									Weight_Vector[e] += 1;
							}
							Changes += 1;
						}
					}
					//Найдена другая цифра
					else {

						//Сумма > порогового значения
						if (Sum[d] > Threshold_Value) {
							for (int e = 0; e < 9; e++) {
								if (table[d][e] == 1)
									Weight_Vector[e] -= 1;
							}
							Changes += 1;
						}
					}
				}
			}
			Sum.clear();
			changes.push_back(Changes);
			Epoha += 1;

			//Кол-во ошибок возросло, а не убавилось
			if (Epoha > 1) {
				for (int end = 1; end < Epoha; end++) {
					if (changes[end - 1] < changes[end]) {
						While = false;
						cout << "Эпох: [" << Epoha << "], ошибок: [" << changes[end - 1] << "]" << endl;
					}
					if (changes[end] == 0) {
						While = false;
						cout << "Эпох: [" << Epoha << "], ошибок: [" << changes[end] << "]" << endl;
					}
				}
			}
			Changes = 0;
		}
		changes.clear();
		cout << endl;
	}
	return 0;
}
