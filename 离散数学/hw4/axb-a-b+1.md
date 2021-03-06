题目：给定$a,b$且$gcd(a,b)=1$，求最大的$m$，使得$m$不能被表示为$ax+by(x\geq0,y\geq0)$的形式

aha！我被小学奥数题虐爆了

猜结论：答案是$ab-a-b$，当然猜出来还不够，我们还得证出来

用到一个引理：不定方程$ax+by=c(a,b,c\gt0)$一定有一组解$(x_1,y_1)$满足$-a\lt y_1\leq0$且$x_1\gt0$

先证引理

首先，显然$x,y$中至少有一个非负（都是负数怎么等于$c$）

然后假设有一组特解$(x_0,y_0)$，那么通解为$(x_0+bt,y_0-at)(t\in Z)$

所以有一组特解$(x_1,y_1)$满足$-a\lt y_1\leq0$

因为$y_1\leq0$，所以$x_1\gt0$

引理得证

再证原命题

$a=1$或$b=1$时命题成立，下面考虑$a\gt1,b\gt1$

分两步：

#1.证$ab-a-b\neq ax+by$

假设$ab-a-b=ax+by(x\geq0,y\geq0)$

那么$ab=a(x+1)+b(y+1)$

令$m=x+1,n=y+1(m\geq1,n\geq1)$，则$ab=am+bn$

所以$a|bn$

又因为$gcd(a,b)=1$，所以$a|n$，不妨设$n=an'$

上面的式子变为$ab=am+abn'$，推出$am=(1-n')ab\leq0$，矛盾！

原命题得证

#2.证$ab-a-b+t(t\geq1)$可以被分解为$ax+by$的形式

构造不定方程$au+bv=t$，由引理得它有一组特解满足$-a\lt v_0\leq0$且$u_0\gt0$

$ab-a-b+t=ab-a-b+au_0+bv_0=(u_0-1)a+(v_0+a-1)b$

因为$u_0-1\geq0,v_0+a-1\geq0$，所以原命题得证

所以，$ab-a-b$是最大的不能被表示为$ax+by$的整数