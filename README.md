# Island Cleaner Simulator — PlayGame

Aceasta este ramura **`playgame`**, versiunea interactiva 3D a proiectului.
Este dezvoltata separat de laboratoarele predate: `lab05` si ramurile
laboratoarelor anterioare raman neschimbate. Jocul porneste de la modelele de
date realizate in laboratoare si le foloseste in aplicatia raylib.

## Cerinte

- Windows 64-bit si MSYS2 UCRT64
- `g++`, GNU Make si raylib 5

Instaleaza raylib in MSYS2 UCRT64, daca nu este deja instalata:

```sh
pacman -S mingw-w64-ucrt-x86_64-raylib
```

## Construire si rulare

Deschide terminalul **MSYS2 UCRT64**, mergi in directorul repository-ului si
ruleaza:

```sh
make clean
make
./IslandCleaner.exe
```

Din PowerShell, daca `make` nu este in `PATH`, foloseste executabilul instalat
de MSYS2:

```powershell
C:\msys64\usr\bin\make.exe clean
C:\msys64\usr\bin\make.exe
.\IslandCleaner.exe
```

Porneste jocul din directorul repository-ului, ca sa poata gasi modelele din
`Assets/Trash`. Executabilul si bibliotecile statice sunt generate local si
nu trebuie adaugate in Git.

## Cum se joaca

- Alege **Start Joc** din meniul principal.
- Misca jucatorul cu `W`, `A`, `S`, `D`.
- Tine apasat `Shift` in timp ce te misti pentru sprint; stamina se consuma
  si se regenereaza automat cand mergi normal sau stai pe loc.
- Deplasarea este la viteza normala, jucatorul se roteste spre directia de mers
  si obiectele apropiate sunt colectate automat. Personajul are brate si
  picioare articulate, animate in directia deplasarii.
- Apasa `U` sau butonul **Upgrade-uri** pentru magazin. Jocul continua in timp
  real cat timp magazinul este deschis; `U` sau `Esc` il inchide.
- Cumpara upgrade-uri de viteza, raza de colectare, castig de monede,
  capacitate de stamina si regenerare cu monedele obtinute.
- Fiecare tip de gunoi ofera monede in functie de valoarea sa; upgrade-ul de
  castig inmulteste recompensa primita.
- Curata toate obiectele pentru a vedea ecranul de victorie.
- Alege **Iesire** din meniu sau inchide fereastra pentru a opri jocul.

## Continutul jocului

- Insula 3D de 50 × 40 de unitati si 40 de obiecte colectabile.
- Zece modele GLB de deseuri, convertite din modelul FBX furnizat, aflate in
  `Assets/Trash`.
- Meniu principal, magazin de upgrade-uri si ecran de victorie.
- Clasele de date se construiesc in biblioteci statice; codul meniului,
  motorului, evenimentelor si redarii se afla in fisierele `.cpp` si `.hpp`
  din directorul repository-ului.

## Separarea ramurilor

- **`playgame`** — aplicatia interactiva 3D si fisierele sale.
- **`lab05`** — lucrarea despre biblioteci si SQLite.
- **`lab04`**, **`lab03`** si celelalte ramuri — lucrarile de laborator
  respective.

Schimbarea sau testarea jocului in `playgame` nu modifica ramura `lab05`.
