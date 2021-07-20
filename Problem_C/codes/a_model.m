function [rate] = a_model(star_rate, helpful_vote, total_vote, review_sentiment, review_length)
    rate = star_rate + review_sentiment;
end