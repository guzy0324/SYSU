x=float(raw_input('ԭ����'))
y=x/2
z=0.00000000001
a=float(raw_input('����������'))
while abs(y**a-x)>z:
        y=y-(y**a-x)/(2*y)
        b+=1
print(y)
