# assignment1.py
'''
Caden Snelling
101196193
COMP 3106
Assignment 1
'''

import csv
import heapq

def parseGrid(filePath):
    grid = []
    start = None
    goal = None

    with open(filePath, 'r') as file:
        reader = csv.reader(file)
        for row_index, row in enumerate(reader):
            grid_row = []
            for col_index, cell in enumerate(row):
                cell = cell.strip()
                grid_row.append(cell)
                if cell == 'S':
                    start = (row_index, col_index)
                elif cell == 'G':
                    goal = (row_index, col_index) 
                else:
                    pass  # Regular square, no action needed
            grid.append(grid_row)

    return grid, start, goal

def getHeuristic(node, goal):
    return abs(node[0] - goal[0]) + abs(node[1] - goal[1])

def a_star_search(grid, start, goal):
    openList = []
    initialPosition = start
    initialKeysCollected = frozenset()
    initialDoorsOpened = frozenset()
    initialState = (initialPosition, initialKeysCollected, initialDoorsOpened)

    initialCost = 0
    initialHeuristic = getHeuristic(start, goal)
    initialPriority = initialCost + initialHeuristic

    heapq.heappush(openList, (initialPriority, initialCost, initialState))

    cameFrom = {}
    costSoFar = {}

    costSoFar[initialState] = 0

    exploredStates = 0

    while openList:
        priorityTuple = heapq.heappop(openList)
        currentPriority = priorityTuple[0]
        currentCost = priorityTuple[1]
        currentState = priorityTuple[2]
        
        currentPosition = currentState[0]
        keysCollected = currentState[1]
        doorsOpened = currentState[2]

        exploredStates += 1
        
        if currentPosition == goal:
            path = [currentPosition]
            totalCost = currentCost
            
            while currentState in cameFrom:
                currentState = cameFrom[currentState]
                path.append(currentState[0])
            
            path.reverse()
            return path, totalCost, exploredStates
        
        for direction in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            dx, dy = direction
            nextRow = currentPosition[0] + dx
            nextCol = currentPosition[1] + dy
            nextPosition = (nextRow, nextCol)

            if nextRow >= 0 and nextRow < len(grid) and nextCol >= 0 and nextCol < len(grid[0]):
                nextCell = grid[nextRow][nextCol]

                newKeysCollected = keysCollected
                newDoorsOpened = doorsOpened

                if nextCell not in ['S', 'G', 'K', 'D', 'O']:
                    continue

                if nextCell == 'K' and nextPosition not in keysCollected:
                    newKeysCollected = frozenset(set(keysCollected).union({nextPosition}))

                if nextCell == 'D':
                    if nextPosition in doorsOpened:
                        newDoorsOpened = doorsOpened
                    else:
                        numUnusedKeys = len(newKeysCollected) - len(doorsOpened)
                        if numUnusedKeys > 0:
                            newDoorsOpened = frozenset(set(doorsOpened).union({nextPosition}))
                        else:
                            continue

                nextState = (nextPosition, newKeysCollected, newDoorsOpened)
                moveCost = 1
                newCost = currentCost + moveCost
                
                if nextState not in costSoFar or newCost < costSoFar[nextState]:
                    costSoFar[nextState] = newCost
                    heuristic = getHeuristic(nextPosition, goal)
                    newPriority = newCost + heuristic
                    heapq.heappush(openList, (newPriority, newCost, nextState))
                    
                    cameFrom[nextState] = currentState

    return None, float('inf'), exploredStates


# The pathfinding function must implement A* search to find the goal state
def pathfinding(filepath):
    # filepath is the path to a CSV file containing a grid 
    grid, start, goal = parseGrid(filepath)
    
    # Perform A* search
    optimal_path, optimal_path_cost, num_states_explored = a_star_search(grid, start, goal)
    # optimal_path is a list of coordinates of squares visited (in order)
    # optimal_path_cost is the cost of the optimal path
    # num_states_explored is the number of states explored during A* search
    return optimal_path, optimal_path_cost, num_states_explored


'''
if __name__ == "__main__":
    filepath = "Examples/Example0/grid.csv"  # Update this with the actual path to your grid file
    path, cost, explored = pathfinding(filepath)
    print("Optimal Path:", path)
    print("Cost of the Optimal Path:", cost)
    print("Number of States Explored:", explored)
'''