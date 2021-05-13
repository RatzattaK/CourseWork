#include <iostream> //Ввод/Вывод
#include <string> //Работа со строками
#include <sstream> //Работа со строками через поток (как одна строка)   
#include <vector> //Работа с векторами
#include <iomanip> //Манипуляторы ввода
#include <fstream> //Работа с файлами
#include <algorithm> //Работа с transorm
using namespace std;

struct Esports //Структура таблицы
{
    string TeamName; //Название команды
    string Country; //Страна
    int MemberCount; //Количество участников
    string Game; //Дисциплина (игра)
    int TournamentsPlayedInTotal; //Всего сыграно матчей за карьеру
    int MoneyEarned;  //Всего заработано за карьеру
};

void RemoveEmptyLines()
{
    //Создание фалйа Temp без пустых строк
    ifstream fin("Table.txt");
    ofstream fout ("Temp.txt");
    string CurrentLine;
    while (getline(fin, CurrentLine))
        if (!CurrentLine.empty())
            fout << CurrentLine << '\n';
    fin.close();
    fout.close();
    //Перенести содержимое Temp в Table
    fin.open("Temp.txt");
    fout.open("Table.txt");
    while (getline(fin, CurrentLine))
        fout << CurrentLine << '\n';
    fin.close();
    fout.close();
}

vector <Esports> ReadFromFile()
{
    RemoveEmptyLines();
    Esports esports; //Объявление структуры
    vector <Esports> vec_esports; //Создание вектора структуры
    string CurrentLine; //Текущая строка в файле
    ifstream fin; //Объект считывания из файла
    fin.open("Table.txt");
    while (getline(fin, CurrentLine)) //Пока в файле есть строка
    {
        int counter = 1; //Счётчик для записи в структуру
        stringstream line(CurrentLine); //Записать в переменную line текущую строку в файле как поток символов
        string buff; //Буферная строка, в которой будут хранится текущие подстроки (которые идут через запятую)
        while (getline(line, buff, ',')) //В текущей строке записывааем слова через ','
        {
            switch (counter) //В зависимости от counter меняем, в какое поле структуры будет записана текущая подстрока
            {
            case 1:
                esports.TeamName = buff;
                break;
            case 2:
                esports.Country = buff;
                break;
            case 3:
                esports.MemberCount = stoi(buff); //stoi для перевода строки в int
                break;
            case 4:
                esports.Game = buff;
                break;
            case 5:
                esports.TournamentsPlayedInTotal = stoi(buff);
                break;
            case 6:
                esports.MoneyEarned = stoi(buff);
                break;
            }
            counter++;
        }
        counter = 1; //Обнуляем счётчик для новой строки
        vec_esports.push_back(esports); //Записываем структуру в вектор структур
    }
    fin.close();
    return vec_esports; //Возвращаем полученный вектор в main
}

void WriteIntoFile(vector <Esports> &vec_esports)
{
    ofstream fout ("Table.txt");
    for (int i = 0; i < vec_esports.size(); i++)
        fout << vec_esports[i].TeamName << ',' << vec_esports[i].Country << ',' << vec_esports[i].MemberCount << ',' << vec_esports[i].Game << ',' << vec_esports[i].TournamentsPlayedInTotal << ',' << vec_esports[i].MoneyEarned << '\n';
    fout.close();
}

vector <Esports> AddTeam() //Функция считывания данных с кавиатуры
{
    Esports esports; //Создание структуры
    vector <Esports> vec_esports;
    ofstream fout; //Объект записи в файл
    cout << "Team name: ";
    while(1) // Проверка на ввод
    {
        getline(cin, esports.TeamName);
        if (esports.TeamName.empty())
            cout << "Enter a valid team name: ";
        else if ((esports.TeamName.size() > 20))
            cout << "Team name must be less than 20 characters: ";
        else break;
    }
    cout << "Country: ";
    while(1)
    {
        getline(cin, esports.Country);
        if (esports.Country.empty())
            cout << "Enter a valid country code: ";
        else if ((esports.Country.size() > 2))
            cout << "Country code must contain only 2 letters: ";
        else break;
    }
    transform(esports.Country.begin(), esports.Country.end(), esports.Country.begin(), ::toupper); //transform применяет функцию toupper(преообразование строчных букв в прописные) и записывает значение в эту же строку
    cout << "Number of members: ";
    while(1)
    {
        cin >> esports.MemberCount;
        if (cin.fail())
        {
            cout << "Enter an integer: ";
            cin.clear(); //Избавиться от состояния ошибки
            cin.ignore(256, '\n'); //Удалить из потока ввода все символы
        }
        else if (esports.MemberCount > 100)
            cout << "Number of members must be less than 100: ";
        else break;
    }
    cin.get(); //Очистка буфера ввода
    cout << "Game: ";
    while(1)
    {
        getline(cin, esports.Game);
        if (esports.Game.empty())
            cout << "Enter a valid game name: ";
        else if ((esports.Game.size() > 20))
            cout << "Choose an Esports game: ";
        else break;
    }
    cout << "Tournaments played in total: ";
    while(1)
    {
        cin >> esports.TournamentsPlayedInTotal;
        if (cin.fail())
        {
            cout << "Enter an integer: ";
            cin.clear(); //Избавиться от состояния ошибки
            cin.ignore(256, '\n'); //Удалить из потока ввода все символы
        }
        else if ((esports.TournamentsPlayedInTotal > 2000))
            cout << "Number of played tournaments must be less than 2000: ";
        else break;
    }
    cout << "Total earnings: ";
    while(1)
    {
        cin >> esports.MoneyEarned;
        if (cin.fail())
        {
            cout << "Enter an integer: ";
            cin.clear();
            cin.ignore(256, '\n');
        }
        else if ((esports.MoneyEarned > 99999999))
        {
            cout << "The number must be less than 8 digits: ";
            cin.clear();
        }
        else break;
    }
    fout.open("Table.txt", ios_base::out | ios_base::app); //Связывает объект fout с файлом test.txt, открытие файла в режиме ЗАПИСИ(out) и ТОЛЬКО В КОНЦЕ(app)
    fout << '\n'; //Всегда добавлять символ новой строки в файл
    fout << esports.TeamName << ',' << esports.Country << ',' << esports.MemberCount << ',' << esports.Game << ',' << esports.TournamentsPlayedInTotal << ',' << esports.MoneyEarned; //Запись строчки в файл
    fout.close(); //Закрытие файла
    vec_esports = ReadFromFile();
    system("cls");
    cout << "Team has been added successfully." << endl;
    return vec_esports;
}

void EditTeam(vector <Esports> &vec_esports)
{
    cout << "Write the name of the team you want to edit: ";
    string TeamName;
    bool TeamFound = false;
    while(1)
    {
        getline(cin, TeamName);
        if (TeamName.empty())
            cout << "Enter a valid team name: ";
        else if ((TeamName.size() > 20))
            cout << "Team name must be less than 20 characters: ";
        else break;
    }
    system("cls");
    for (int i = 0; i < vec_esports.size(); i++)
    {
        if (vec_esports[i].TeamName == TeamName)
        {
            int choice;
            do
            {
                cout << "1. Team name" << endl;
                cout << "2. Country" << endl;
                cout << "3. Member count" << endl;
                cout << "4. Game" << endl;
                cout << "5. Total tournaments" << endl;
                cout << "6. Total earnings" << endl;
                cout << "What do you want to edit: ";
                cin >> choice;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(256, '\n');
                }
            } while (choice > 6);
            string buff;
            cin.clear();
            cin.ignore(256, '\n');
            switch (choice)
            {
            case 1:
                cout << "New team name: ";
                while(1) // Проверка на ввод
                {
                    getline(cin, buff);
                    if (buff.empty())
                        cout << "Enter a valid team name: ";
                    else if ((buff.size() > 20))
                        cout << "Team name must be less than 20 characters: ";
                    else break;
                }
                vec_esports[i].TeamName = buff;
                break;
            case 2:
                cout << "New country: ";
                while(1)
                {
                    getline(cin, buff);
                    if (buff.empty())
                        cout << "Enter a valid country code: ";
                    else if ((buff.size() > 2))
                        cout << "Country code must contain only 2 letters: ";
                    else break;
                }
                vec_esports[i].Country = buff;
                transform(vec_esports[i].Country.begin(), vec_esports[i].Country.end(), vec_esports[i].Country.begin(), ::toupper);
                break;
            case 3:
                cout << "New member count: ";
                while(1)
                {
                    cin >> vec_esports[i].MemberCount;
                    if (cin.fail())
                    {
                        cout << "Enter an integer: ";
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                    else if (vec_esports[i].MemberCount > 100)
                        cout << "Number of members must be less than 100: ";
                    else break;
                }
                break;
            case 4:
                cout << "New game: ";
                while(1)
                {
                    getline(cin, buff);
                    if (buff.empty())
                        cout << "Enter a valid game name: ";
                    else if ((buff.size() > 20))
                        cout << "Choose an Esports game: ";
                    else break;
                }
                vec_esports[i].Game = buff;
                break;
            case 5:
                cout << "New number of tournaments: ";
                while(1)
                {
                    cin >> vec_esports[i].TournamentsPlayedInTotal;
                    if (cin.fail())
                    {
                        cout << "Enter an integer: ";
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                    else if (vec_esports[i].TournamentsPlayedInTotal > 2000)
                        cout << "Number of played tournaments must be less than 2000: ";
                    else break;
                }
                break;
            case 6:
                cout << "New earnings count: ";
                while(1)
                {
                    cin >> vec_esports[i].MoneyEarned;
                    if (cin.fail())
                    {
                        cout << "Enter an integer: ";
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                    else if (vec_esports[i].MoneyEarned > 99999999)
                        cout << "The number must be less than 8 digits: ";
                    else break;
                }
                break;
            }
            TeamFound = true;
            break;
        }
    }
    system("cls");
    if (!TeamFound)
        cout << "Team not found." << endl;
    else
    {
        WriteIntoFile(vec_esports);
        cout << "Changes have been made successfully." << endl;
    }
}

void DeleteTeam(vector <Esports> &vec_esports)
{
    ofstream fout;
    string TeamName;
    bool TeamFound = false;
    cout << "Write the name of the team you want to delete: ";
    while(1) // Проверка на ввод
    {
        getline(cin, TeamName);
        if (TeamName.empty())
            cout << "Enter a valid team name: ";
        else if ((TeamName.size() > 20))
            cout << "Team name must be less than 20 characters: ";
        else break;
    }
    for (int i = 0; i < vec_esports.size(); i++)
    {
        if (vec_esports[i].TeamName == TeamName)
        {
            vec_esports.erase(vec_esports.begin() + i);
            WriteIntoFile(vec_esports);
            RemoveEmptyLines();
            TeamFound = true;
            break;
        }
    }
    system("cls");
    if (!TeamFound)
        cout << "Team not found." << endl;
    else
        cout << "Team has been deleted successfully." << endl;
}

void PrintStructure(vector <Esports> vec) //Функция вывода информации в виде таблицы
{
    for (int i = 0; i < vec.size(); i++) //Вывод всех данных в виде табицы
    {
        if (i == 0)
            cout << left << setw(20) << "Team name" << "|" << setw(8) << "Country" << "|" << setw(13) << "Member count" << "|" << setw(20) << "Game" << "|" << setw(17) << "Total tournaments" << "|" << setw(16) << "Total earnings $" << "\n";
        cout << left << setw(20) << vec[i].TeamName << "|" << setw(8) << vec[i].Country << "|" << setw(13) << vec[i].MemberCount << "|" << setw(20) << vec[i].Game << "|" << setw(17) << vec[i].TournamentsPlayedInTotal << "|" << setw(16) << vec[i].MoneyEarned << "\n";
    }
}

bool SortComp(Esports a, Esports b)
{
    return (a.TeamName < b.TeamName);
}

void SortVector(vector <Esports> &vec_esports)
{
    sort(vec_esports.begin(),vec_esports.end(),SortComp);
    WriteIntoFile(vec_esports);
    RemoveEmptyLines();
    PrintStructure(vec_esports);
}

void FilterVector(vector <Esports> vec_esports)
{
    vector <Esports> filtered;
    cout << "1. Country" << endl;
    cout << "2. Amount of players" << endl;
    cout << "3. Game" << endl;
    cout << "4. Amount of played tournaments" << endl;
    cout << "5. Total earnings" << endl;
    cout << "Filter by: ";
    string buff_str;
    int buff_int;
    int counter;
    cin >> counter;
    cin.get();
    switch (counter)
    {
    case 1:
        cout << "Country code: ";
        getline(cin, buff_str);
        //while(1) - проверка ввода
        for (int i = 0; i < vec_esports.size(); i++)
            if (vec_esports[i].Country == buff_str)
                filtered.push_back(vec_esports[i]);
        break;
    case 2:
        cin >> buff_int;
        for (int i = 0; i < vec_esports.size(); i++)
            if (vec_esports[i].MemberCount == buff_int)
                filtered.push_back(vec_esports[i]);
        break;
    case 3:
        cout << "Game name: ";
        getline(cin, buff_str);
        //while(1) - проверка ввода
        for (int i = 0; i < vec_esports.size(); i++)
            if (vec_esports[i].Game == buff_str)
                filtered.push_back(vec_esports[i]);
        break;
    case 4:
        cin >> buff_int;
        for (int i = 0; i < vec_esports.size(); i++)
            if (vec_esports[i].TournamentsPlayedInTotal == buff_int)
                filtered.push_back(vec_esports[i]);
        break;
    case 5:
        cin >> buff_int;
        for (int i = 0; i < vec_esports.size(); i++)
            if (vec_esports[i].MoneyEarned == buff_int)
                filtered.push_back(vec_esports[i]);
        break;
    default:
        system("cls");
        cout << "Error: Invalid value." << endl;
        break;
    }
    system("cls");
    PrintStructure(filtered);
}

int menu() //Отображаемое меню в консоли
{
    int choice;
    do
    {
        //system("cls"); //Очистка консоли
        cout << "Menu" << endl;
        cout << "1. Display file content" << endl;
        cout << "2. Add team" << endl;
        cout << "3. Edit team" << endl;
        cout << "4. Delete team" << endl;
        cout << "5. Sort" << endl;
        cout << "6. Filter" << endl;
        cout << "7. Exit" << endl;
        cout << "What action would you like to perform: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear(); //Избавиться от состояния ошибки
            cin.ignore(256, '\n'); //Удалить из потока ввода все символы
        }
    } while (choice > 7);
    cin.clear();
    cin.ignore(256,'\n');
    return choice;  
}

int main()
{
    vector <Esports> vec_esports; //Создать вектор структуры
    while (1)
    {
        switch (menu())
        {
        case 1:
            system("cls");
            vec_esports = ReadFromFile(); //Считать с файла в вектор
            PrintStructure(vec_esports);
            cout << endl;
            break;
        case 2:
            system("cls");
            vec_esports = AddTeam(); //Записать новое значение в файл
            break;
        case 3:
            EditTeam(vec_esports);
            break;
        case 4:
            DeleteTeam(vec_esports);
            break;
        case 5:
            system("cls");
            SortVector(vec_esports);
            break;
        case 6:
            FilterVector(vec_esports);
            break;
        case 7:
            return 0;
        default:
            cout << "Choose a valid option." << endl;
            break;
        }
    }
}
/*vector <data> data(5);
data[2].i
push_back()
pop_back()
erase()
insert()
sort() - алгоритмы сортировки

Nazvanie.is_open() - bool открыл ли файл
Nazvanie.eof() - bool конец ли файла

переход на строку eomanip

<tuple> //Картеж. Возвращает несколько значений 
tuple <int, string> t;
get <0> t;
int a; string b;
tie (a, b) = t; //Распаковка

Фильтр (a - vector, b - vector)
remove_copy_if(a.begin(), a.end(), back_insert (b), comp)

false - если копирую в новый вектор
true - не копирую
*/
