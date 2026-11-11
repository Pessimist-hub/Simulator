# Prompturi folosite (Lab 05)

LLM folosit: Copilot (asistent AI in VS Code).

Prompturile de mai jos rezuma solicitarile din sesiune; nu sunt transcrieri
exacte ale mesajelor.

## Prompt 1: biblioteci si module pentru Lab 5

Am trimis cerinta laboratorului despre crearea si utilizarea bibliotecilor,
care solicita cate o biblioteca statica sau dinamica pentru fiecare clasa de
date, o biblioteca externa pentru grafica sau stocarea datelor, si actualizarea
fisierului de construire. Am cerut aplicarea cerintei pe ramura `lab05`.

**Rezultat:** clasele de date sunt construite separat in biblioteci statice,
iar biblioteca SQLite este folosita pentru salvarea si incarcarea hartii.
Makefile-ul construieste si leaga modulele si SQLite.

## Prompt 2: documentatie si verificare

Am cerut actualizarea README-ului in acelasi stil ca laboratoarele anterioare
si crearea fisierului `prompts_lab05.md`.

**Rezultat:** README-ul descrie bibliotecile statice, dependenta SQLite,
instructiunile de instalare si pasii de build/rulare. Acest fisier sumarizeaza
solicitarile si rezultatele Lab 5.

## Verificari

- Build complet prin Makefile si link cu SQLite.
- Rulare demonstrativa cu salvare si incarcare SQLite a hartii.
- Testarea salvarii/incarcarii pentru harti cu obiecte si fara obiecte,
  inclusiv suprascrierea datelor salvate anterior.
- Compararea hartii incarcate cu cea originala.
- Verificare ca bibliotecile si baza de date generate nu ajung in Git.
