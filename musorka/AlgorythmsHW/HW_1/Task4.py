class Solution:
    def findJudge(self, n: int, trust: list[list[int]]) -> int:
        persons = [[0, 0] for _ in range(n)] # [Скольким доверяет; сколько ему доверяют]

        for relation in trust:
            persons[relation[0] - 1][0] += 1
            persons[relation[1] - 1][1] += 1

        for i in range(n):
            if persons[i] == [0, n - 1]:
                return i + 1

        return -1