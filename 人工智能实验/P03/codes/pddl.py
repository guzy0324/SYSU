#coding=utf-8
from functools import *
from itertools import * 
from copy import *
from time import *

movevec = []
prevec = []
iniku = []
goalyes = []
goalno = []
statelib = []
statecircle = []
types = []
ob = []
actionku = []

class pre(object):
    def __init__(self):
        self.name = ''
        self.order = []
        self.bian = []
        self.num = 0

    def dealpre(self,line):
        self.name = line[0][1:len(line[0])]
        self.order = []
        self.bian = []
        self.num = 0
        for i in range(1,len(line)):
            if(line[i][0]=='?'):
                self.num = self.num + 1

class move(object):
    def __init__(self,thename):
        self.name = thename
        self.par = []
        self.duplicate = []
        self.type = []
        self.precon = []
        self.prenot = []
        self.adds = []
        self.dels = []
    def para(self,line):
        for i in range(1,len(line)):
            if(line[i][0]=='?'):
                nowbian = line[i][1:len(line[i])]
                self.par.append(nowbian)
                self.duplicate.append(None)
            elif(line[i][0]=='(' and line[i][1]=='?'):
                nowbian = line[i][2:len(line[i])]
                self.par.append(nowbian)
                self.duplicate.append(None)
            elif(line[i][0]=='-'):
                nowtype = line[i][1:len(line[i])]
                if(nowtype[-1]==')'):
                    nowtype = nowtype[0:len(nowtype)-1]
                wei = -1
                for j in range(0,len(types)):
                    if(types[j]==nowtype):
                        wei = j
                        break
                if(wei==-1):
                    print("error!")
                else:
                    self.type.append(wei)
      
    def prec(self,line):
        zheng = 1
        shide = -1
        for i in range(0,len(line)):
            nowprec = line[i][1:len(line[i])]
            if(nowprec=='not'):
                zheng = -1
            else:
                shide = -1
                for j in range(0,len(prevec)):
                    if(prevec[j].name==nowprec):
                        shide = j
                        break
                if(shide!=-1):
                    num = prevec[shide].num
                    thisprec = pre()
                    thisprec.name = nowprec
                    for j in range(0,num):
                        nowbian = line[i+j+1][1:len(line[i+j+1])]
                        while 1:
                            if(nowbian[len(nowbian)-1]!=')'):
                                break
                            else:
                                nowbian = nowbian[0:len(nowbian)-1]
                        thisprec.bian.append(nowbian)
                        thisprec.order.append(None)
                    if(zheng==1):
                        self.precon.append(thisprec)
                    else:
                        self.prenot.append(thisprec)
                        zheng = 1

    def effe(self,line):
        zheng = 1
        shide = -1
        for i in range(0,len(line)):
            nowprec = line[i][1:len(line[i])]
            if(nowprec=='not'):
                zheng = -1
            else:
                shide = -1
                for j in range(0,len(prevec)):
                    if(prevec[j].name==nowprec):
                        shide = j
                        break
                if(shide!=-1):
                    num = prevec[shide].num
                    thisprec = pre()
                    thisprec.name = nowprec
                    for j in range(0,num):
                        nowbian = line[i+j+1][1:len(line[i+j+1])]
                        while 1:
                            if(nowbian[len(nowbian)-1]!=')'):
                                break
                            else:
                                nowbian = nowbian[0:len(nowbian)-1]
                        thisprec.bian.append(nowbian)
                        thisprec.order.append(None)
                    if(zheng==1):
                        self.adds.append(thisprec)
                    else:
                        self.dels.append(thisprec)
                        zheng = 1

def managedomain():
    filename = input("domain file：")
    f = open(filename,"r")
    status = 0
    movenum = 0
    while 1:
        oneline = f.readline()
        if(not oneline):
            break
        if(status==0):
            line = oneline.split()
            if(line[0]=='(:types'):
                for i in range(1,len(line)):
                    thetype = line[i]
                    if(thetype[-1]==')'):
                        thetype = thetype[0:len(thetype)-1]
                    types.append(thetype)
                    ob.append([])
            if(line[0]=='(:predicates'):
                status = 1
        elif(status==1):
            line = oneline.split()
            if(line[0]==')'):
                status = 2
            else:
                thisprec = pre()
                thisprec.dealpre(line)
                prevec.append(thisprec)
        elif(status==2):
            line = oneline.split()
            if(line[0]=='(:action'):
                movevec.append(move(line[1]))
                line = f.readline().split()
                movevec[movenum].para(line)
                line = f.readline().split()
                movevec[movenum].prec(line)
                line = f.readline().split()
                movevec[movenum].effe(line)
                line = f.readline()
                movenum = movenum + 1

def manageproblem():
    filename = input("problem file：")
    f = open(filename,"r")
    zheng = 1
    while 1:
        oneline = f.readline().split()
        if(not oneline):
            break
        if(oneline[0]=='(:init'):
            for i in range(0,len(oneline)):
                wei = -1
                nowprename = oneline[i][1:len(oneline[i])]
                for j in range(0,len(prevec)):
                    if(nowprename==prevec[j].name):
                        wei = j
                        break
                if(wei!=-1):
                    num = prevec[wei].num
                    thispre = pre()
                    thispre.name = nowprename
                    for j in range(0,num):
                        nowbian = oneline[i+j+1]
                        while 1:
                            if(nowbian[len(nowbian)-1]!=')'):
                                break
                            else:
                                nowbian = nowbian[0:len(nowbian)-1]
                        thispre.order.append(nowbian)
                    iniku.append(thispre)
        elif(oneline[0]=='(:goal'):
            for i in range(0,len(oneline)):
                wei = -1
                nowprename = oneline[i][1:len(oneline[i])]
                if(nowprename=='not'):
                    zheng = -1
                else:
                    for j in range(0,len(prevec)):
                        if(nowprename==prevec[j].name):
                            wei = j
                            break
                    if(wei!=-1):
                        num = prevec[wei].num
                        thispre = pre()
                        thispre.name = nowprename
                        for j in range(0,num):
                            nowbian = oneline[i+j+1]
                            while 1:
                                if(nowbian[len(nowbian)-1]!=')'):
                                    break
                                else:
                                    nowbian = nowbian[0:len(nowbian)-1]
                            thispre.order.append(nowbian)
                        if(zheng==1):
                            goalyes.append(thispre)
                        else:
                            goalno.append(thispre)
                            zheng = 1
        elif(oneline[0]=='(:objects'):
            while 1:
                oneline = f.readline().split()
                if(oneline[0]==')'):
                    break
                thislei = oneline[-1][1:len(oneline[-1])]
                for i in range(0,len(types)):
                    if(thislei==types[i]):
                        for j in range(0,len(oneline)-1):
                            ob[i].append(oneline[j])

def actduplicate(themove):
    onemove = move('')
    onemove = deepcopy(themove)
    for i in onemove.precon:
        for j in range(0,len(i.bian)):
            wei = -1
            for k in range(0,len(onemove.par)):
                if(i.bian[j]==onemove.par[k]):
                    wei = k
                    break
            if(wei==-1):
                print("error")
            else:
                i.order[j] = onemove.duplicate[wei]
    for i in onemove.prenot:
        for j in range(0,len(i.bian)):
            wei = -1
            for k in range(0,len(onemove.par)):
                if(i.bian[j]==onemove.par[k]):
                    wei = k
                    break
            if(wei==-1):
                print("error")
            else:
                i.order[j] = onemove.duplicate[wei]
    for i in onemove.adds:
        for j in range(0,len(i.bian)):
            wei = -1
            for k in range(0,len(onemove.par)):
                if(i.bian[j]==onemove.par[k]):
                    wei = k
                    break
            if(wei==-1):
                print("error")
            else:
                i.order[j] = onemove.duplicate[wei]
    for i in onemove.dels:
        for j in range(0,len(i.bian)):
            wei = -1
            for k in range(0,len(onemove.par)):
                if(i.bian[j]==onemove.par[k]):
                    wei = k
                    break
            if(wei==-1):
                print("error")
            else:
                i.order[j] = onemove.duplicate[wei]
    return onemove            

def getactionlib():
    for i in movevec:
        funum = len(i.par)
        if(funum==1):
            for d in product(ob[i.type[0]]):
                i.duplicate[0] = d[0]
                themove = actduplicate(i)
                actionku.append(themove)
        elif(funum==2):
            for d in product(ob[i.type[0]],ob[i.type[1]]):
                i.duplicate[0] = d[0]
                i.duplicate[1] = d[1]
                themove = actduplicate(i)
                actionku.append(themove)            
        elif(funum==3):
            for d in product(ob[i.type[0]],ob[i.type[1]],ob[i.type[2]]):
                i.duplicate[0] = d[0]
                i.duplicate[1] = d[1]
                i.duplicate[2] = d[2]
                themove = actduplicate(i)
                actionku.append(themove) 
        elif(funum==4):
            for d in product(ob[i.type[0]],ob[i.type[1]],ob[i.type[2]],ob[i.type[3]]):
                i.duplicate[0] = d[0]
                i.duplicate[1] = d[1]
                i.duplicate[2] = d[2]
                i.duplicate[3] = d[3]
                themove = actduplicate(i)
                actionku.append(themove) 
        else:
            print("error!")


def CountActions(G,num,theS,theA):
    if(num==0):
        return 0
    else:
        GP = []
        GN = []
        for i in G:
            if(isinku(i,theS[num-1])):
                GP.append(i)
            else:
                GN.append(i)
        NewG = deepcopy(GP)
        for i in theA[num-1]:
            for j in i.precon:
                if(isinku(j,NewG)==0):
                    NewG.append(j)
        newnum = num-1
        return CountActions(NewG,newnum,theS,theA) + len(theA[num-1])

def specantake(oneact,nowku):
    keyi = 1
    for i in oneact.precon:
        if(isinku(i,nowku)==0):
            keyi = 0
            break
    return keyi    



def heuristic(thestate):
    num = 0
    theS = []
    theA = []
    theS.append([])
    theS[0] = deepcopy(thestate.ku)
    lastnum = len(theS[0])
    while 1:
        if(isgoal(theS[num])==1):
            break
        else:
            theS.append([])
            theA.append([])
            num = num + 1
            theS[num] = deepcopy(theS[num-1])
            for i in actionku:
                if(specantake(i,theS[num-1])==1):
                    theA[num-1].append(i)
            for i in theA[num-1]:
                for j in i.adds:
                    if(isinku(j,theS[num])==0):
                        theS[num].append(j)
            thisnum = len(theS[num])
            if(lastnum==thisnum):
                return 10000
            else:
                lastnum = thisnum          
    if(num==0):
        return 0
    else:
        iniG = deepcopy(iniku)
        return CountActions(iniG,num,theS,theA)

def isgoal(theku):
    goalnum = 1
    for i in goalyes:
        if(isinku(i,theku)==0):
            goalnum = 0
            break
    return goalnum    

class state(object):
    def __init__(self):
        self.h = 0
        self.g = 0
        self.order = 0
        self.ku = []
        self.havetake = []

def isinku(onepre,preku):
    zai = 0
    for i in preku:
        if(i.name==onepre.name):
            deng = 1
            for j in range(0,len(i.order)):
                #print(onepre.order[j])
                #print(i.order[j])
                if(onepre.order[j]!=i.order[j]):
                    deng = 0
                    break
            if(deng==1):
                zai = 1
                break
    return zai 

def getgoal(nowstate):
    goalnum = 1
    for i in goalyes:
        if(isinku(i,nowstate.ku)==0):
            goalnum = 0
            break
    for i in goalno:
        if(isinku(i,nowstate.ku)==1):
            goalnum = 0
            break
    return goalnum


def cantake(oneact,nowku):
    keyi = 1
    for i in oneact.precon:
        if(isinku(i,nowku)==0):
            keyi = 0
            break
    if(keyi==1):
        for i in oneact.prenot:
            if(isinku(i,nowku)==1):
                keyi = 0
                break
    return keyi

def getnextstate(nowstate):
    nextstatelib = []
    thenum = 0
    for i in actionku:
        if(cantake(i,nowstate.ku)==1):
            nextstatelib.append(state())
            nextstatelib[thenum] = deepcopy(nowstate)

            for j in i.dels:
                if(isinku(j,nextstatelib[thenum].ku)==1):
                    wei = -1
                    for k in range(0,len(nextstatelib[thenum].ku)):
                        if(j.name==nextstatelib[thenum].ku[k].name):
                            deng = 1
                            for m in range(0,len(j.order)):
                                if(nextstatelib[thenum].ku[k].order[m]!=j.order[m]):
                                    deng = 0
                                break
                            if(deng==1):
                                wei = k
                                break    
                    if(wei==-1):
                        print("error!")
                    nextstatelib[thenum].ku.pop(wei)

            for j in i.adds:
                if(isinku(j,nextstatelib[thenum].ku)==0):
                    nextstatelib[thenum].ku.append(j)

            nextstatelib[thenum].g = heuristic(nextstatelib[thenum])
            nextstatelib[thenum].h = nowstate.h + 1
            nextstatelib[thenum].order = nextstatelib[thenum].g + nextstatelib[thenum].h
            nextstatelib[thenum].havetake.append(i)
            thenum = thenum + 1

    return nextstatelib


def huan(nowstate):
    zai = 0
    for i in statecircle:
        if(len(i.ku)==len(nowstate.ku)):
            shi = 1
            for j in nowstate.ku:
                if(isinku(j,i.ku)==0):
                    shi = 0
                    break
            if(shi==1):
                zai = 1
                break
    return zai

def cmp(a,b):
    if(a.order<b.order):
        return -1
    if(a.order>b.order):
        return 1
    return 0



def printpre(thepre,num):
    print(thepre.name)
    if(num==0):
        for i in thepre.bian:
            print(i,end = ' ')
    else:
        for i in thepre.order:
            print(i,end = ' ')
    print("")

def printmove(themove):
    print(themove.name,end = ' ( ')
    for i in themove.duplicate:
        print(i,end = ' ')
    print(")")

def printstate(thestate):
    print(thestate.g)
    print(thestate.h)
    print("\nku:")
    for i in thestate.ku:
        printpre(i, 1)
    print("\nmove:")
    for i in thestate.havetake:
        printmove(i)




def Astar():
    global statelib
    global statecircle
    while 1:
        nowstate = statelib.pop()
        if(getgoal(nowstate)==1):
            print("result as follows：")
            for i in nowstate.havetake:
                printmove(i)
            break
        else:
            nextstatelib = getnextstate(nowstate)
            for i in nextstatelib:
                if(huan(i)==0):
                    statelib.append(i)
                    statecircle.append(i)
            statelib = sorted(statelib,key=cmp_to_key(cmp))



ticks1 = process_time()
managedomain()
manageproblem()
getactionlib()
inistate = state()
inistate.ku = deepcopy(iniku)
inistate.g = heuristic(inistate)
inistate.h = 0
inistate.order = inistate.g + inistate.h
statelib.append(inistate)
statecircle.append(inistate)
Astar()
ticks2 = process_time()
print("time cost: %f"%(ticks2-ticks1))

