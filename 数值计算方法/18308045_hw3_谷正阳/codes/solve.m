%solve.m
function [solution] = solve(UV)
    solution = zeros(size(UV, 1), 1);
    for  i = size(UV, 1):-1:1
        UV(i, :) = UV(i, :) / UV(i, i);
        for j = 1:(i - 1)
            UV(j, :) = UV(j, :) - UV(j, i) / UV(i, i) * UV(i, :);
        end
        solution(i) = UV(i, size(UV, 2));
    end
end