%frac23_method.m
function [x, sampling] = frac23_method(f, x0, x3, km)
    %f 目标函数
    %x0 区间左边界
    %x3 区间右边界
    %km 最大迭代次数
    c = 2/3;                %常数0.666
    k = 1;                  %第k次迭代
    x = zeros(1, km);       %记录计算当前步长随迭代次数变化的所有取值
    sampling = zeros(1, km);%记录采样数随迭代次数变化的所有取值
    x1 = x3 - c * (x3 - x0);%待比较点较小值
    x2 = c * (x3 - x0) + x0;%待比较点较大值
    f1 = f(x1);
    f2 = f(x2);
    sampling(1, k) = 2;

    while k <= km - 1
        if f1 >= f2
            x(1, k) = x2;
            k = k + 1;
            x0 = x1;
            x1 = x3 - c * (x3 - x0);
            x2 = c * (x3 - x0) + x0;
            f1 = f(x1);
            f2 = f(x2);
            sampling(1, k) = sampling(1, k - 1) + 2;
        else
            x(1, k) = x1;
            k = k + 1;
            x3 = x2;
            x2 = c * (x3 - x0) + x0;
            x1 = x3 - c * (x3 - x0);
            f2 = f(x2);
            f1 = f(x1);
            sampling(1, k) = sampling(1, k - 1) + 2;
        end
    end

    if f1 >= f2
        x(1, k) = x2;
    else
        x(1, k) = x1;
    end
end
