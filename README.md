# vfd-display

Ndotes on building a display driver for a Futaba 16-LY-01ZL display.
This is a sixteen digit alphanumeric display.  Each digit has sixteen
segments, plus three more indicators: a dot in the upper left corner (Q) and
a decimal (R) and comma (S) in the lower right corner.

```
.             Q
 --- ---         AAA BBB
|\  |  /|       CD  E  FG
| \ | / |       C D E F G
 --- ---         HHH III
| / | \ |       J K L M N
|/  |  \|       JK  L  MN
 --- ---         OOO PPP
         .               R
          /               S
```

No datasheet is available for the device itself, however, it is mentioned in [this datasheet](tdk-converter-datasheet.pdf) for DC/AC inverters:

|Converter | E_f r.m.s V | I_f (mAac) | V_1 (Vdc) | V_2 (Vdc) | I_1 (mAdc) max. | I_2 (mAdc) max. | Display |
|---|---|---|---|---|---|---|---|
|CD-1884N | 7.2 | 75 | -47 | -58 | 20.4 | 7.5 | 16-LY-01ZL |
|CD-1884P | 7.2 | 75 | 58 | - | 29.9 | -| 16-LY-01ZL |

The pinout can be determined quickly by applying 3V DC to the filament pins at each end,
and then applying +30V DC to the grids and anodes:

Pin | Type | Number
---|---|---
1 | Filament | X 
2 | Anode | D
3 | Grid | 1
4 | Anode | Q
5 | Grid | 2
6 | Anode | K
7 | Grid | 3
8 | Anode | M
9 | Grid | 4
10 | Anode | F
11 | Grid | 5
12 | Anode | L
13 | Anode | E
14 | Grid | 6
15 | Anode | I
16 | Grid | 7
17 | Anode | H
18 | Grid | 8
19 | Anode | R
20 | Grid | 9
21 | Anode | S
22 | Grid | 10
23 | Anode | C
24 | Grid | 11
25 | Anode| J
26 | Anode | O
27 | Grid | 12
28 | Anode | P
29 | Grid | 13
30 | Anode | N
31 | Grid | 14
32 | Anode | G
33 | Grid | 15
34 | Anode | B
35 | Grid | 16
36 | Anode | A
37 | Filament | Y


