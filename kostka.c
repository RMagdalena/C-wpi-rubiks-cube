#include <stdio.h>

#ifndef N
#define N 5
#endif

// ściany kostki
#define U 0
#define L 1
#define F 2
#define R 3
#define B 4
#define D 5

// Dla kazdej ściany cykl scian w kierunku przeciwnym do wskazowek zegara zaczynajac od gory.
// Dodatkowo dla kazdej sciany podane jest ile razy w prawo nalezy ja obrocic aby stykala sie pierwszym
// wierszem ze ścianą wokoł ktorej jest obrot.
// Przykład 1:
//   - dla ściany U cykl to B->L->F->R
//   - nie trzeba nic obracac bo wszystkie sciany z cyklu dotykaja pierwszym wierszem sciany U
// Przykład 2:
//   - dla ściany F cykl to U->L->D->R
//   - przykładowo ścianę L trzeba obrocić raz w prawo aby dotykała ściany F pierwszym wierszem
int cykle[][4][2] = {
    {{B, 0}, {L, 0}, {F, 0}, {R, 0}}, // U
    {{U, 3}, {B, 1}, {D, 3}, {F, 3}}, // L
    {{U, 2}, {L, 1}, {D, 0}, {R, 3}}, // F
    {{U, 1}, {F, 1}, {D, 1}, {B, 3}}, // R
    {{U, 0}, {R, 1}, {D, 2}, {L, 3}}, // B
    {{F, 2}, {L, 2}, {B, 2}, {R, 2}}, // D
};

int przeciwlegla_sciana[] = {
    D, // U
    R, // L
    B, // F
    L, // R
    F, // B
    U, // D
};

// zwroc znak z buforu (czyszcząc bufor) lub wczytaj znak z wejścia
char wczytaj_znak(char *buffor)
{
    if (*buffor != '?')
    {
        char wartosc = *buffor;
        *buffor = '?';
        return wartosc;
    }
    else
    {
        return getchar();
    }
}

// zapisz znak w buforze do pozniejszego wykorzystania
void oddaj_znak(char znak, char *buffor)
{
    *buffor = znak;
}

void ustaw_poczatkowa_wartosc(char k[][N][N])
{
    for (int i = 0; i < 6; i++)
    {
        char wartosc = '0' + i;
        for (int x = 0; x < N; x++)
        {
            for (int y = 0; y < N; y++)
            {
                k[i][x][y] = wartosc;
            }
        }
    }
}

int obrot_w_prawo_wiersz(int wiersz, int kolumna, int obrot)
{
    for (int i = 0; i < obrot; i++)
    {
        int stary_wiersz = wiersz;
        wiersz = kolumna;
        kolumna = N - 1 - stary_wiersz;
    }
    return wiersz;
}

int obrot_w_prawo_kolumna(int wiersz, int kolumna, int obrot)
{
    for (int i = 0; i < obrot; i++)
    {
        int stary_wiersz = wiersz;
        wiersz = kolumna;
        kolumna = N - 1 - stary_wiersz;
    }
    return kolumna;
}

void obroc_sciane(char k[][N][N], int sciana, int kat_obrotu)
{
    for (int obrot = 0; obrot < kat_obrotu; obrot++)
    {
        for (int i = 0; i < N / 2; i++)
        {
            for (int j = 0; j < (N + 1) / 2; j++)
            {
                int wiersz = i;
                int kolumna = j;
                char tmp = k[sciana][wiersz][kolumna];
                for (int p = 0; p < 3; p++)
                {
                    int nowy_wiersz = obrot_w_prawo_wiersz(wiersz, kolumna, 3);
                    int nowa_kolumna = obrot_w_prawo_kolumna(wiersz, kolumna, 3);
                    k[sciana][wiersz][kolumna] = k[sciana][nowy_wiersz][nowa_kolumna];
                    wiersz = nowy_wiersz;
                    kolumna = nowa_kolumna;
                }
                k[sciana][wiersz][kolumna] = tmp;
            }
        }
    }
}

void obroc_boki(char k[][N][N], int sciana, int liczba_warstw, int kat_obrotu)
{
    int gora_sciana = cykle[sciana][0][0];
    int gora_sciana_rotacja = cykle[sciana][0][1];
    int lewa_sciana = cykle[sciana][1][0];
    int lewa_sciana_rotacja = cykle[sciana][1][1];
    int dol_sciana = cykle[sciana][2][0];
    int dol_sciana_rotacja = cykle[sciana][2][1];
    int prawa_sciana = cykle[sciana][3][0];
    int prawa_sciana_rotacja = cykle[sciana][3][1];

    for (int obrot = 0; obrot < kat_obrotu; obrot++)
    {
        for (int warstwa = 0; warstwa < liczba_warstw; warstwa++)
        {
            for (int kolumna = 0; kolumna < N; kolumna++)
            {
                int gora_wiersz = obrot_w_prawo_wiersz(warstwa, kolumna, gora_sciana_rotacja);
                int gora_kolumna = obrot_w_prawo_kolumna(warstwa, kolumna, gora_sciana_rotacja);

                int lewy_wiersz = obrot_w_prawo_wiersz(warstwa, kolumna, lewa_sciana_rotacja);
                int lewa_kolumna = obrot_w_prawo_kolumna(warstwa, kolumna, lewa_sciana_rotacja);

                int dol_wiersz = obrot_w_prawo_wiersz(warstwa, kolumna, dol_sciana_rotacja);
                int dol_kolumna = obrot_w_prawo_kolumna(warstwa, kolumna, dol_sciana_rotacja);

                int prawy_wiersz = obrot_w_prawo_wiersz(warstwa, kolumna, prawa_sciana_rotacja);
                int prawa_kolumna = obrot_w_prawo_kolumna(warstwa, kolumna, prawa_sciana_rotacja);

                char tmp = k[lewa_sciana][lewy_wiersz][lewa_kolumna];
                k[lewa_sciana][lewy_wiersz][lewa_kolumna] = k[dol_sciana][dol_wiersz][dol_kolumna];
                k[dol_sciana][dol_wiersz][dol_kolumna] = k[prawa_sciana][prawy_wiersz][prawa_kolumna];
                k[prawa_sciana][prawy_wiersz][prawa_kolumna] = k[gora_sciana][gora_wiersz][gora_kolumna];
                k[gora_sciana][gora_wiersz][gora_kolumna] = tmp;
            }
        }
    }
}

void obroc(char k[][N][N], int sciana, int liczba_warstw, int kat_obrotu)
{
    // obroc przednia sciane
    obroc_sciane(k, sciana, kat_obrotu);

    // obroc boczne sciany
    obroc_boki(k, sciana, liczba_warstw, kat_obrotu);

    // jezeli trzeba to obroc tez tylna sciane w przeciwnym kierunku, czyli (4 - kat_obrotu) razy w tym samym kierunku
    if (liczba_warstw == N)
    {
        obroc_sciane(k, przeciwlegla_sciana[sciana], 4 - kat_obrotu);
    }
}

void wypisz_wiersz(char wiersz[])
{
    for (int j = 0; j < N; j++)
    {
        putchar(wiersz[j]);
    }
}

void wypisz(char k[][N][N])
{
    putchar('\n'); // pierwszy wiersz jest pusty

    // N kolejnych wierszy opisuje ścianę górną
    for (int i = 0; i < N; i++)
    {
        // Każdy wiersz opisu ściany górnej i dolnej zaczyna się od N + 1 spacji,
        // po których jest N cyfr określających kolory kwadratów tej ściany.
        for (int j = 0; j < N + 1; j++)
        {
            putchar(' ');
        }
        wypisz_wiersz(k[U][i]);
        putchar('\n');
    }

    // następnych N wierszy to opis ściany lewej, przedniej, prawej i tylnej
    for (int i = 0; i < N; i++)
    {
        wypisz_wiersz(k[L][i]);
        putchar('|');
        wypisz_wiersz(k[F][i]);
        putchar('|');
        wypisz_wiersz(k[R][i]);
        putchar('|');
        wypisz_wiersz(k[B][i]);
        putchar('\n');
    }

    // N kolejnych wierszy opisuje ścianę dolną
    for (int i = 0; i < N; i++)
    {
        // Każdy wiersz opisu ściany górnej i dolnej zaczyna się od N + 1 spacji,
        // po których jest N cyfr określających kolory kwadratów tej ściany.
        for (int j = 0; j < N + 1; j++)
        {
            putchar(' ');
        }
        wypisz_wiersz(k[D][i]);
        putchar('\n');
    }
}

int wykonaj_rozkaz(char k[][N][N], char *buffor)
{
    int sciana;
    const char c = wczytaj_znak(buffor);
    if (c == '.')
    {
        return 0;
    }
    else if (c == '\n')
    {
        wypisz(k);
        return 1;
    }
    else if (c == 'u')
    {
        sciana = 0;
    }
    else if (c == 'l')
    {
        sciana = 1;
    }
    else if (c == 'f')
    {
        sciana = 2;
    }
    else if (c == 'r')
    {
        sciana = 3;
    }
    else if (c == 'b')
    {
        sciana = 4;
    }
    else if (c == 'd')
    {
        sciana = 5;
    }

    int liczba_warstw = 0;
    char potencjalna_cyfra_liczby_warstw = wczytaj_znak(buffor);
    while (potencjalna_cyfra_liczby_warstw >= '0' && potencjalna_cyfra_liczby_warstw <= '9')
    {
        int cyfra_liczby_warstw = potencjalna_cyfra_liczby_warstw - '0';
        liczba_warstw = liczba_warstw * 10 + cyfra_liczby_warstw;
        potencjalna_cyfra_liczby_warstw = wczytaj_znak(buffor);
    }
    oddaj_znak(potencjalna_cyfra_liczby_warstw, buffor);
    if (liczba_warstw == 0)
    {
        liczba_warstw = 1;
    }

    int kat_obrotu = 1; // 90 stopni, domyślna wartość
    char potencjalny_kat_obrotu = wczytaj_znak(buffor);
    if (potencjalny_kat_obrotu == '"')
    {
        kat_obrotu = 2; // 180 stopni
    }
    else if (potencjalny_kat_obrotu == '\'')
    {
        kat_obrotu = 3; // 270 stopni
    }
    else
    {
        oddaj_znak(potencjalny_kat_obrotu, buffor);
    }
    obroc(k, sciana, liczba_warstw, kat_obrotu);
    return 1;
}

int main(void)
{
    char kostka[6][N][N];
    char buffor = '?';
    ustaw_poczatkowa_wartosc(kostka);
    while (wykonaj_rozkaz(kostka, &buffor))
    {
    }
    return 0;
}
