import os

def print_in_red (msg):
    FAIL = '\033[91m'
    print(FAIL + msg)


def print_in_green (msg):
    OKGREEN = '\033[92m'
    print(OKGREEN + msg)


def print_in_cyan (msg):
    OKCYAN = '\033[96m'
    print(OKCYAN + msg)

def bold_print (msg):
    print('\033[1m' + msg)


def sort_files_from_dir (dir):
    files = os.listdir(dir)
    files.sort()
    return files
