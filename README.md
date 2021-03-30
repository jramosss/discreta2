# Correccion de penazzi 2020

1) ChicoGrandeBC ordena al revez de lo que se pide:
Si ordenamos con ChicoGrandeBC y luego imprimimos 
los colores de los vertices en el orden en que estan,
y agrupamos vértices con el mismo color, indicando cuántos tienen
ese color, obtenemos cosas como:


10(10),2(9),6(9),0(8),1(8),3(8),5(8),7(8),8(8),4(7),9(7),11(6),12(4)

lo cual muestra que ustedes ordenan de MAYOR A MENOR y no de menor a mayor por cantidad de vértices con ese color.

Este es un error pero solo descuenta un punto de la nota.
El siguiente es mucho más grave.

---

2) Dijimos que el programa debía correr a una velocidad razonable.
Se suponia que tenian que hacer 1000 reordenamientos+Greedys en alrededor de 15  minutos.
Con grafos grandes, uds no lo hacen.
Veamos algunos grafos de testeo obligatorio:

Con 
https://www.famaf.unc.edu.ar/~penazzi/DisII2016/R1999999_10123123_1.gz
intentar Bipartito demora por si solo 98m42.058s (y lo detuve porque no terminaba)

Si simplemente testeo los Greedys, entonces luego de
174m32.082s

lo detuve y solo habia hecho 16 Greedys.

Con 
https://www.famaf.unc.edu.ar/~penazzi/DisII2016/Gf12345_12111222_457_15.gz
estuvieron mejor.
Luego de 151m54.498s habían hecho unos 300 reordenamientos+Greedys.
Pero 2 horas y media para hacer menos de un tercio de lo que tienen que hacer en 15 minutos no es aceptable.


Con el grafo de testeo obligatorio 
https://www.famaf.unc.edu.ar/~penazzi/DisII2016/BxB1100_999_54_2017.tar.gz
uds demoran 78m15.151s para hacer Bipartito y menos de 15 Greedys.


Luego lo testee  sin correr Bipartito y lo deje 137m42.794s y estaba igual que antes.

Ahí me di cuenta de una cosa: mi programa primero hace una serie de AleatorizarVertices+Greedy
y luego comienza con los ordenamientos por bloques de colores.

Su programa no era capaz de hacer NI UNO de los reordenes por bloque de colores.

Lo retestee y fue capaz de hacer 300 AleatorizarVertices+Greedys en 5 minutos.
Así que, al menos con ese grafo, el problema no es Greedy sino los reordenes.

En el caso del R1999... anterior el problema son LAS DOS cosas. (y Bipartito tampoco anda bien, quizás NumCCs tampoco pero no llegue a testearla)

Pej, para hacer 34 AleatorizarVertices+Greedy, demora 78m1.253s.


Proyecto Desaprobado.