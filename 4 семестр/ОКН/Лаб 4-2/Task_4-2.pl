% 1. patient_card(НомерКарты, ФИО, Адрес, Телефон, Возраст, МестоРаботы)
patient_card(101, 'Иванов И.И.', 'ул. Ленина 1', '555-0101', 45, 'Завод "Прогресс"').
patient_card(102, 'Петрова М.С.', 'пр. Мира 25', '555-0102', 32, 'Школа №5').
patient_card(103, 'Сидоров В.П.', 'ул. Садовая 8', '555-0103', 68, 'Пенсионер').
patient_card(104, 'Кузнецова А.Н.', 'ул. Ленина 1', '555-0104', 29, 'ООО "Ромашка"').

% 2. doctor(КодВрача, ФИО, Специализация)
doctor(1, 'Сергеев П.В.', терапевт).
doctor(2, 'Васильева Е.А.', хирург).
doctor(3, 'Николаев А.Д.', окулист).
doctor(4, 'Михайлов С.И.', терапевт).

% 3. appointment(Код Врача, Номер Карты, Дата, Диагноз,
% Больничный(yes/no)) Структура date(Год, Месяц, День) для
% удобства работы с датами.
appointment(1, 101, date(2023, 10, 5), орви, yes).
appointment(2, 102, date(2023, 10, 6), ушиб, no).
appointment(3, 103, date(2023, 10, 6), катаракта, no).
appointment(1, 104, date(2023, 11, 12), грипп, yes).
appointment(4, 101, date(2023, 11, 15), бронхит, yes).
appointment(2, 103, date(2023, 11, 20), перелом, yes).
appointment(3, 101, date(2024, 1, 22), конъюнктивит, no).

% 4 правила
% 1. Найти все диагнозы пациента.
% patient_diagnoses(ФИО_пациента, Диагноз)
patient_diagnoses(PatientName, Diagnosis) :-
    patient_card(CardNum, PatientName, _, _, _, _),
    appointment(_, CardNum, _, Diagnosis, _).

% 2. Найти пациентов, получивших больничный.
% received_sick_leave(ФИО_пациента, Диагноз)
received_sick_leave(PatientName, Diagnosis) :-
    patient_card(CardNum, PatientName, _, _, _, _),
    appointment(_, CardNum, _, Diagnosis, yes).

% 3. Найти врачей, которых посещал пациент.
% doctors_visited_by_patient(ФИО_пациента, ФИО_врача, Специализация)
doctors_visited_by_patient(PatientName, DoctorName, Specialization) :-
    patient_card(CardNum, PatientName, _, _, _, _),
    appointment(DoctorID, CardNum, _, _, _),
    doctor(DoctorID, DoctorName, Specialization).

% 4. Найти пациентов, которых принимал заданный врач.
% doctor_appointments(ФИО_врача, ФИО_пациента, Дата)
doctor_appointments(DoctorName, PatientName, Date) :-
    doctor(DoctorID, DoctorName, _),
    appointment(DoctorID, CardNum, Date, _, _),
    patient_card(CardNum, PatientName, _, _, _, _).

