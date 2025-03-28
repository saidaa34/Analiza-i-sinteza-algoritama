# Analiza-i-sinteza-algoritama
Travelling salesman problem (TSP)

Formulacija zadatka:

Travelling salesman problem (TSP) je problem obilaska svakog čvora grafa tačno jednom vraćajući se nakon toga u početni čvor, ali tako da je dužina te rute minimalna (radi se naravno o težinskom grafu). Pretpostavlja se da su svaka dva čvora povezana te da je graf neusmjeren (dakle možete graf čuvati kao matricu susjedstva). Primijetimo da rješenje TSP problema možemo predstaviti kao permutaciju čvorova 1,2, … , 𝑛 (ili 0,1,2, … , 𝑛 − 1). Međutim, permtuacija ima 𝑛! (preciznije, u ovom slučaju (𝑛 − 1)! jer je prvi čvor iz kojeg krećemo fiksan), te je već za 𝑛 = 20 nemoguće u realnom vremenu ispitati dužinu svake moguće rute. Zbog toga se pristupa heurističkim metodama koje ne moraju dati optimalno rješenje, ali se ruta pronalazi u realnom vremenu. Na stranici http://www.math.uwaterloo.ca/tsp/world/countries.html se nalaze fajlovi u kojima su spašeni gradovi iz raznih država, te se na osnovu njih mogu kreirati grafovi koji predstavljaju te države. Data je koordinata svakog grada, a udaljenosti između gradova se računaju kao Euklidska udaljenost između ta dva grada zaokružena na najbliži cijeli broj. Potrebno je implementirati algoritam koji kreira rutu na sljedeći način: svaki put se u rutu dodaje grana sa najmanjom težinom koja ne pravi ciklus sa već dodatim granama, te nakon njenog dodavanja nijedan čvor nema stepen veći od 2. Lako se vidi da će se na ovaj način nakon što se doda 𝑛 − 1 grana dobiti put koji prolazi kroz sve čvorove, čime je dobijena ruta (samo još spojimo prvi i zadnji čvor sa tog puta). 
Implementirati 3 verzije ovog algoritma: 

•	jedna dodaje najmanju granu u rutu i onda nad rutom poziva neki od algoritama za pretraživanje (BFS ili DFS) da utvrdi ima li ciklusa, te briše granu ako ga ima; 

•	druga verzija koristi disjunktne skupove za određivanje ciklusa, pri čemu su disjunktni skupovi implementirani preko listi; 

•	treća verzija koristi implementaciju disjunktnih skupova preko stabala (rađenu na vježbama i predavanjima). 

Nakon toga, za razne države (sa raznim brojem gradova) uporediti vrijeme izvršavanja ova tri algoritma. Pored toga, uporediti koliko se ruta dobijena ovim algoritmima (sva tri algoritma bi trebala dati istu rutu ako na isti način sortirate grane) razlikuje od do sada pronađene najbolje rute za tu državu (ove podatke imate na stranici).
