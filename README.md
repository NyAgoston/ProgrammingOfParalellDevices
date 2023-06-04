# FÉLÉVES FELADAT

## Mandelbrot halmaz

A Mandelbrot halmaz egy matematikai készlet, amelyet a komplex számokból hozunk létre. A Mandelbrot halmaz egy pontját a komplex síkon egy komplex számmal reprezentáljuk, ahol a valós rész az x tengelyen, a képzetes rész pedig az y tengelyen helyezkedik el. Úgy definiáljuk, hogy minden pontot kiválasztunk a komplex síkon, majd kiszámítjuk, hogy az adott pont divergens-e vagy sem. A divergencia egy bizonyos határnál történik meg. Ha a számítás során a pont divergál, azaz az abszolút értéke meghaladja a meghatározott határt, akkor azt a pontot kívülre soroljuk a Mandelbrot-halmazhoz tartozó részre. Ellenkező esetben az adott pontot a Mandelbrot-halmazhoz tartozó részbe soroljuk.

## Feladat
A feladat célja, hogy megvizygáljuk a sima CPU-n és az OpenCl könyvtár segítségével a GPU-n futó programok futási idejét. Ezálltal megnézzük elérhető e gyorsítás.

## Programok adatok

Két program készült, egy CPU-n és egy GPU-n futó. A képek .ppm formátumban lettek elkészítve, de .jpg formátumban töltöttem fel őket mivel nagyon nagy méretű fileok. A data.csv fileban találhatóak a mérési eredmények.

## OpenCL GPU kód leírása

* A kernel.cl fileban található a mandelbrot kódja, ezt hívom majd meg a programból.
* A mandelbrot.c fileban létrehoztam az OpenCl változóit: context, program, kernel, queue.
* megadom az algoritmus változóit: x és y értékek, felbontás, iterációk száma. 
* Megadom a kernelnek az argumentumokat.
* A clEnqueueNDRangeKernel függvénnyel lefutatom a kódot.

## Logika

A program a mandelbrot halmaz egy adott pontjába közelít bele:
* double xmax = -1.2576470439074896;
* double xmin = -1.2576470439078538;
* double ymax = 0.3780652779240597;
* double ymin = 0.3780652779236957;

Az iterációs szám növelésével egyre élesebb és részletesebb képet kapunk erről a pontról. Meg kell jegyezni, hogy 30000 iteráció felett már szemmel nem olyan látványos az élesedés. Összesen tíz mérést végeztem el.

## Képek és iterációk

* 100 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/100.jpg)
* 500 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/500.jpg)
* 1000 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/1000.jpg)
* 5000 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/5000.jpg)
* 10000 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/10000.jpg)
* 20000 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/20000.jpg)
* 30000 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/30000.jpg)
* 40000 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/40000.jpg)
* 50000 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/50000.jpg)
* 60000 Iteráció
    - ![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/60000.jpg)

## Mérések

![image](https://github.com/NyAgoston/ProgrammingOfParalellDevices/blob/main/felevesfeladat/plot.png)

Megfigyelhető, hogy amíg a CPU-n futó program arányosan növekszik addig a GPU-n futóval elég eredményes gyorsítást érhetünk el.