#pragma once

#ifndef HUFFMAN
#define HUFFMAN

#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <algorithm>

namespace Huffman
{
  typedef unsigned long long ulong64;
  using namespace std;

  enum BitEncode
  {
    NotAssigned = -1, Zero = 0, One = 1
  };

  struct LabelFrequency
  {
    string label;
    ulong64 frequency;

    LabelFrequency(string l, ulong64 f):
      label(l), frequency(f)
    {}

    bool operator <(const LabelFrequency &other) const
    {
      return frequency < other.frequency;
    }
  };

  class HuffmanNode
  {
  public:
    HuffmanNode();
    HuffmanNode(LabelFrequency datapoint);
    HuffmanNode(string lbl, ulong64 frq);
    HuffmanNode(HuffmanNode &lf, HuffmanNode &rg);
    ~HuffmanNode();

    void AssignBit(BitEncode b);
    ulong64 GetFrequency();
    string GetLabel();

  private:
    LabelFrequency DataPoint;
    BitEncode assignedbit;
    HuffmanNode *left, *right, *up;
  };

  class Huffman
  {
  public:
    Huffman(vector<LabelFrequency> datapoints);
    ~Huffman();

  private:
    vector<LabelFrequency> DataPoints;
    HuffmanNode Paths;

  };

  Huffman::Huffman(const vector<LabelFrequency> datapoints)
  {
    DataPoints = datapoints; // ToDo: Make a deep copy of datapoints

    if (datapoints.size() == 0) return;

    if (datapoints.size() == 1)
    {
      HuffmanNode right(datapoints[0]);
      right.AssignBit(BitEncode::One);

      Paths = right;
      return;
    }


    sort(DataPoints.begin(), DataPoints.end());

    if (datapoints.size() == 2)
    {
      HuffmanNode left(DataPoints[0]);
      left.AssignBit(BitEncode::Zero);

      HuffmanNode right(DataPoints[1]);
      right.AssignBit(BitEncode::One);

      Paths = HuffmanNode(left, right);
      return;
    }

    queue<HuffmanNode> constructs;

    typedef vector<LabelFrequency>::iterator dpIterator;

    HuffmanNode leftright[2];

    dpIterator i = DataPoints.begin();
    while (i != DataPoints.end() || constructs.size() > 0)
    {

      if (constructs.size() > 0 && i != DataPoints.end())
      {
        if ((*i).frequency < constructs.front().GetFrequency())
        {
          left = HuffmanNode(*i);
          ++i;
        }
      }
      else
      {
        left = HuffmanNode(*i);
        ++i;
      }

      if (true)
      {

      }
    }

  }

  Huffman::~Huffman()
  {
  }
}
#endif // !HUFFMAN
