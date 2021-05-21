# -*- coding: utf-8 -*-
# brief
# find the two entries that sum to 2020 and then multiply those two numbers together.
import csv

def readFile():
    values_list = []
    with open('input.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter='\r')
        line_count = 0
        for row in csv_reader:
            values_list.append(row)
            line_count += 1
        print(f'Processed {line_count} lines.')
    return values_list


if __name__ == '__main__':
    values_list = readFile()
    questions_answered = []
    count = 0
    for line in values_list:
        if(len(line) == 0):
            questions_answered = []
        else:
            for q in line[0]:
                if not q in questions_answered:
                    questions_answered.append(q)
                    count = count + 1
    print(count)
            
                   
        
    
        
    