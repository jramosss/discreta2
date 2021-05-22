#!/usr/bin/env python3

import os
import subprocess
import sys
if __name__ == '__main__':
    from _utils import *
else:
    from ._utils import *


if __name__ == '__main__':
    GRAPHS_DIR  = '../grafos/'
    graphs = sort_files_from_dir(GRAPHS_DIR)

    os.system('make orden')

    try:
        times = sys.argv[1]
    except IndexError:
        times = 1

    print_in_cyan("Testing with " + str(times) + " OrdenPorBloqueDeColores")
    maxtime = -1
    maxtime_name = ""

    for graph in graphs:

        filename = GRAPHS_DIR + graph

        graph_time = subprocess.check_output('./test ' + str(times) + ' < ' + filename,
                                             shell=True,encoding='utf-8',text=True)

        time_min = float(graph_time) / 60
        print_in_green(graph + " tardo " + graph_time)

        if float(graph_time) > float(maxtime):
            maxtime = graph_time
            maxtime_name = graph
    
    bold_print("The graph that took the longest was " + maxtime_name + " with " + maxtime + " seconds")

    os.system('rm test')