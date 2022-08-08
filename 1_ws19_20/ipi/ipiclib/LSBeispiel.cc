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
#include"Terminal.hh"
#include"TerminalImp.cc"
#include"Fork.hh"
#include"ForkImp.cc"
#include"Analyzer.hh"
#include"AnalyzerImp.cc"
#include"Clock.hh"
#include"ClockImp.cc"

int main ()
{
  Nand nand1; Analyzer analyzer(3);
  Fork fork1,fork2; Clock clock(10,high);
  Wire a,b,c,d,e,f,g; Terminal term(high);

  a.ConnectInput(term,0);   a.ConnectOutput(fork1,0);  
  b.ConnectInput(clock,0);  b.ConnectOutput(fork2,0); 
  c.ConnectInput(fork1,0);  c.ConnectOutput(nand1,0);
  d.ConnectInput(fork1,1);  d.ConnectOutput(analyzer,0);
  e.ConnectInput(fork2,0);  e.ConnectOutput(nand1,1);
  f.ConnectInput(fork2,1);  f.ConnectOutput(analyzer,1);
  g.ConnectInput(nand1,0);  g.ConnectOutput(analyzer,2);

  Sim.Simulate(33);
}
