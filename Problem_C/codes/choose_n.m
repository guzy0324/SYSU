function [ans_theta, ans_n] = choose_n(X, y)
    A = min(X):max(X);
    A = A';
    m = size(A, 1);
    if size(X, 1) ~= 1
        yy = interp1(X, y, A, 'Spline');
    else
        yy = y;
    end
    figure
    plot(A, yy, 'r+');
    xlabel("date")
    ylabel("sum of reviews")
    title("interpolated points");
    
    A = [ones(m, 1), A, A .^ 2, A .^ 3, A .^ 4, A .^ 5, A .^ 6];
    temp = [ones(size(X, 1), 1), X, X .^ 2, X .^ 3, X .^ 4, X .^ 5, X .^ 6];
    
    a = A(:, 1:2);
    ans_n = 2;
    ans_theta = pinv(a' * a) * a' * yy;
    min_J = (a * ans_theta - yy)' * (a * ans_theta - yy) / (2 * m);
    figure
    subplot(2, 3, 1);
    hold on
    plot(X, y, 'r+')
    subplot(2, 3, 1);
    plot(X, temp(:, 1:2) * ans_theta, 'b-')
    title(['n = 1    J = ', num2str(min_J)]);
    hold off
    
    for n = 3:7
        a = A(:, 1:n);
        theta = pinv(a' * a) * a' * yy;
        J = (a * theta - yy)' * (a * theta - yy) / (2 * m);
        subplot(2, 3, n - 1);
        hold on
        plot(X, y, 'r+')
        subplot(2, 3, n - 1);
        plot(X, temp(:, 1:n) * theta, 'b-')
        title(['n = ', num2str(n - 1), '    J = ', num2str(J)]);
        hold off
        if J < min_J
            ans_n = n;
            ans_theta = theta;
            min_J = J;
        end
    end
    
end

