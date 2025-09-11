// Rozwiązanie do zadania 'Trójkąty' z II etapu II OI.
// Autor rozwiązania: Paweł Putra
// Złożoność czasowa: O(1)
// Złożoność pamięciowa: O(1)
// Punkty: 100 (upsolve)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    vector<int> numbers;
    int input;
    int count = 0;

    while (true) {
        cin >> input;
        // Żeby nie było żadnego trójkąta w posortowanym ciągu długości boków a_i
        // musi zachodzić a_i + a_{i+1} <= a_i{i+2} dla każdego i, czyli każdy kolejny element
        // musi być równy conajmniej sumie poprzednich, czyli a_i >= F(n), dla n=60 to już ponad 10^12.
        // Więc dla 60 długości boków jakiś trójkąt musi istnieć.
        if (input == 0 || count == 60) {
            break;
        }
        if (input > 0) {
            numbers.push_back(input);
            count++;
        }
    }

    sort(numbers.begin(), numbers.end());
    
    for (size_t i = 0; i + 2 < numbers.size(); ++i) {
        if (numbers[i] + numbers[i+1] > numbers[i+2]) {
            cout << numbers[i] << " " << numbers[i+1] << " " << numbers[i+2] << endl;
            return 0;
        }
    }

    cout << "NIE" << endl;
    return 0;
}