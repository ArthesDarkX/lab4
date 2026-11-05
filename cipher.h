#pragma once
#include <cwctype>
#include <string>
#include <stdexcept>

/**
 * @file cipher.h
 * @brief Заголовочный файл для модуля cipher
 * @details Содержит определение классов Cipher и Cipher_error. 
 * @version 1.0
 * @date 01.11.2026
 * @author Борискин Я. С.
 */

/**
 * @brief Класс для шифрования методом маршрутной перестановки
 * @details В классе ключ устанавливается в конструкторе.
 * Для зашифрования используется метод encrypt.
 * Для расшифрования используется метод decrypt.
 */
class Cipher
{
private:
    unsigned length_text{}; ///< Длина текста
    int key{}; ///< Ключ шифрования

public:
    Cipher()=delete; ///< Конструктор без параметров

    /**
     * @brief СОздаёт объект шифра для установки ключа
     * @param [in] key ключ шифрования
     * @throw Cipher_error Если ключ меньше или равен нулю.
     */
    Cipher(const int& key);

    /**
     * @brief Проверяет строку на соответсвие правилам
     * @details Проверяет, что строка:
     * - не является пустой;
     * - не содержит цифр;
     * - не содержит строчных букв;
     * Строка не должна содержать строчных букв.
     * @param [in] string введённая строка.
     * @throw Cipher_error Если строка пустая, в тексте присутствуют числа или строчные буквы.
     */
    void checkString(const std::wstring& string);

    /**
     * @brief Зашифровывает текст
     * @details Зашифровывает введённый текст при помощи таблицы.
     * @param [in] string открытый текст
     * @return Зашифрованный текст
     * @throw Cipher_error Если строка пустая, в тексте присутствуют числа или строчные буквы.
     */
    std::wstring encrypt(const std::wstring& string);

    /**
     * @brief Расшифровывает текст
     * @details Расшифровывает зашифрованный текст при помощи таблицы.
     * @param [in] string зашифрованный текст
     * @return Расшифрованный текст
     * @throw Cipher_error Если строка пустая, в тексте присутствуют числа или строчные буквы.
     */
    std::wstring decrypt(const std::wstring& string);
};

/**
 * @brief Пользовательский класс для исключений шифра.
 * @details Класс наследуется от std::invalid_argument и используется для сообщений об ошибках
 * входных данных или некорректном ключе шифрования.
*/
class Cipher_error: public std::invalid_argument
{
public:
    explicit Cipher_error(const std::string& what_arg)
    : std::invalid_argument(what_arg) {}
    explicit Cipher_error(const char* what_arg)
    : std::invalid_argument(what_arg) {}
};