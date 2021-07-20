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
        for pos3 in l:
            if (int(pos1[1]) - int(pos2[1]))\
            * (int(pos2[1]) - int(pos3[1])) == 1\
                and pos1[2] == pos2[2] and pos2[2] == pos3[2]:
                    print('(line ' + pos1 + ' '\
                        + pos2 + ' ' + pos3 + ')')
            elif (int(pos1[2]) - int(pos2[2]))\
            * (int(pos2[2]) - int(pos3[2])) == 1\
                and pos1[1] == pos2[1] and pos2[1] == pos3[1]:
                    print('(line ' + pos1 + ' '\
                        + pos2 + ' ' + pos3 + ')')

