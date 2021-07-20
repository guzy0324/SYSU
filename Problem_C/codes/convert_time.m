function [date_list] = convert_time(temp_list)
    date_list = datetime('now');
    date_list = repmat(date_list, size(temp_list, 1), 1);
    for i = 1:size(temp_list, 1)
        temp = strsplit(temp_list(i), '/');
        temp = [str2double(temp(3)), str2double(temp(1)), str2double(temp(2))];
        date_list(i, 1) = datetime(temp);
    end
    date_list = datenum(date_list - date_list(1));
end

