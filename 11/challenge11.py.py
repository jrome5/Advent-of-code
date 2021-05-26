# -*- coding: utf-8 -*-
"""
Created on Thu Apr 22 13:40:41 2021

@author: jackrome
"""
import csv
import numpy as np
import copy
floor = '.'
occupied = '#'
free = 'L'

def readFile():
    values_list = []
    with open('input.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter='\r')
        line_count = 0
        for row in csv_reader:
            char_array = []
            for c in row[0]:
                char_array.append(c)
            values_list.append(char_array)
            line_count += 1
        print(f'Processed {line_count} lines.')
    return values_list

def search_adjacent(data, row, col):
    adjacent = 0
    #up left down right
    if(row > 0):
        adjacent += data[row-1][col] == occupied
    if(col > 0):
        adjacent += data[row][col-1] == occupied
    if(row < len(data)-1):
        adjacent += data[row+1][col] == occupied
    if(col < len(data[0])-1):
        adjacent += data[row][col+1] == occupied
    #diag left up
    if(row > 0 and col > 0):
        adjacent += data[row-1][col-1] == occupied
    #diag left down
    if((row < len(data)-1) and (col > 0)):
        adjacent += data[row+1][col-1] == occupied
    #diag right up
    if(row > 0 and (col < len(data[0])-1)):
        adjacent += data[row -1][col+1] == occupied
    if((row < len(data)-1) and (col < len(data[0])-1)):
        adjacent += data[row+1][col+1] == occupied
    return adjacent

def simulate_people(data):
    new_data = []
    for row in range(len(data)):
        new_row = []
        for col in range(len(data[0])):
            current_seat = data[row][col]
            if(current_seat == free):
                adjacent_cells = search_adjacent(data, row, col)
                if(adjacent_cells == 0):
                    new_row.append(occupied)
                else:
                    new_row.append(free)
            elif(current_seat == occupied):
                adjacent_cells = search_adjacent(data, row, col)
                if(adjacent_cells >= 4):
                    new_row.append(free)
                else:
                    new_row.append(occupied)
            else:
                new_row.append(floor)
        new_data.append(new_row)
    return new_data

def has_data_changed(old_data, new_data):
    for row in range(len(data)):
        for col in range(len(data[0])):
            if(old_data[row][col] != new_data[row][col]):
                return True
    return False
        
def display_data(data):
    print("data:")
    for row in range(len(data)):
        line = ""
        for col in range(len(data[0])):
            line += data[row][col]
        print(line)
          
def count_occupied(data):
    count = 0
    for row in range(len(data)):
        line = ""
        for col in range(len(data[0])):
            if(data[row][col] == occupied):
                count += 1
    return count
    

if __name__ == '__main__':
    data = readFile()
    #displayData(data)
    data_changed = True
    iterations = 0
    while(data_changed):
        new_data = simulate_people(data)
        iterations += 1
        print(iterations)
        data_changed = has_data_changed(data, new_data)
        data = copy.deepcopy(new_data)
    print(count_occupied(data))
    #displayData(data)
    
    