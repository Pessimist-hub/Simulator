# Prompturi folosite (Lab 01)

LLM folosit: Claude (Anthropic).

## Prompturi

### Prompt 1: ideea jocului
Am descris jocul "Island Cleaner" (3D): jucătorul se trezește pe o insulă
plină de gunoaie, strânge gunoiul cu W A S D și E, primește coinuri și
cumpără upgrade-uri; când gunoiul ajunge la 0 apare o barcă. Am cerut
scripturi simple (max 30-50 linii) în stilul din laborator: GameEngine,
Renderer, EventListener etc.

**Rezultat:** scripturi în C# (Unity) + README.md. Le-am verificat structura
și am cerut varianta în C++, cum cere laboratorul.

### Prompt 2: varianta C++
Am cerut aceleași scripturi în C++ (fișiere .hpp și .cpp).

**Rezultat:** structurile Point, Item, Player, Map, EventListener, Renderer,
AudioController, GameEngine și main.cpp.

### Prompt 3: coordonate 3D
Jocul e 3D, deci am cerut ca poziția să aibă 3 coordonate și codul să fie
ușor de extins.

**Rezultat:** Point cu x, y, z și funcția DistanceTo (distanța în spațiu),
Item cu nume și poziție 3D, harta cu width și depth.

### Prompt 4: rulare și explicatii
Am întrebat cum compilez jocul în Visual Studio și în VS Code, apoi am cerut
explicații pentru fiecare linie de cod și pentru fiecare fișier .hpp, ca să
le pot explica la laborator.

## Erori Intilnite și fixari
- **Visual Studio nu găsea șabloane C++:** nu era instalat workload-ul
  "Desktop development with C++". L-am instalat din Visual Studio Installer.
- **`pacman` dădea "target not found":** am copiat din text un punct în plus
  la sfârșitul comenzii. Am scris comanda fără punct și s-a instalat g++.
- **Nume diferit între fișier și #include:** `point.hpp` vs `Point.hpp`.
  Am făcut numele la fel peste tot.
- **Fișier dublu `Engine.hpp` și `GameEngine.hpp`:** am păstrat doar
  `GameEngine.hpp`.
- **.gitignore:** am verificat că `*.exe` e ignorat, ca `joc.exe` să nu ajungă
  pe GitHub.

## Ce am verificat eu
- Am compilat cu `g++ -std=c++17 *.cpp -o joc` și am rulat jocul în terminal.
- Am testat mișcarea, luarea gunoiului și scăderea contorului de gunoi.