/* EXAMPLE 5: Three Classes, method and data called from a different classes. */
program complex;
class myArray
{
  declarations
  int[] seq = int[10];
    enddeclarations
}

class arrayOperations
{
  method int sum ()
    declarations
  int s = 0;
  int i = 0;
    enddeclarations
  {
    while (i < myArray.seq.length)
      {
      s:= s + myArray.seq[i];
	i:= i + 1;
      };
    return (sum);
  }

  method void readArray (val int n)
    declarations
  int i = 0;
  enddeclarations
  {
    while (i < n)
      {
	System.readln (myArray.seq[i]);
      i:= i + 1;
      };
    if (x > 1)
      {
      x:= 2;
      }
    else
      {
      x:= 3;
      };

    if (x > 1)
      {
      x:= 2;
      }
    else
      {
	if (x > 1)
	  {
	  x:= 2;
	  }
	else
	  {
	  x:= 3;
	  };
      };

  }
}

class test
{
  method void main ()
  {
    arrayOperations.readArray (10);
    System.println (arrayOperations.sum);
  }
}
