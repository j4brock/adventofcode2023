import numpy as np 

def get_grid_group(grid, idx):
    row_start_index = np.max([0, idx[0] - 1])
    row_stop_index = np.min([idx[0] + 2, grid.shape[1]])
    col_start_index = np.max([0, idx[1] - 1])
    col_stop_index = np.min([idx[1] + 2, grid.shape[0]])

    return grid[row_start_index:row_stop_index, col_start_index:col_stop_index]

def traveling_horizontally(current_idx, next_idx):
    return next_idx == (current_idx[0], current_idx[1] + 1) or next_idx == (current_idx[0], current_idx[1] - 1)

def traveling_vertically(current_idx, next_idx):
    return next_idx == (current_idx[0] - 1, current_idx[1]) or next_idx == (current_idx[0] + 1, current_idx[1])

def print_grid(grid):
    print('  ', end = '')
    print(''.join([f'{i:^3}' for i in range(grid.shape[0])]))
    for iR, row in enumerate(grid):
        print(f'{iR:^2}', end = '')
        print(''.join([f'{c:^3}' for c in row]))


def propagate(grid, energized, visited, current_idx, next_idx):
    next_tile = grid[next_idx]
    energized[current_idx] = 1
    
    # Detects loops 
    direction = (next_idx[0] + 1j * next_idx[1]) - (current_idx[0] + 1j * current_idx[1])
    if (current_idx, direction) in visited:
        return energized
    else:
        visited[(current_idx, direction)] = 0

    if next_tile == '.':
        if traveling_vertically(current_idx, next_idx):
            # Going down
            if next_idx == (current_idx[0] + 1, current_idx[1]):
                current_idx = next_idx 
                # keep going down
                next_idx = (current_idx[0] + 1, current_idx[1])
            # Going up
            if next_idx == (current_idx[0] - 1, current_idx[1]):
                current_idx = next_idx 
                # keep going up
                next_idx = (current_idx[0] - 1, current_idx[1])
            
            energized |= propagate(grid, energized, visited, current_idx, next_idx)   
        else: # Traveling horizontally
            # Going right
            if next_idx == (current_idx[0], current_idx[1] + 1):
                current_idx = next_idx 
                # Keep going right
                next_idx = (current_idx[0], current_idx[1] + 1)
            # Going left
            if next_idx == (current_idx[0], current_idx[1] - 1):
                current_idx = next_idx 
                # Keep going left
                next_idx = (current_idx[0], current_idx[1] - 1)

            energized |= propagate(grid, energized, visited, current_idx, next_idx)   

    elif next_tile == '|': # Vertical split
        # Coming in horizontally; split beam
        if traveling_horizontally(current_idx, next_idx):
            current_idx = next_idx
            for next_idx in [(current_idx[0] - 1, current_idx[1]), (current_idx[0] + 1, current_idx[1])]:
                energized |= propagate(grid, energized, visited, current_idx, next_idx)   
        else:
            # Coming in from top
            if next_idx == (current_idx[0] + 1, current_idx[1]):
                current_idx = next_idx 
                # Keep going 
                next_idx = (current_idx[0] + 1, current_idx[1])
            # Coming in from bottom
            elif next_idx == (current_idx[0] - 1, current_idx[1]):
                current_idx = next_idx 
                # Keep going 
                next_idx = (current_idx[0] - 1, current_idx[1])

            energized |= propagate(grid, energized, visited, current_idx, next_idx)   
    elif next_tile == '-': # Horizontal split
        if traveling_horizontally(current_idx, next_idx):
            # Coming in from left
            if next_idx == (current_idx[0], current_idx[1] + 1):
                current_idx = next_idx 
                # Keep going 
                next_idx = (current_idx[0], current_idx[1] + 1)
            # Coming in from right
            if next_idx == (current_idx[0], current_idx[1] - 1):
                current_idx = next_idx 
                # Keep going 
                next_idx = (current_idx[0], current_idx[1] - 1)
            
            energized |= propagate(grid, energized, visited, current_idx, next_idx)   
        else:
            # Coming in vertically; split beam
            current_idx = next_idx
            for next_idx in [(current_idx[0], current_idx[1] - 1), (current_idx[0], current_idx[1] + 1)]:
                energized |= propagate(grid, energized, visited, current_idx, next_idx)   
    elif next_tile == '/': 
        # Coming in from left
        if next_idx == (current_idx[0], current_idx[1] + 1):
            current_idx = next_idx 
            # Go up
            next_idx = (current_idx[0] - 1, current_idx[1])
        # Coming in from right
        elif next_idx == (current_idx[0], current_idx[1] - 1):
            current_idx = next_idx 
            # Go down
            next_idx = (current_idx[0] + 1, current_idx[1])
        # Coming in from top
        elif next_idx == (current_idx[0] + 1, current_idx[1]):
            current_idx = next_idx 
            # Go left
            next_idx = (current_idx[0], current_idx[1] - 1)
        # Coming in from bottom
        elif next_idx == (current_idx[0] - 1, current_idx[1]):
            current_idx = next_idx 
            # Go right
            next_idx = (current_idx[0], current_idx[1] + 1)
        else:
            print('something has gone wrong in / mirror')

        energized |= propagate(grid, energized, visited, current_idx, next_idx)   
    elif next_tile == '\\': 
        # Coming in from left
        if next_idx == (current_idx[0], current_idx[1] + 1):
            current_idx = next_idx 
            # Go down
            next_idx = (current_idx[0] + 1, current_idx[1])
        # Coming in from right
        elif next_idx == (current_idx[0], current_idx[1] - 1):
            current_idx = next_idx 
            # Go up
            next_idx = (current_idx[0] - 1, current_idx[1])
        # Coming in from top
        elif next_idx == (current_idx[0] + 1, current_idx[1]):
            current_idx = next_idx 
            # Go right
            next_idx = (current_idx[0], current_idx[1] + 1)
        # Coming in from bottom
        elif next_idx == (current_idx[0] - 1, current_idx[1]):
            current_idx = next_idx 
            # Go left
            next_idx = (current_idx[0], current_idx[1] - 1)
        else:
            print('something has gone wrong in / mirror')

        energized |= propagate(grid, energized, visited, current_idx, next_idx)   

    return energized

def write_output(grid, filename):
    with open(filename, 'w') as f_out:     
        f_out.write('  ')
        f_out.write(''.join([f'{i:^3}' for i in range(grid.shape[0])]))
        f_out.write('\n')
        for iR, row in enumerate(grid):
            f_out.write(f'{iR:^2}')
            f_out.write(''.join([f'{c:^3}' for c in row]))
            f_out.write('\n')

with open('input.txt') as f_in:
    inner_grid = np.array([[c for c in line.strip()] for line in f_in.readlines()])
grid = np.full((inner_grid.shape[0] + 2, inner_grid.shape[1] + 2), '#')
grid[1:-1, 1:-1] = inner_grid
energized = np.full(grid.shape, 0)
visited = {}

current_idx = (1, 0)
next_idx = (1, 1)

propagate(grid, energized, visited, current_idx, next_idx)
print_grid(grid)
print_grid(energized)
print(f'Part 1: {np.sum(energized) - 1}')

write_output(grid, 'grid')
write_output(energized, 'energized')

# Part 2
energies = []
for iC in np.arange(1, grid.shape[1] - 1):
    # Top row
    current_idx = (0, iC)
    next_idx = (1, iC)
    
    visited = {}
    energized = np.full(grid.shape, 0)
    propagate(grid, energized, visited, current_idx, next_idx)
    energies.append(np.sum(energized) - 1)
    
    # Bottom row
    current_idx = (grid.shape[0] - 1, iC)
    next_idx = (grid.shape[0] - 2, iC)
    
    visited = {}
    energized = np.full(grid.shape, 0)
    propagate(grid, energized, visited, current_idx, next_idx)
    energies.append(np.sum(energized) - 1)

for iR in np.arange(1, grid.shape[0] - 1):
    # Left col
    current_idx = (iR, 0)
    next_idx = (iR, 1)
    
    visited = {}
    energized = np.full(grid.shape, 0)
    propagate(grid, energized, visited, current_idx, next_idx)
    energies.append(np.sum(energized) - 1)
    
    # Right col
    current_idx = (iR, grid.shape[1] - 1)
    next_idx = (iR, grid.shape[1] - 2)
    
    visited = {}
    energized = np.full(grid.shape, 0)
    propagate(grid, energized, visited, current_idx, next_idx)
    energies.append(np.sum(energized) - 1)

print(f'Part 2: {np.max(energies)}')































