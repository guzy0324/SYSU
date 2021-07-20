function [out] = tf_idf(total, vec)
    tf = vec ./ total;
    idf = log(repmat(size(vec, 1), 1, size(vec, 2)) ./ (sum(vec ~= 0) + 1));
    out = tf .* idf;
end