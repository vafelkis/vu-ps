# Procedurinio programavimo pagrindai - 6 tema

## Failai
- `task1.c` ... `task5.c`: 1-5 uzduotys su 7 ir 8a/8b reikalavimais.
- `validation.h` / `validation.c`: bendras validacijos modulis, universaliu filtru masyvai ir funkciju rodykles.
- `task6.c`: 6a ir 6b (rikiuotas zodynas + dvejetaine paieska RAM atmintyje; issaugojimas faile).
- `in.txt`, `week.txt`, `text.txt`, `dictionary.txt`: pavyzdiniai duomenu failai.

## Kompiliavimas (GCC, C11)

```bash
gcc -std=c11 -Wall -Wextra -pedantic task1.c validation.c -o task1
gcc -std=c11 -Wall -Wextra -pedantic task2.c validation.c -o task2
gcc -std=c11 -Wall -Wextra -pedantic task3.c validation.c -o task3
gcc -std=c11 -Wall -Wextra -pedantic task4.c validation.c -o task4
gcc -std=c11 -Wall -Wextra -pedantic task5.c validation.c -o task5
gcc -std=c11 -Wall -Wextra -pedantic task6.c -o task6
```

Windows aplinkoje naudokite `-o task1.exe` ir pan. Paleiskite is sio katalogo, nes tekstiniai failai atidaromi pagal darbini kataloga.

## Svarbios pastabos
- 1 uzduotyje priimami skaiciai 1..20, kad `unsigned long long` nepersipildytu.
- 2 uzduotyje ilgis reiskia *simboliu skaiciu*, iskaitant kableli. Reikalaujamas **vienas** skaicius vienoje eiluteje.
- 3 uzduotyje realiu skaiciu desimtainis skirtukas `.`; separatorius `;`. Pvz. `-4;2.5;1`. Rezultatas rasomas i vartotojo nurodyta `.txt` faila.
- 4 uzduotyje `week.txt` eilutes eina **nuo pirmadienio iki sekmadienio**. Pakeiskite jas anglu ar lietuviu kalba: programa perkaitys naujas reiksmes. Tekstinio failo koduote geriausia UTF-8.
- 5 uzduotyje validacijos logika tycia laikosi supaprastintu uzduoties taisykliu, o ne pilno el. pasto standarto.
- 6b naudoja RAM atmintyje laikoma surikiuota zodyna su O(log n) dvejetaine paieska; dideliems zodynams, kurie netelpa i RAM, reiketu diskinio indekso (pvz. B medzio).
- 7 uzduotis ideta i 1-5 uzduotis: visur yra `#define MAX_ERRORS 5`.
- 8a ir 8b integruotos i 1-5: `Rule` masyvai laiko funkciju rodykles ir parametrus.
- Konsoles pranesimai kode be lietuvisku raidziu, kad senos Windows C konsoles nekraipytu UTF-8.
