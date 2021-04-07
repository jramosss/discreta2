import os
import subprocess
import time

if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *

def test_all ():
    GRAPHS_DIR  = '../grafos/'
    files       = sort_files_from_dir(GRAPHS_DIR)

    os.system('make greedy')

    for graph in files:
        print_in_cyan("-----Testing " + graph)
        filename = GRAPHS_DIR + graph
        
        try:
            start   = time.time()
            result  = subprocess.check_output('./test < ' + filename,shell=True,encoding='utf-8',text=True)
            end     = time.time()

            print_in_green(str(result) + str(end-start))

            #Expected response = Greedy coloreo con n colores
            #TODO check correct results for each graph
            
            
        except:
            print_in_red("Error corriendo el grafo")



if __name__ == '__main__':
    test_all()