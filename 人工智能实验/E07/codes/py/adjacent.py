l = ['P32',
     'P42',
     'P52',
     'P33',
     'P53',
     'P34',
     'P44',
     'P54',
     'P64',
     'P74',
     'P25',
     'P35',
     'P45',
     'P55',
     'P65',
     'P75',
     'P26',
     'P36',
     'P27',
     'P37']
for pos1 in l:
    for pos2 in l:
        if abs(int(pos1[1]) - int(pos2[1]))\
        + abs(int(pos1[2]) - int(pos2[2])) == 1:
            print('(adjacent ' + pos1 + ' ' + pos2 + ')')
