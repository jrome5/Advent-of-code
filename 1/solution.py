# -*- coding: utf-8 -*-
# brief
# find the two entries that sum to 2020 and then multiply those two numbers together.
import csv

def readFile():
    values_list = []
    with open('values.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter='\r')
        line_count = 0
        for row in csv_reader:
            values_list.append(int(row[0]))
            line_count += 1
        print(f'Processed {line_count} lines.')
    return values_list


if __name__ == '__main__':
    values_list = readFile()
    result = 0
    sorted_list = sorted(values_list)
    indexA = 0
    indexB = len(sorted_list) -1
    valueA = 0
    valueB = 0
    while result != 2020:
        valueA = sorted_list[indexA]
        valueB = sorted_list[indexB]
        result = (valueA + valueB)
        if(result > 2020):
            indexB -= 1
        elif(result < 2020):
            indexA += 1
            indexB = len(sorted_list)-1
    print("indexA: " + str(valueA))
    print("indexB: " + str(valueB))
    print("result: " + str(valueA * valueB))
        
    
        
    