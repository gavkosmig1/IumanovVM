def ls_to_ms(ls:list[list[int]]) -> list[list[int]]:
    ms = [0] * len(ls)
    for i in len(ls):
        for j in ls[i]:
            ms[i][j] = 1
    return ms

def ls_to_le(ls:list[list[int]]) -> list[tuple[int, int]]:
    n = len(ls)
    le = []
    for i in n:
        for j in ls[i]:
            le.append((i, j))
    return le

def ms_to_le(ms:list[list[int]]) -> list[tuple[int, int]]:
    n = len(ms)
    le = []
    for i in range(n):
        for j in range(len(ms[i])):
            if j:
                le.append((i, j))
    return le

def ms_to_ls(ms:list[list[int]]) -> list[list[int]]:
    n = len(ms)
    ls = [[] for _ in range(n)]
    for i in range(n):
        for j in range(len(ms[i])):
            if j:
                ls[i].append(j)
    return ls

def le_to_ls(le:list[tuple[int, int]]) -> list[list[int]]:
    n = max(max(edge) for edge in le)
    ls = [[] for _ in range(n)]
    for edge in le:
        ls[edge[0]].append(edge[1])
    return ls

def le_to_ms(le:list[tuple[int, int]]) -> list[list[int]]:
    n = max(max(edge) for edge in le)
    ms = [[0] for _ in range(n)]
    for edge in le:
        ms[edge[0]][edge[1]] = 1
    return ms