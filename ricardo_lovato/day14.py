import numpy as np

def tilt_table(loc_direction, rocks, cubes):
    movement = True
    while movement:
        movement = False
        for rock_loc in list(rocks.keys()):
            new_loc = (rock_loc[0] + loc_direction[0], rock_loc[1] + loc_direction[1])
            if new_loc not in cubes and new_loc not in rocks:

                while new_loc not in cubes and new_loc not in rocks:
                    new_loc = (new_loc[0] + loc_direction[0], new_loc[1] + loc_direction[1])
                del rocks[rock_loc]
                rocks[(new_loc[0] - loc_direction[0], new_loc[1] - loc_direction[1])] = 0
                movement = True

def visualize_platform(platform, rocks, cubes):
    print(platform)
    print()
    test_platform = np.full(platform.shape, '.')
    for cube_location, _ in cubes.items():
        test_platform[cube_location] = '#'
    for rock_location, _ in rocks.items():
        test_platform[rock_location] = 'O'
    print(test_platform)

    total_load = calculate_load(test_platform)
    print(f'Total load: {total_load}')

def calculate_load(platform):
    load = []
    for iR in np.arange(platform.shape[0]):
        num_rocks = len([idx for idx, c in enumerate(platform[iR]) if c == 'O'])
        load.append((platform.shape[0] - iR - 1 , num_rocks))

    total_load = sum([a * b for a, b in load])
    # print(f'Total load: {total_load}')
    return total_load

def get_locations(platform):
    cubes = {}
    rocks = {}
    for iR in np.arange(platform.shape[0]):
        for iC in np.arange(platform.shape[1]):
            if platform[iR][iC] == 'O':
                rocks[(iR, iC)] = 0
            elif platform[iR][iC] == '#':
                cubes[(iR, iC)] = 0
    return cubes, rocks

with open('input.txt') as f_in:
    contents = np.array([[c for c in line.strip()] for line in f_in.readlines()])

# Ring of cubes along the outside to simplify bound checks
platform = np.full((contents.shape[0] + 2, contents.shape[1] + 2), '#')
platform[1:platform.shape[0] - 1, 1:platform.shape[1] - 1] = contents

directions = {'N':(-1, 0),
              'S':(1, 0),
              'E':(0, 1),
              'W':(0, -1)}

# Part 1
cubes, rocks = get_locations(platform)
loc_direction = directions['N']
tilt_table(loc_direction, rocks, cubes)
visualize_platform(platform, rocks, cubes)


# Ring of cubes along the outside to simplify bound checks
platform = np.full((contents.shape[0] + 2, contents.shape[1] + 2), '#')
platform[1:platform.shape[0] - 1, 1:platform.shape[1] - 1] = contents

# The platform positions become periodic after a certain number
# The number isnt 300 but 300 is high enough to capture the repeat
# interval and i dont want to optimize this 
first_repeat = None
repeats = []
platforms = {}
# Reset locations for part 2
cubes, rocks = get_locations(platform)
for cycle in np.arange(300):
    for direction in ['N', 'W', 'S', 'E']:
        loc_direction = directions[direction]
        tilt_table(loc_direction, rocks, cubes)

        test_platform = np.full(platform.shape, '.')
        for cube_location, _ in cubes.items():
            test_platform[cube_location] = '#'
        for rock_location, _ in rocks.items():
            test_platform[rock_location] = 'O'
        
        platform_key = tuple(test_platform.ravel())
        if platform_key in platforms:
            repeat_num = list(platforms.keys()).index(platform_key)
            total_load = calculate_load(test_platform)
            # print(f'Cycle {cycle}, {direction} - {repeat_num} - load {total_load}')
            if first_repeat is None:
                first_repeat = (cycle, direction, repeat_num)
            if direction == 'E':
                # print(f'Cycle {cycle}, {direction} - {repeat_num} - load {total_load}')
                repeats.append((cycle, direction, repeat_num))
        else:
            total_load = calculate_load(test_platform)
            # print(f'Cycle {cycle}, {direction} - #keys {len(platforms)} - load {total_load}')
            platforms[platform_key] = test_platform


platform_keys = list(platforms.keys())
start_cycle, _, start_key = repeats[0]
repeat_interval = [repeat[2] for repeat in repeats[1:]].index(repeats[0][2]) + 1
interval_keys = [repeat[2] for repeat in repeats[0:repeat_interval]]

# # Output for testing 
# for cycle_num, repeat in enumerate(repeats):
#     current_cycle = start_cycle + cycle_num
#     current_key = (current_cycle - start_cycle) % repeat_interval
#     current_key = interval_keys[current_key]
    
#     platform = platforms[platform_keys[current_key]]
#     total_load = calculate_load(platform)
#     print(f'{repeat[0]} ({current_cycle})\t{repeat[2]} ({current_key}) - {total_load}')


# Calculate the position in the repeat interval and use that platform
current_cycle = 1000000000 - 1
current_key = (current_cycle - start_cycle) % repeat_interval
current_key = interval_keys[current_key]

platform = platforms[platform_keys[current_key]]
total_load = calculate_load(platform)
print(f'Total load: {total_load}')














