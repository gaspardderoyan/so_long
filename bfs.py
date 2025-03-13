def bfs(matrix, cell):
    queue = []
    seen = []

    queue.append(cell)
    seen.append(cell)

    while (queue is not empty):
        current = queue.pop(0);

        # get the cells in 4 directions (not 9)
        surrounding_cells: int[] = get_surrounding_cells(current);

        for surrounding_cell in surrounding_cells:
            if cell == EXIT:
                return True
            elif (cell not in seen) and (cell != WALL):
                queue.append(surrounding_cell)
                seen.append(surrounding_cell)
