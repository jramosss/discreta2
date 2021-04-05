#!/usr/bin/env python3

import os
import time
if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *

def timekeep_all ():
    GRAPHS_DIR  = '../grafos/'
    graphs = sort_files_from_dir(GRAPHS_DIR)

    f = open('results/construccion.txt','a')
    times = {}
    os.system('gcc -g -Wall -Wextra -std=c99 -Wpedantic -Wstrict-prototypes -Wunreachable-code -Wconversion -Wshadow -O3 ../src/construccion.c ../src/parser.c ../src/hash.c ../src/utils.c  ../mains/main_construccion.c -o test')
    for graph in graphs:
        print_in_cyan("------CONSTRUYENDO " + graph)

        filename = GRAPHS_DIR + graph
        start = time.time()
        os.system('../test < ' + filename)
        end = time.time()
        total = str(end-start)
        times[graph] = total
        print_in_green(graph + " tardo                  " + total)
        f.write("Graph " + graph + ": " + total + "\n")

    #TODO calcular cual es el que mas tardo 
    f.close()
    os.system('rm test')


if __name__ == '__main__':
    timekeep_all()

