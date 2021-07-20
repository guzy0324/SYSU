function [date_list, sum_list, temp_list, temp_sum_list] = plot_review_time(list)
    list = flipud(list);
    temp_list = convert_time(list(:, 8));
    date_list = sort(unique(temp_list), 'ascend');
    sum_list = zeros(size(date_list, 1), 1);
    sum_list(1) = length(find(temp_list == date_list(1)));
    
    temp_sum_list = zeros(size(temp_list, 1), 1);
    index = 1;
    while index <= size(temp_list, 1) && temp_list(index) == date_list(1)
        temp_sum_list(index) = sum_list(1);
        index = index + 1;
    end
    
    for i = 2:size(date_list, 1)
        sum_list(i, 1) =  sum_list(i - 1) + length(find(temp_list == date_list(i, 1)));
        while index <= size(temp_list, 1) && temp_list(index, 1) == date_list(i, 1)
            temp_sum_list(index, 1) = sum_list(i, 1);
            index = index + 1;
        end
    end
    figure
    plot(date_list, sum_list, 'r+');
    xlabel("date")
    ylabel("sum of reviews")
    title("original points");
end