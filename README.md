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

# Correccion primera parte penazzi 2021

Tienen segfault incluso con grafos chicos
empezando la construccion
p edge 4 5
e 1 4
e 1 5
e 1 7
e 4 5
e 5 7
lista construccion
Segmentation fault (core dumped)


Incluso con 1 solo lado

empezando la construccion
p edge 2 1
e 1 2
lista construccion
 Calculando el numero de Vertices
Segmentation fault (core dumped)

Ni siquiera puede uno pedir el numero de vertices que se clava.

Sin embargo, eso es solo si uno introduce el grafo desde stdin, como habiamos dicho que ibamos a hacer.
Si uno introduce el grafo haciendo redirect a un archivo DESDE stdin, entonces funciona bien.

Ademas no pusieron un include de GrafoSt21.h como se pedia sino de GrafoSt2020.h
y hay lineas de un proyecto de 2020 comentadas.

Tienen esto:
void check_bipartito (char bip) {
    check_cond(bip == '1',"El grafo es bipartito","El grafo no es bipartito");
}

Para que esta esto?

En FijarOrden y FijarColor devuelven '0' o '1' en vez de 0 o 1.

Mas importante: Su FijarOrden NO HACE lo que se pide que haga.

No usa el orden natural de los vertices sino el orden INICIAL en que ustedes crean
al principio de todo.

El resto parece estar bien.  
