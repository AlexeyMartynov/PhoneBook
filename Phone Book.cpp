#include <iostream>
#include <cstdlib>
using namespace std;

enum Command { add, del, list, none };
enum Message { number_is_not_exist, command_is_not_exist, successful, type_code, type_number, type_command, can_contain_only_numbers };

string* codes = new string[1]{};
string* numbers = new string[1]{};

inline const string GetCommand(Command command)
{
    switch (command)
    {
    case add: return "add";
    case del: return "del";
    case list: return "list";
    default: return 0;
    }
}

inline const string GetMessage(Message message)
{
    switch (message)
    {
    case command_is_not_exist: return "Такої команди не існує!\n";
    case type_code: return "Введіть код міста (без +):\n";
    case type_number: return "Введіть номер телефону:\n";
    case type_command: return "Введіть команду (add/del/list):\n";
    case number_is_not_exist: return "Цього номеру не існує у телефонній книзі\n";
    case successful: return "Успіх!\n";
    default: return 0;
    }
}

inline const Command GetCommand(string value)
{
    for (int commandIndex = add; commandIndex < none; commandIndex++)
    {
        Command command = static_cast<Command>(commandIndex);
        if (GetCommand(command) == value)
            return command;
    }

    return none;
}

inline int GetSize()
{
    return sizeof(numbers) / sizeof(numbers[0]);
}

inline bool IsNumberExist(string code, string number)
{
    for (int index = 0; index < GetSize(); index++)
    {
        if (codes[index] == code && numbers[index] == number)
            return true;
    }

    return false;
}

inline bool IsNumeric(string const& value)
{
    auto it = std::find_if(value.begin(), value.end(), [](char const& c) 
    {
        return !std::isdigit(c);
    });

    return !value.empty() && it == value.end();
}

inline void Add(string code, string number)
{
    string* temp;
    const int size = GetSize();
    temp = codes;
    codes = new string[size + 1];
    for (int index = 0; index < size; index++)
        codes[index] = temp[index];

    codes[size] = code;

    temp = numbers;
    numbers = new string[size + 1];
    for (int index = 0; index < size; index++)
        numbers[index] = temp[index];

    numbers[size] = number;   

    cout << GetMessage(successful);
}

inline void Del(string code, string number)
{
    if (!IsNumberExist(code, number))
    {
        cout << GetMessage(number_is_not_exist);
        return;
    }

    string* temp;
    int size = GetSize();
    for(int index = 0; index < size; index++)
    {
        if(codes[index] == code && numbers[index] == number)
        {
            codes[index] = "none";
            numbers[index] = "none";
            size--;
        }
    }

    temp = codes;
    codes = new string[size];
    int count = 0;
    for (int index = 0; index < size; index++)
    {
        if (temp[index] != "none")
        {
            codes[count] = temp[index];
            count++;
        }
    }

    temp = numbers;
    numbers = new string[size];
    count = 0;
    for (int index = 0; index < size; index++)
    {
        if (temp[index] != "none")
        {
            numbers[count] = temp[index];
            count++;
        }
    }

    cout << GetMessage(successful);
}

void List()
{
    for (int index = 0; index < GetSize(); index++)
        cout << codes[index] + " " + numbers[index];
}

inline void GetPhoneNumber(bool add)
{
    string* number = new string[2];
    for (int index = 0; index < 2; index++)
    {
        if (index == 0) cout << GetMessage(type_code);
        else cout << GetMessage(type_number);

        cin >> number[index];
        if (!IsNumeric(number[index]))
        {
            cout << GetMessage(can_contain_only_numbers);
            index = -1;
        }
    }

    if (add) Add(number[0], number[1]);
    else Del(number[0], number[1]);
}

inline void DoCommand(Command command)
{
    switch (command)
    {
    case add: GetPhoneNumber(true);
    case del: GetPhoneNumber(false);
    case list: List();
    default: break;
    }
}

int main()
{
    while (true)
    {
        string value;
        cout << GetMessage(type_command);
        cin >> value;
        Command command = GetCommand(value);
        if (command == none)
        {
            std::cout << GetMessage(command_is_not_exist);
            continue;
        }

        DoCommand(command);
    }

    system("pause");
    return 0;
}