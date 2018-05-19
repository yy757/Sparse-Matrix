//  MEMORY USAGE MONITOR
//  memusage.cpp
//  Assignment5
//
//  Created by Leslie Yu on 5/18/18.
//  Copyright © 2018 Leslie Yu. All rights reserved.
//  Description : This file contains the memory monitor function.

#include "memusage.hpp"

void memUsage(){
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;
    
    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                          (host_info64_t)&vm_stats, &count))
    {
        long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;
        
        long long used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
        printf("free memory: %f GB \nused memory: %f GB\n", free_memory / float(pow(1024,3)), used_memory / float(pow(1024,3)));
    }
}
