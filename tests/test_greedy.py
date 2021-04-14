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
            result  = subprocess.check_output('./test < ' + filename,shell=True,encoding='utf-8',text=True)
            colores = result.split("COLORES: ")[1]
            print(colores)
            #Expected response = Greedy coloreo con n colores
            #TODO check correct results for each graph
            
            
        except Exception as e:
            print_in_red("Error corriendo el grafo" + e.__str__())



if __name__ == '__main__':
    test_all()