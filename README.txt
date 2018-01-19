Rafał Galczak 277292

Użycie programu

    Wywołanie programu zwyczajnie wypisze help.

Specyfikacja problemu

    Danych jest n ponumerowanych kolejno pojemników. W pojemnikach znajdują
    się klocki w k kolorach, przy czym łącznie we wszystkich pojemnikach
    jest nie więcej niż n klocków danego koloru. Pojemność i-tego pojemnika
    wynosi pi klocków. Należy przełożyć klocki w taki sposób, żeby w każdym
    pojemniku pozostał co najwyżej jeden klocek każdego koloru. W jednym
    ruchu można przełożyć jeden klocek z pojemnika, w którym się znajduje,
    do pudełka sąsiedniego (dozwolone jest przenoszenie pomiędzy pudełkiem
    pierwszym i n-tym). Porównać czas obliczeń i wyniki różnych metod.

Dane wejściowe

    Pierwszy wiersz zawiera kolejno liczbę pojemników i liczbę wszystkich różnych kolorów.
    Następne wiersze zawierają, dla każdego pojemnika:
    Pojomnośc pojemnika, liczbę klocków w pojemniku, a nastepnie identyfikatory kolorów w danym pojemniku.
    Identyfikatory zaczynają się od 0.

    Identyfikator nie może być większy niż podana wcześniej liczba kolorów - 1.
    W pojemniku może się znajdować maksymalnie tyle klocków ile jest pojemników.


Dane Wyjściowe

    Na wyjście w zależności od trybu w jakim odpalono program zostają wypisane różne informacje.
    tryb m1 i m2 wypisują, dla każdego algorytmu ile przestawień klocków wykonał i ile czasu w ms
    mu to zajęło.

    Dla trybu m3 poza ciągle wypisywanym postępem (co jest związane z długim czasem obliczeń, i ogromną zasobożernością
    algorytmów - potrzebna jest informacja przy jakich parametrach i jaki algorytm ma problemm) wypisuje
    tabelkę z średnim czasem w ms na wszystkie testy, średnią liczbę przestawień, kóre wykonał algorytm i liczbę
    nierozwiązanych przez algorytm problemów (z powodu albo dojścia do wniosku, że problem jest nierozwiązywalny,
    albo zbyt dużego zużycia zasobów i przerwania dalszych obliczeń).

Metody Rozwiązania

    Do rozwiązania zostały użyte 3 algorytmy. 2 wspomniane wcześniej w dokumentacji wstępnej. Ostatni został
    zmieniony z programowania z nawrotami na A*. Ze względu na prostotę implementacji przy napisanym już wcześniej
    BFSie i  skuteczną heurystykę.

Algorytmy

    1. Naiwny - Każdy pojemnik trzyma listę klocków, których chce się pozbyć i listę kolorów, które może przyjąć.
       Dla każdego pojemnika bierzemy po kolei po jednym z listy do pozbycia się i szukamy pierwszego pojemnika, który
       taki klocek może przyjąć. Jeżeli taki się znajdzie próbujemy dojść krótszą drogą, jeżeli dojście jest niemożliwe
       (po drodze pełny pojemnik) próbujemy przejść dłuższą drogą, jeżeli tutaj dojście również jest niemożliwe, sprawdzamy
       kolejny niepotrzebny klocek. Powtarzamy, aż nie dojdziemy do rozwiązania albo po przejściu przez wszystkie
       pojemniki nie uda nam się wykonać żadnego ruchu. W drugim przypadku algorytm stwierdza, że problem jest
       nierozwiązywalny.

    2. BFS - przeszukiwanie w szerz. Nowe stany rozwijane są na bierząco z obecnego stanu przez przełożenie jednego
       klocka do pojemnika na lewo, następnie do pojemnika na prawo. W ten sposób postępujemy z każdym możliwym klockiem.
       Algorytm może zostać przerwany jeżeli zużyje za dużo zasobów

    3. A* - BFS z zastosowaniem kolejki priorytetowej. Priotytet określany jest na podstawie funkcji kosztu stanu.
       Funkcja kosztu to suma sumy liczby klocków z powtarzającymi się kolorami z każdego pojemnika z liczbą kroków
       potrzebnych żeby dotrzeć do rozpatrywanego stanu.

Struktury

    Wszystkie 3 algorytmy opierają się na podobnych strukturach:
    Algorithm - struktura algorytmu, przygotowuje pozostałe struktury do rozwiązania problemu z podanego testu.
    Bucket - pojemnik, zawiera kontener identyfikatorów kolorów i proste metody jak porównanie, sprawdzenie
             czy jest pust/pełny. W zależności od algorytmu może zawierać dodatkowe motedy i/lub struktury.
             Zazwyczaj kontenerem jest kolekcja z szybkim dostępem, która nie zachowuje kolejności elementów.
             np multiset.
    State - wykorzystywany przy BFS i A*. Hashowalna struktora zawierająca kontener pojemników. W tym przypadku
            kolejność elementów w kolekcji ma znaczenie, dlatego używany jest vector.

Przewodnik po źródłach

    Algorithm.h/cpp - Pliki nagłówkowe i źrodłowe CLI. Odpowiadające za komunikację z użytkownikiem
    generator.h/cpp - namespace generator - Klasa testu, podstawowego pojemnika, generacja losowych testów.
    Naive.h/cpp     - namespace algorithm - Klasa rozwiązania naiwnego wraz z pomocniczymi strukturami - Bucket
    BFS.h/cpp       - namespace algorithm - Klasa rozwiązania przeszukiwaniem wstecz, wraz z pomocniczymi strukturami
                      Bucket, State
    AStar.h/cpp     - namespace algorothm - Klasa rozwiązania A*, wraz z pomocniczymi strukturami
                      Bucket, State, Comperator <- (dla kojejki priorytetowej).
    main.cpp        - zainicjowanie i odpalenie klasy aplikacji.


Decyzje projektowe

    Każdy z algorytmów zostaje przerwany po 10000 iteracji ich pętli głównej. Czas przerwanego algorytmu
    nie jest brany pod uwagę przy wyliczaniu średniej.
    W przypadku rozwiązania naiwnego jest to związane z tym, że istnieją przypadki testowe, dla których
    algorytm jest w stanie wpaść w nieskończoną pętlę. W takim wypadku należy go przerwać.
    Dla A* i BFS jest to związane z ogromną zasobożernością algorytmów jako, że trzymają one w pamięci wszystkie
    stany do odwiedzenia. Dają gwarancję znalezienia rozwiązania jednak komputerowi nie starcza pamięci.
