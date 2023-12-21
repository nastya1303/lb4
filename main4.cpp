#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int searchSubstring(string text, string pattern) {
    int n = text.length(); // длина текста
    int m = pattern.length(); // длина подстроки

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m) // если все символы совпали
            return i; // вернуть индекс начала подстроки
    }
    return -1; // подстрока не найдена
}

std::vector<int> suffixes(const std::string& pattern) {
    int length = pattern.length();
    std::vector<int> suffix(length, 0);

    int g, f;
    g = f = length - 1;
    for (int i = length - 2; i >= 0; --i) {
        if (i > g && suffix[i + length - 1 - f] < i - g) {
            suffix[i] = suffix[i + length - 1 - f];
        } else {
            if (i < g) {
                g = i;
            }
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + length - 1 - f]) {
                --g;
            }
            suffix[i] = f - g;
        }
    }

    return suffix;
}

std::vector<int> boyerMoore(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> occurrences;

    std::vector<int> shift(256, m);
    for (int i = 0; i < m - 1; ++i) {
        shift[pattern[i]] = m - i - 1;
    }

    std::vector<int> suffix = suffixes(pattern);

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            --j;
        }
        if (j < 0) {
            occurrences.push_back(i);
            i += shift[text[i + m]];
        } else {
            int x = suffix[j];
            int y = j - x;
            int z = m - 1 - j;
            i += std::max(shift[text[i + j]] - y, z);
        }
    }

    return occurrences;
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    bool task = true;
    int choose = 0, idz = 0, idzChoose = -1;

    while (choose != -1) {
        cout << "\n\n\nИз данных заданий, выберете то, которое хотите выполнить: \n"
                "1.С клавиатуры вводится последовательность, содержащая от 1 до 50 слов, в каждом из которых от 1 до 10 строчных латинских букв и цифр. Между словами произвольное количество пробелов. За последним символом стоит точка\n"
                "2.Редактирование входного текста.\n"
                "3.Вывести на экран только те слова последовательности, в которых первая буква слова встречается в этом слове еще раз.\n"
                "4.Вывести на экран ту же последовательность, заменив во всех словах первую букву соответствующей прописной буквой.\n"
                "5.Необходимо найти все подстроки, которую введёт пользователь в имеющейся строке. Реализуйте алгоритм Линейный поиск.\n\n\n";

        cout << "Задание: ";
        cin >> choose;
        cout << "\n";

        if (choose != 1 and choose != 2 and choose != 3 and choose != 4 and choose != 5 and choose != 0)
            cout << "Такого варианта ответа нет \n";

        else
            switch (choose) {
                case 0: {
                    cout << "Пока \n\n";
                    choose = -1;
                    break;
                }

                case 1: {
                    std::string sequence;
                    std::cout << "Введите последовательность слов:" << std::endl;
                    std::getline(std::cin, sequence, '.'); // вводим последовательность до точки

                    int wordCount = 0;
                    std::string currentWord;
                    // перебираем символы в последовательности
                    for (char c : sequence) {
                        // если символ - пробел, то заканчиваем текущее слово и начинаем следующее
                        if (c == ' ') {
                            if (!currentWord.empty()) {
                                std::cout << currentWord << " " ;
                                currentWord.clear();
                            }
                        } else if (isalnum(c)) { // добавляем буквы и цифры в слово
                            currentWord += c;
                        } else { // игнорируем другие символы
                            continue;
                        }
                    }
                    // печатаем последнее слово, если оно есть
                    if (!currentWord.empty()) {
                        std::cout << currentWord << "." << std::endl;
                    }
                    break;
                }

                case 2: {
                    std::string inputText;
                    std::cout << "Введите текст: ";
                    std::getline(std::cin, inputText);
                    std::getline(std::cin, inputText);
                    std::cout << "Вывели:" << inputText<< '\n';

                    // Удаление лишних пробелов
                    bool previousIsSpace = false;
                    for (auto it = inputText.begin(); it != inputText.end();) {
                        if (std::isspace(*it)) {
                            if (previousIsSpace) {
                                it = inputText.erase(it);
                            } else {
                                previousIsSpace = true;
                                ++it;
                            }
                        } else {
                            previousIsSpace = false;
                            ++it;
                        }
                    }
                    // Удаление лишних знаков препинания
                    for (auto it = inputText.begin(); it != inputText.end();) {
                        if (std::ispunct(*it)) {
                            auto next = std::next(it);
                            while (next != inputText.end() && std::ispunct(*next)) {
                                next = inputText.erase(next);
                            }
                            ++it;
                        } else {
                            ++it;
                        }
                    }
                    // Исправление регистра букв
                    for (auto &ch : inputText) {
                        if (std::isalpha(ch)) {
                            if (std::islower(ch)) {
                                ch = std::tolower(ch);
                            } else {
                                ch = std::tolower(ch);
                            }
                        }
                    }
                    std::cout << "Отредактированный текст: " << inputText;
                    break;
                }

                case 3:{
                    std::string inputText;
                    std::cout << "Введите текст: ";
                    std::getline(std::cin, inputText);
                    std::getline(std::cin, inputText);

                    bool is_new_word = true;
                    bool need_to_print_word = false;
                    int from = 0;
                    char first_char = inputText[0];
                    for (int i = 0; i < inputText.length(); i++) {
                        if (is_new_word && !ispunct(inputText[i]) && inputText[i] != ' ') {
                            from = i;
                            first_char = inputText[i];
                            is_new_word = false;
                        } else if (ispunct(inputText[i]) || inputText[i] == ' ') {
                            if (need_to_print_word) {
                                cout << inputText.substr(from, i - from) << '\n';
                            }
                            need_to_print_word = false;
                            is_new_word = true;
                        } else if (first_char == inputText[i]) {
                            need_to_print_word = true;
                        }
                    }
                    if (need_to_print_word) {
                        cout << inputText.substr(from, inputText.length()) << '\n';
                    }
                    break;
                }

                case 4:{
                    std::string sequence;
                    std::cout << "Введите последовательность: " << std::endl;
                    std::getline(std::cin, sequence);
                    std::getline(std::cin, sequence);

                    bool needToLower = true;

                    for (auto &ch : sequence) {
                        if (ch == ' '){
                            needToLower = true;
                        }
                        if (std::isalpha(ch) && needToLower == true) {
                            if (std::isupper(ch)) {
                                ch = std::tolower(ch);
                                needToLower = false;
                            }
                        }
                    }
                    std::cout << "Отредактированный текст: " << sequence;
                    break;
                }

                case 5:{
                    string text, pattern;
                    std::cout << "Введите строку: ";
                    std::cin >> text;
                    std::cout << "Введите подстроку: ";
                    std::getline(std::cin, pattern);
                    std::getline(std::cin, pattern);

                    int result = searchSubstring(text, pattern);
                    if (result == -1)
                        cout << "Подстрока не найдена" << endl;
                    else
                        cout << "Подстрока найдена в позиции: " << result << endl;


                    std::string text1, pattern1;
                    std::cout << "Введите строку: ";
                    std::cin >> text1;
                    std::cout << "Введите подстроку: ";
                    std::getline(std::cin, pattern1);
                    std::getline(std::cin, pattern1);

                    std::vector<int> occurrences = boyerMoore(text1, pattern1);

                    if (!occurrences.empty()) {
                        std::cout << "Pattern found at positions: ";
                        for (int i = 0; i < occurrences.size(); ++i) {
                            std::cout << occurrences[i] << " ";
                        }
                    } else {
                        std::cout << "Pattern not found.";
                    }

                    break;
                }
            }
    }
    return 0;
}