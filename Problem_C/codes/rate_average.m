function [out_rate, out_time] = rate_average(rate, time)
    now = time(1);
    sum_rate = rate(1);
    sum_days = 1;
    out_time = sort(unique(time), 'ascend');
    out_rate = zeros(size(out_time, 1), 1);
    index = 1;
    for i = 2:size(rate, 1)
        if time(i, 1) == now
            sum_rate = sum_rate + rate(i, 1);
            sum_days = sum_days + 1;
        else
            out_rate(index, 1) = sum_rate / sum_days;
            now = time(i, 1);
            sum_rate = rate(i, 1);
            sum_days = 1;
            index = index + 1;
        end
    end
    out_rate(index) = sum_rate / sum_days;
end

