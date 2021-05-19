import os
import subprocess
import sys

if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *


RESULTS = {
    "queen10" : 16,
    "queen13" : 21,
    "school1" : 42,
    "CBQsc100_200_11_1517" : 42,
    "CBQsv1000_77_150" : 77,
    "K100" : 100,
    "K500" : 500,
    "K1000" : 1000,
    "Octo" : 339,
    "zzz_BxB1100_999_54_2017" : 5,
    "Gf12345_12111222_457_15" : 600,
    "GRD99704280" : 6,
    "adopta1" : 6,
    "adopta2" : 6,
    "lux4" : 1500
}

if __name__ == '__main__':
    GRAPHS_DIR  = '../grafos/'
    files       = sort_files_from_dir(GRAPHS_DIR)

    os.system('make greedy')

    try:
        times = sys.argv[1]
    except IndexError:
        times = 1

    print_in_cyan("Testing with " + str(times) + " Greedys each graph")

    for graph in files:
        print_in_cyan("-----Testing " + graph)
        filename = GRAPHS_DIR + graph
        
        try: 
            command = './test ' + str(times) + ' < ' + filename
            result  = subprocess.check_output(command,shell=True,encoding='utf-8',text=True)
            splitt  = result.split(' ')
            colores = splitt[0]
            tiempo  = splitt[1]
            
            print("Colores: " + colores)
            print("Tiempo : " + tiempo)
            
            if graph in RESULTS.keys():
                res = str(RESULTS[graph])
                if colores == res:
                    print_in_green("Coloreo correcto")
                else:
                    print_in_red("Coloreo incorrecto " + "GOT: " + colores + "EXPECTED: " + res)
            
            
        except Exception as e:
            print_in_red("Error corriendo el grafo" + e.__str__())

    os.system('rm test')