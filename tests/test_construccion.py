import os
import subprocess

if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *


if __name__ == '__main__':
    GRAPHS_DIR  = '../grafos/'
    graphs      = sort_files_from_dir(GRAPHS_DIR)

    os.system('make construccion')

    for graph in graphs:
        print_in_cyan("------CONSTRUYENDO " + graph)

        filename = GRAPHS_DIR + graph
        result   = subprocess.check_output('./test < ' + filename,shell=True
                                            ,encoding='utf-8',text=True)
        
        print_in_green(result)

    #TODO calcular cual es el que mas tardo 
    os.system('rm test && rm gmon.out')

