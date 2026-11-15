#include <vector>
#include "cipher.h"

/**
 * @file cipher.cpp
 * @brief Реализация методов класса Cipher
 * @details Файл содержит реализации конструктора и методы 
 * для шифрования и расшифрования методом маршрутной перестановки.
 * @version 1.0
 * @date 01.11.2026
 * @author Борискин Я. С.
 */

/**
 * @brief Конструктор для установки ключа.
 * @details Конструктор для установки ключа шифрования.
 * Проверяет, что ключ положительный.
 * @param [in] key ключ шифрования
 * @throw Cipher_error Если ключ меньше или равен нулю.
 */
Cipher::Cipher(const int& key) {
    if (key <= 0) {
        throw Cipher_error("Ключ меньше или равен 0!");
    }
    this->key = key;
}

/**
 * @brief Проверяет строку на соответствие правилам
 * @details Проверяет строку на соответствие правилам:
 * Строка не должна быть пустой.
 * Строка не должна содержать чисел.
 * Строка не должна содержать строчных букв.
 * @param [in] string введённая строка.
 * @throw Cipher_error Если строка пустая, в тексте присутствуют числа или строчные буквы.
 */
void Cipher::checkString(const std::wstring& string) {
    if (string.empty()) {
        throw Cipher_error("Не введён текст!");
    }
    for (auto c : string) {
        if (iswdigit(c)) {
            throw Cipher_error("В тексте не должно быть чисел!");
        }
        if (iswlower(c)) {
            throw Cipher_error("В тексте не должно быть строчных букв!");
        }
    }
}

/**
 * @brief Зашифровывает текст
 * @details Зашифровывает введённый текст при помощи таблицы.
 * @param [in] string открытый текст
 * @return Зашифрованный текст
 * @warning Незанятые ячейки таблицы заполняются пробелами.
 */
std::wstring Cipher::encrypt(const std::wstring& string) {
    Cipher::checkString(string);
    length_text = string.size();
    int columns = key;
    int rows = (length_text - 1) / key + 1;

    std::vector<wchar_t> table(rows * columns, L' ');
    int index = 0;
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            index = row*columns + column;
            if (index < length_text) {
                table[index] = string[index];
            }
        }
    }

    std::wstring result;

    for (int column = columns - 1; column >= 0; --column) {
        for (int row = 0; row < rows; ++row) {
            index = row*columns + column;
            if (index < length_text) {
                result += table[index];
            }
        }
    }
    return result;
}

/**
 * @brief Расшифровывает текст
 * @details Расшифровывает зашифрованный текст при помощи таблицы.
 * @param [in] string зашифрованный текст
 * @return Расшифрованный текст
 * @warning Разделителем в таблице используется пробел!
*/
std::wstring Cipher::decrypt(const std::wstring& text) {
    checkString(text);
    length_text = text.size();
    int columns = key;
    int rows = (length_text - 1) / key + 1;

    std::vector<wchar_t> table(columns*rows, L' ');
    int index = 0;
    int text_index = 0;
    for (int column = columns - 1; column >= 0; --column) {
        for (int row = 0; row < rows; ++row) {
            index = row*columns + column;
            if (index < length_text) {
                table[index] = text[text_index++];
            }
        }
    }

    std::wstring result;

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            index = row*columns + column;
            if (index < length_text) {
                result += table[index];
            }
        }
    }
    return result;
}
