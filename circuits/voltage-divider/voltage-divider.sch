<Qucs Schematic 0.0.18>
<Properties>
  <View=0,0,1130,800,1,0,0>
  <Grid=10,10,1>
  <DataSet=voltage-divider.dat>
  <DataDisplay=voltage-divider.dpl>
  <OpenDisplay=1>
  <Script=voltage-divider.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
  <.PortSym 40 20 1 0>
  <.PortSym 40 60 2 0>
  <.PortSym 40 100 3 0>
</Symbol>
<Components>
  <R R1 1 520 240 -119 -16 0 1 "700 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <R R2 1 520 430 -118 -17 0 1 "3300 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <GND * 1 520 560 0 0 0 0>
  <Vdc Source 1 280 320 18 -26 0 1 "10 V" 1>
  <.DC DC1 1 60 300 0 43 0 0 "26.85" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "no" 0 "150" 0 "no" 0 "none" 0 "CroutLU" 0>
  <Port P1 1 740 160 4 -42 0 2 "1" 1 "analog" 0>
  <Port P2 1 740 340 4 -42 0 2 "2" 1 "analog" 0>
  <Port P3 1 740 500 4 -42 0 2 "3" 1 "analog" 0>
  <R Load 1 660 430 15 -26 0 1 "330 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
</Components>
<Wires>
  <280 160 520 160 "" 0 0 0 "">
  <520 160 520 210 "" 0 0 0 "">
  <280 500 520 500 "" 0 0 0 "">
  <520 270 520 340 "" 0 0 0 "">
  <520 460 520 500 "" 0 0 0 "">
  <280 160 280 290 "" 0 0 0 "">
  <280 350 280 500 "" 0 0 0 "">
  <520 500 520 560 "" 0 0 0 "">
  <520 160 740 160 "" 0 0 0 "">
  <520 340 520 400 "" 0 0 0 "">
  <520 340 660 340 "" 0 0 0 "">
  <520 500 660 500 "" 0 0 0 "">
  <660 500 740 500 "" 0 0 0 "">
  <660 460 660 500 "" 0 0 0 "">
  <660 340 740 340 "" 0 0 0 "">
  <660 340 660 400 "" 0 0 0 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
