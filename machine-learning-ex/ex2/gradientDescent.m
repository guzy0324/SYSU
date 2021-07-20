function [theta, J_history] = gradientDescent(X, y, initialTheta, alpha, num_iters)
    theta = initialTheta;
    [J, grad] = costFunction(theta, X, y);
    J_history = zeros(num_iters, 1);
    for i = 1:num_iters
        theta = theta - alpha * grad;
        [J, grad] = costFunction(theta, X, y);
        J_history(i) = J;
    end
end

