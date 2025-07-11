// Huffman.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Huffman.h"

#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;
Huffman::HuffmanNode::HuffmanNode()
{
  DataPoint = LabelFrequency("", 0);
  assignedbit = NotAssigned;
  left = 0;
  right = 0;
  up = 0;
}

Huffman::HuffmanNode::HuffmanNode(LabelFrequency datapoint)
{
  DataPoint = datapoint;
  assignedbit = NotAssigned;
  left = 0;
  right = 0;
  up = 0;
}

Huffman::HuffmanNode::HuffmanNode(string lbl, ulong64 frq)
{
  DataPoint.label = lbl;
  DataPoint.frequency = frq;
  assignedbit = NotAssigned;
  left = 0;
  right = 0;
  up = 0;
}

Huffman::HuffmanNode::HuffmanNode(HuffmanNode &lt, HuffmanNode &rt)
{
  left = &lt;
  right = &rt;
  rt.up = this;
  lt.up = this;
  DataPoint.frequency = rt.DataPoint.frequency + lt.DataPoint.frequency;
  DataPoint.label = rt.DataPoint.label + "|" + lt.DataPoint.label;
}

Huffman::HuffmanNode::~HuffmanNode()
{
  if (left) delete &left;
  if (right) delete &right;
}

void Huffman::HuffmanNode::AssignBit(BitEncode b)
{
  assignedbit = b;
}

Huffman::ulong64 Huffman::HuffmanNode::GetFrequency()
{
  return DataPoint.frequency;
}

string Huffman::HuffmanNode::GetLabel()
{
  return DataPoint.label;
}


