def a(n):
    assert type(n)==int and n>=0
    if n==0 or n==1:
        return 1
    if n>1:
        return a(n-1)+a(n-2)
