# IPK - Projekt 2

## Autor
Vojtěch Bůbela
login: xbubel08

## Zadání projektu 2:
Implementujte aplikaci paket sniffer, která bude schopná "krást" pakety
z vybrané sítě a následně je vypsat.
Aplikace bude nastavitelná přes sadu přepínačů, které umožní filtrovat
vybrané typy protokolů, počet zobrazených paketů či port, na kterém
se má naslouchat.

## Ovládání
Projekt lze přeložit pomocí příkazu `make` a smazat pomocí `make clean`
Projekt je možné spustit s následujícími přepínači:

    `./ipk-sniffer` nebo `./ipk-sniffer -i` - vypíše seznam dostupných rozhraní
    `./ipk-sniffer -i nazev_rozhrani`       - vypíše jeden paket libovolného protokolu z rozhraní
    `./ipk-sniffer -i nazev_rozhrani -n cislo` - vypíše `cislo` paketů
    `./ipk-sniffer -i nazev_rozhrani -p cislo` - vypise pouze pakety které jdou z/na port `cislo`
    `./ipk-sniffer -i nazev_rozhrani -t/--tcp` - vypise pouze pakety protokolu tcp
    `./ipk-sniffer -i nazev_rozhrani -u/--udp` - vypise pouze pakety protokolu udp
    `./ipk-sniffer -i nazev_rozhrani --icmp` - vypise pouze pakety protokolu icmp

Vsechny argumenty lze kombinovat v libovolnem pořadí (pouze -i, -n a -p za sebou musí mít odpovídající hodnotu).
V případě spuštění aplikace jako `./ipk-sniffer` nebo `./ipk-sniffer -i` nepřijímá aplikace žádné další přepínače.

## Detaily implementace
V mém projektu nepodporuji přepínač --arp. Může být zadán aplikaci, avšak nic nevykoná.
Aplikace také nepodporuje IPv6.
