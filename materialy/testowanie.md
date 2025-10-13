# Cośtam o testowaniu

## Jasio przepisuje testy...
Ach, to już luty... W walentykowy dzień idziesz sobie na drugi etap i widzisz takie zadanko:
> Mając dane słowo długości n, znajdź długość jego najdłuższego **buńczucznego** podsłowa.

Od razu wpadasz na pomysł, rozwiązanie przyśniło ci się poprzedniej nocy, więc klepiesz ile sił.
Już czujesz, że masz finał w kieszeni. Odpalasz i wpisujesz test przykładowy:

> ./program
> 
> blabla**bunczucznepodslowo**blabla

Nie działa...
Szybko znajdujesz błąd, naprawiasz, wpisujesz znów test
> ./program
>
> blabla**buńczucznepodslowo**blabla

Nadal nie działa???

Czytasz cały kod od góry do dołu tylko po to, 
żeby po pięciu minutach zobaczyć, że źle przepisałeś przykładowy...

Zapisuj testy jako pliki (np. test.in), i puszczaj tak:
> ./program **<** test.in

oszczędzisz sobie literówek i nie będziesz musieć nic przepisywać.
Strzałka `<` to bashowy redirect, przeczytasz o nim więcej [tutaj](https://www.gnu.org/software/bash/manual/html_node/Redirections.html).

## Jasio przepisuje kolejne testy 
Jesteś już doświadczonym zawodnikiem, więc od dawna wiesz że zielony werdykt na przykładowym to tylko pułapka na naiwniaków.
Rysujesz więc kilka testów na kartce i znów przepisujesz.

Na chwilę przed końcem konkursu robisz szybką poprawkę, bo widzisz że program trochę zamula...
Wysyłasz na sprawdzarkę, jest zielono, ale punktów po odsłonięciu wyników tylko 50...

Dobijając wychodzi, że testy z kartki nie przechodziły, a nie chciało ci się ich sprawdzić drugi raz.
Je też zapisuj jako pliki (np. 1.in), **wyniki też zapisuj**, bo jeszcze je zapomnisz (np. do pliku 1.out).

> ./program < 1.in > wzor.out
> 
> **cmp** wzor.out 1.out 

Albo nic się nie stanie - wtedy wygrałeś. Jak nie, to zobaczysz linijkę tego typu:
> wzor.out 1.out differ: byte 3, line 1

i od razu wiesz że pierwszy błąd jest w 3 znaku pierwszej linijki.
Jeśli chcesz dodatkowo zobaczyć różnicę między plikami możesz zamiast `cmp` użyć polecenia `diff`.

## Jasio myśli o maturze... 

Oczywiście zauważyłeś, że żeby słowo było **buńczuczne** wystarczy sprawdzić trzy przypadki.
Myślisz o submicie, ale przypominasz sobie słowa starszego kolegi z klasy maturalnej: *gdybym tylko przetestował z brutem...*
Na myśl o pisaniu matury z informatyki łapią cię ciarki. Spisujesz na szybko bruta, porównujesz na ręcznych. Wszystko działa...

Ale czy na pewno? Przypominasz sobie o studencie co był na kółku i gadał coś o losowaniu testów jak jeszcze nie wiedziałeś co to tablica. Myślisz - no więcej testów to chyba lepiej cnie?

Zamykasz oczy, twoja fotograficzna pamięć pokazuje ci magiczne linijki napisane przez studenta na tablicy:

```cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch()).count());
// Zwraca losową liczbę całkowitą z przedziału [l, r].
int R(int l, int r) {
    return uniform_int_distribution<>(l, r)(rng);
}
```

 <details>
    <summary> Dlaczego tak, a nie rand() + srand(time(0))? </summary>

---

1. `rand()`:
- nie gwarantuje losowania z równym prawdopodobieństwem
- na niektórych platformach zwraca tylko liczby z przedziału [0, 2^16] m.in. na sprawdzarce [codeforces](https://codeforces.com/).

2. `time(0)`:
- zwraca ile sekund minęło od [początku epoki unixa (unix epoch)](https://en.wikipedia.org/wiki/Unix_time) czyli początku roku 1970.
W efekcie testy wygenerowane w tej samej sekundzie będą identyczne, a my chcemy setki na sekundę.
- Cała linijka `chrono::steady_clock::now().time_since_epoch().count()` robi to samo co `time(0)`, ale zwraca czas w **nanosekundach** a nie **sekundach**.
- Jak zapamiętać tę paskudnie długą linijkę? 
    - `chrono` potrzebuję **czasu** więc
    - `::steady_clock` patrzę na **zegarek**
    - `::now()` która godzina **teraz**
    - `.time_since_epoch()` ile to czasu od unixowego **epochu**.
    - `count()` **licząc** w nanosekundach
---
</details>

Piszesz więc program, który generuje losowe słowa długości n i chrzcisz go szlachetną nazwą `generatorka.cpp`
```cpp
// generatorka.cpp
mt19937 rng(chrono::steady_clock::now().time_since_epoch()).count());
// Zwraca losową liczbę całkowitą z przedziału [l, r].
int R(int l, int r) {
    return uniform_int_distribution<>(l, r)(rng);
}
int main() {
    int n = R(1, 10);
    for (int i = 0; i < n; i++) cout << (char)R('a', 'z');
}
```

Po chwili namysłu uznajesz, że jednak sensowne są tylko testy z literek `E`, `P`, `I` oraz `C`, więc
zmieniasz kod na
```cpp
...
string alpha = "EPIC";
int main() {
    int n = R(1, 10);
    for (int i = 0; i < n; i++) cout << alpha[R(0, 3)]; 
}
```

Kompilujesz i nawalasz w kółko:
``` 
./generatorka > test.in
./wzorcowka < test.in > wzor.out
./brut < test.in > brut.out
cmp wzor.out brut.out
```

Szybko ci się to nudzi, co robisz?

<details>
<summary>(a) (trait: script kiddie) Piszesz skrypt testujący w bashu </summary>

---

```sh
for ((i=0;;i++)); do
    ./generatorka > test.in
    ./wzorcowka < test.in > wzor.out
    ./brut < test.in > brut.out
    cmp wzor.out brut.out || exit 1
    echo "[OK] $i"
done
```

Chyba strasznie nie wygląda? 
Program wywala się jak `cmp` skończyło się z niezerowym kodem, w sczególności gdy pliki się różnią,
a cmp wypisuje dlaczego. 
`echo` wypisuje tekst jaki mu każemy. `$i` wstawia wartość zmiennej jako tekst. 

To tyle.

---

</details>

<details>
<summary>(b) (trait: afraid of bash) Piszesz skrypt testujący w C++.</summary>

---

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int i = 0;; ++i) {
        system("./generatorka > test.in");
        system("./wzorcowka < test.in > wzor.out");
        system("./brut < test.in > brut.out");

        if (system("cmp wzor.out brut.out") != 0) {
            cout << "[FAIL]" << i << endl;
            return 1;
        }

        cout << "[OK] " << i << endl;
    }
}
```

Tak, `system(...)` po prostu odpala komendę bashową i zwraca jej exit-code...
Niezerowy znaczy, że cmp znalazło jakieś różnice.

---
</details>

<details>
<summary>(c) (trait: out of the box thinker) Dodajesz testkejsy do zadania.</summary>

Przerabiasz swój kod z:
```cpp
...
int main() {
    > kod rozwiązujący zadanie <
}
```

na 

```cpp
void solve() {
    > kod rozwiązujący zadanie <
}

int main() {
    int tests = 1;
    cin >> tests;
    while (tests--) solve();
}
```

I generujesz generatorką np. 1000 testów na jeden plik.
Przed submitem wykomentowujesz `cin >> tests`, i działa jak normalne zadanie.

- Plus: Testuje się najszybciej z wszystkich sposobów.
- Minus: Jak masz globalne zmienne, to niekoniecznie będzie takie hop-siup.

---
</details>

Po trzystu testach wywaliło WA, okazało się, że przypadki były dobre, 
ale dałeś w jednym miejscu `i zamiast `j` i wszystko się sypało...

Poprawiasz, odpalasz testy jeszcze raz, i wywala na tym samym... Co jest??


A, no tak, zapomniałeś przekompilować rozwiązanie. Żeby tego nigdy nie zapomnieć
dodajesz linijkę `make wzorcowka && make brut && make generatorka` do skryptu.


## Jasio wbił zadanko.
Tyle wystarczy, żeby wyłapać prawie wszystkie błędy w naszym rozwiązaniu.
To absolutne minimum, żeby nie spalić przez nieuwagę ważnego zadania na II etapie,
dlatego Jasio zaczął tak testować każde zadanie na treningach. 
Po piątym napisanie skryptu z brutem zajmuje mu już tylko 7 minut, 
a wcześniej jak zobaczył WA po submicie to była pora na CSka.

Niżej jeszcze garść pytań, na które fajnie znać odpowiedź:

<details>
<summary> Jak złapać błędy typu "zapomniałem o long longach"?</summary>

Dajesz w brucie 

```cpp
#include <bits/stdc++.h>
#define int long long

...

int32_t main() {
    ...
}

``` 

żeby nadal się kompilowało bez warningów typ funkcji main() zmieniasz na int32_t.
Możesz też dać po prostu samo main(), też się skompiluje, ale z warningiem.

W szczególności można tak przetestować poprawność "brut bez long longów" vs "brut z long longami",
nawet jak nie mamy wzorcówki.

---

</details>


<details>
<summary> Jak zmierzyć ile dokładnie czasu i pamięci zużywam na teście?</summary>

---

Disclaimer: [`time` to nie to samo co `/usr/bin/time`](https://askubuntu.com/questions/1054456/what-is-the-difference-between-time-and-usr-bin-time)!
O tak: 

```sh
/usr/bin/time ./rozw < test.in > rozw.out`
```

Wypluje nam to coś takiego:

0.55user 0.01system **0:00.56elapsed** 100%CPU (0avgtext+0avgdata **1700maxresident)k**
0inputs+8outputs (0major+94minor)pagefaults 0swaps

Pierwsze pogrubione to łączny czas wykonania, a drugie to maksymalne użycie pamięci w kilobajtach.

Jak wczytamy się w instrukcję (otwieramy ją robiąc `man /usr/bin/time`),
to zobaczymy, że możemy zrobić z tego coś bardziej czytelnego dodając flagę 
-v, albo jeszcze lepiej, formatując wyjście tak jak chcemy:

`/usr/bin/time -f "%es %MKB"`,
wtedy wypisze po prostu `0.56s 1700KB`

---

</details>

<details>
<summary> Jak wygenerować losowe drzewo?</summary>

---

Najprościej generować je tak:

```cpp
    int n = R(1, MAXN);
    cout << n << "\n";
    for (int i = 2; i <= n; i++)
        cout << R(1, i-1) << " " << i << "\n";
```

Jak widać generujemy drzewo tak, że zawsze dołączamy i-ty wierzchołek do losowego
wierzchołka drzewa.

Disclaimer: Losowe drzewo ma oczekiwaną średnicę $$O(\sqrt{n})$$, więc jeśli nasz algorytm działa w czasie zależnym od długości ścieżek to czas będzie zaniżony i makstest lepiej wygenenerować inaczej, np. robiąc.

```cpp
    for (int i = 2; i <= n; i++)
        cout << R(max(1, i-5), i-1) << " " << i << "\n";
```
Tu już będzie średnica conajmniej $$O(n/5)$$.

---

</details>

<details>
<summary> Jak wygenerować losowy **spójny** graf?</summary>

---

Losujemy losowe drzewo tak jak wyżej a potem dolosowujemy krawędzie.
    
```cpp
    int n = R(1, MAXN), m = R(n-1, MAXM);
    cout << n << "\n";
    
    set<pair<int,int>> edges;
    auto add_edge = [&](int a, int b) {
        cout << a << " " << b << "\n";
        edges.insert({a, b});
        edges.insert({b, a});
    };
    for (int i = 2; i <= n; i++) {
        add_edge(R(1, i-1), i);
    }

    m -= n-1;
    while (m--) {
        int a = R(1, n-1);
        int b = R(a+1, n);
        while (s.count({a, b})) {
            a = R(1, n-1);
            b = R(a+1, n);
        }

        add_edge(a, b);
    }
```

---

</details>

<details>
<summary> Jak wygenerować losową permutację?</summary>

---

```cpp
#include <algorithm>
#include <random>
#include <chrono>

int main() {
    int n = 10;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = i+1;
    shuffle(v.begin(), v.end(), rng);
    for (auto i : v) cout << i << " ";
```
---

</details>

<details>
<summary> Jak wygenerować losowy podzbiór $k$-elementowy?</summary>

---

Robimy sobie tablicę z $k$ jedynkami i $n-k$ zerami, robimy na niej `shuffle()`,
i do losowanego zbioru bierzemy te elementy, którym przypisaliśmy jedynkę.

---

</details>

<details>
<summary> Jak wygenerować losowe testy o sumie po $n$ równej conajwyżej $$10^6$$?</summary>

---

Powiedzmy, że suma $n$ z wszystkich przypadkach testowych ma być równa $S$, i chcemy mieć, $t \leq n$ przypadków testowych.
Niech $n_i$ oznacza $n$ w $i$-tym przypadku.

### Sposób 1:

```cpp
S = R(1, MAXS);
t = R(1, S);
cout << t << "\n";
for (int i = 1; i < t; i++) {
    // Musimy mieć S 
    int n = R(1, S - t);
    S -= n;
    ... generuj test dla n ...
}

... generuj oostatni test o n = S ...

```
Minus: Statystycznie każdy kolejny test ma dwukrotnie mniejsze $n$, więc po $O(log(s))$ testach wszystkie mają $n = 1$.

### Sposób 2:

```cpp
int S  = R(1, MAXS);
int t = R(1, S);

cout << t << "\n";
vector<int> test_n(t, 1);
S -= t;
while (t--) {
    test_n[R(0, t-1)]++;
}

for (auto n : test_n)
    ... generuj test dla n ...
```

Minus: Tu z reguły dostaniemy tylko testy o $n = O(n / t)$.

### Sposób 3:

```cpp
S = R(1, MAXS);
t = R(1, S);
vector<int> podzial(S, 1);
for (int i = 1; i < t; i++) podzial.push_back(0);
shuffle(podzial.begin(), podzial.end(), rng);
int n = 1;
for (auto i : podzial) {
    if (i == 1) n++;
    else {
        ... generuj test dla n ...
        n = 1;
    }
}

n++;
... generuj ostatni test dla n ...
```

Tu dostajemy już równy rozkład, po prostu dzielimy $n$ na $t$ niezerowych części [(Stars and bars)](https://en.wikipedia.org/wiki/Stars_and_bars_(combinatorics)). 

---

</details>

<details>
<summary> Skrypt się wiesza, co robić?</summary>

---

Czasem zdarza się, że testowany program ma jakąś nieskończoną pętlę i klikanie CTRL+C nie 
wystarcza, bo skrypt czeka z obsługą CTRL+C aż wywoływany program się skończy.
Możemy dodać do skryptu testującego taką linijkę, żeby nie czekał tylko od razu zabijał.

```sh
trap 'echo "Aborted."; pkill -P $$; exit 1' INT
```

---

</details>

<details>
<summary> Wywaliło mi `Segmentation fault`. Dlaczego? </summary>

---

Najprościej znaleźć przyczynę używając `gdb`.
1. Kompilujemy program z flagą `-g` (bez tego kompilator usunie nazwy zmiennych i info o tym, która linijka kodu się wykonuje).
2. Odpalamy `gdb ./program`
3. Wpisując `run` odpalamy program, najlepiej zrobić od razu `run < test.in` z testem, który segfaultuje.
4. Po wpisaniu inputu zobaczymy, że program się wywala z kilkoma dodatkowymi informacjami.
5. Wpisujemy `backtrace` albo krocej - `bt`, wtedy zobaczymy stos wywołań funkcji i zobaczymy w której dokładnie linijce kod się wywalił.

---

</details>

<details>
<summary> Zapominałem jak się używa jakiejś komendy. Co począć? </summary>

---

Dokumentację (manual) praktycznie każdego polecenia w terminalu możemy sprawdzić wpisując w terminalu `man <polecenie>`, w szczególności można sobie przeczytać `man man`.
Można tam znaleźć sporo przydatnych rzeczy, flag itp.

---

</details>

<details>
<summary> Co jak w zadaniu jest wiele poprawnych odpowiedzi? </summary>

---

Typowo dopisuje się wtedy program nazywany czekerką, który wczytuje test i wyjście zarówno z bruta i wzorcówki
i sprawdza czy wszystko się zgadza, przykładowa czekerka:

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "usage: ./czekerka test.in brut.out wzo.out";
    }

    ifstream test(argv[1]);
    ifstream brut(argv[2]);
    ifstream wzo(argv[3]);

    int x, y, wynik_brut, wynik_wzo;

    test >> x >> y;
    brut >> wynik_brut;
    wzo >> wynik_wzo;

    if (brut != wzo) {
        cout << "FAIL\n";
    } else {
        cout << "OK\n";
    }

}


```

---

</details>
