# Kostka Rubika (ang. Rubik's Cube)
## Wprowadzenie
Program jest symulacją łamigłówki zwanej Kostką Rubika.

Program wykonuje ciąg rozkazów obracających warstwy kostki rozmiaru N x N x N. Program zaczyna od kostki ułożonej. Na życzenie drukuje aktualny stan kostki.

Stała symboliczna N, określająca rozmiar kostki, ma przypisaną `5` jako wartość domyślną. Inną wartość stałej można wybrać podczas kompilacji programu za pomocą opcji `-DN=wartość`.

## Postać danych
Dane programu to ciąg rozkazów obrotu warstw i wydruku aktualnego stanu kostki, zakończony kropką.

Program ignoruje zawartość wejścia po kropce kończącej dane.

Rozkazem wydruku stanu kostki jest koniec wiersza.

### Rozkaz obrotu warstw składa się z trzech części, które wskazują:
```
ścianę kostki,

liczbę warstw,

kąt obrotu.
```

`Ściana` jest określona literą:
```
u - góra (ang. up),

l - lewo (ang. left),

f - przód (ang. front),

r - prawo (ang. right),

b - tył (ang. back),

d - dół (ang. down).
```

`Liczba warstw`
```
puste pole - wskazuje liczbę 1
liczba dodatnia - jest pozycyjnym dziesiętnym zapisem liczby warstw
```

`Kąt` 
```
puste pole - wskazuje kąt 90 stopni
apostrof  - to -90 stopni 
cudzysłów - to 180 stopni.
```

Wykonanie rozkazu obrotu, ze ścianą S, liczbą warstw W i kątem K, powoduje jednoczesne obrócenie W warstw, patrząc od strony ściany S, o kąt K, zgodnie z ruchem wskazówek zegara.

### Składnię danych opisuje gramatyka z symbolem początkowym Dane:
```
Dane → CiągRozkazów Kropka
CiągRozkazów -> ε | Rozkaz CiągRozkazów
Rozkaz → Obrót | Drukowanie
Obrót → Strona LiczbaWarstw Kąt
Drukowanie → KoniecWiersza
Strona → Litera
LiczbaWarstw → Jedna | Wiele
Jedna → ε
Wiele → Liczba
Liczba → Cyfra | Liczba Cyfra
Kąt → Prosty | MinusProsty | Półpełny
Prosty → ε
MinusProsty → Apostrof
Półpełny → Cudzysłów
Litera → u | l | f | r | b | d
Cyfra → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
Apostrof → '
Cudzysłów → "
KoniecWiersza → \n
Kropka → .
```

## Postać wyniku
Wynik programu jest efektem wykonania rozkazów drukowania aktualnego stanu kostki.

Wydruk stanu kostki składa się ze znaków `0, 1, 2, 3, 4, 5`, symbolizujących kolory kwadratów na ścianach kostki, oraz ze `spacji` i `kresek pionowych |`.

Przyjmujemy, że w ułożonej kostce:
```
kwadraty ściany górnej mają kolor 0,
kwadraty ściany lewej mają kolor 1,
kwadraty ściany przedniej mają kolor 2,
kwadraty ściany prawej mają kolor 3,
kwadraty ściany tylnej mają kolor 4,
kwadraty ściany dolnej mają kolor 5.
```

Położenie ścian na wydruku stanu kostki jest zgodne ze schematem:
```
  u
l|f|r|b
  d
```
gdzie `u, l, f, r, b, d` to, odpowiednio, ściana `górna, lewa, przednia, prawa, tylna i dolna.`


## Uwagi
Zakładamy, że dane są poprawne oraz że każdy wiersz danych, także ostatni, jest zakończony reprezentacją końca wiersza `\n`.
