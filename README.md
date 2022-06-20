# vfd-display

Some notes on building a display driver for a Futaba 16-LY-01ZL alphanumeric display.
It seems that Futaba no longer manufactures or supports these devices, but they are
commonly available for secondhand purchase.  The device has 37 pins at 0.2in spacing.

This is a vacuum flourescent display (VFD), which is a variant of the vacuum tube.
A small AC current is used to heat a filament (cathode) when then produces electrons
via thermionic emission.  The electrons are naturally attracted to anodes, if they
are positively charged.  Each anode is coated with a flourescent material, and glows
a distinctive amber/green color when active.  Between the cathode and anode is a grid
that controls whether the electrons flow.

This particular one is a sixteen digit alphanumeric display.  Each digit has sixteen
segments, plus three more indicators: a dot in the upper left corner (Q) and
a decimal (R) and comma (S) in the lower right corner.  Each segment corresponds
to one anode, and each digit is controlled by a separate grid.  As a result, the
display can be multiplexed much like a multi-digit LED display.

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

No datasheet is available for the device itself, however, it is mentioned in [this datasheet](TDK-CD1867N.pdf) for DC/AC inverters,
which provides some key parameters:

|Converter | Ef r.m.s Vac | If (mAac) | V1 (Vdc) | V2 (Vdc) | I1 (mAdc) max. | I2 (mAdc) max. | Display |
|---|---|---|---|---|---|---|---|
|CD-1884N | 7.2 | 75 | -47 | -58 | 20.4 | 7.5 | 16-LY-01ZL |
|CD-1884P | 7.2 | 75 | 58 | - | 29.9 | -| 16-LY-01ZL |

There are two power supply variants here: the N variant sets both the cathode and anodes well below ground, while the P variant sets the cathode at ground (+/- the small AC voltage) and the anodes and grids at 58V.  Ef is the AC voltage applied to the filament to generate electrons, and V1 is the potential difference between cathode and anodes.

We can test the pinouts quickly by using some lower voltages that are easily available with components on hand.  Handily, the connections for the filament (either end) and grids are easily visible through the glass, while the anode connections are printed on the back of the device.  Test by applying 3.3V DC to the filament pins, and then using +30VDC to the grids and anodes to light up various segments:

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



