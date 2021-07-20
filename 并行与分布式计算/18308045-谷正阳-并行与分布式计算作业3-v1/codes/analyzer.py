def read():
    # init
    # path = input()
    path = 'tiny_race.ll'
    file = open(path)
    code = dict()

    # variable
    code['var'] = dict()
    while True:
        line = file.readline()
        if line.startswith('; Function'):
            break
        if len(line) > 0 and line[0] == '@':
            line_split = line.split(' ', 1)
            code['var'][line_split[0][1:]] = line_split[1]

    # function
    code['fun'] = dict()
    while True:
        line = file.readline()
        if not line:  # finish
            break
        if line[:6] == 'define':
            fun_name = line.split('@', 1)[1].split('(', 1)[0]
            code['fun'][fun_name] = list()
            while True:
                line = file.readline()
                if len(line) > 0 and line[0] == '}':
                    break
                code['fun'][fun_name].append(line)
    file.close()

    # build tree
    code['parent'] = dict()
    for fun_name in code['fun']:
        code['parent'][fun_name] = list()
    for (fun_name, fun_content) in code['fun'].items():
        for line in fun_content:
            if '= call' in line:
                child_fun = line.split('@', 1)[1].split('(', 1)[0]
                if child_fun in code['fun']:
                    code['parent'][child_fun].append(fun_name)
    return code


def global_or_static(code, reentrant_fun):
    # get global or static variable
    flag = False
    glob_var = list()
    for (var_name, var_content) in code['var'].items():
        if 'global' in var_content:
            glob_var.append(var_name)

    # check every function
    for (fun_name, fun_content) in code['fun'].items():
        flag = False
        for line in fun_content:
            for var in glob_var:
                if var in line:
                    reentrant_fun.add(fun_name)
                    flag = True
                    break
            if flag:
                break


def is_heap(code, reentrant_fun):
    # init
    heap = ['malloc', 'free']  # demo

    # check every function
    for (fun_name, fun_content) in code['fun'].items():
        flag = False
        for line in fun_content:
            for heap_fun in heap:
                if heap_fun in line:
                    reentrant_fun.add(fun_name)
                    flag = True
                    break
            if flag:
                break


def is_IO(code, reentrant_fun):
    # init
    IO = ['getchar', 'gutchar', 'gets', 'puts', 'scanf', 'printf']  # demo

    # check every function
    for (fun_name, fun_content) in code['fun'].items():
        flag = False
        for line in fun_content:
            for IO_fun in IO:
                if IO_fun in line:
                    reentrant_fun.add(fun_name)
                    flag = True
                    break
            if flag:
                break


def sub_reentrant(code, reentrant_fun):
    reentrant = list(reentrant_fun)
    while reentrant != []:
        fun = reentrant.pop()
        for pa in code['parent'][fun]:
            if pa not in reentrant_fun:
                reentrant.append(pa)
        reentrant_fun.add(fun)


code = read()
reentrant_fun = set()
global_or_static(code, reentrant_fun)
is_heap(code, reentrant_fun)
is_IO(code, reentrant_fun)
sub_reentrant(code, reentrant_fun)
print(reentrant_fun)
