#include <stdlib.h>
#include "fs.h"
#include "disk.h"
#include "validate.h"
#include <assert.h>
#include <stdio.h>

#define INODE_SIZE (64)
#define NUM_INODE_PER_BLOCK (BLOCK_SIZE/INODE_SIZE)	// 512/64 = 8
#define TOTAL_INODE_NUM (NUM_INODE_PER_BLOCK * INODELIST_BLKS) 	// 8 * 4 = 32
#define TOTAL_BLOCK_NUM (TOTAL_INODE_NUM)	//32

void testcase1(void)
{
	int i =0;
	FileSysInit();
	
	for(i=0; i < TOTAL_BLOCK_NUM;i++)
	{
		if(i%4==3)
		{
			SetBlockBitmap(i);
			
			if(vGetBitValue(BLOCK_BITMAP_BLK_NUM, i)==1)
			{
				printf("Success about SetBlockBitmap().\n");
			}
			else
			{
				printf("Fail about SetBlockBitmap().\n");
				return;
			}
			
		}
	}
	
	fo