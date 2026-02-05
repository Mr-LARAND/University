% Скрипт для визуализации результатов интерполяции
% Очищаем рабочее пространство
clear all;
close all;
clc;

% Экспериментальные данные
x = [0.68, 0.73, 0.80, 0.88, 0.93, 0.99];
y = [0.80866, 0.89492, 1.02964, 1.20966, 1.34087, 1.52368];

% Точки для интерполяции
x_interp = [0.896, 0.774, 0.955];

% Создаем мелкую сетку для построения графиков
x_fine = linspace(min(x), max(x), 100);

%% 1. Интерполяционный полином Лагранжа
function y = lagrange_interp(x_data, y_data, t)
    n = length(x_data);
    y = 0;

    % Для каждой точки данных
    for i = 1:n
        % Вычисляем базисный полином Лагранжа L_i(t)
        L = 1;
        for j = 1:n
            if j ~= i
                L = L * (t - x_data(j)) / (x_data(i) - x_data(j));
            end
        end
        % Суммируем y_i * L_i(t)
        y = y + y_data(i) * L;
    end
end

%% 2. Интерполяционный полином Ньютона
function y = newton_interp(x_data, y_data, t)
    n = length(x_data);

    % Создаем таблицу разделенных разностей
    C = zeros(n, n);
    C(:, 1) = y_data';  % Первый столбец - значения y

    % Вычисляем разделенные разности
    for j = 2:n
        for i = j:n
            C(i, j) = (C(i, j-1) - C(i-1, j-1)) / (x_data(i) - x_data(i-j+1));
        end
    end

    % Вычисляем значение полинома Ньютона
    y = C(1, 1);
    prod = 1;

    for i = 2:n
        prod = prod * (t - x_data(i-1));
        y = y + C(i, i) * prod;
    end
end

%% 3. Канонический полином (встроенная функция polyfit)
% Коэффициенты полинома степени n-1
n = length(x);
p_canonical = polyfit(x, y, n-1);

%% 4. Линейная интерполяция (встроенная функция)
% Используется для сравнения

%% 5. Сплайн-интерполяция (встроенная функция)
% Используется для сравнения

%% Вычисляем значения для всех методов

% Для мелкой сетки (для графиков)
y_lagrange_fine = zeros(size(x_fine));
y_newton_fine = zeros(size(x_fine));
for i = 1:length(x_fine)
    y_lagrange_fine(i) = lagrange_interp(x, y, x_fine(i));
    y_newton_fine(i) = newton_interp(x, y, x_fine(i));
end
y_canonical_fine = polyval(p_canonical, x_fine);
y_linear_fine = interp1(x, y, x_fine, 'linear');
y_spline_fine = interp1(x, y, x_fine, 'spline');

% Для точек интерполяции (x1, x2, x3)
y_lagrange_points = zeros(size(x_interp));
y_newton_points = zeros(size(x_interp));
for i = 1:length(x_interp)
    y_lagrange_points(i) = lagrange_interp(x, y, x_interp(i));
    y_newton_points(i) = newton_interp(x, y, x_interp(i));
end
y_canonical_points = polyval(p_canonical, x_interp);
y_linear_points = interp1(x, y, x_interp, 'linear');
y_spline_points = interp1(x, y, x_interp, 'spline');

%% Выводим результаты в консоль
fprintf('\n=== РЕЗУЛЬТАТЫ ИНТЕРПОЛЯЦИИ ===\n\n');
fprintf('Точки для интерполяции:\n');
fprintf('x1 = %.3f, x2 = %.3f, x3 = %.3f\n\n', x_interp(1), x_interp(2), x_interp(3));

fprintf('%-15s%-15s%-15s%-15s%-15s%-15s\n', 'Точка', 'Лагранж', 'Ньютон', 'Канонич.', 'Линейная', 'Сплайн');
fprintf('------------------------------------------------------------------------\n');

for i = 1:length(x_interp)
    fprintf('x = %-10.3f%-15.6f%-15.6f%-15.6f%-15.6f%-15.6f\n', ...
        x_interp(i), ...
        y_lagrange_points(i), ...
        y_newton_points(i), ...
        y_canonical_points(i), ...
        y_linear_points(i), ...
        y_spline_points(i));
end

%% Построение графиков

% График 1: Все методы на одном графике
figure('Position', [100, 100, 1200, 800]);

subplot(2, 3, 1);
plot(x, y, 'ko', 'MarkerSize', 10, 'LineWidth', 2, 'DisplayName', 'Эксп. данные');
hold on;
plot(x_fine, y_lagrange_fine, 'b-', 'LineWidth', 2, 'DisplayName', 'Лагранж');
plot(x_interp, y_lagrange_points, 'r*', 'MarkerSize', 12, 'LineWidth', 2, 'DisplayName', 'Интерп. точки');
grid on;
xlabel('x');
ylabel('y');
title('Интерполяция Лагранжа');
legend('Location', 'northwest');

subplot(2, 3, 2);
plot(x, y, 'ko', 'MarkerSize', 10, 'LineWidth', 2, 'DisplayName', 'Эксп. данные');
hold on;
plot(x_fine, y_newton_fine, 'g-', 'LineWidth', 2, 'DisplayName', 'Ньютон');
plot(x_interp, y_newton_points, 'r*', 'MarkerSize', 12, 'LineWidth', 2, 'DisplayName', 'Интерп. точки');
grid on;
xlabel('x');
ylabel('y');
title('Интерполяция Ньютона');
legend('Location', 'northwest');

subplot(2, 3, 3);
plot(x, y, 'ko', 'MarkerSize', 10, 'LineWidth', 2, 'DisplayName', 'Эксп. данные');
hold on;
plot(x_fine, y_canonical_fine, 'm-', 'LineWidth', 2, 'DisplayName', 'Канонический');
plot(x_interp, y_canonical_points, 'r*', 'MarkerSize', 12, 'LineWidth', 2, 'DisplayName', 'Интерп. точки');
grid on;
xlabel('x');
ylabel('y');
title('Канонический полином');
legend('Location', 'northwest');

subplot(2, 3, 4);
plot(x, y, 'ko', 'MarkerSize', 10, 'LineWidth', 2, 'DisplayName', 'Эксп. данные');
hold on;
plot(x_fine, y_linear_fine, 'c-', 'LineWidth', 2, 'DisplayName', 'Линейная');
plot(x_interp, y_linear_points, 'r*', 'MarkerSize', 12, 'LineWidth', 2, 'DisplayName', 'Интерп. точки');
grid on;
xlabel('x');
ylabel('y');
title('Линейная интерполяция');
legend('Location', 'northwest');

subplot(2, 3, 5);
plot(x, y, 'ko', 'MarkerSize', 10, 'LineWidth', 2, 'DisplayName', 'Эксп. данные');
hold on;
plot(x_fine, y_spline_fine, 'r-', 'LineWidth', 2, 'DisplayName', 'Сплайн');
plot(x_interp, y_spline_points, 'r*', 'MarkerSize', 12, 'LineWidth', 2, 'DisplayName', 'Интерп. точки');
grid on;
xlabel('x');
ylabel('y');
title('Сплайн-интерполяция');
legend('Location', 'northwest');

subplot(2, 3, 6);
plot(x, y, 'ko', 'MarkerSize', 10, 'LineWidth', 3, 'DisplayName', 'Эксп. данные');
hold on;
plot(x_fine, y_lagrange_fine, 'b-', 'LineWidth', 1.5, 'DisplayName', 'Лагранж');
plot(x_fine, y_newton_fine, 'g--', 'LineWidth', 1.5, 'DisplayName', 'Ньютон');
plot(x_fine, y_canonical_fine, 'm-.', 'LineWidth', 1.5, 'DisplayName', 'Канонич.');
plot(x_fine, y_linear_fine, 'c:', 'LineWidth', 2, 'DisplayName', 'Линейная');
plot(x_fine, y_spline_fine, 'r-', 'LineWidth', 1.5, 'DisplayName', 'Сплайн');
plot(x_interp, y_lagrange_points, 'r*', 'MarkerSize', 12, 'LineWidth', 2, 'DisplayName', 'Интерп. точки');
grid on;
xlabel('x');
ylabel('y');
title('Сравнение всех методов');
legend('Location', 'northwest');

% Сохраняем график
print -dpng 'interpolation_results.png' -r300;
fprintf('\nГрафик сохранен в файл: interpolation_results.png\n');

% График 2: Отдельный большой график со всеми методами
figure('Position', [150, 150, 1000, 700]);
plot(x, y, 'ko', 'MarkerSize', 12, 'LineWidth', 3, 'DisplayName', 'Экспериментальные данные');
hold on;
plot(x_fine, y_lagrange_fine, 'b-', 'LineWidth', 2, 'DisplayName', 'Лагранж');
plot(x_fine, y_newton_fine, 'g--', 'LineWidth', 2, 'DisplayName', 'Ньютон');
plot(x_fine, y_canonical_fine, 'm-.', 'LineWidth', 2, 'DisplayName', 'Канонический');
plot(x_fine, y_linear_fine, 'c:', 'LineWidth', 2.5, 'DisplayName', 'Линейная');
plot(x_fine, y_spline_fine, 'r-', 'LineWidth', 2, 'DisplayName', 'Сплайн');
plot(x_interp, y_lagrange_points, 'r*', 'MarkerSize', 15, 'LineWidth', 3, 'DisplayName', 'Интерполированные точки');
grid on;
xlabel('x', 'FontSize', 14);
ylabel('y', 'FontSize', 14);
title('Сравнение методов интерполяции', 'FontSize', 16);
legend('Location', 'northwest', 'FontSize', 12);
set(gca, 'FontSize', 12);

% Сохраняем график
print -dpng 'interpolation_comparison.png' -r300;
fprintf('График сохранен в файл: interpolation_comparison.png\n');

fprintf('\nВсе графики успешно построены!\n');