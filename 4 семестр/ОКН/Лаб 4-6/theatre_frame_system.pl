% Лабораторная работа №6.
% Тема: Фреймовая модель представления знаний.
% Предметная область: театр.

% -----------------------------
% Иерархия фреймов
% a_kind_of(Sub, Super)  - связь AKO между прототипами
% instance_of(Inst, Class) - связь экземпляра с прототипом
% -----------------------------

a_kind_of(cultural_institution, entity).
a_kind_of(theatre, cultural_institution).
a_kind_of(drama_theatre, theatre).
a_kind_of(musical_theatre, theatre).
a_kind_of(repertoire_show, entity).
a_kind_of(ticketing_system, entity).

instance_of(chekhov_theatre, drama_theatre).
instance_of(revizor_show, repertoire_show).
instance_of(ticket_101, ticketing_system).

% -----------------------------
% Слоты прототипов и экземпляров
% slot(Frame, Slot, Value).
% -----------------------------

slot(entity, description, 'Base frame for theatre-domain objects').
slot(entity, status, active).
slot(entity, language, russian).
slot(entity, creator, lab6).
slot(entity, object_type, generic).

slot(cultural_institution, city_default, unknown).
slot(cultural_institution, opening_hours, '10:00-20:00').
slot(cultural_institution, accessibility, yes).
slot(cultural_institution, ticket_policy, 'cash_and_card').
slot(cultural_institution, website_style, public).

slot(theatre, hall_count, 2).
slot(theatre, average_capacity, 650).
slot(theatre, seat_categories, [parterre, balcony, box]).
slot(theatre, rehearsal_days, [mon, wed, fri]).
slot(theatre, foyer_bar, yes).

% Исключение на уровне подкласса:
% у драматического театра цена базового билета выше, чем у theatre.
slot(drama_theatre, repertoire_style, classical_modern).
slot(drama_theatre, ticket_price_base, 1200).
slot(drama_theatre, classical_share, 70).
slot(drama_theatre, premiere_day, friday).
slot(drama_theatre, audience_profile, family).

slot(musical_theatre, repertoire_style, musical_opera).
slot(musical_theatre, ticket_price_base, 1800).
slot(musical_theatre, orchestra_pit, yes).
slot(musical_theatre, chorus_size, 24).
slot(musical_theatre, premiere_day, saturday).

slot(repertoire_show, title, untitled_show).
slot(repertoire_show, duration, 120).
slot(repertoire_show, genre, drama).
slot(repertoire_show, age_limit, 12).
slot(repertoire_show, intermission, yes).

slot(ticketing_system, ticket_type, standard).
slot(ticketing_system, base_price, 800).
slot(ticketing_system, currency, rubles).
slot(ticketing_system, refund_policy, 'refund_24h_before').
slot(ticketing_system, payment_methods, [cash, card, online]).

% Экземпляр театра.
% Исключение на уровне экземпляра:
% ticket_price_base переопределён для конкретного театра.
slot(chekhov_theatre, name, 'Chekhov Drama Theatre').
slot(chekhov_theatre, city, moscow).
slot(chekhov_theatre, address, 'Moscow, Kamergersky lane, 3').
slot(chekhov_theatre, director, 'I. Petrov').
slot(chekhov_theatre, website, 'chekhov-theatre.example').
slot(chekhov_theatre, ticket_price_base, 1400).
slot(chekhov_theatre, press_service, yes).
slot(chekhov_theatre, visitor_rating, 'A').

% Экземпляр спектакля.
slot(revizor_show, title, 'Revizor').
slot(revizor_show, premiere_date, '2026-05-15').
slot(revizor_show, seats_left, 0).
slot(revizor_show, stage_version, spring_revival).
slot(revizor_show, running_status, repertory).

% Экземпляр билета.
slot(ticket_101, seat_category, box).
slot(ticket_101, row, 5).
slot(ticket_101, seat, 12).
slot(ticket_101, buyer, 'E. Smirnova').
slot(ticket_101, sale_status, paid).

% -----------------------------
% Демоны
% daemon(FrameOrClass, Slot, GoalPredicate).
% Демон срабатывает, если слот не задан напрямую и не найден по наследованию.
% -----------------------------

daemon(ticketing_system, ticket_price, compute_ticket_price).
daemon(revizor_show, sold_out, compute_sold_out).

% Демон: вычисление цены билета по базовой цене и категории места.
compute_ticket_price(Frame, Price) :-
    get_slot(Frame, base_price, Base),
    get_slot(Frame, seat_category, Category),
    price_multiplier(Category, Multiplier),
    Price is Base * Multiplier.

price_multiplier(parterre, 1.0).
price_multiplier(balcony, 1.2).
price_multiplier(box, 1.5).
price_multiplier(standard, 1.0).

% Демон: спектакль считается распроданным, если мест не осталось.
compute_sold_out(Frame, yes) :-
    get_slot(Frame, seats_left, 0),
    !.
compute_sold_out(_, no).

% -----------------------------
% Механизм наследования
% -----------------------------

parent(Sub, Super) :- a_kind_of(Sub, Super).
parent(Inst, Class) :- instance_of(Inst, Class).

find_daemon(Frame, Slot, Goal) :-
    daemon(Frame, Slot, Goal),
    !.
find_daemon(Frame, Slot, Goal) :-
    parent(Frame, Parent),
    find_daemon(Parent, Slot, Goal).

% Основной предикат получения значения слота.
% 1) прямое значение;
% 2) демон;
% 3) наследование по AKO/instance_of;
% 4) сообщение об отсутствии.
get_slot(Frame, Slot, Value) :-
    slot(Frame, Slot, Value),
    !.
get_slot(Frame, Slot, Value) :-
    find_daemon(Frame, Slot, Goal),
    call(Goal, Frame, Value),
    !.
get_slot(Frame, Slot, Value) :-
    parent(Frame, Parent),
    get_slot(Parent, Slot, Value),
    !.
get_slot(Frame, Slot, _) :-
    format('Error: slot ~w was not found for frame ~w.~n', [Slot, Frame]),
    fail.

% Вспомогательный предикат: вывести все найденные слоты фрейма.
show_frame(Frame) :-
    format('Frame: ~w~n', [Frame]),
    forall(get_slot(Frame, Slot, Value),
           format('  ~w = ~w~n', [Slot, Value])).
