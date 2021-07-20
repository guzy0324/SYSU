function [predict] = b_model(rate, time)
    predict = sum(rate .* sigmoid(time)) / sum(sigmoid(time));
end