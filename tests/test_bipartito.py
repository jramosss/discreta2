import os
import subprocess

if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *


if __name__ == '__main__':
    GRAPHS_DIR  = '../grafos/'
    files       = sort_files_from_dir(GRAPHS_DIR)

    os.system('make bipartito')

    for graph in files:
        print_in_cyan("-----Testing " + graph)
        filename = GRAPHS_DIR + graph
        
        try: 
            result  = subprocess.check_output('./test < ' + filename,shell=True,encoding='utf-8',text=True)
            
            resultado = result.split('Resultado: ')
            print(resultado)
            
            #TODO check correct results for each graph
            
        except Exception as e:
            print_in_red("Error corriendo el grafo" + e.__str__())