function [] = plot_2_bar(y, leg, xla, yla)
    %y = [197.9 163.8;220.45 166.95;319 265.7]; % y�����ݣ���״ͼ�߶ȣ��������ֺ�֮��Ϊһ������
    figure;
    bar(y); % ����״ͼ

    %Cell = {'10', '20', '40'};
    %set(gca, 'XTick',1:3, 'XTickLabel',Cell);  % ������x��[1,2,3]�̶��ϻ�ͼ�����ѿ̶�������Ϊ[10,20,40]
    % set(gca, 'XLim',[0 4])    % ����x��̶ȷ�Χ����ѡ��
    % set(gca, 'YLim',[0 360])  % ����y��̶ȷ�Χ���˴���y��̶�ǿ�ƴ�0��ʼ��
    ylabel(yla)
    % ylabel('Average Throughout (per Second)')  % ����y�����
    xlabel(xla)  % ����x�����
    legend(leg(1), leg(2))  % ����ͼ������y���һ�����ݴ�����һһ��Ӧ
end

