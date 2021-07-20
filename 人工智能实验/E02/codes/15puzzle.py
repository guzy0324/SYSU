import time
path = list()
# 通过值查目标位置
goal_reverse = ((3, 3), (0, 0), (0, 1), (0, 2),
                (0, 3), (1, 0), (1, 1), (1, 2),
                (1, 3), (2, 0), (2, 1), (2, 2),
                (2, 3), (3, 0), (3, 1), (3, 2))
row = 4
col = 4
range_row = range(row)
range_col = range(col)
puzzle = list()
# 曼哈顿距离，只调用一次，后续动态修改f值
def h():
    ans = 0
    for i in range_row:
        for j in range_col:
            if puzzle[i][j] is 0:
                continue
            goal_pos = goal_reverse[puzzle[i][j]]
            ans += abs(i - goal_pos[0]) + abs(j - goal_pos[1])
    return ans
cost = 1
# 通过位置查目标值
goal = ((1, 2, 3, 4),
        (5, 6, 7, 8),
        (9, 10, 11, 12),
        (13, 14, 15, 0))
def is_goal():
    for i in range_row:
        for j in range_col:
            if puzzle[i][j] is 0:
                continue
            if puzzle[i][j] is not goal[i][j]:
                return False
    return True
# 记录0所在的位置，方便更新
zero_pos
directions = ((-1, 0), (1, 0), (0, -1), (0, 1))
def successors():
    global zero_pos
    ans = list()
    for direction in directions:
        succ = (zero_pos,
                (zero_pos[0] + direction[0],
                 zero_pos[1] + direction[1]))
        if 0 <= succ[1][0]\
                and succ[1][0] < row\
                and 0 <= succ[1][1]\
                and succ[1][1] < col:
            ans.append(succ)
    return ans
# 当前图的hash值，可以放入set中用于路经检测
# list类型的puzzle无法放入set中
cur_hash = 0
# 初始化cur_hash，后续只对变化元素修改cur_hash
def hash():
    global cur_hash
    base = 1
    for i in range_row:
        for j in range_col:
            cur_hash += base * puzzle[i][j]
            base *= 16
inf = float("inf")
vis = set()
def ida_star():
    global zero_pos
    stt = h()
    bound = stt
    vis.add(hash())
    for i in range_row:
        for j in range_col:
            if puzzle[i][j] is 0:
                zero_pos = (i, j)
                break
        else:
            continue
        break
    while 1:
        t = search(path, stt, bound)
        if t is True:
            return (path, bound)
        if t == inf:
            return False
        bound = t 
def search(path, f, bound):
    global zero_pos
    global cur_hash
    if f > bound:
        return f
    if is_goal():
        return True
    min = inf
    for succ in successors():
        succ_value = puzzle[succ[1][0]][succ[1][1]]
        last_hash = cur_hash
        cur_hash += succ_value
        * (16 ** (succ[0][0] * col + succ[0][1])
           - 16 ** (succ[1][0] * col + succ[1][1]))
        puzzle[succ[0][0]][succ[0][1]] = succ_value
        puzzle[succ[1][0]][succ[1][1]] = 0
        zero_pos = succ[1]
        if cur_hash not in vis:
            path.append(succ)
            vis.add(cur_hash)
            goal_pos = goal_reverse[succ_value]
            t = search(path,
                        f + abs(succ[0][0] - goal_pos[0]) +
                        abs(succ[0][1] - goal_pos[1])
                        - (abs(succ[1][0] - goal_pos[0]) +
                            abs(succ[1][1] - goal_pos[1])) + cost,
                        bound)
            if t is True:
                return True
            if t < min:
                min = t
            vis.remove(cur_hash)
            path.pop()
        zero_pos = succ[0]
        puzzle[succ[1][0]][succ[1][1]] = succ_value
        puzzle[succ[0][0]][succ[0][1]] = 0
        cur_hash = last_hash
    return min
def read_15puzzle(file_name):
    with open(file_name) as f:
        for i in range_row:
            line = f.readline()
            if not line:
                break
            puzzle.append([int(i) for i in line.split()])
read_15puzzle("test4.txt")
for i in puzzle:
    for j in i:
        print(j, end = '\t')
    print()
start = time.perf_counter()
ans = ida_star()
end = time.perf_counter()
print("Time used:", end - start)
print(ans)
