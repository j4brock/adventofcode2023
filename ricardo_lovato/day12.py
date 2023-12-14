import re
from itertools import product
import functools

# All the parts of this code that works came from 
# https://www.reddit.com/r/adventofcode/comments/18hbbxe/2023_day_12python_stepbystep_tutorial_with_bonus/

def check_group(check_condition, groups):
    damaged = [len(d) for d in re.findall(r'(#+)', ''.join(check_condition))]
    if damaged == [] or len(damaged) != len(groups): 
        return False
    
    for item, group_len in zip(damaged, groups):
        if item != group_len:
            return False
    return True
    
def find_group_length(conditions, idx):
    group_len = 0
    current_item = conditions[idx]
    while current_item != '.':
        group_len += 1
        if idx + group_len >= len(conditions):
            break
        current_item = conditions[idx + group_len]
    
    return group_len

def get_positions(conditions, groups):
    unknown_idx = {r.span()[0]:find_group_length(conditions, r.span()[0]) for r in re.finditer('(\?)', ''.join(conditions))}
    # for idx, group_length in unknown_idx.items():
    #     print(''.join(conditions))
    #     print(' ' * idx + f'^{group_length}')

    group_positions = {}
    for iG, group in enumerate(groups):
        group_positions[iG] = []
        # print(f'Group length {group} can go in index:')
        for idx, group_length in unknown_idx.items():
            if group_length >= group:
                # print(f'\tindex {idx} of length {group_length}')
                group_positions[iG].append(idx)
    return unknown_idx, group_positions

def next_dot(record, groups):
    return fill_record(record[1:], groups)

def next_hash(record, groups):
    segment = record[0:groups[0]]
    segment = segment.replace('?', '#')
    # for idx in range(len(segment)):
    #     if segment[idx] == '?':
    #         segment[idx] = '#'

    if segment != '#' * groups[0]:
        return False
    
    if len(record) == groups[0]:
        if len(groups) == 1:
            return True
        else:
            return False
    
    if record[groups[0]] in ['?', '.']:
        return fill_record(record[groups[0] + 1::], groups[1::])
    
    return False

@functools.cache
def fill_record(record, groups):
    # print(record, groups)
    # current_char = record[0]
    # current_group = groups[0]
    if groups == ():
        if '#' not in record:
            return True
        else:
            return False
    
    if record == '':
        return False

    if record[0] == '.':
        # output = next_dot(record, groups)
        return fill_record(record[1:], groups)
    elif record[0] == '#':
        output = next_hash(record, groups)
    elif record[0] == '?':
        output = next_dot(record, groups) + next_hash(record, groups)

    # print(record, groups, output)
    return output


with open('input.txt') as f_in:
    lines = [line.strip() for line in f_in.readlines()]

record_lens = []
for iR, record in enumerate(lines):
    conditions, groups = record.split(' ')
    groups = [int(v) for v in groups.split(',')]

    # Part 2
    conditions = '?'.join([conditions] * 5)
    groups = groups * 5

    # conditions = [c for c in conditions]
    # unknown_idx, group_positions = get_positions(conditions, groups)

    # # If any group can only fit into one index, fill it in 
    # #   ex: .??..??...?##. 1,1,3
    # #       group 3 of length 3 can only fit in the last ?## position
    # solo_positions = {}
    # for iG, current_positions in group_positions.items():
    #     if len(current_positions) != 1: 
    #         continue
        
    #     solo_positions[iG] = []
    #     group_position = current_positions[0]
    #     for iP in range(group_position, group_position + unknown_idx[group_position]):
    #         conditions[iP] = '#'
    #         solo_positions[iG].append(iP)

    # # Delete the things we just updated 
    # groups = [num_items for iG, num_items in enumerate(groups) if iG not in solo_positions]
    # unknown_idx, group_positions = get_positions(conditions, groups)

    # new_conditions = []
    # for position in product('#.', repeat=len(unknown_idx)):
    #     new_condition = list(conditions)
        
    #     for (idx, _), p in zip(unknown_idx.items(), position):
    #         new_condition[idx] = p
    #     if check_group(new_condition, groups):
    #         new_conditions.append(new_condition)
    # record_lens.append(len(new_conditions))

    count = fill_record(''.join(conditions), tuple(groups))
    record_lens.append(count)

    
            
print(f'sum: {sum(record_lens)}')




































