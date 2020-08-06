from typing import List
import heapq

# def heuristic(start,end): 
#     dist = 0
#     for i in range(4):
#         up = (10 + int(start[i]) - int(end[i])) % 10
#         down = (10 + int(end[i]) - int(start[i])) % 10
#         dist += min(up, down)
#     return dist

# def mutate(start):
#     ret = []
#     for i in range(4):
#         for move in [+1, -1]:
#             neighbor = list(start)
#             neighbor[i] = str((int(neighbor[i]) + 10 + move) % 10)
#             ret.append("".join(neighbor))
#     return ret


def heuristic(start,end): 
    dist = 0
    for start_letter, end_letter in zip(start, end):
        if start_letter != end_letter:
            dist+=1
    return dist

def mutate(start):
    ret = []
    for i in range(len(start)):
        for letter in 'abcdefghijklmnopqrstuvwxyz':
            neighbor = list(start)
            neighbor[i] = letter
            ret.append("".join(neighbor))
    return ret

# This is only a class because someone at leetcode read a book about OOP
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        return self.openLock(beginWord,wordList, endWord)

    def openLock(self, initial: str, deadends: List[str], target: str) -> int:
        # we take an A* aproach, 
        # optimzing for length of total estimated path:
        #heuristic distance + length already travelled
        seen = set([initial])
        deadends_lookup = set(deadends)

        if target not in deadends_lookup:
            return 0 # fuck you 
        if initial == target:
            return 0 # fuck you

        path_heap = []
        heapq.heappush( path_heap, (heuristic(initial, target), [initial]))
        while path_heap:
            _, cur_path = heapq.heappop(path_heap)
            next_steps = mutate(cur_path[-1])
            # print( cur_path, next_steps)
            for step in next_steps:
                if step not in deadends_lookup:
                    # CHANGED in to NOT IN from original openlock
                    # prune
                    continue
                if step == target:
                    # we're done, son! 
                    # we're on the cur_best path and we got there.
                    # this is as least as good as any we will find afterwards
                    print(cur_path)
                    return len(cur_path) + 1
                if step in seen:
                    #this is already in our queue, with a shorter or equal path
                    continue
                step_weight = heuristic(step, target) + len(cur_path)
                heapq.heappush(path_heap, (step_weight, cur_path + [step]))
                seen.add(step) 

        return 0 #guess we can't get there