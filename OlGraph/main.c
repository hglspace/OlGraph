//
//  main.c
//  OlGraph
//
//  Created by zyq on 2018/1/6.
//  Copyright © 2018年 zyq. All rights reserved.
//

#include <stdio.h>
#include "myhead.h"
int main(int argc, const char * argv[]){
    //printf("你好");
    struct OlGraph init(void);
    void DFSTraverse(struct OlGraph g);
    struct OlGraph g=init();
    DFSTraverse(g);
    return 0;
}
