function [] = plot_2_bar(y, leg, xla, yla)
    %y = [197.9 163.8;220.45 166.95;319 265.7]; % y轴数据（柱状图高度），两个分号之间为一组数据
    figure;
    bar(y); % 画柱状图

    %Cell = {'10', '20', '40'};
    %set(gca, 'XTick',1:3, 'XTickLabel',Cell);  % 设置在x轴[1,2,3]刻度上绘图，并把刻度重命名为[10,20,40]
    % set(gca, 'XLim',[0 4])    % 设置x轴刻度范围（可选）
    % set(gca, 'YLim',[0 360])  % 设置y轴刻度范围（此处将y轴刻度强制从0开始）
    ylabel(yla)
    % ylabel('Average Throughout (per Second)')  % 设置y轴标题
    xlabel(xla)  % 设置x轴标题
    legend(leg(1), leg(2))  % 设置图例，与y轴的一组数据从左到右一一对应
end

