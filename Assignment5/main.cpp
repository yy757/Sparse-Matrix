//
//  main.cpp
//  Assignment5
//
//  Created by Leslie Yu on 5/15/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "spdefs.h"
#include "spunittest.hpp"
#include "memusage.hpp"
#include <time.h>

using namespace std;

int main(int argc, const char * argv[]) {
    
    testLargeScaleMatrix("Direct");
}
