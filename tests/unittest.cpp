#include <iostream>
#include <locale>

#include <UnitTest++/UnitTest++.h>

#include "cipher.h"

/**
 * @file unittest.cpp
 * @brief Тестировочный модуль
 * @version 1.0
 * @date 01.11.2026
 * @author Борискин Я. С.
 * @note Используется сторонняя библиотека UnitTest++
*/

/**
 * @brief Набор тестов для проверки конструктора ключа.
 */
SUITE(Key)
{
    TEST(PositiveKey)
    {
        Cipher cipher(2);
        CHECK(true);
        std::cout << "Тест 1.1 - OK\n";
    }
    TEST(ZeroKey)
    {
        CHECK_THROW(Cipher(0), Cipher_error);
        std::cout << "Тест 1.2 - OK\n";
    }
    TEST(NegativeKey)
    {
        CHECK_THROW(Cipher(-100), Cipher_error);
        std::cout << "Тест 1.3 - OK\n";
    }
}

/**
 * @brief Тестовая структура для проверки класса Cipher.
 * @details Создаёт объект класса Cipher с ключом 3, который используется в тестах.
 */
struct fixture_key
{
    Cipher cipher;
    fixture_key() : cipher(3) {}
};

/**
 * @brief Набор тестов для проверки шифрования текста.
 * @details Проверяет корректность шифрования строк и обработку некорректных входных данных.
 */
SUITE(ENCRYPT)
{
    TEST_FIXTURE(fixture_key, UPCaseString)
    {
        CHECK(L"КТЕЕСР" == cipher.encrypt(L"СЕКРЕТ"));
        std::cout << "Тест 2.1 - OK\n";
    }
    TEST_FIXTURE(fixture_key, OneLetterString)
    {
        CHECK(L"А" == cipher.encrypt(L"А"));
        std::cout << "Тест 2.2 - OK\n";
    }
    TEST_FIXTURE(fixture_key, StringNOTKey)
    {
        CHECK(L"ВБДАГ" == cipher.encrypt(L"АБВГД"));
        std::cout << "Тест 2.3 - OK\n";
    }
    TEST(KeyMoreText)
    {
        CHECK(L"ВБА" == Cipher(5).encrypt(L"АБВ"));
        std::cout << "Тест 2.4 - OK\n";
    }
    TEST_FIXTURE(fixture_key, EmptyString)
    {
        CHECK_THROW(cipher.encrypt(L""), Cipher_error);
        std::cout << "Тест 2.5 - OK\n";
    }
    TEST_FIXTURE(fixture_key, DigitsInString)
    {
        CHECK_THROW(cipher.encrypt(L"ТЕКСТ123"), Cipher_error);
        std::cout << "Тест 2.6 - OK\n";
    }
    TEST_FIXTURE(fixture_key, LowCaseString)
    {
        CHECK_THROW(cipher.encrypt(L"текст"), Cipher_error);
        std::cout << "Тест 2.7 - OK\n";
    }
    TEST_FIXTURE(fixture_key, NoAlphaString)
    {
        CHECK_THROW(cipher.encrypt(L"1234+8765=9999"), Cipher_error);
        std::cout << "Тест 2.8 - OK\n";
    }
}

/**
 * @brief Набор тестов для проверки расшифрования текста.
 * @details Проверяет корректность расшифрования строк и обработку некорректных входных данных.
 */
SUITE(DECRYPT)
{
    TEST_FIXTURE(fixture_key, UPCaseString)
    {
        CHECK(L"СЕКРЕТ" == cipher.decrypt(L"КТЕЕСР"));
        std::cout << "Тест 3.1 - OK\n";
    }
    TEST_FIXTURE(fixture_key, OneLetterString)
    {
        CHECK(L"А" == cipher.decrypt(L"А"));
        std::cout << "Тест 3.2 - OK\n";
    }
    TEST_FIXTURE(fixture_key, StringNOTKey)
    {
        CHECK(L"АБВГД" == cipher.decrypt(L"ВБДАГ"));
        std::cout << "Тест 3.3 - OK\n";
    }
    TEST(KeyMoreText)
    {
        CHECK(L"АБВ" == Cipher(5).decrypt(L"ВБА"));
        std::cout << "Тест 3.4 - OK\n";
    }
    TEST_FIXTURE(fixture_key, EmptyString)
    {
        CHECK_THROW(cipher.decrypt(L""), Cipher_error);
        std::cout << "Тест 3.5 - OK\n";
    }
    TEST_FIXTURE(fixture_key, DigitsInString)
    {
        CHECK_THROW(cipher.decrypt(L"АБВ123"), Cipher_error);
        std::cout << "Тест 3.6 - OK\n";
    }
    TEST_FIXTURE(fixture_key, LowCaseString)
    {
        CHECK_THROW(cipher.decrypt(L"абв"), Cipher_error);
        std::cout << "Тест 3.7 - OK\n";
    }
    TEST_FIXTURE(fixture_key, NoAlphaString)
    {
        CHECK_THROW(cipher.decrypt(L"1234+8765=9999"), Cipher_error);
        std::cout << "Тест 3.8 - OK\n";
    }
}

/**
 * @brief Главная функция программы.
 * @details Устанавливает русскую локаль и запускает все модульные тесты.
 * @return Код завершения программы.
*/
int main()
{
    std::locale loc("");
    std::locale::global(loc);
    return UnitTest::RunAllTests();
}