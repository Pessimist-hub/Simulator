# Simulator
Island Cleaner Simulator
## Ideea jocului
Playerul se trezeste singur, fără să știe cum a ajuns acolo. Insula cindva era nu poluata, dar acum e plină de gunoaie și murdărie peste tot. I se spune (printr-un mesaj sau un semn găsit pe plajă) că nu poate pleca de pe insulă până nu o curăță complet.
Scopul jocului: strângi tot gunoiul de pe insulă ca să poți scăpa de acolo.
Cum se joacă
Te miști pe insulă cu W A S D
Când te apropii de un gunoi, îl iei automat (sau apeși E)
Pentru fiecare gunoi luat primești câteva puncte/coinuri
Cu coinurile astea poți cumpăra upgrade-uri, ca să te ajute să cureți mai repede (de exemplu iei gunoiul de la o distanță mai mare, sau te miști mai repede)
Când ai luat tot gunoiul de pe insulă, apare o barcă (sau un portal) prin care poți pleca asta e finalul jocului
De ce coinuri și upgrade-uri
Ca să nu fie plictisitor doar să aduni gunoi fără sens, o sa fie un sistem de recompensă. Cu cât cureți mai mult, cu atât progresezi mai repede.
Idei de upgrade:
Playerul o sa poata  sa ia gunoiul la distanta
Viteză de mișcare mai mare
Un fel de magnet care atrage gunoiul din jur
Upgrade la cos de gunoi
Player care se mișcă pe hartă
Gunoaie puse prin diferite locuri de pe insulă când player-ul dă de ele, dispar și adaugă puncte
Un contor care ține minte câte gunoaie au mai rămas
Un contor pentru coinuri
Când gunoiul a ajuns la 0, apare barca/portalul și jocul se termină


## Point
x, y, z
DistanceTo
## Item
name
position
value
## Player
position
coins
movementSpeed
pickupRange
Move, BuySpeed, BuyRange
## Map
width, depth
trash (vector<Item>)
Init, TrashLeft, Collect
## AudioController
PlayPickup
## GameEngine
Init
Run
## EventListener
GetEvent
## Renderer
Clear
PutText
DrawMap
## AbstractRenderer
Clasa abstractă de bază pentru Renderer (Clear, PutText, DrawMap sunt funcții virtuale pure)


## Lab 3: Constructori și operatori

În această lucrare au fost adăugați constructori și operatori pentru structurile care reprezintă elemente de joc, iar pentru clasa responsabilă de redare a fost creată o clasă de bază abstractă.

### Ce s-a adăugat

| Structură | Constructori | Operatori |
|---|---|---|
| `Point` | implicit și cu parametri `Point(x, y, z)` (valori implicite 0), de copiere | `=`, `==`, `!=`, `>>`, `<<` |
| `Item` | implicit, cu parametri `Item(name, position, value)`, de copiere | `=`, `==`, `!=`, `>>`, `<<` |
| `Player` | implicit, cu parametri `Player(position, coins, speed, range)`, de copiere | `=`, `==`, `!=`, `>>`, `<<` |
| `Map` | implicit, cu parametri `Map(width, depth)`, de copiere | `=`, `==`, `!=`, `>>`, `<<` |

### Detalii

- **Constructorul implicit și cel cu parametri** inițializează câmpurile prin lista de inițializare (`: x(_x), y(_y)`).
- **Constructorul de copiere** creează un obiect nou dintr-unul existent (`Point b = a;`).
- **Operatorul de atribuire `=`** copiază câmpurile într-un obiect care există deja (`b = a;`) și returnează `*this`.
- **Operatorii `==` și `!=`** compară obiectele câmp cu câmp. Operatorii structurilor mari îi refolosesc pe cei ai structurilor mici (`Item` folosește `Point::operator==`).
- **Operatorii `>>` și `<<`** sunt funcții în afara clasei, ca să funcționeze cu `std::cin` și `std::cout`. `Map` se citește astfel: lățime, adâncime, numărul de iteme, apoi itemele. Numele unui `Item` se citește ca un singur cuvânt (fără spații).
- **`AbstractRenderer`** (fișier `AbstractRenderer.hpp`) conține funcții virtuale pure și destructor virtual. Clasa `Renderer` moștenește din ea și implementează funcțiile cu `override`.

### Exemplu de utilizare

```cpp
Point a(1, 2, 3);
Point b = a;          // constructor de copiere
Point c;
c = a;                // operator=
std::cout << b << "\n";            // 1 2 3
std::cout << (a == c) << "\n";     // 1

Item bottle("Bottle", Point(2, 0, 5), 10);
std::cout << bottle << "\n";       // Bottle 2 0 5 10
```


## Cum se construiește proiectul

Proiectul folosește un Makefile și compilatorul g++ (MinGW).

1. Deschide consola în folderul proiectului.
2. Pentru a curăța fișierele vechi:
   make clean
3. Pentru a construi proiectul:
   make
4. Se va crea fișierul IslandCleaner.exe, plus fișiere .o (obiect) pentru fiecare
   fișier .cpp.
5. Rulează jocul cu:
   ./IslandCleaner.exe

Notă: după ce modifici un fișier `.hpp`, rulează `make clean` înainte de `make`, pentru ca toate fișierele să fie recompilate.