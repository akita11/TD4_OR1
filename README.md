# TD4_OR1

4bit CPU, TD4, in book ["How to Build CPU" ("CPUの創りかた" in Japanese)](https://www.amazon.co.jp/dp/4839909865/) using NDA-free PDK, [OpenRule1um](https://github.com/akita11/OpenRule1um).

## Contents

- Layout GDS: TD4core.GDS (open with [KLayout](https://www.klayout.de/), with [OpenRul1um PDK(https://github.com/MakeLSI/OpenRule1um) and [its standard cells](https://github.com/MakeLSI/OpenRule1um_StdCell) installed)

- Schematic: sch/TD4core.kicad_sch (open with EEschema in [KiCAD](https://www.kicad.org/))

## How to do LVS check

- Export netlit from TD4core.kicad_sch using EEschema, TD4core.cir.
- Add ".inc OR1SC.cir" at 2nd line in netlist file, TD4core.cir.
- Open TD4core.GDS with KLayout, execute "get_reference" macro with specifying TD4core.cir for reference netlist, and then, execute LVS (mainly digitl script).

<img src="https://github.com/akita11/TD4_OR1/blob/main/sch/LVSresult.jpg" width="320px">

## How to fabricate chip

- convert to fabrication GDS, with required information in fab's PDK, such as layer definitions, contact/via size conversion. Popular CMOS 0.6um PDK will satisfy OpenRule1um's design rule.


## Author

Junichi Akita (akita@fdi.jp), @akita11
