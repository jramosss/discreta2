import os
import subprocess
if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *


def test_all ():
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
    test_all()