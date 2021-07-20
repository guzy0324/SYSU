%eliminate.m
function [UY] = eliminate(AB)
    for i = 2:size(AB, 1)
        for j = 1:(i - 1)
            AB(i, :) = AB(i, :) - AB(i, j) / AB(j, j) * AB(j, :);
        end
    end
    UY = AB;
end