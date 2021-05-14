import os
import subprocess
from optparse import OptionParser

if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *

def timekeep (times):
    GRAPHS_DIR = '../grafos/'
    os.system('make alv')
    files = sort_files_from_dir(GRAPHS_DIR)
    time_pg = 0
    print_in_cyan("Corriendo " + str(times) + " veces")

    for graph in files:
        time_pg = 0

        filename = GRAPHS_DIR + graph

        result = subprocess.check_output('./test ' + str(times) + ' ' + '< ' + 
                                         filename,shell=True,encoding='utf-8',text=True)
        time_pg += float(result.replace('\n',''))

        print_in_green(graph + ": " + str(result).replace('\n',''))


def test_same_result ():
    GRAPHS_DIR = '../grafos/'
    os.system('make alv2')
    files = sort_files_from_dir(GRAPHS_DIR)
    flag = True
    
    for graph in files:
        filename = GRAPHS_DIR + graph

        result   = subprocess.check_output('./test 1 < ' + filename,shell=True,encoding='utf-8',text=True)

        splitt   = result.split('[')
        fst      = [int(v) for v in splitt[1].replace(']','').replace('\n','').split(',')]
        snd      = [int(v) for v in splitt[2].split(',')]
    
        for i in range (0,len(fst)):
            if int(fst[i]) != int(snd[i]):
                print_in_red(f"El vertice {fst[i]} difiere del vertice {snd[i]} en la posicion {i}")
                flag = False
        
        print_in_green(graph) if flag else print_in_red(graph)


def test_result ():
    GRAPHS_DIR  = '../grafos/'
    files       = sort_files_from_dir(GRAPHS_DIR)
    os.system('make alv')
    result = ""
    for graph in files:
        print_in_cyan("-----Testing " + graph)

        filename = GRAPHS_DIR + graph
        try:
            result   = subprocess.check_output('./test < ' + filename,shell=True,encoding='utf-8',text=True)

            if int(result) == 1:
                print_in_red(graph)
            elif int(result) == 0:
                print_in_green(graph)
            else:
                print_in_red("Unknown parameter in " + graph + ": " + result)

        except Exception as e:
            print_in_red("Error corriendo el grafo: " + e.__str__())

def test_correct ():
    GRAPHS_DIR = '../grafos/'
    os.system('make alv3')
    files = sort_files_from_dir(GRAPHS_DIR)

    for graph in files:
        filename = GRAPHS_DIR + graph
        result = subprocess.check_output('./test ' + str(1) + ' ' + '< ' + 
                                        filename,shell=True,encoding='utf-8',text=True)
        
        clean_res   = [int(v) for v in result.replace('[','').replace(']','').replace('\n','').split(',')]
        print(clean_res)

        for i in range (0,len(clean_res)):
            for j in range (0,len(clean_res)):
                if i != j and clean_res[i] == clean_res[j]:
                    print_in_red(f"El vertice {clean_res[i]} se repite en la posicion {i}")
                    break



if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option(
        "-r", "--result",
        help="Testea solo el resultado de AleatorizarVertices (0/1)")
    parser.add_option(
        "-c", "--correct",
        help="Testea que no se haya perdido ningun vertice ni se repita")
    parser.add_option(
        "-t", "--time",
        help="Testea el tiempo que tarda en correr n AleatorizarVertices")
    parser.add_option(
        "-s", "--sameresult"
    )

    options, args = parser.parse_args()

    if options.result != None:
        print_in_cyan("Test result")
        test_result()
    elif options.correct != None:
        print_in_cyan("Test correct")
        test_correct()
    elif options.sameresult != None:
        print_in_cyan("Test sameresult")
        test_same_result()
    elif options.time != None:
        print_in_cyan("Test time")
        try:
            times = int(options.time)
            print_in_green("Corriendo AleatorizarVertices " + str(times) +  " veces en cada grafo")
            timekeep(times)
        except ValueError:
            print("Numero invalido, corriendo con 1")
            timekeep(1)
    else:
        print_in_cyan("Test all")
        test_result()
        test_correct()
        timekeep(int(options.time))
        test_same_result()

    os.system('rm test && rm gmon.out')
    
