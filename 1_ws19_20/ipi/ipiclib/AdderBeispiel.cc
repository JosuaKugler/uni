#include<iostream>
#include<cassert>
#include"DLL.hh"
#include"MinPriorityQueue.hh"
#include"MinPriorityQueueImp.cc"
#include"Queue.hh"
class Simulator; // forward declaration
class Wire;      // forward declaration
class Circuit;   // forward declaration
#include"Wire.hh"
#include"Circuit.hh"
#include"Simulator.hh"
#include"SimulatorImp.cc"
#include"WireImp.cc"
#include"Nand.hh"
#include"NandImp.cc"
#include"And.hh"
#include"AndImp.cc"
#include"Nor.hh"
#include"NorImp.cc"
#include"Or.hh"
#include"OrImp.cc"
#include"Exor.hh"
#include"ExorImp.cc"
#include"Inverter.hh"
#include"InverterImp.cc"
#include"Fork.hh"
#include"ForkImp.cc"
#include"Terminal.hh"
#include"TerminalImp.cc"
#include"Analyzer.hh"
#include"AnalyzerImp.cc"
#include"Clock.hh"
#include"ClockImp.cc"
#include"HalfAdder.hh"
#include"HalfAdderImp.cc"
#include"FullAdder.hh"
#include"FullAdderImp.cc"
#include"Adder4Bit.hh"
#include"Adder4BitImp.cc"

int main ()
{
  Adder4Bit adder;
  Analyzer analyzer(5);
  Terminal a3(low ),a2(high),a1(high),a0(high);
  Terminal b3(high),b2(low ),b1(high),b0(low );
  Terminal c0(low);

  Wire wa0,wa1,wa2,wa3;
  Wire wb0,wb1,wb2,wb3;
  Wire ws0,ws1,ws2,ws3;
  Wire wc0,wc4; 

  wc0.ConnectInput(c0,0);
  wc0.ConnectOutput(adder,8);

  wa0.ConnectInput(a0,0);
  wa1.ConnectInput(a1,0);
  wa2.ConnectInput(a2,0);
  wa3.ConnectInput(a3,0);
  wa0.ConnectOutput(adder,0);
  wa1.ConnectOutput(adder,1);
  wa2.ConnectOutput(adder,2);
  wa3.ConnectOutput(adder,3);

  wb0.ConnectInput(b0,0);
  wb1.ConnectInput(b1,0);
  wb2.ConnectInput(b2,0);
  wb3.ConnectInput(b3,0);
  wb0.ConnectOutput(adder,4);
  wb1.ConnectOutput(adder,5);
  wb2.ConnectOutput(adder,6);
  wb3.ConnectOutput(adder,7);

  ws0.ConnectInput(adder,0);
  ws1.ConnectInput(adder,1);
  ws2.ConnectInput(adder,2);
  ws3.ConnectInput(adder,3);
  ws0.ConnectOutput(analyzer,0);
  ws1.ConnectOutput(analyzer,1);
  ws2.ConnectOutput(analyzer,2);
  ws3.ConnectOutput(analyzer,3);

  wc4.ConnectInput(adder,4);
  wc4.ConnectOutput(analyzer,4);

  Sim.Simulate(40);
}
