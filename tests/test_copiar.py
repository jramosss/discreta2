# python3 test_copiar.py |  sed -i 's/[92//g' > results/copiar.txt

import os
import subprocess
if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *

ACCEPTABLE_TIME = 20

#Class where each array corresponds with a field of the graph
#Array`s first element is the affirmative answer of the question
#Are these fields equal? second one is the neggative 
class Responses:
    def __init__(self) -> None:
        self.DELTA = ["Los campos delta son iguales","Los campos delta NO son iguales"]
        self.N     = [self.DELTA[0].replace('delta','N'),self.DELTA[1].replace('delta','N')]
        self.M     = [self.DELTA[0].replace('delta','M'),self.DELTA[1].replace('delta','M')]
        self.NAT   = [self.DELTA[0].replace('delta','orden natural'),self.DELTA[1].replace('delta','orden natural')]
        self.VERT  = [self.DELTA[0].replace('delta','vertices'),self.DELTA[1].replace('delta','vertices')]
    

def check_eq (param1,param2,field):
    if param1 == param2:
        print_in_green(field)
    else:
        print_in_red(field)


def test_all ():
    GRAPHS_DIR  = '../grafos/'
    files       = sort_files_from_dir(GRAPHS_DIR)
    responses   = Responses()

    os.system('make copiar')
    for graph in files:
        print_in_cyan("-----Testing " + graph)
        filename = GRAPHS_DIR + graph
        try:
            result   = subprocess.check_output('./test < ' + filename,shell=True,encoding='utf-8',text=True)
            fields   = result.split('\n')
            _,TIME,COPY,DELTA,N,M,NAT_ORDER,VERT,_ = fields
        except:
            print_in_red("Error corriendo el grafo")

        if float(TIME) > ACCEPTABLE_TIME:
            print_in_red("La construccion del grafo " + graph + " tardo mas de " + str(ACCEPTABLE_TIME) + "segundos") 
        else:
            print_in_green("Construccion")

        if float(COPY) > ACCEPTABLE_TIME:
            print_in_red("La copia del grafo " + graph + " tardo mas de " + str(ACCEPTABLE_TIME) + "segundos") 
        else:
            print_in_green("Copia")

        check_eq(N,responses.N[0],'N')
        check_eq(M,responses.M[0],'M')
        check_eq(DELTA,responses.DELTA[0],'Delta')
        check_eq(NAT_ORDER,responses.NAT[0],'Orden natural')
        check_eq(VERT,responses.VERT[0],'Vertices')

    os.system('rm test')


if __name__ == '__main__':
    test_all()