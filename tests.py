import os
from sys import stdout
import time

class Tests:
    def __init__(self,testname,main_name,results) -> None:
        self.testname   = testname
        self.main_name  = "main_for_" + main_name + ".c"
        self.results    = results

#TODO hay que acomodar los resultados, ni idea de que es esto, ademas 
#tuve que borrar algunos grafos asi que se desacomodo esto 
# La otra es hacer un dict con grafo : resultado, pero es un bardo 
CHICOGRANDE =   [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
GREEDY      =   [4, 16, 21, 42, 42, 339, 77, 6, 100, 500, 1000]
WELSHPOWELL =   [17, 23, 34, 34, 264, 97, 239, 581, 5, 2099]
BIPARTITO   =   ['0','0','0','0','0','0','0','0','0','1','1','1','0','0','0']
NUMCCS      =   [1, 3, 3, 3, 3, 1, 1, 1, 1, 1, 9]
ALV         =   [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
SWITCH      =   ALV

chicogrande     = Tests("cg","chicogrande",CHICOGRANDE)
greedy          = Tests("greedy","greedy",GREEDY)
welsh           = Tests("wp","welshpowell",WELSHPOWELL)
bipartito       = Tests("bip","bipartito",BIPARTITO)
numccs          = Tests("nc","NumCCs",NUMCCS)
alv             = Tests("alv","aleatvert",ALV)
switch          = Tests("sc","switchcolores",SWITCH)

def print_in_red (msg):
    FAIL = '\033[91m'
    print(FAIL + msg)


def print_in_green (msg):
    OKGREEN = '\033[92m'
    print(OKGREEN + msg)


def print_in_cyan (msg):
    OKCYAN = '\033[96m'
    print(OKCYAN + msg)


def clean_and_exit ():
    print("-------- TEST: Exiting")
    os.system("make clean")
    os.system("rm ts")


def test_setup (filename,testname):
    os.system("cp " + filename + " temp_main.c")
    os.system("make clean")
    os.system("make " + testname)


def calc_points (test,results):
    for res in test.results:
        for res2 in results:
            if res == res2:
                print_in_green("a")
    

def test (test,dir,ammount_of_greedys = 200,compare_results=False):
    print_in_cyan("-------- TESTING " + test.testname.upper())
    files = os.listdir(dir)
    files.sort()
    print(files)
    os.system("make " + test.testname)
    total_time = 0

    for GRAPH in files:
        filename = dir + GRAPH
        print_in_cyan("\n\nTesting with " + GRAPH)
        start = time.time()
        if (test.testname == "greedy"):
            for _ in range (1,ammount_of_greedys/200):
                os.system("./test < " + filename)
        else:
            os.system('./test < ' + filename)
        end = time.time()
        total_time += end-start
        if compare_results:
            pass
        print("TIME: ",end-start)

    return total_time


def main ():
    print("Test para?")
    print("0: greedy")
    print("1: bipartito")
    print("2: chicogrande")
    print("3: welshpowell")
    print("4: aleatorizarvertices")
    print("5: numccs")
    print("6: switchcolores")
    print("7: todo")
    choice = input()

    if choice == '0' or choice == 'greedy' or choice == 'gr':
        test(greedy,"greedy_test_data/")
    elif choice == '1' or choice == 'bip' or choice == 'bipartito':
        test(bipartito,"bipartito_test_data/")
    elif choice == '2' or choice == 'chicogrande' or choice == 'cg':
        test(chicogrande,"chicogrande_test_data/")
    elif choice == '3' or choice == 'wp' or choice == 'welshpowell':
        test(welsh,"welshpowell_test_data/")
    elif choice == '4' or choice == 'alv' or choice == 'aleatvert' or choice == 'aleatorizarvertices':
        test(alv,"chicogrande_test_data/")
    elif choice == '5' or choice == 'nc' or choice == 'numccs':
        test(numccs,"numCCs_test_data/")
    elif choice == '6' or choice == 'sc' or choice == 'sw' or choice == 'switchcolores':
        test(switch,"chicogrande_test_data/")
    elif choice == '8':
        test(chicogrande,"chicogrande_test_data/")
        test(bipartito,"bipartito_test_data/")

    else:
        test(greedy,"greedy_test_data/")
        test(chicogrande,"chicogrande_test_data/")
        test(welsh,"welshpowell_test_data/")
        test(alv,"chicogrande_test_data/")
        test(bipartito,"bipartito_test_data/")
        test(switch,"chicogrande_test_data/")
        test(numccs,"numCCs_test_data/")

    os.system('make clean')


def diagnose (dump):
    greedy_time =   test(greedy,"greedy_test_data/",dump)
    cg_time     =   test(chicogrande,"chicogrande_test_data/",dump)
    wp_time     =   test(welsh,"welshpowell_test_data/",dump)
    alv_time    =   test(alv,"chicogrande_test_data/",dump)
    bip_time    =   test(bipartito,"bipartito_test_data/",dump)
    sc_time     =   test(switch,"chicogrande_test_data/",dump)
    numccs_time =   test(numccs,"numCCs_test_data/",dump)

    f = open('dump','a')
    f.write("Greedy Time: " + str(greedy_time))
    f.write("Chicogrande Time: " + str(cg_time))
    f.write("Welshpowell Time: " + str(wp_time))
    f.write("Aleatorizar Vertices Time: " + str(alv_time))
    f.write("Bipartito Time: " + str(bip_time))
    f.write("Switch Colores Time: " + str(sc_time))
    f.write("NumCCS Time: " + str(numccs_time))
    f.write("Total time " + str(greedy_time+cg_time+wp_time+alv_time+bip_time+sc_time+numccs_time))
    f.close()


if __name__ == '__main__':
    main()
    #diagnose()