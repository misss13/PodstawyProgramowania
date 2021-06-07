#include <stdio.h>
#include <stdlib.h>

/**
 * Program, który pokazuje jak utworzyć trzyelementową listę jednokierunkową
 *
 * @author Stanisław Polak
 * @version 1.0 22-05-2020
*/
int main(void)
{
    enum Day
    {
        MON,
        TUE,
        WED,
        THU,
        FRI,
        SAT,
        SUN
    };

    /**********************/
    /* Struktura 'Lesson' */
    /**********************/
    struct Lesson
    {
        char *className;
        enum Day day;
        int hour;
        int minute;
        int duration;
    };

    /********************/
    /* Struktura 'Node' */
    /********************/
    struct Node
    {
        struct Lesson lesson;
        struct Node *next;
    };

    // Zmienna 'head' będzie przechowywać wskazanie na pierwszy element / węzeł listy
    struct Node *head = NULL; // Na razie nie przechowuje niczego

    //  Utworzenie pierwszego węzła listy
    struct Node *node1 = (struct Node *)malloc(sizeof(struct Node));
    if (node1 != NULL) // Jeżeli udało się utworzyć węzeł, to wypełnij go danymi
    {
        // Określanie zawartości struktury 'Lesson'
        node1->lesson.className = "Podstawy Programowania";
        node1->lesson.day = WED;
        node1->lesson.hour = 12;
        node1->lesson.minute = 50;
        node1->lesson.duration = 90;

        // Określanie wskazania na następny węzeł listy
        node1->next = NULL; // Wartość NULL oznacza, że dany węzeł nie ma następnika
    }

    /*
    Po wykonaniu tych instrukcji zmienna 'node1' wskazuje na następującą strukturę danych:

                                   Struktura 'Node'
                   +--------------------------------------------------------+
                   |                          Struktura 'Lesson             |
                   |              +---------------------------------------+ |
                   |              | className -> "Podstawy Programowania" | |
                   |              | day:          WED                     | |
                   | lesson :     | hour:         12                      | |
                   |              | minute:       50                      | |
                   |              | duration:     90                      | |
                   |              +---------------------------------------+ |
      node1 -----> +--------------------------------------------------------+
                   | next:        NULL                                      |
                   +--------------------------------------------------------+
        */

    //  Utworzenie drugiego węzła
    struct Node *node2 = (struct Node *)malloc(sizeof(struct Node));
    if (node2 != NULL)
    {
        node2->lesson.className = "Wychowanie fizyczne";
        node2->lesson.day = MON;
        node2->lesson.hour = 8;
        node2->lesson.minute = 00;
        node2->lesson.duration = 90;
        node2->next = NULL;
    }

    //  Utworzenie trzeciego węzła
    struct Node *node3 = (struct Node *)malloc(sizeof(struct Node));
    if (node3 != NULL)
    {
        node3->lesson.className = "Konsultacje";
        node3->lesson.day = THU;
        node3->lesson.hour = 11;
        node3->lesson.minute = 05;
        node3->lesson.duration = 30;
        node3->next = NULL;
    }

    // Wstawianie węzłów do listy — pierwszy sposób
    if (node1 != NULL && node2 != NULL && node3 != NULL)
    {
        head = node1;
        node1->next = node2;
        node2->next = node3;

        /*
        Po wykonaniu tych instrukcji lista wygląda następująco:

                         +--------+         +--------+         +------------+
                         | lesson |         | lesson |         | lesson     |
                   +-->  +--------+    +--> +--------+    +--> +------------+
                   |     |        |    |    |        |    |    |            |
          head ----+     | next   |----+    | next   |----+    | next: NULL |
                         +--------+         +--------+         +------------+
                             ^                  ^                     ^
                             |                  |                     |
                           node1              node2                  node3
    */
    }

    // Wstawianie węzłów do listy — drugi sposób
    if (node1 != NULL && node2 != NULL && node3 != NULL)
    {
        head = node1;
        head->next = node2;
        head->next->next = node3;
    }

    // Wstawianie węzłów do listy — trzeci sposób
    struct Node *current;

    if (node1 != NULL && node2 != NULL && node3 != NULL)
    {
        current = head = node1; // Ustawienie wskaźników (zmiennych) 'current' oraz 'head' na pierwszy węzęł listy
        current->next = node2;  // Dopięcie drugiego elementu (węzła) do 'current', czyli de facto do pierwszego węzła listy

        current = current->next; // Ustawienie zmiennej 'current' na drugi element listy
        current->next = node3;   // Dopięcie trzeciego elementu do 'current', czyli do drugiego (węzła)

        /*
        Dopinanie, ewentualnych, kolejnych węzłów:

        current = current->next; // Ustawienie zmiennej 'current' na trzeci element listy
        current->next = node4;   // Dopięcie czwartego elementu do 'current', czyli do trzeciego

        current = current->next; // Ustawienie zmiennej 'current' na czwart element listy
        current->next = node5;   // Dopięcie piątego elementu do 'current', czyli do czwartego

        ...
        */
    }

    char *dayNames[] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};

    // Wypisanie informacji o wszystkich lekcjach zawartych na liście
    for (current = head; current != NULL; current = current->next)
    {
        printf("Przedmiot: \e[31m%s\e[0m\nDzień tygodnia: \e[31m%s\e[0m\nGodzina rozpoczęcia [Czas trwania]: \e[31m%02d:%02d [%d]\e[0m\n\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);
    }
    // Nie można zapomnieć o zwalnianiu pamięci — każdemu wywołaniu 'malloc()' / 'calloc()', na samym końcu programu, powinno towarzyszyć wywołanie funkcji 'free()'
    // Zwalniane  w kolejności od ostatniego do pierwszego elementu listy
    free(head->next->next); // Zwolnienie pamięci dla trzeciego elementu
    free(head->next);       // Zwolnienie pamięci dla drugiego elementu
    free(head);             // Zwolnienie pamięci dla pierwszego elementu

    // Zwalniane pamięci w kolejności od pierwszego do ostatniego elementu listy
    /*
    current = head;    // Ustawienie zmiennej 'current' na pierwszy element listy
    head = head->next; // Ustawienie zmiennej 'head' na drugi element listy
    free(current);     // Zwolnienie pamięci dla pierwszego elementu

    current = head;    // Ustawienie zmiennej 'current' na drugi element listy
    head = head->next; // Ustawienie zmiennej 'head' na trzeci element listy
    free(current);     // Zwolnienie pamięci dla drugiego elementu

    free(head); // Zwolnienie pamięci dla trzeciego elementu
    */
}
