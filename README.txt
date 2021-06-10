Programnyelv az informatika tanárainknak:

Lényeg: Van egy 2D-s pálya (maga a kód) és egy parancs mutató (PM). Ennek van egy iránya és egy helyzete. Legelőször jobbra megy, és a bal felső sarokban lévő parancson áll. Mindig lefuttatja a mutatott parancsot (1 parancs = 1 karakter), majd az irányában továbblép egyet. Hogyha elér egy sorvéget, a sor elejére ugrik. Ez fordítva és függőlegesen is igaz. (A jobb megértéshez el lehet olvasni a ><> nyelv dokumentációját (angol nyelvű): https://esolangs.org/wiki/Fish)
Adatstruktúra:
- Van egy 24 elemű tömb (az osztályt szimbolizálja), mindegyik eleme egy egész számot tárol (−2147483648 - +2147483647), alapból minden elem 0. A tömb elemei 1-től 24-ig vannak számozva. Van egy tanár, aki mindig megfigyel egy diákot. Az ő értékét tudja elérni, módosítani.
- Van egy verem, szintén ugyanakkora számot tárolhat, mint a tömb elemei. A program indításakor üres.
- Még egy változó is rendelkezésünkre áll, ugyanakkora számot tárolhat mint az előzőek. Indításkor az értéke 0.

Programfájl: szövegfájl, LF vagy CRLF sortörések. Maximális sorhossz: 4294967295, sorok száma maximum: 4294967295. A kódot érdemes Notepad-dal szerkeszteni (magyar Windows-on Jegyzettömb).

Parancsok:
A parancsokat külön kategóriákba osztottam. Minden parancs egy karakter. Kommentnek számítanak azok a karakterek, amiket mindig elkerül a PM. Vigyázat! Érdemes kerülni az ékezetes karaktereket, mert tönkretehetik a kódunkat! (Legtöbbjük két karakternek számít.)

PM irányítása:
Ezek a parancsok átállítját a PM irányát.
 <    PM balra
 >    PM jobbra
 ^    PM fel
 v    PM le

Verem:
 Hogyha valamilyen módon elérjük a legfelső elemet, akkor azt kivesszük a veremből.
 Hogyha nincsen elég elem a veremben a megfelelő utasításhoz, akkor a program hibaüzenetet ír ki, majd a futtatás megáll.
 Matematikai és logikai műveletek:
  A művelet eredményét belerakják a verembe.
  x: legfelső elem a veremből
  y: második legfelső elem a veremből
   +  y+x (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 87})
   -  y-x (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 81})
   /  y/x (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 28}) Lefelé kerekít!
   *  y*x (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 252})
   %  y%x (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 0})
   =  Ha y==x, akkor 1, különben 0 (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 0})
   )  Ha y>x, akkor 1, különben 0 (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 0})
   (  Ha y<x, akkor 1, különben 0 (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 1})
 Számjegyek:
  0-9 Az értéket belerakja a verembe
 Verem műveletek:
  :   Duplikálja a legfelső értéket a veremben (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 84, 3, 3})
  ~   Kiveszi a legfelső elemet a veremből (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 84})
  $   Kicseréli a két legfelső elemet a veremben (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 3, 84})
  r   Megfordítja a vermet (pl. verem = {65, 1, -4, 84, 3} -> {3, 84, -4, 1, 65})
  l   A verem méretét belerakja a verembe (pl. verem = {65, 1, -4, 84, 3} -> {65, 1, -4, 84, 3, 5})

Változó:
 &    A legfelső elemet kiveszi a veremből, és eltárolja a változóban
 @    A változó értékét belerakja a verembe (a változó nem nullázódik!)

Osztály:
 s    Az aktuálisan megfigyelt diák sorszámát belerakja a verembe
 p    A verem legfelső elemét kiveszi, és eltárolja a jelenleg megfigyelt diákban
 u    Az aktuálisan megfigyelt diák értékét belerakja a verembe
 k    Az aktuálisan megfigyelt gyereknek "kitekeri a nyakát" -> értéke 0 lesz
 h    Az aktuálisan megfigyelt gyerek teljesítményén szórakozik, ezért a gyerek értéke a négyzetére változik (pl. gyerek = 75 -> 5625)
 t    A következő diákot vonja megfigyelés alá (24 -> 1)
 e    Eggyel előrébb lévő diákra megy (1 -> 24)
 b    Kiveszi a legfelső elemet a veremből, majd ahhoz a gyerekhez teleportál. Formula a kisebb / nagyobb értékek átszámolásához: (x - 1) % 24 + 1, vagyis hogyha a 25-ös gyerekhez menne, akkor az 1-eshez megy.

Kimenet/bemenet:
 n    A verem legfelső értékét kiveszi, majd számként kiírja
 a    A verem legfelső értékét kiveszi, majd karakterként kiírja (ASCII kód alapján)
 i    Egy karakter bemenetet vár a program, majd az ASCII értékét belerakra a verembe
 m    Egy karakter bemenetet vár a program, majd az ASCII értékét belerakra a verembe. Hogyha a bemenet elfogyott, a program kilép.

Feltétel:
 ?    Kiveszi a legfelső elemet a veremből, ha ez 0, akkor a PM egy helyett kétszer mozog

Leállítás:
 ;    Leállítja a programot
 Másik opció lehet az 'm' parancs használata, az leállítja a programot, ha elfogyott a bemenet.

Egyéb:
 minden más karakter: nem csinál semmit, de utasításnak számít. Vigyázat! Az ékezetes karakterek néha két utasításnak számíthatnak! (Érdemes mellőzni őket)



A CD tartalma:
- README.txt: Ez a fájl
- interpreter.exe: Windows-os futtatóprogram. Parancssorból indítható el.
- interpreter.cpp: A futtatóprogram forráskódja. C++-ban lett megírva.

Példaprogramok:
- hello_world.txt: Kiírja, hogy "Hello World!". Csak a vermet használja.
- hello_world2.txt: Kiírja, hogy "Hello World!". Az osztályt is használja.
- cat.txt: Egy program, ami mindent kiír, amit a bemenetbe bevittünk.
- truth-machine.txt: Egy program, ami vár egy számot, ha ez 0, akkor kiírja, hogy 0, hogyha pedig 1, akkor végtelen 1-t ír ki.
