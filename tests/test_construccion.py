import os
import time

def print_in_red (msg):
    FAIL = '\033[91m'
    print(FAIL + msg)


def print_in_green (msg):
    OKGREEN = '\033[92m'
    print(OKGREEN + msg)


def print_in_cyan (msg):
    OKCYAN = '\033[96m'
    print(OKCYAN + msg)

def timekeep_all ():
    GRAPHS_DIR  = '../grafos/'
    graphs      = os.listdir(GRAPHS_DIR)
    graphs.sort()

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

