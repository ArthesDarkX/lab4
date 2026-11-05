#include <iostream>
#include <cwctype>
#include <locale>

#include "cipher.h"

/**
 * @file main.cpp
 * @brief Главный модуль
 * @version 1.0
 * @date 05.11.2026
 * @author Борискин Я. С.
*/

/**
 * @brief Главная функция программы
 * @details Устанавливает русскую локаль
 * @return Код завершения программы.
 * @throw Cipher_error Если ключ или текст некорректны
*/
int main()
{
    std::locale loc("");
    std::locale::global(loc);

    int key{};      ///< Ключ шифрования, вводимый пользователем
    unsigned op{};  ///< Код выбранной операции

    std::wcout << L"Введите ключ: ";
    std::wcin >> key;
    try {
        Cipher cipher(key);
        do {
            std::wcout << L"Введите операцию, которую хотите выполнить: 1 — шифрование, 2 — расшифрование, 0 — выход" << L'\n';
            std::wcin >> op;
            switch (op) {
            case 0:
            {
                std::wcout << L"Выход из программы" << L'\n';
                break;
            }
            case 1:
            {
                std::wcout << L"Выбрана операция — шифрование" << L'\n';
                std::wstring text;                             ///> Введённый пользователем текст
                std::wcout << L"Введите текст: ";
                std::wcin >> text;
                std::wstring result = cipher.encrypt(text);     ///> Зашифрованный текст
                std::wcout << L"Результат: " << result << L'\n';
                break;
            }   
            case 2:
            {
                std::wcout << L"Выбрана операция — расшифрование" << L'\n';
                std::wstring text;                             ///> Введённый пользователем текст
                std::wcout << L"Введите текст: ";
                std::wcin >> text;
                std::wstring result = cipher.decrypt(text);     ///> Расшифрованный текст
                std::wcout << L"Результат: " << result << L'\n';
                break;
            }
            default:
            {
                std::wcerr << L"Такой операции не предусмотрено" << L'\n';
                break;
            }
            }
        } while (op != 0);
    }
    catch (const Cipher_error& ex) {
        std::cerr << "Ошибка: " << ex.what() << '\n';
    }
}
