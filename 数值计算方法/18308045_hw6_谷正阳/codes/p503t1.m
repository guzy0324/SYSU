%p503t1
y=@(t)-exp(-t)+t^2-2*t+2;
plot(2, y(2), 'o')
hold on
R1 = rk4(@f,0,0+0.1*20,1,20)
plot(R1(:, 1), R1(:, 2), 'b')
R2 = rk4(@f,0,0+0.05*40,1,40)
plot(R2(:, 1), R2(:, 2), '-.')
xlabel('t')
ylabel('y')
legend('Exact', 'h=0.1', 'h=0.05')