s = 'obwobobobxobooobobbsbobbsbobobobobtobaeo'
k=0
while s.find('bob')!=-1:
    k+=1
    s=s.replace('bob','b',1)
print('Number of times bob occurs is: '+str(k))
