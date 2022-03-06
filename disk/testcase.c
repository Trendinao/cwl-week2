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
	
	for(i=0;i<TOTAL_BLOCK_NUM;i++)
	{
		if(i%8==7)
		{
			ResetBlockBitmap(i);
			
			if(vGetBitValue(BLOCK_BITMAP_BLK_NUM,i)==0)
			{
				printf("Success about ResetBlockBitmap().\n");
			}
			else
			{
				printf("Fail about ResetBlockBitmap().\n");
				return;
			}
			
		}
	}
	
	printf("Testcase 1 Complete!\n");
}


void testcase2(void)
{
	int i=0;
	int BitValue =0;
	
	FileSysInit();
	
	for(i=0;i<TOTAL_BLOCK_NUM;i++)
	{
		SetBlockBitmap(i);
	}
	
	for(i=0;i<TOTAL_BLOCK_NUM;i++)
	{
		if(i%8==7)
		{
			ResetBlockBitmap(i);
			if(i== GetFreeBlockNum())
			{
				
				if(vGetBitValue(BLOCK_BITMAP_BLK_NUM,i)==0)
				{
					BitValue = vGetBitValue(BLOCK_BITMAP_BLK_NUM,i);
					printf("Reseult of GetFreeBlockNum() : %d ,	The Value of Bit %d : %d \n", GetFreeBlockNum(), GetFreeBlockNum(), BitValue);
					SetBlockBitmap(i);
				}
				else
				{
					printf("Fail : The Value of Bit %d is not 0.\n",GetFreeBlockNum());
					return;
				}
				
			}
			else
			{
				printf("Fail : GetFreeBlockNum() is incorrect!\n");
				return;
			}
		}
	}
	
	printf("TestCase 2 Complete!\n");
}


void testcase3(void)
{
	int i =0;
	FileSysInit();
	
	for(i=0; i < TOTAL_INODE_NUM;i++)
	{
		if(i%4==3)
		{
			SetInodeBitmap(i);
			
			if(vGetBitValue(INODE_BITMAP_BLK_NUM, i)==1)
			{
				printf("Success about SetInodeBitmap().\n");
			}
			else
			{
				printf("Fail about SetInodeBitmap().\n");
				return;
			}
			
		}
	}
	
	for(i=0;i<TOTAL_INODE_NUM;i++)
	{
		if(i%8==7)
		{
			ResetInodeBitmap(i);
			
			if(vGetBitValue(INODE_BITMAP_BLK_NUM,i)==0)
			{
				printf("Success about ResetInodeBitmap().\n");
			}
			else
			{
				printf("Fail about ResetInodeBitmap().\n");
				return;
			}
			
		}
	}
	
	printf("Testcase 3 Complete!\n");

}

void 