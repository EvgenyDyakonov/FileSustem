#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <direct.h>
#include <io.h>
#include <Windows.h>
#include <string>

using namespace std;

void findfiles(char *path)
{
	int size = strlen(path);
	char working_path[200];
	for (int i = 0; i < size; i++)
	{
		working_path[i] = path[i];
	}
	working_path[size] = '/';
	working_path[size + 1] = '*';
	working_path[size + 2] = '\0';

	_finddata_t data;
	intptr_t  handle = _findfirst(working_path, &data);
	
	do {
		try
		{
			if(handle<0)
				throw "Некорректый адрес директории.";
		}
		catch (const char *exeption)
		{
			cout << "Ошибка: " << exeption << endl;
			break;
		}
		cout.width(70);
		if (data.attrib & _A_SUBDIR)
		{
			if (data.name[0] == '.')
			{
				continue;
			}
			else {
				cout << data.name << "\t[Папка]" << endl;
				int i = 0;
				int new_size = size + strlen(data.name);
				char new_path[200]{'\0'};
				for (; i < size; i++)
				{
					new_path[i] = path[i];
				}
				new_path[i] = '/';
				i++;
				for (int j = 0; i < new_size+1; i++, j++)
				{
					new_path[i] = data.name[j];
				}
				new_path[new_size+1] = '/';
				new_path[new_size+2] = '\0';
				findfiles(new_path);
			}

		}
		else
		{
			cout << data.name << "\t" << data.size / 1024 << " KB\t" << "file" << endl;
		}
	} while (_findnext(handle, &data) == 0);
	_findclose(handle);
}


int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	char path[200];
	cout << "Это программа поиска файлов и папок по заданному адресу." << endl;
	cout << "Введите адрес поиска (Максимальное число символов в адресе - 200). Пример: С:/имя папки" << endl;
	cin.getline(path, 200);
	findfiles(path);

	/*cin.getline(path, 100);
	int size = strlen(path);
	path[size]='*';
	path[size + 1] = '\0';
	cout << path;*/
	
	cout << "Поиск завершен, для выхода введите любой символ." << endl;
	char exit;
	cin >> exit;

	SetConsoleOutputCP(866);
	SetConsoleCP(866);
	return 0;
}