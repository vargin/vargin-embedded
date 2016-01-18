<Qucs Schematic 0.0.18>
<Properties>
  <View=0,-21,920,728,1,0,0>
  <Grid=10,10,1>
  <DataSet=basic.dat>
  <DataDisplay=basic.dpl>
  <OpenDisplay=1>
  <Script=basic.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
  <.ID -20 -16 SUB>
  <Line -20 20 40 0 #000080 2 1>
  <Line 20 20 0 -40 #000080 2 1>
  <Line -20 -20 40 0 #000080 2 1>
  <Line -20 20 0 -40 #000080 2 1>
</Symbol>
<Components>
  <GND * 1 240 280 0 0 0 0>
  <Lib REDLED 1 460 180 13 17 0 1 "LEDs" 0 "red" 0>
  <.DC DC1 1 740 340 0 43 0 0 "26.85" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "no" 0 "150" 0 "no" 0 "none" 0 "CroutLU" 0>
  <VProbe Pr2 1 630 120 28 -31 0 0>
  <IProbe Pr3 1 410 40 -26 16 0 0>
  <Switch S1 1 330 150 -26 11 0 0 "on" 0 "1 ms" 0 "0" 0 "1e12" 0 "26.85" 0 "1e-6" 0>
  <Vdc Battery2 1 240 110 18 -26 0 1 "1.5 V" 1>
  <Vdc Battery1 1 250 190 18 -26 0 1 "1.5 V" 1>
  <R R1 1 270 20 -26 15 0 0 "235 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
</Components>
<Wires>
  <460 210 460 220 "" 0 0 0 "">
  <250 220 460 220 "" 0 0 0 "">
  <250 220 250 280 "" 0 0 0 "">
  <240 280 250 280 "" 0 0 0 "">
  <240 160 250 160 "" 0 0 0 "">
  <300 20 300 150 "" 0 0 0 "">
  <240 20 240 80 "" 0 0 0 "">
  <620 140 620 150 "" 0 0 0 "">
  <460 150 620 150 "" 0 0 0 "">
  <640 140 640 210 "" 0 0 0 "">
  <460 210 640 210 "" 0 0 0 "">
  <360 40 360 150 "" 0 0 0 "">
  <460 40 460 150 "" 0 0 0 "">
  <360 40 380 40 "" 0 0 0 "">
  <440 40 460 40 "" 0 0 0 "">
  <240 140 240 160 "" 0 0 0 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
