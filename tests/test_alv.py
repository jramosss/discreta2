import os
import subprocess
from optparse import OptionParser
import sys

if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *

def timekeep (times):
    GRAPHS_DIR = '../grafos/'
    os.system('make alv')
    files = sort_files_from_dir(GRAPHS_DIR)
    
    for graph in files:
        for _ in range (0,times):
            print_in_cyan("-----Testing " + graph)

            filename = GRAPHS_DIR + graph

            result = subprocess.check_output('./test < ' + filename,shell=True,encoding='utf-8',text=True)
            print_in_cyan(graph + " tardo " + str(result).replace('\n','') + " segundos")

    os.system('rm test')


def test_correct ():
    GRAPHS_DIR = '../grafos/'
    os.system('make alv')
    files = sort_files_from_dir(GRAPHS_DIR)
    flag1,flag2 = True,True
    
    for graph in files:
        print_in_cyan("-----Testing " + graph)
        #if graph.startswith('Bx') or graph.startswith('GRD') or graph.startswith('R1') or graph == 'bossgraph' or graph == 'elpi' or graph == "elgordo" or graph == 'elgraph':
         #   continue
        filename = GRAPHS_DIR + graph

        result   = subprocess.check_output('./test < ' + filename,shell=True,encoding='utf-8',text=True)

        aux_vertices = result.split("[")[1].replace(']','').replace('\n','').split(',')
        aux_orden_nat = result.split("[")[1].replace(']','').split(',')
        vertices = [int(v) for v in aux_vertices]
        orden_nat = [int(ov) for ov in aux_orden_nat]


        for vert in vertices:
            if vert not in orden_nat:
                print_in_red("Se perdio el vertice: "+vert)
                flag1 = False
    
        for i in range (0,len(vertices)):
            for j in range (0,len(vertices)):
                if i != j and int(vertices[i]) == int(vertices[j]):
                    print_in_red(f"El vertice {vertices[i]} se repite en la posicion {i} y {j}")
                    flag2 = False
        
        print_in_green(graph) if flag1 and flag2 else print_in_red(graph)



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


    os.system('rm test')


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
        help="Testea el tiempo que tarda en correr n AleatorizarVertices",default=1)

    options, args = parser.parse_args()
    
    print(options)

    if options.result != None:
        test_result()
    elif options.correct != None:
        test_correct()
    elif options.time != None:
        try:
            times = int(options.time)
            timekeep(times)
        except ValueError:
            print("Numero invalido")
            sys.exit(1)
    else:
        test_result()
        test_correct()
        timekeep(int(options.time))
    
