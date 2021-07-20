import os
import random
import time
class pool:
    __board=[]
    for __i in range(0,11):
        for __j in range(0,11):
            __board.append((__i,__j))
    def __init__(self):
        self.__deadF=0
        self.__screan=[]
        for i in range(0,11):
            self.__screan.append(list(' '*11).copy())
        self.__position=random.sample(self.__board, 11)
        t=turtle(self.__position[10])
        self.__screan[self.__position[10][0]][self.__position[10][1]]='0'
        print(self.__position[10][0])
        print(self.__position[10][1])
        print(self.__screan)
        f=[]
        for i in range(0,10):
            f.append(fish(self.__position[i]))
            self.__screan[self.__position[i][0]][self.__position[i][1]]='1'
        self.display()
        while True:
            time.sleep(0.1)
            self.onestep(t,f)
            self.display()
            if self.__deadF==10:
                print('Turtle win!')
                os.system("pause")
                break
            elif t.tellH()<=0:
                print('Fish win!')
                os.system("pause")
                break
    def onestep(self,t,f):
        t.move()
        self.__screan[self.__position[10][0]][self.__position[10][1]]=' '
        self.__position[10]=t.tellP()
        self.__screan[self.__position[10][0]][self.__position[10][1]]='0'
        for i in range(0,10):
            if self.__position[i]==(-1,-1):
                continue
            else:
                f[i].move()
                self.__screan[self.__position[i][0]][self.__position[i][1]]=' '
                self.__position[i]=f[i].tellP()
                self.__screan[self.__position[i][0]][self.__position[i][1]]='1'
                if self.__position[10]==self.__position[i]:
                    f[i].die()
                    self.__screan[self.__position[i][0]][self.__position[i][1]]=' '
                    self.__position[i]=(-1,-1)
                    self.__deadF+=1
                    t.eat()
    def display(self):
        os.system('cls')
        for i in range(0,11):
            for j in range(0,11):
                print(self.__screan[i][j],end='')
            print()
class turtle:
    def __init__(self,p):
        self.__px=p[0]
        self.__py=p[1]
        self.__hp=100
    def move(self):
        direction=random.randint(0,3)
        pace=random.randint(1,2)
        if direction==0:
            if self.__px-pace>=0:
                self.__px-=pace
            else:
                self.__px+=pace
        elif direction==1:
            if self.__px+pace<=10:
                self.__px+=pace
            else:
                self.__px-=pace
        elif direction==2:
            if self.__py-pace>=0:
                self.__py-=pace
            else:
                self.__py+=pace
        else:
            if self.__py+pace<=10:
                self.__py+=pace
            else:
                self.__py-=pace
        self.__hp-=1
    def tellP(self):
        return self.__px,self.__py
    def tellH(self):
        return self.__hp
    def eat(self):
        self.__hp+=20
class fish:
    def __init__(self,p):
        self.__px=p[0]
        self.__py=p[1]
    def move(self):
        direction=random.randint(0,3)
        pace=1
        if direction==0:
            if self.__px-pace>=0:
                self.__px-=pace
            else:
                self.__px+=pace
        elif direction==1:
            if self.__px+pace<=10:
                self.__px+=pace
            else:
                self.__px-=pace
        elif direction==2:
            if self.__py-pace>=0:
                self.__py-=pace
            else:
                self.__py+=pace
        else:
            if self.__py+pace<=10:
                self.__py+=pace
            else:
                self.__py-=pace
    def tellP(self):
        return self.__px,self.__py
    def die(self):
        self.__px=-1
        self.__py=-1
pool()