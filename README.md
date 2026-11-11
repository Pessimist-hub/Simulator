# Island Cleaner Simulator

Un proiect C++ despre un jucător care curăță o insulă de deșeuri. Acest
repository este dezvoltat în cadrul laboratoarelor de programare C++.

> **Starea proiectului:** codul conține modelele de bază ale jocului și o
> demonstrație a operațiilor C++. Mecanici precum mișcarea jucătorului,
> cumpărarea upgrade-urilor și redarea hărții sunt încă în lucru.

## Despre joc

Jucătorul explorează insula și adună deșeurile pentru a o curăța. Ideile
prevăzute pentru joc includ:

- deplasarea pe hartă cu tastele `W`, `A`, `S`, `D`;
- colectarea deșeurilor și obținerea de monede;
- upgrade-uri pentru viteză și distanța de colectare;
- afișarea numărului de obiecte rămase;
- încheierea jocului după curățarea insulei.

## Structura proiectului

| Componentă | Responsabilitate |
|---|---|
| `Point` | Coordonate 3D și calculul distanței |
| `Item` | Numele, poziția și valoarea unui obiect |
| `Player` | Poziția, monedele și parametrii jucătorului |
| `Map` | Dimensiunile hărții și obiectele de pe insulă |
| `GameEngine` | Inițializarea și rularea jocului |
| `Renderer` | Interfața de afișare a hărții și a textului |
| `EventListener` | Preluarea evenimentelor de intrare |
| `AudioController` | Gestionarea sunetelor |

## Laboratorul 5 — Module, biblioteci și SQLite

Clasele de date sunt construite în biblioteci statice separate: `libpoint.a`,
`libitem.a`, `libplayer.a` și `libmap.a`. Aplicația folosește biblioteca
externă SQLite pentru a salva și încărca dimensiunile hărții și obiectele de
pe insulă în `island_cleaner.db`. La pornire, demonstrația salvează harta în
SQLite și o citește înapoi.

### Dependențe

- `g++` compatibil cu C++17
- GNU Make
- SQLite 3 (header-ele și biblioteca de dezvoltare, inclusiv `sqlite3.h` /
  `-lsqlite3`)

În MSYS2 UCRT64, SQLite poate fi instalat cu:

```sh
pacman -S mingw-w64-ucrt-x86_64-sqlite3
```

### Construire și rulare

Din terminalul MSYS2 UCRT64, în directorul proiectului:

```sh
make clean
make
./IslandCleaner.exe
```

Bibliotecile și fișierele obiect sunt generate la build și nu trebuie adăugate
în Git. Baza de date creată de program rămâne locală și este ignorată de Git.

## Laboratorul 4 — Biblioteca standard C++ și STL

Codul folosește elemente din biblioteca standard C++ pentru gestionarea
datelor și resurselor:

- `std::vector` pentru colecția de obiecte;
- `std::string` pentru text;
- fluxuri de intrare și ieșire (`std::istream`, `std::ostream`);
- referințe și `std::unique_ptr` pentru lucrul cu obiecte;
- algoritmi STL pentru sortare, căutare, copiere și filtrare.

Programul demonstrează aceste operații prin afișarea obiectelor, sortarea
numelor și căutarea unui obiect.

## Laboratorul 3 — Constructori și operatori

Pentru structurile jocului au fost implementați constructori și operatori de
comparare, atribuire și flux:

| Tip | Constructori | Operatori |
|---|---|---|
| `Point` | implicit, cu parametri, de copiere | `=`, `==`, `!=`, `>>`, `<<` |
| `Item` | implicit, cu parametri, de copiere | `=`, `==`, `!=`, `>>`, `<<` |
| `Player` | implicit, cu parametri, de copiere | `=`, `==`, `!=`, `>>`, `<<` |
| `Map` | implicit, cu parametri, de copiere | `=`, `==`, `!=`, `>>`, `<<` |

`AbstractRenderer` definește interfața abstractă pentru redare, iar
`Renderer` o implementează.
