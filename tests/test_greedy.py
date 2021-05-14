import os
import subprocess
import sys

if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *


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
            #Expected response = Greedy coloreo con n colores
            #TODO check correct results for each graph
            
            
        except Exception as e:
            print_in_red("Error corriendo el grafo" + e.__str__())

    os.system('rm test && rm gmon.out')