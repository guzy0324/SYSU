balance = 999999
annualInterestRate = 0.18
lo=balance/12
hi=balance*(1+annualInterestRate)**12/12
while True:
 mi=(lo+hi)/2
 mon=1
 b=balance
 while mon<=12:
  b=(b-mi)*(1+annualInterestRate/12)
  mon+=1
 if -0.1<b<0.1:
  print('Lowest Payment: '+str(round(mi,2)))
  break
 if b<=-0.1:
  hi=mi
 if b>=0.1:
  lo=mi
