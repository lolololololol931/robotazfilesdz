#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

//n1
void serGrade(const string& file1, int porog) {
    ifstream file(file1);
    if (!file) {
        cout << "Не вдалося відкрити файл!" << endl;
        return;
    }

    string surname, name;
    int grade, sum = 0, count = 0;
    vector<string> lowGrades;
    while (file >> surname >> name >> grade) {
        sum += grade;
        count++;
        if (grade < porog) {
            lowGrades.push_back(surname + " " + name);
        }
    }
    file.close();
    cout << "Студенти з оцінками нижче " << porog << ":\n";
    for (const auto& student : lowGrades) {
        cout << student << endl;
    }
    if (count > 0)
        cout << "Середній бал: " << (double)sum / count << endl;
}

//n2
void filterWords(const string& inputFile, const string& bannedwords, const string& outputFile) {
    ifstream forbidden(bannedwords);
    if (!forbidden) {
        cout << "Не вдалося відкрити файл" << endl;
        return;
    }

    vector<string> badWords;
    string word;
    while (forbidden >> word) {
        badWords.push_back(word);
    }
    forbidden.close();

    ifstream input(inputFile);
    ofstream output(outputFile);
    if (!input || !output) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    string line;
    while (getline(input, line)) {
        istringstream iss(line);
        string word;
        string result;
        while (iss >> word) {
            if (find(badWords.begin(), badWords.end(), word) == badWords.end()) {
                result += word + " ";
            }
            else {
                result += "";
            }
        }
        output << result << endl;
    }
    input.close();
    output.close();
}

//n3
string translatingabet(const string& text) {
    string result;
    string ukr = "АБВГҐДЕЄЖЗИІЇЙКЛМНОПРСТУФХЦЧШЩЮЯабвгґдеєжзиіїйклмнопрстуфхцчшщюя";
    string eng[] = { "A", "B", "V", "H", "G", "D", "E", "Ye", "Zh", "Z", "Y", "I", "Yi", "Y", "K", "L", "M", "N", "O", "P", "R", "S", "T", "U", "F", "Kh", "Ts", "Ch", "Sh", "Shch", "Yu", "Ya", "a", "b", "v", "h", "g", "d", "e", "ie", "zh", "z", "y", "i", "yi", "y", "k", "l", "m", "n", "o", "p", "r", "s", "t", "u", "f", "kh", "ts", "ch", "sh", "shch", "yu", "ya" };

    for (char c : text) {
        size_t pos = ukr.find(c);
        if (pos != string::npos) {
            result += eng[pos];
        }
        else {
            result += c;
        }
    }
    return result;
}

void translate(const string& inputFile, const string& outputFile) {
    ifstream input(inputFile);
    ofstream output(outputFile);
    if (!input || !output) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    string line;
    while (getline(input, line)) {
        output << translatingabet(line) << endl;
    }
    input.close();
    output.close();
}

int main() {
    system("chcp 1251>nul");
    cout << "Введіть порогову оцінку: ";
    int porog;
    cin >> porog;
    cout << "n1" << endl;
    serGrade("grades.txt", porog);
    cout << "n2" << endl;
    filterWords("text.txt", "banned.txt", "filtered_text.txt");
    cout << "результат у файлі" << endl;
    cout << "n3" << endl;
    translate("ukrainian.txt", "translated.txt");
    cout << "результат у файлі" << endl;

    return 0;
}
