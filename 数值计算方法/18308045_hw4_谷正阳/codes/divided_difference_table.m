%divided_difference_table.m
function [t] = divided_difference_table(f)
    t = [f, zeros(size(f, 1), size(f, 1) - 1)];
    for i = 2:size(f, 1)
        t(i:size(f, 1), i) = (t(i:size(f, 1), i - 1) - t(i - 1:size(f, 1) - 1, i - 1)) / (i - 1);
    end
end