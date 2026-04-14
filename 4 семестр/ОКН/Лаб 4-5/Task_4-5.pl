% ИЕРАРХИЯ КЛАССОВ (ТАКСОНОМИЯ)
is_a(theater, organization).
is_a(drama_theater, theater).

is_a(employee, person).
is_a(actor, employee).

% ЭКЗЕМПЛЯРЫ
instance_of(mhat, drama_theater).
instance_of(ivanov, actor).
instance_of(petrov, actor).

% СВОЙСТВА КЛАССОВ
class_property(organization, has_building, yes).
class_property(organization, goal, profit).

class_property(theater, has_stage, yes).
class_property(theater, sells_tickets, yes).
% Исключение на уровне подкласса: театр преследует цель искусства, а не прибыли
class_property(theater, goal, art). 

class_property(drama_theater, genre, drama).

class_property(person, breathes, yes).
class_property(employee, receives_salary, yes).
class_property(employee, has_vacation, yes).

class_property(actor, performs_on_stage, yes).
class_property(actor, wears_costume, yes).
class_property(actor, role_type, main_cast).

% СВОЙСТВА ЭКЗЕМПЛЯРОВ
instance_property(mhat, location, moscow).
instance_property(mhat, founded, 1898).

instance_property(ivanov, age, 40).

instance_property(petrov, age, 35).
% Исключение на уровне экземпляра: Петров играет роли второго плана, в отличие от остальных актеров
instance_property(petrov, role_type, supporting_cast).

% ПРАВИЛА ВЫВОДА С НАСЛЕДОВАНИЕМ
% Получить свойство класса (сначала ищет у самого класса, затем у суперклассов)
get_class_property(Class, Property, Value) :-
    class_property(Class, Property, Value), !.
get_class_property(Class, Property, Value) :-
    is_a(Class, SuperClass),
    get_class_property(SuperClass, Property, Value).

% Получить свойство экземпляра (сначала ищет у самого экземпляра, затем у его класса)
get_property(Instance, Property, Value) :-
    instance_property(Instance, Property, Value), !.
get_property(Instance, Property, Value) :-
    instance_of(Instance, Class),
    get_class_property(Class, Property, Value).