function [] = plot_b_model(list)
    list = flipud(list);
    star_rate = str2double(list(:, 3));
    helpful_vote = str2double(list(:, 4));
    total_vote = str2double(list(:, 5));
    review_sentiment = str2double(list(:, 9));
    review_length = str2double(list(:, 10));
    time = convert_time(list(:, 8));
    rate = a_model(star_rate, helpful_vote, total_vote, review_sentiment, review_length);
    
    predict = zeros(size(list, 1), 1);
    for i = 1:size(list, 1)
        predict(i, 1) = b_model(rate(1:i), helpful_vote(1:i), total_vote(1:i), review_length(1:i), time(1:i));
    end
    figure
    plot(time, predict, 'b+')
end

