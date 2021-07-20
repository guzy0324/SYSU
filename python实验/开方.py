x=float(raw_input('原数：'))
y=x/2
z=0.00000000001
a=float(raw_input('开方次数：'))
while abs(y**a-x)>z:
        y=y-(y**a-x)/(2*y)
        b+=1
print(y)
