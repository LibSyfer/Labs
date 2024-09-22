% В педагогическом институте Аркадьева, Бабанова, Корсакова, Дашков, Ильин и Флеров преподают географию, английский язык, французский язык, немецкий язык, историю и математику. Преподаватель немецкого языка и преподаватель математики в студенческие годы занимались художественной гимнастикой. Ильин старше Флерова, но стаж работы у него меньше, чем у преподавателя географии. Будучи студентками, Аркадьева и Бабанова учились вместе в одном университете. Все остальные окончили педагогический институт. Флеров отец преподавателя французского языка. Преподаватель английского языка самый старший из всех и по возрасту и по стажу. Он работает в этом институте с тех пор, как окончил его. Преподаватели математики и истории его бывшие студенты. Аркадьева старше преподавателя немецкого языка. Кто какой предмет преподает?

discipline(geography).
discipline(english).
discipline(french).
discipline(german).
discipline(history).
discipline(math).

teach(Dis):- discipline(Dis).
gymnastics(T).

is_older(T1, T2).
work_longer(T1, T2).

stud_together(T1 , T2).

from_ped(T):-
    not(stud_together(T, _)).
from_ped(T):-
    not(stud_together(_, T)).

is_father(T1, T2).

is_oldest(T):-
    is_older(T, _),
    work_longer(T, _).

is_teacher(T1, T2).

main([Arkadieva, Babanova, Korsakova, Dashkov, Ilin, Flerov]):-
    discipline(Dis1),
    Arkadieva = teach(Dis1),
    discipline(Dis2), Dis2 @< Dis1,
    Babanova = teach(Dis2),
    discipline(Dis3), Dis3 @< Dis1, Dis3 @< Dis2,
    Korsakova = teach(Dis3),
    discipline(Dis4), Dis4 @< Dis3, Dis4 @< Dis2, Dis2 @< Dis1,
    Dashkov = teach(Dis4),
    discipline(Dis5), Dis5 @< Dis4, Dis5 @< Dis3, Dis5 @< Dis2, Dis5 @< Dis1,
    Ilin = teach(Dis5),
    discipline(Dis6), Dis6 @< Dis5, Dis6 @< Dis4, Dis6 @< Dis3, Dis6 @< Dis2, Dis6 @< Dis1,
    Flerov = teach(Dis6),
    gymnastics(teach(math)),
    gymnastics(teach(german)),
    is_older(Ilin, Flerov),
    work_longer(teach(geography), Ilin),
    stud_together(Arkadieva, Babanova),
    is_father(Flerov, teach(french)),
    is_oldest(teach(english)),
    is_teacher(teach(english), teach(math)),
    is_teacher(teach(english), teach(history)),
    is_older(Arkadieva, teach(german)).
