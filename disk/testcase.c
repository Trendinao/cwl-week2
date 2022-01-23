#include <stdlib.h>
#include "fs.h"
#include "disk.h"
#include "validate.h"
#include <assert.h>
#include <stdio.h>

#define INODE_SIZE (64)
#define NUM_INODE_PER_BLOCK (BLOCK_SIZE/INODE_SIZE)	// 512/64 = 8
#define TOTAL_INODE_NUM (N