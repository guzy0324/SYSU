%solve.m
function [solution] = solve(UV)
    solution = zeros(size(UV, 1), 1);
    for  i = 1:size(UV, 1) - 1
        for j = i + 1:size(UV, 1)
            UV(j, :) = UV(j, :) - UV(j, i) / UV(i, i) * UV(i, :);
        end
    end
    for  i = size(UV, 1):-1:1
        UV(i, :) = UV(i, :) / UV(i, i);
        solution(i) = UV(i, size(UV, 2));
        for j = 1:i - 1
            UV(j, :) = UV(j, :) - UV(j, i) / UV(i, i) * UV(i, :);
        end
    end
end