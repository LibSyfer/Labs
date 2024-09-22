parents('Lev Tolstoy', 'Nikolai Tolstoy', 'Maria Volkonskaya').
parents('Maria Volkonskaya', 'Nikolai Volkonsky', 'Ekaterina Trubetskaya').
parents('Nikolai Tolstoy', 'Ilya Tolstoy', 'Alisa Akraeva').
parents('Ilya Tolstoy', 'Andrey Tolstoy', 'Aleksandra Shetinina').
parents('Andrey Tolstoy', 'Ivan Tolstoy', 'Anastasiya Polyakina').
parents('Nikolai Volkonsky', 'Sergey Volkonsky', 'Maria Chaadaeva').
parents('Sergey Volkonsky', 'Fedor Volkonsky', 'Alexandra Nikolaeva').
parents('Ekaterina Trubetskaya', 'Dmitriy Trubetskoy', 'Varvara Odoevskaya').
parents('Dmitriy Trubetskoy', 'Uriy Trubetskoy', 'Olga Golovina').
parents('Varvara Odoevskaya', 'Ivan Odoevsky', 'Praskovya Толстая').
parents('Alexandr Tolstoy', 'Petr Tolstoy', 'Ekatherina Dubrovskaya').
parents('Elizabeth Tolstaya', 'Alexandr Tolstoy', 'Nadejda Ritova').
parents('Aleksandra Tolstaya', 'Andrey Tolstoy', 'Aleksandra Shetinina').
parents('Tatyana Tolstaya', 'Andrey Tolstoy', 'Aleksandra Shetinina').
parents('Petr Tolstoy', 'Andrey Tolstoy', 'Aleksandra Shetinina').
parents('Janna Volkonskaya', 'Sergey Volkonsky', 'Maria Chaadaeva').
parents('Bogdan Volkonsky', 'Sergey Volkonsky', 'Maria Chaadaeva').
parents('Kirill Trubetskoy', 'Uriy Trubetskoy', 'Olga Golovina').

child(Person,Y) :-
    parent(Person, Y, Z);
    parent(Person, Z, Y).

sameparents(Person,Y) :-
    parent(Person, U, V),
    parent(Y, U, V),
    Person \= Y.

cousin(Person,Y) :-
    ((sameparents(U,V), child(Person,U), child(Y,V));
    (sameparents(U,V), child(Y,U), child(Person,V))),
    Person \= Y.

quadrocousin(Person,Y) :- % Троюродный брат или сестра
    ((cousin(U,V), child(Person,U), child(Y,V));
    (cousin(U,V), child(Y,U), child(Person,V))),
    Person \= Y.
