#Este test tiene 2 flags disponibles, -t y -n
#-n muestra el resultado con valor numerico
#-t muestra el tiempo que tardo el test

import os
import subprocess
from optparse import OptionParser

if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *


if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option(
        "-t", "--time",
        help="Mostrar el tiempo que tardo",default=None,action='store_true',
        dest='t')
    parser.add_option(
        "-n", "--num",
        help="Muestra el resultado con numeros (1/0)",action='store_true',
        dest='n')

    options, args = parser.parse_args()

    GRAPHS_DIR  = '../grafos/'
    files       = sort_files_from_dir(GRAPHS_DIR)

    os.system('make bipartito')

    for graph in files:
        print_in_cyan("-----Testing " + graph)
        filename = GRAPHS_DIR + graph
        
        try: 
            result  = subprocess.check_output('./test < ' + filename,shell=True,encoding='utf-8',text=True)

            splitt    = result.split(' ')
            resultado = splitt[0]
            tiempo    = splitt[1]

            if not options.n:
                if int(resultado) == 1:
                    print_in_green("Bipartito")
                elif int(resultado) == 0:
                    print_in_red("No bipartito")
                else: 
                    print_in_red("Resultado inesperado: " + resultado)
            else:
                print(resultado)

            if options.t:
                print('\033[95m' + "Tiempo: " + tiempo)
            #TODO check correct results for each graph
            
        except Exception as e:
            print_in_red("Error corriendo el grafo" + e.__str__())

    os.system('rm test')