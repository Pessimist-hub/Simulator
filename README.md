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

## Construire și rulare

Este necesar un compilator `g++` compatibil cu C++17 și utilitarul `make`.
Din directorul proiectului, rulează:

```sh
make clean
make
./IslandCleaner.exe
```

`make clean` este opțional la prima construire. Folosește-l pentru a elimina
fișierele generate și a recompila întregul proiect.
