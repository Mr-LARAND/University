% Скрипт для визуализации метода наименьших квадратов
% Задача: линейная и квадратичная регрессия

clear all;
close all;
clc;

%% Экспериментальные данные
s = [1, 1.25, 1.5, 1.75, 2, 2.25, 2.5, 2.75, 3];
Q = [5.21, 4.196, 3.759, 3.672, 4.592, 4.621, 5.758, 7.173, 9.269];

N = length(s);

fprintf('\n=== МЕТОД НАИМЕНЬШИХ КВАДРАТОВ ===\n\n');

%% 1. ЛИНЕЙНАЯ РЕГРЕССИЯ Q = a + b*s

% Вычисляем необходимые суммы
sum_s = sum(s);
sum_Q = sum(Q);
sum_s2 = sum(s.^2);
sum_sQ = sum(s .* Q);
sum_Q2 = sum(Q.^2);

mean_s = mean(s);
mean_Q = mean(Q);

% Решаем систему уравнений для линейной регрессии
% [sum_s2  sum_s ] [b]   [sum_sQ]
% [sum_s   N     ] [a] = [sum_Q ]

A_lin = [sum_s2, sum_s;
         sum_s,  N];
b_vec = [sum_sQ; sum_Q];

coef_lin = A_lin \ b_vec;  % Решение системы
b_coef = coef_lin(1);
a_coef = coef_lin(2);

fprintf('Линейная регрессия: Q(s) = %.4f + %.4f*s\n', a_coef, b_coef);

% Коэффициент корреляции
numerator = N * sum_sQ - sum_s * sum_Q;
denominator = sqrt((N * sum_s2 - sum_s^2) * (N * sum_Q2 - sum_Q^2));
r = numerator / denominator;

fprintf('Коэффициент корреляции r = %.4f\n\n', r);

% Вычисляем предсказанные значения для линейной регрессии
Q_lin = a_coef + b_coef * s;

% Ошибки для линейной регрессии
errors_lin = Q - Q_lin;
SSE_lin = sum(errors_lin.^2);
MSE_lin = SSE_lin / N;
MAE_lin = mean(abs(errors_lin));
MARE_lin = mean(abs(errors_lin ./ Q) * 100);

fprintf('ЛИНЕЙНАЯ РЕГРЕССИЯ - Ошибки:\n');
fprintf('Суммарная квадратичная ошибка (SSE): %.6f\n', SSE_lin);
fprintf('Средняя квадратичная ошибка (MSE):   %.6f\n', MSE_lin);
fprintf('Средняя абсолютная ошибка (MAE):     %.6f\n', MAE_lin);
fprintf('Средняя относительная ошибка (MARE): %.2f%%\n\n', MARE_lin);

%% 2. КВАДРАТИЧНАЯ РЕГРЕССИЯ Q = A*s² + B*s + C

% Вычисляем дополнительные суммы
sum_s3 = sum(s.^3);
sum_s4 = sum(s.^4);
sum_s2Q = sum(s.^2 .* Q);

% Система нормальных уравнений для квадратичной регрессии
% [sum_s4  sum_s3  sum_s2] [A]   [sum_s2Q]
% [sum_s3  sum_s2  sum_s ] [B] = [sum_sQ ]
% [sum_s2  sum_s   N     ] [C]   [sum_Q  ]

A_quad = [sum_s4, sum_s3, sum_s2;
          sum_s3, sum_s2, sum_s;
          sum_s2, sum_s,  N];
b_quad = [sum_s2Q; sum_sQ; sum_Q];

coef_quad = A_quad \ b_quad;
A_parabola = coef_quad(1);
B_parabola = coef_quad(2);
C_parabola = coef_quad(3);

fprintf('Квадратичная зависимость: Q(s) = %.4f*s² + %.4f*s + %.4f\n\n', ...
        A_parabola, B_parabola, C_parabola);

% Вычисляем предсказанные значения для квадратичной регрессии
Q_quad = A_parabola * s.^2 + B_parabola * s + C_parabola;

% Ошибки для квадратичной регрессии
errors_quad = Q - Q_quad;
SSE_quad = sum(errors_quad.^2);
MSE_quad = SSE_quad / N;
MAE_quad = mean(abs(errors_quad));
MARE_quad = mean(abs(errors_quad ./ Q) * 100);

% Индекс корреляции
SST = sum((Q - mean_Q).^2);
R_squared = 1 - (SSE_quad / SST);
R_index = sqrt(R_squared);

fprintf('Индекс корреляции R = %.4f\n', R_index);
fprintf('Коэффициент детерминации R² = %.4f\n\n', R_squared);

fprintf('КВАДРАТИЧНАЯ РЕГРЕССИЯ - Ошибки:\n');
fprintf('Суммарная квадратичная ошибка (SSE): %.6f\n', SSE_quad);
fprintf('Средняя квадратичная ошибка (MSE):   %.6f\n', MSE_quad);
fprintf('Средняя абсолютная ошибка (MAE):     %.6f\n', MAE_quad);
fprintf('Средняя относительная ошибка (MARE): %.2f%%\n\n', MARE_quad);

%% 3. СРАВНЕНИЕ ВСТРОЕННЫХ ФУНКЦИЙ OCTAVE

% Линейная регрессия через polyfit
p_lin_octave = polyfit(s, Q, 1);
fprintf('Octave polyfit (линейная): Q(s) = %.4f + %.4f*s\n', ...
        p_lin_octave(2), p_lin_octave(1));

% Квадратичная регрессия через polyfit
p_quad_octave = polyfit(s, Q, 2);
fprintf('Octave polyfit (квадратичная): Q(s) = %.4f*s² + %.4f*s + %.4f\n\n', ...
        p_quad_octave(1), p_quad_octave(2), p_quad_octave(3));

%% 4. ПОСТРОЕНИЕ ГРАФИКОВ

% Создаем мелкую сетку для гладких кривых
s_fine = linspace(min(s), max(s), 100);
Q_lin_fine = a_coef + b_coef * s_fine;
Q_quad_fine = A_parabola * s_fine.^2 + B_parabola * s_fine + C_parabola;

% График 1: Все на одном графике
figure('Position', [100, 100, 1200, 800]);

subplot(2, 2, 1);
plot(s, Q, 'ko', 'MarkerSize', 12, 'LineWidth', 3, 'DisplayName', 'Эксп. данные');
hold on;
plot(s_fine, Q_lin_fine, 'b-', 'LineWidth', 2, 'DisplayName', 'Линейная регрессия');
plot(s_fine, Q_quad_fine, 'r-', 'LineWidth', 2, 'DisplayName', 'Квадратичная регрессия');
grid on;
xlabel('s', 'FontSize', 12);
ylabel('Q', 'FontSize', 12);
title('Сравнение методов регрессии', 'FontSize', 14, 'FontWeight', 'bold');
legend('Location', 'northwest', 'FontSize', 10);
set(gca, 'FontSize', 11);

% График 2: Только линейная регрессия
subplot(2, 2, 2);
plot(s, Q, 'ko', 'MarkerSize', 12, 'LineWidth', 3, 'DisplayName', 'Эксп. данные');
hold on;
plot(s_fine, Q_lin_fine, 'b-', 'LineWidth', 2.5, 'DisplayName', 'Линейная регрессия');
plot(s, Q_lin, 'bs', 'MarkerSize', 8, 'LineWidth', 2, 'DisplayName', 'Предсказания');
grid on;
xlabel('s', 'FontSize', 12);
ylabel('Q', 'FontSize', 12);
title(sprintf('Линейная регрессия (r = %.4f)', r), 'FontSize', 14, 'FontWeight', 'bold');
legend('Location', 'northwest', 'FontSize', 10);
set(gca, 'FontSize', 11);

% График 3: Только квадратичная регрессия
subplot(2, 2, 3);
plot(s, Q, 'ko', 'MarkerSize', 12, 'LineWidth', 3, 'DisplayName', 'Эксп. данные');
hold on;
plot(s_fine, Q_quad_fine, 'r-', 'LineWidth', 2.5, 'DisplayName', 'Квадратичная регрессия');
plot(s, Q_quad, 'rs', 'MarkerSize', 8, 'LineWidth', 2, 'DisplayName', 'Предсказания');
grid on;
xlabel('s', 'FontSize', 12);
ylabel('Q', 'FontSize', 12);
title(sprintf('Квадратичная регрессия (R = %.4f)', R_index), 'FontSize', 14, 'FontWeight', 'bold');
legend('Location', 'northwest', 'FontSize', 10);
set(gca, 'FontSize', 11);

% График 4: Ошибки
subplot(2, 2, 4);
bar_data = [SSE_lin, SSE_quad; MSE_lin, MSE_quad; MAE_lin, MAE_quad];
bar(bar_data);
set(gca, 'XTickLabel', {'SSE', 'MSE', 'MAE'});
ylabel('Величина ошибки', 'FontSize', 12);
title('Сравнение ошибок', 'FontSize', 14, 'FontWeight', 'bold');
legend('Линейная', 'Квадратичная', 'Location', 'northwest', 'FontSize', 10);
grid on;
set(gca, 'FontSize', 11);

% Сохраняем график
print -dpng 'regression_analysis.png' -r300;
fprintf('График сохранен в файл: regression_analysis.png\n');

% График 5: Детальное сравнение на большом графике
figure('Position', [150, 150, 1000, 700]);

plot(s, Q, 'ko', 'MarkerSize', 14, 'LineWidth', 4, 'DisplayName', 'Экспериментальные данные');
hold on;
plot(s_fine, Q_lin_fine, 'b-', 'LineWidth', 3, 'DisplayName', ...
     sprintf('Линейная: Q = %.4f + %.4f*s', a_coef, b_coef));
plot(s_fine, Q_quad_fine, 'r-', 'LineWidth', 3, 'DisplayName', ...
     sprintf('Квадратичная: Q = %.4f*s² + %.4f*s + %.4f', A_parabola, B_parabola, C_parabola));

% Добавляем вертикальные линии от точек до кривых (остатки)
for i = 1:N
    % Остатки для линейной регрессии
    plot([s(i), s(i)], [Q(i), Q_lin(i)], 'b:', 'LineWidth', 1.5);
    % Остатки для квадратичной регрессии
    plot([s(i), s(i)], [Q(i), Q_quad(i)], 'r:', 'LineWidth', 1.5);
end

grid on;
xlabel('s', 'FontSize', 14, 'FontWeight', 'bold');
ylabel('Q', 'FontSize', 14, 'FontWeight', 'bold');
title('Метод наименьших квадратов: линейная и квадратичная регрессия', ...
      'FontSize', 16, 'FontWeight', 'bold');
legend('Location', 'northwest', 'FontSize', 12);
set(gca, 'FontSize', 12);

% Добавляем текстовую аннотацию с метриками
text_str = {sprintf('Линейная: r = %.4f, SSE = %.4f', r, SSE_lin),
            sprintf('Квадратичная: R = %.4f, SSE = %.4f', R_index, SSE_quad)};
text(1.1, 8.5, text_str, 'FontSize', 11, 'BackgroundColor', 'white', ...
     'EdgeColor', 'black', 'LineWidth', 1.5);

% Сохраняем график
print -dpng 'regression_detailed.png' -r300;
fprintf('График сохранен в файл: regression_detailed.png\n');

% График 6: График остатков (residuals)
figure('Position', [200, 200, 1000, 600]);

subplot(1, 2, 1);
stem(s, errors_lin, 'b', 'LineWidth', 2, 'MarkerSize', 8);
hold on;
plot(s, zeros(size(s)), 'k--', 'LineWidth', 1.5);
grid on;
xlabel('s', 'FontSize', 12);
ylabel('Остатки (Q_{изм} - Q_{пред})', 'FontSize', 12);
title('Остатки линейной регрессии', 'FontSize', 14, 'FontWeight', 'bold');
set(gca, 'FontSize', 11);

subplot(1, 2, 2);
stem(s, errors_quad, 'r', 'LineWidth', 2, 'MarkerSize', 8);
hold on;
plot(s, zeros(size(s)), 'k--', 'LineWidth', 1.5);
grid on;
xlabel('s', 'FontSize', 12);
ylabel('Остатки (Q_{изм} - Q_{пред})', 'FontSize', 12);
title('Остатки квадратичной регрессии', 'FontSize', 14, 'FontWeight', 'bold');
set(gca, 'FontSize', 11);

% Сохраняем график
print -dpng 'residuals_plot.png' -r300;
fprintf('График сохранен в файл: residuals_plot.png\n');

fprintf('\nВсе графики успешно построены!\n');
fprintf('\n=== ЗАКЛЮЧЕНИЕ ===\n');
fprintf('Квадратичная регрессия лучше описывает данные:\n');
fprintf('  - Меньше SSE: %.4f < %.4f\n', SSE_quad, SSE_lin);
fprintf('  - Выше индекс корреляции: R = %.4f > r = %.4f\n', R_index, r);
fprintf('  - Меньше средняя ошибка: MAE = %.4f < %.4f\n', MAE_quad, MAE_lin);
