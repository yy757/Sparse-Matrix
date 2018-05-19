//  MEMORY USAGE MONITOR
//  memusage.hpp
//  Assignment5
//
//  Created by Leslie Yu on 5/18/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//  Description : This file contains the memory monitor function.

#ifndef memusage_hpp
#define memusage_hpp

#include <stdio.h>
#include <cmath>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

void memUsage();

#endif /* memusage_hpp */
