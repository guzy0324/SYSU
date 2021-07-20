def gcdRecur(a, b):
    '''
    a, b: positive integers
    
    returns: a positive integer, the greatest common divisor of a & b.
    '''
    # Your code here
    c=max(a,b)
    d=min(a,b)
    if d==0:
     return c
    else:
     return gcdRecur(d,c%d)
