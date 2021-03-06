/* mbr_types.h
 *
 * Copyright (C) 2017 Motoharu Gosuto
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once

//this header is partially based on information from
//https://wiki.henkaku.xyz/vita/Partitions

#include <stdint.h>

#define SCEHeader "Sony Computer Entertainment Inc."

#define MAX_MBR_PARTITIONS 16

enum PartitionCodes
{
   empty_c = 0,
   eMMC = 0x01, //first eMMC partition, some data, IdStorage?
   SLB2 = 0x02, //SLB2 Boot loaders
   os0 =  0x03, //Main OS partition, contains kernel libraries
   vs0 =  0x04, //Contains system applications & libraries
   vd0 = 0x05,  //Registry and error history
   tm0 = 0x06,  //Unknown, has an empty folder nphome
   ur0 = 0x07,  //User resources, LiveArea cache, database, & other stuff
   ux0 = 0x08,  //Memory Card
   gro0 = 0x09, //Game Card
   grw0 = -1,   //Game Card writable area
   ud0 = 0x0B,  //Updater copied here before reboot
   sa0 = 0x0C,  //Dictionary and font data
   cardsExt = 0x0D, //Some data on Memory Card & Game Card
   pd0 = 0x0E //Welcome Park and welcome video
};

enum PartitionTypes
{
   empty_t = 0,
   fat16 = 0x06,
   exfat = 0x07,
   raw = 0xDA
};

#pragma pack(push, 1)

typedef struct PartitionEntry
{
   uint32_t partitionOffset; //in blocks
   uint32_t partitionSize; //in blocks
   uint8_t partitionCode; //PartitionCodes
   uint8_t partitionType; //PartitionTypes
   uint8_t partitionActive;
   uint8_t flags;
   uint8_t unk[5];
} PartitionEntry;

typedef struct MBR
{
   char header[0x20];
   uint32_t version; //3
   uint32_t sizeInBlocks;
   uint32_t unk_28;
   uint32_t unk_2C;
   uint32_t unk_30;
   uint32_t unk_34;
   uint32_t unk_38;
   uint32_t unk_3C;
   uint32_t unk_40;
   uint32_t unk_44;
   uint32_t unk_48;
   uint32_t unk_4C;
   
   PartitionEntry partitions[MAX_MBR_PARTITIONS]; //offset 0x50

   uint8_t unk_data[0x5E];

   uint8_t unk_data_1BE[0x10];
   uint8_t unk_data_1CE[0x10];
   uint8_t unk_data_1DE[0x10];
   uint8_t unk_data_1EE[0x10];
   
   uint16_t signature;
} MBR;

#pragma pack(pop) 

//defalut size of sector for SD MMC protocol
#define SD_DEFAULT_SECTOR_SIZE 0x200
