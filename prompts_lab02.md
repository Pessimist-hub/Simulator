# Prompturi folosite (Lab 02)

LLM folosit: Claude (Anthropic).

## Prompturi

### Prompt 1: ce trebuie facut la Lab 2
Am intrebat cum fac Lab 2, pe baza fisierelor .hpp create la Lab 1, in Visual
Studio 2022, si am cerut explicatie pas cu pas, ca sa inteleg despre ce e
vorba (clase, fisiere .cpp, Makefile).

**Rezultat:** am primit explicatia cerintei (ce se puncteaza) si pasii:
creare ramura lab2, adaugare fisiere .cpp, creare Makefile, compilare prin
linia de comanda, .gitignore, actualizare README.md, push si pull request.

### Prompt 2: fisierele .cpp si Makefile
Am cerut fisierele .cpp corespunzatoare fiecarui .hpp de la Lab 1, plus un
Makefile, in stilul din cerinta laboratorului (asemanator cu exemplul
SnakeGame din Lab 2).

**Rezultat:** cate un .cpp pentru fiecare structura (Point, Item, Player,
Map, EventListener, Renderer, AudioController, GameEngine) si Makefile.

### Prompt 3: simplificarea codului
Am cerut varianta simpla a fisierelor .cpp, fara logica de joc completa -
doar metodele implementate cu cod minim, ca sa pot explica usor la
laborator ca jocul nu trebuie sa fie complet functional, doar sa se
compileze corect.

**Rezultat:** fisiere .cpp cu functii goale sau cu cod minim (return 0,
std::cout simplu), conform semnaturilor din .hpp.

### Prompt 4: compilare si Git
Am intrebat cum compilez proiectul in consola (make, g++), cum repar erori
de compilare si cum fac merge intre ramurile main si lab2.

## Erori intalnite si fixari
- **`make` nu era recunoscut in Developer Command Prompt:** am folosit
  terminalul MSYS2 UCRT64, unde era instalat `make` de la laboratorul
  anterior.
- **Fisier `MakeFile` in loc de `Makefile`:** `make` nu-l gasea din cauza
  numelui gresit (litere mari/mici). L-am redenumit cu `mv MakeFile Makefile`.
- **`Point.cpp: No such file or directory`:** fisierele .cpp nu erau inca
  adaugate in folderul proiectului. Le-am adaugat din Visual Studio
  (Add > Existing Item).
- **Fisier dublu `point.hpp` si `Point.hpp`:** pe GitHub (case-sensitive)
  apareau ca doua fisiere diferite. Am sters varianta cu litere mici.
- **`IslandCleaner.exe` blocat de Windows (Smart App Control):** am adaugat
  folderul proiectului ca exceptie in Windows Security si am rulat
  executabilul direct, nu doar prin dublu-click.
- **Conflict la `git push` (branch-urile `main` si `lab2` au divergat):**
  am facut `git merge main -m "..."` si apoi `git push --force-with-lease`,
  dupa ce am verificat ca varianta locala e cea corecta.
- **Vim deschis pentru mesajul de merge:** nu stiam sa folosesc Vim (trebuia
  apasat `i` inainte de a scrie, apoi `Esc` si `:wq`). Am invatat sa dau
  mesajul direct in comanda, cu `-m "mesaj"`, ca sa evit Vim complet.

## Ce am verificat eu
- Am compilat cu `make clean` si `make`, fara erori.
- Am verificat ca `.gitignore` nu lasa `.o` si `.exe` sa ajunga pe GitHub.
- Am verificat ca README.md contine sectiunea de build.
- Am verificat pe GitHub ca toate fisierele .cpp si Makefile sunt pe ramura
  `lab2`.