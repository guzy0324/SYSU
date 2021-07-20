function [temp_sum_list, theta, n, d] = fit_products(list)
    [date_list, sum_list, temp_list, temp_sum_list] = plot_review_time(list);
    [theta, n] = choose_n(date_list, sum_list);
    d = density(theta, n, temp_list);
end