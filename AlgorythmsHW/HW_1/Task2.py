def if_odd_index_cycle(list_sm: list[list[int]]) -> bool:
    color = [0]**len(list_sm)
    def dfs(v : int) -> bool:
        if v % 2 == 1:
            return False
        color[v] = 1
        for u in list_sm[v]:
            if color[u] == 1 or (color[u] == 0 and dfs(u)):
                return True
        color[v] = 2
        return False
    for v in range(0, len(list_sm), 2) :
        if color[v] == 0 and dfs(v):
            return True
    return False