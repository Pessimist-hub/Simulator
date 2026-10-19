# Prompturi folosite (Lab 03)

LLM folosit: Claude (Anthropic).

## Prompturi

### Prompt 1: ce trebuie facut la Lab 3
Am atasat cerinta din Moodle (Constructori si Operatori), textul laboratorului
de la profesor (exemplul SnakeGame) si linkul spre repository-ul meu. Am cerut
ca Claude sa se comporte ca profesor de C++ si sa-mi dea cod simplu, cu
explicatii, ca sa inteleg despre ce este vorba.

**Rezultat:** am primit explicatia cerintei (constructor implicit, cu
parametri, de copiere, operator de atribuire, de comparare, de citire si
afisare, clasa abstracta de baza) si un exemplu complet pe clasa Point, cu
explicatii pentru fiecare element. Claude nu a putut deschide linkul GitHub,
asa ca mi-a cerut fisierele.

### Prompt 2: adaptarea la proiectul meu
Am trimis captura repository-ului si continutul fisierelor .cpp, .hpp,
Makefile si README.md, ca sa adapteze exemplul profesorului la proiectul meu
(Island Cleaner Simulator).

**Rezultat:** cod pentru Point, Item, Player si Map (constructori, operatorii
`=`, `==`, `>>`, `<<`), clasa abstracta AbstractRenderer (functii virtuale
pure) si Renderer care o mosteneste. Claude a observat ca regulile din
Makefile nu au dependente, deci este nevoie de `make clean` inainte de `make`.

### Prompt 3: verificarea cerintelor
Am intrebat daca a fost inclus tot ce se cere la Lab 3.

**Rezultat:** Claude a verificat cerintele una cate una si a observat ca
lipsea operatorul `!=` (in Moodle scrie "operatori de comparare", la plural).
Am adaugat `!=` la Point, Item, Player si Map, bazat pe `==`.

### Prompt 4: pasii in Visual Studio 2022
Am spus ca lucrez in Visual Studio 2022 si am cerut ajutor pas cu pas.

**Rezultat:** pasii: salvare, terminal in Visual Studio, creare ramura lab03,
modificarea fisierelor in ordine, crearea fisierului nou AbstractRenderer.hpp,
compilare cu `make clean` si `make` in terminal, test in Main.cpp, commit,
push si Pull Request.

### Prompt 5: conflicte la Pull Request
Am atasat captura paginii de pe GitHub cu conflictele din Pull Request #3
(Item.cpp, Map.cpp, Player.cpp, Point.cpp, Renderer.cpp).

**Rezultat:** explicatia de ce apar conflictele (ramura lab03 pornita din lab2,
iar main contine aceleasi fisiere modificate altfel) si cum se rezolva:
"Accept current change" (versiunea din lab03), verificarea ca au disparut
marcajele `<<<<<<<`, `=======`, `>>>>>>>`, apoi "Mark as resolved" si
"Commit merge".

### Prompt 6: README.md si acest fisier
Am cerut sectiunea despre Lab 3 pentru README.md si fisierul prompts_lab03.md,
in acelasi stil ca la Lab 2.

**Rezultat:** README.md actualizat si acest fisier.

## Erori intalnite si fixari
- **Conflicte in Pull Request #3 (5 fisiere .cpp):** `lab03` a fost creata din
  `lab2`, iar `main` avea versiuni diferite ale acelorasi fisiere. Am rezolvat
  conflictele pe GitHub, alegand "Accept current change" (versiunea din
  `lab03`), dupa ce am comparat cele doua variante.
- **Makefile fara dependente:** regulile nu urmaresc fisierele .hpp, deci
  `make` nu recompila fisierele deja construite. Am rulat `make clean` inainte
  de fiecare `make`.

## Ce am verificat eu
- Am compilat cu `make clean` si `make`, fara erori.
- Am rulat `IslandCleaner.exe` si am verificat exemplul din `Main.cpp`
  (constructor de copiere, `=`, `==`, `<<`).
- Am verificat ca `.gitignore` nu lasa `.o` si `.exe` sa ajunga pe GitHub.
- Am verificat ca README.md contine sectiunea Lab 3 si sectiunea de build.
- Am verificat pe GitHub ca Pull Request-ul nu mai are conflicte.