# the code for P02 part 2

###### input for AIpine Club ######
# A(TONY)
# A(MIKE)
# A(JOHN)
# L(TONY, RAIN)
# L(TONY, SNOW)
# (¬A(x), S(x), C(x))
# (¬C(y), ¬L(y, RAIN))
# (L(z, SNOW), ¬S(z))
# (¬L(TONY, u), ¬L(MIKE, u))
# (L(TONY, v), L(MIKE, v))
# (¬A(w), ¬C(w), S(w))
###################################

#### input for hardworker(sue) ####
# GradStudent(SUE)
# (¬GradStudent(x), Student(x))
# (¬Student(y), HardWorker(y))
# ¬HardWorker(SUE)
###################################

####### input for 3' blocks #######
# On(AA,BB)
# On(BB,CC)
# Green(AA)
# ¬Green(CC)
# (¬On(x,y), ¬Green(x), Green(y))
###################################


import time
import re
import copy
import queue


clause_index = 1
num_of_init = None


class Linked_list():
    def __init__(self, size):
        if size < 0:
            return
        self.size = size + 2
        self.space = [[0, (i + 1) % self.size, None] for i in range(self.size)]
        self.header = 1
        self.space[0][1] = self.space[1][1]
        self.space[1][1] = 0
        self.length = 0

    def Header(self):
        return self.header

    def Tail(self):
        return 1

    def Last(self, pointer):
        if 1 > pointer or pointer >= self.size or pointer == self.header:
            return None
        return self.space[pointer][0]

    def Next(self, pointer):
        if 2 > pointer or pointer >= self.size:
            return None
        return self.space[pointer][1]

    def __getitem__(self, pointer):
        if 2 > pointer or pointer >= self.size:
            return None
        return self.space[pointer][2]

    def __setitem__(self, pointer, value):
        if 2 > pointer or pointer >= self.size:
            return None
        self.space[pointer][2] = value
        return value

    def New(self, value, pointer):
        new_pointer = self.space[0][1]
        if 1 > pointer or pointer >= self.size or new_pointer == 0:
            return None
        self.space[0][1] = self.space[new_pointer][1]
        self.space[new_pointer][1] = pointer
        if pointer == self.header:
            self.header = new_pointer
        else:
            self.space[self.space[pointer][0]][1] = new_pointer
        self.space[new_pointer][0] = self.space[pointer][0]
        self.space[pointer][0] = new_pointer
        self.space[new_pointer][2] = value
        self.length += 1
        return new_pointer

    def Delete(self, pointer):
        if 2 > pointer or pointer >= self.size:
            return None
        ret = self.space[pointer][1]
        self.space[ret][0] = self.space[pointer][0]
        if pointer == self.header:
            self.header = ret
        else:
            self.space[self.space[pointer][0]][1] = ret
        self.space[pointer][1] = self.space[0][1]
        self.space[0][1] = pointer
        self.length -= 1
        return ret

    def Size(self):
        return self.size - 2

    def __len__(self):
        return self.length

    def __eq__(self, linked_list2):
        if self.length != len(linked_list2):
            return False
        pointer1 = self.header
        pointer2 = linked_list2.Header()
        while pointer1 != 1:
            if self.space[pointer1][2] != linked_list2.Vlaue(pointer2):
                return False
            pointer1 = self.space[pointer1][1]
            pointer2 = linked_list2.Next(pointer2)
        return True

    def Extend(self, linked_list2):
        length = self.length + linked_list2.length
        if length > self.size - 2:
            return None
        pointer2 = linked_list2.Header()
        while pointer2 != 1:
            self.New(copy.deepcopy(linked_list2[pointer2]), 1)
            pointer2 = linked_list2.Next(pointer2)
        self.length = length
        return length

    def Print(self, end=' '):
        pointer = self.header
        while pointer != 1:
            print(self.space[pointer][2], end=end)
            pointer = self.space[pointer][1]


class Array():
    def __init__(self):
        self.space = list()
        self.table = list()
        self.length = 0

    def append(self, value):
        self.space.append(value)
        self.table.append(True)
        self.length += 1

    def pop(self):
        self.table.pop()
        self.length -= 1
        return self.space.pop()

    def Length(self):
        return self.length

    def restore(self, index):
        if not self.table[index]:
            self.table[index] = True
            self.length += 1

    def __getitem__(self, index):
        if self.table[index] == False:
            return None
        else:
            return self.space[index]

    def __delitem__(self, index):
        if self.table[index]:
            self.table[index] = False
            self.length -= 1

    def __len__(self):
        return len(self.space)

    def __add__(self, array):
        new = Array()
        for i in range(len(self.space)):
            if self.table[i]:
                new.append(self.space[i])
        for i in range(len(array)):
            if array[i] is not None:
                new.append(array[i])
        return new


class Clauses(Array):
    pass


class Clause(Array):
    def __init__(self, index):
        super(Clause, self).__init__()
        self.index = index

    def Index(self):
        return self.index

    def deepcopy(self):
        new = Clause(self.index)
        for i in range(len(self.space)):
            if self.table[i]:
                new.append(copy.deepcopy(self.space[i]))
        return new

    def __add__(self, clause):
        global clause_index
        new = Clause(clause_index)
        for i in range(len(self.space)):
            if self.table[i]:
                new.append(self.space[i])
        for i in range(len(clause)):
            if clause[i] is not None:
                for j in range(len(self.space)):
                    if self.table[j]:
                        if self.space[j][0] == clause[i][0]:
                            for k in range(1, len(self.space[j])):
                                if self.space[j][k] != clause[i][k]\
                                    and not (len(self.space[j][k]) == 1
                                             and len(clause[i][k]) == 1):
                                    break
                            else:
                                break
                else:
                    new.append(clause[i])
        return new

    def Dump(self):
        l = list()
        for i in range(len(self.space)):
            if self.table[i]:
                l.append(self.space[i])
        return l


class Tree():
    def __init__(self):
        self.space = [()]
        self.value = [None]
        self.size = [0]

    def append(self, value, a, b):
        self.space.append((a, b))
        self.size.append(self.size[a] + self.size[b] + 1)
        self.value.append(value)

    def Size(self, a):
        return self.size[a]

    def Value(self, a):
        return self.value[a]

    def Children(self, a):
        return self.space[a]

    def is_sub(self, a, b):
        if a == b:
            return True
        if b == 0:
            return False
        return self.is_sub(a, self.space[b][0]) or self.is_sub(a, self.space[b][1])

    def __contains__(self, a):
        return a in self.space

    def Back(self):
        return len(self.space) - 1


class set_repeated():
    def __init__(self, dict2):
        self.dict = dict(dict2)
        self.length = 0
        for key, value in dict2.items():
            self.length += value

    def Dict(self):
        return self.dict

    def __add__(self, set2):
        dict3 = copy.deepcopy(self.dict)
        for key, value in set2.Dict().items():
            if dict3.get(key) is None:
                dict3[key] = value
            else:
                dict3[key] += value
        return set_repeated(dict3)

    def __eq__(self, set2):
        return self.dict == set2.Dict()

    def __len__(self):
        return self.length()


# 假设一个字母是变量，否则是常量，且变量名不包含常量。
# clauses: Array(clause)
# clause: Array(item)
# f/g/items: list(item=str())
# sigma: Linked_list(equation)
# equation: [str, str]


def get_clauses(path):
    global clause_index
    clauses = Clauses()
    clauses.append(None)
    with open(path, encoding='utf-8') as f:
        line = f.readline()
        while line != str():
            clause = Clause(clause_index)
            clause_index += 1
            for items_raw in re.findall(r'¬*[a-zA-Z]+\([a-zA-Z,\s]*\)', line):
                items = re.findall(r'[¬a-zA-Z]+', items_raw)
                clause.append(items)
            clauses.append(clause)
            line = f.readline()
    return clauses


def MGU(f, g):
    sigma = Linked_list(20)
    if len(f) != len(g):
        return None
    length = len(f)
    while True:
        index = 0
        while index < length:
            if f[index] != g[index]:
                if len(f[index]) == 1 and f[index] not in g[index]:
                    V = f[index]
                    t = g[index]
                    V_in = 'f'
                elif len(g[index]) == 1 and g[index] not in f[index]:
                    V = g[index]
                    t = f[index]
                    V_in = 'g'
                else:
                    return None
                break
            index += 1
        if index == length:
            return sigma
        pointer = sigma.Header()
        while pointer != sigma.Tail():
            sigma[pointer][1] = sigma[pointer][1].replace(V, t)
            pointer = sigma.Next(pointer)
        pointer = sigma.Header()
        while pointer != sigma.Tail():
            last = pointer
            pointer = sigma.Next(pointer)
            if sigma[last][0] == sigma[last][1]:
                sigma.Delete(last)
        pointer = sigma.Header()
        while pointer != sigma.Tail():
            if sigma[pointer][0] == V:
                break
            pointer = sigma.Next(pointer)
        else:
            sigma.New([V, t, V_in], sigma.Tail())
        for index in range(len(f)):
            if V_in == 'f':
                f[index] = f[index].replace(V, t)
            else:
                g[index] = g[index].replace(V, t)


def union(clause1_constant, clause2_constant):
    clause1 = clause1_constant.deepcopy()
    clause2 = clause2_constant.deepcopy()
    index1 = 0
    for i in range(len(clause1)):
        if clause1[i] is None:
            continue
        f = clause1[i]
        index2 = 0
        for j in range(len(clause2)):
            if clause2[j] is None:
                continue
            g = clause2[j]
            if f[0] == '¬' + g[0]\
                    or '¬' + f[0] == g[0]:
                sigma = MGU(f[1:], g[1:])
                if sigma is None:
                    return None, None, None
                pointer = sigma.Header()
                while pointer != sigma.Tail():
                    V, t, V_in = sigma[pointer]
                    if V_in == 'f':
                        for k in range(len(clause1)):
                            if clause1[k] is None:
                                continue
                            for index in range(len(clause1[k][1:])):
                                clause1[k][index +
                                           1] = clause1[k][index + 1].replace(V, t)
                    else:
                        for k in range(len(clause2)):
                            if clause2[k] is None:
                                continue
                            for index in range(len(clause2[k][1:])):
                                clause2[k][index +
                                           1] = clause2[k][index + 1].replace(V, t)
                    pointer = sigma.Next(pointer)
                del clause1[i]
                del clause2[j]
                return clause1 + clause2, chr(ord('a') + index1), chr(ord('a') + index2)
            index2 += 1
        index1 += 1
    return None, None, None


def resolve(clauses, tree, based_on, min_spouse):
    global clause_index
    while True:
        if clauses.Length() == 0:
            return False
        left_bound = 1
        right_bound = len(clauses) - 1
        min_sum = float('inf')
        min_clause1_index = None
        min_clause2_index = None
        min_clause3 = None
        min_items_index1 = None
        min_items_index2 = None
        while left_bound < right_bound:
            if clauses[left_bound] is None:
                left_bound += 1
                continue
            clause1 = clauses[left_bound]
            index = min_spouse[left_bound]
            while index <= right_bound:
                if clauses[index] is None:
                    index += 1
                    continue
                if based_on[left_bound] + based_on[index] in based_on:
                    index += 1
                    continue
                if tree.is_sub(left_bound, index):
                    index += 1
                    continue
                clause2 = clauses[index]
                clause3, items_index1, items_index2 = union(
                    clause1, clause2)
                if items_index1 is None:
                    index += 1
                    continue
                sum_base = tree.Size(left_bound) + tree.Size(index)
                if sum_base < min_sum:
                    min_sum = sum_base
                    min_clause1_index = left_bound
                    min_clause2_index = index
                    min_clause3 = clause3
                    min_items_index1 = items_index1
                    min_items_index2 = items_index2
                right_bound = index - 1
            min_spouse[left_bound] = index
            left_bound += 1
        if min_items_index1 is None:
            return True
        tree.append((min_items_index1, min_items_index2),
                    min_clause1_index, min_clause2_index)
        clause_index += 1
        based_on.append(based_on[min_clause1_index] +
                        based_on[min_clause2_index])
        clauses.append(min_clause3)
        min_spouse.append(clause_index)
        if min_clause3.Length() == 0:
            return False


def print_path(clauses, tree):
    index = 1
    mapping = dict()
    while index <= num_of_init:
        print(index, end='\t')
        print(clauses[index].Dump())
        mapping[index] = str(index)
        index += 1
    Stack = list()
    Queue = queue.Queue()
    Queue.put(tree.Back())
    while not Queue.empty():
        current = Queue.get()
        children = tree.Children(current)
        if children == (0, 0):
            continue
        value = tree.Value(current)
        base = (children[0], value[0], children[1], value[1])
        Stack.append((current, base, str(clauses[current].Dump())))
        Queue.put(children[0])
        Queue.put(children[1])
    while len(Stack) != 0:
        print(index, end='\t')
        node = Stack.pop()
        mapping[node[0]] = str(index)
        base = (mapping[node[1][0]] + node[1][1],
                mapping[node[1][2]] + node[1][3])
        print('R' + str(base) + node[2])
        index += 1


clauses = get_clauses('test.txt')
tree = Tree()
num_of_init = clause_index - 1
for i in range(0, num_of_init):
    tree.append(None, 0, 0)
based_on = [set_repeated({i: 1}) for i in range(clause_index)]
min_spouse = [i + 1 for i in range(clause_index)]
time_start = time.time()
unsatisfiable = resolve(clauses, tree, based_on, min_spouse)
time_end = time.time()
if not unsatisfiable:
    print_path(clauses, tree)
else:
    print('Unsatisfiable')
print('Time cost:', time_end-time_start, end=' s')
