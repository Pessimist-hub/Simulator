# Prompturi folosite (Lab 01)

LLM folosit: Claude (Anthropic).

## Prompturi

### Prompt 1: ideea jocului
Am descris jocul "Island Cleaner" (3D): juc?torul se treze?te pe o insul?
plin? de gunoaie, str?nge gunoiul cu W A S D ?i E, prime?te coinuri ?i
cump?r? upgrade-uri; c?nd gunoiul ajunge la 0 apare o barc?. Am cerut
scripturi simple (max 30-50 linii) ?n stilul din laborator: GameEngine,
Renderer, EventListener etc.

**Rezultat:** scripturi ?n C# (Unity) + README.md. Le-am verificat structura
?i am cerut varianta ?n C++, cum cere laboratorul.

### Prompt 2: varianta C++
Am cerut acelea?i scripturi ?n C++ (fi?iere .hpp ?i .cpp).

**Rezultat:** structurile Point, Item, Player, Map, EventListener, Renderer,
AudioController, GameEngine ?i main.cpp.

### Prompt 3: coordonate 3D
Jocul e 3D, deci am cerut ca pozi?ia s? aib? 3 coordonate ?i codul s? fie
u?or de extins.

**Rezultat:** Point cu x, y, z ?i func?ia DistanceTo (distan?a ?n spa?iu),
Item cu nume ?i pozi?ie 3D, harta cu width ?i depth.

### Prompt 4: rulare ?i explica?ii
Am ?ntrebat cum compilez jocul ?n Visual Studio ?i ?n VS Code, apoi am cerut
explica?ii pentru fiecare linie de cod ?i pentru fiecare fi?ier .hpp, ca s?
le pot explica la laborator.

## Erori ?nt?lnite ?i fix?ri
- **Visual Studio nu g?sea ?abloane C++:** nu era instalat workload-ul
  "Desktop development with C++". L-am instalat din Visual Studio Installer.
- **`pacman` d?dea "target not found":** am copiat din text un punct ?n plus
  la sf?r?itul comenzii. Am scris comanda f?r? punct ?i s-a instalat g++.
- **Nume diferit ?ntre fi?ier ?i #include:** `point.hpp` vs `Point.hpp`.
  Am f?cut numele la fel peste tot.
- **Fi?ier dublu `Engine.hpp` ?i `GameEngine.hpp`:** am p?strat doar
  `GameEngine.hpp`.
- **.gitignore:** am verificat c? `*.exe` e ignorat, ca `joc.exe` s? nu ajung?
  pe GitHub.

## Ce am verificat eu
- Am compilat cu `g++ -std=c++17 *.cpp -o joc` ?i am rulat jocul ?n terminal.
- Am testat mi?carea, luarea gunoiului ?i sc?derea contorului de gunoi.