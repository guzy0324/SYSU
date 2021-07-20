polystr=input("输入一个多项式：")
def split(polystr):
    op=['+','-','*','/','(',')']
    poly=[]
    il=0
    for i in range(len(polystr)):
        while polystr[il] in op:
            poly.append(polystr[il])
            il+=1
        if polystr[i] in op and i>il:
            poly.append(float(polystr[il:i]))
            poly.append(polystr[i])
            il=i+1
    if polystr[-1]!=')':
        poly.append(float(polystr[il:len(polystr)]))
    return poly
def convert(poly):
    stack=[]
    temp=poly.copy()
    poly.clear()
    for i in temp:
        if isinstance(i,float):
            poly.append(i)
        elif i=='(':
            stack.append(i)
        elif i=='*' or i=='/':
            stack.append(i)
        elif i=='+' or i=='-':
            while stack!=[] and stack[-1]!='(':
                poly.append(stack.pop())
            stack.append(i)
        elif i==')':
            print(stack[-1])
            while stack[-1]!='(':
                poly.append(stack.pop())
            stack.pop()
    while stack!=[]:
        poly.append(stack.pop())
def calculate(poly):
    stack=[]
    tempStack=poly
    poly.reverse()
    while tempStack!=[]:
        if tempStack[-1]=='+':
            tempStack.pop()
            temp=stack[-2]+stack[-1]
            stack.pop()
            stack.pop()
            stack.append(temp)
        elif tempStack[-1]=='-':
            tempStack.pop()
            temp=stack[-2]-stack[-1]
            stack.pop()
            stack.pop()
            stack.append(temp)
        elif tempStack[-1]=='*':
            tempStack.pop()
            temp=stack[-2]*stack[-1]
            stack.pop()
            stack.pop()
            stack.append(temp)
        elif tempStack[-1]=='/':
            tempStack.pop()
            temp=stack[-2]/stack[-1]
            stack.pop()
            stack.pop()
            stack.append(temp)
        else:
            stack.append(tempStack.pop())
    return stack[0]
poly=split(polystr)
print(poly)
convert(poly)
print(poly)
print(calculate(poly))