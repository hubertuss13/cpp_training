Dane

Wejście:
coins[]: lista nominałów (dodatnie liczby całkowite, bez powtórzeń)
amount: kwota do uzyskania (liczba całkowita ≥ 0)

coins = {1, 3, 4}
amount = 6

Tablica ma amount + 1 = 7 komórek (indeksy 0..6)
a:     0    1    2    3    4    5    6
dp:    0   INF  INF  INF  INF  INF  INF

Wzór:
dp[0] = 0       (kwota 0 → zero monet)
dp[a] = min po wszystkich monetach c, gdzie c <= a: dp[a - c] + 1


dp[1]: kwota 1
moneta 1: mieści się (1 ≤ 1) → dp[1-1] + 1 = dp[0] + 1 = 0 + 1 = 1
moneta 3: nie mieści się (3 > 1)
moneta 4: nie mieści się (4 > 1)
min = 1 (jedna moneta: 1)


dp[2]: kwota 2
moneta 1: dp[2-1] + 1 = dp[1] + 1 = 1 + 1 = 2
monety 3, 4: nie mieszczą się
min = 2 (1+1)


dp[3]: kwota 3
moneta 1: dp[3-1] + 1 = dp[2] + 1 = 2 + 1 = 3
moneta 3: dp[3-3] + 1 = dp[0] + 1 = 0 + 1 = 1
moneta 4: nie mieści się
min(3, 1) = 1 (jedna moneta: 3)


dp[4]: kwota 4
moneta 1: dp[3] + 1 = 1 + 1 = 2
moneta 3: dp[1] + 1 = 1 + 1 = 2
moneta 4: dp[0] + 1 = 0 + 1 = 1
min(2, 2, 1) = 1 (jedna moneta: 4)


dp[5]: kwota 5
moneta 1: dp[4] + 1 = 1 + 1 = 2
moneta 3: dp[2] + 1 = 2 + 1 = 3
moneta 4: dp[1] + 1 = 1 + 1 = 2
min(2, 3, 2) = 2 (4+1)


dp[6]: kwota 6
moneta 1: dp[5] + 1 = 2 + 1 = 3
moneta 3: dp[3] + 1 = 1 + 1 = 2
moneta 4: dp[2] + 1 = 2 + 1 = 3
min(3, 2, 3) = 2 (3+3)


Gotowa tablica:
a:     0    1    2    3    4    5    6
dp:    0    1    2    1    1    2    2
