# Prompturi folosite (Lab 04)

LLM folosit: Copilot (asistent AI in VS Code).

Prompturile de mai jos rezuma solicitarile din sesiune; nu sunt transcrieri
exacte ale mesajelor.

## Prompturi

### Prompt 1: adaptarea proiectului la cerinta Lab 4

Am trimis cerinta laboratorului despre utilizarea bibliotecii standard C++ si
am cerut adaptarea proiectului Island Cleaner Simulator. Cerinta solicita
containere STL, fluxuri de intrare/iesire, referinte si smart
pointers, `std::string` si algoritmi STL pentru cautare, sortare, comparare si
copiere. Modificarile trebuiau facute pe ramura `lab04`, inclusiv actualizarea
fisierului de build.

**Rezultat:** proiectul a fost actualizat pentru `std::vector`,
`std::string`, `std::unique_ptr`, fluxuri standard si algoritmi STL. A fost
actualizat Makefile-ul si adaugata sectiunea Lab 4 in README.md.

### Prompt 2: documentarea prompturilor folosite

Am cerut un fisier `prompts_lab04.md` care sa descrie solicitarile,
rezultatele si verificarile facute pentru Lab 4.

**Rezultat:** a fost creat acest fisier. Descrierile sunt rezumate
retrospective, nu transcrieri exacte.

### Prompt 3: verificarea codului si publicarea pe GitHub

Am cerut verificarea codului pentru greseli, documentarea prompturilor si
publicarea modificarilor pe GitHub in ramura `lab04`.

**Rezultat:** revizuite operatiile de citire din fluxuri. Operatorii de
extragere din `Point`, `Item`, `Player` si `Map` au fost corectati astfel incat
sa nu modifice obiectele cand citirea esueaza; `Map` respinge si un numar
negativ de obiecte. Build-ul si rularea programului au fost verificate inainte
de push.

## Verificari

- Proiectul foloseste containere si algoritmi STL, `std::string`, referinte,
  fluxuri si `std::unique_ptr`.
- Makefile-ul foloseste `Main.cpp`, numele real al fisierului principal, si
  include dependentele headerelor.
- Modificarile au fost construite si executabilul a fost rulat.
- Ramura de lucru este `lab04`.

## Observatii

Unele metode erau deja schelet inaintea acestui laborator si raman neimplementate:
`Player::Move`, `Player::BuySpeed`, `Player::BuyRange`, `EventListener::GetEvent`,
metodele din `Renderer` si `AudioController::PlayPickup`. Ele nu tin de
cerintele de utilizare STL rezolvate aici.
