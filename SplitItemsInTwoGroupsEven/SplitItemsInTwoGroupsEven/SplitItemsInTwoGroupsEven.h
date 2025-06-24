//
//  SplitItemsInTwoGroupsEven.hpp
//  SplitItemsInTwoGroupsEven
//
//  Created by Juan Jofre on 10/18/18.
//  Copyright © 2018 Juan Jofre. All rights reserved.
//


#ifndef SplitItemsInTwoGroupsEven_h
#define SplitItemsInTwoGroupsEven_h

#include "general.h"


template<class T> ABlists<T> SplitExhaustive(std::vector<T> l);
template<class T> ABlists<T> SplitGreedy(std::vector<T> l);
template<class T> ABlists<T> SplitClosestDifference(std::vector<T> l, ClosestDifferenceType cdt);
template<class T> ABlists<T> SplitClosestDifferenceUp(std::vector<T> l);
template<class T> ABlists<T> SplitClosestDifferenceDownUp(std::vector<T> l);
template<class T> ABlists<T> SplitClosestDifferenceDownDown(std::vector<T> l);


#endif /* SplitItemsInTwoGroupsEven_hpp */
