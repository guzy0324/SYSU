%hw2.m
km = 100;
[x_opt, sampling_opt] = optimization_method(@f, -1, 1, km);
[x_frac23, sampling_frac23] = frac23_method(@f, -1, 1, km);

error_opt = abs(x_opt);
error_frac23 = abs(x_frac23);

log_error_opt = log(error_opt);
log_error_frac23 = log(error_frac23);

k = 1:km;
P_log_error_opt_k = polyfit(k, log_error_opt, 1)
P_log_error_frac23_k = polyfit(k, log_error_frac23, 1)
P_log_error_opt_sampling = polyfit(sampling_opt, log_error_opt, 1)
P_log_error_frac23_sampling = polyfit(sampling_frac23, log_error_frac23, 1)
X1 = [k; ones(1, km)];
X2 = [1:2 * km; ones(1, 2 * km)];

figure;
plot(log_error_opt, '.');
hold on;
plot(log_error_frac23, '.');
plot(P_log_error_opt_k * X1, 'Linewidth', 1.5);
plot(P_log_error_frac23_k * X1, 'Linewidth', 1.5);
hold off;
legend('0.618法', '0.666法', '0.618法拟合', '0.666法拟合');
xlabel('k');
ylabel('log(error)');
title('log(error)-k图');

figure;
plot(sampling_opt, log_error_opt, '.');
hold on;
plot(sampling_frac23, log_error_frac23, '.');
plot(P_log_error_opt_sampling * X2, 'Linewidth', 1.5);
plot(P_log_error_frac23_sampling * X2, 'Linewidth', 1.5);
hold off;
legend('0.618法', '0.666法', '0.618法拟合', '0.666法拟合');
xlabel('sampling');
ylabel('log(error)');
title('log(error)-sampling图');
