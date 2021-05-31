# -*- coding: utf-8 -*-
import csv
import re

def readFile():
    values_list = []
    with open('input.txt') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter='\r')
        line_count = 0
        for row in csv_reader:
            values_list.append(row)
            line_count += 1
        print(f'Processed {line_count} lines.')
    return values_list

def checkValid(value, limits):
    for limit_set in limits:
        for i in range(0, len(limit_set), 2):
            lower = limit_set[i]
            higher = limit_set[i+1]
            if(lower <= value and value <= higher):
                return True
    return False

if __name__ == '__main__':
    values_list = readFile()
    questions_answered = []
    limits = []
    tickets = []
    limits_collected = False
    values_iter = iter(values_list)
    for line in values_iter:
        print(line)
        if(len(line) == 0):
            limits_collected = True
            continue
        if(line[0] == "your ticket:"):
            next(values_iter) #skip this line
            next(values_iter) #skip data line
            next(values_iter) #skip empty line 
        else:    
            values = (([int(s) for s in re.findall(r'\b\d+\b', line[0])]))
            if(limits_collected):
                tickets.append(values)
            else:
                limits.append(values)
    #check all nearby ticket values
    invalid_values = []
    count = 0
    for ticket in tickets:
        for value in ticket:
            if(not checkValid(value, limits)):
                invalid_values.append(value)
                count = count + value
    print(count)
            
                   
        
    
        
    
