#include<stdio.h>
int main() 
{
double payRate, workHours, wages;
printf("please enter the payRate: " );
scanf("%lf", & payRate );
printf("please enter the workHours: " );
scanf("%lf", &workHours );
/*printf("%f",workHours);*/
if ( workHours <=40 )
wages = workHours * payRate;
else
wages = 40*payRate +( workHours-40 ) * payRate * 1.5;
printf("%lf",wages);
return 0;
}
