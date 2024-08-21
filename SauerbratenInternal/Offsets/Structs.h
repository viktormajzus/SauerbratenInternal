#pragma once
#include <cstdint>
#include "../Utility/Math.h"

// Created with ReClass.NET 1.2 by KN4CK3R

class Entity
{
public:
	Vector3 position; //0x0000
	Vector3 velocity; //0x000C
	char pad_0018[24]; //0x0018
	Vector3 position2; //0x0030
	Vector3 viewAngle; //0x003C
	char pad_0044[47]; //0x0044
	int8_t entityState; //0x0077
	char pad_0078[256]; //0x0078
	int32_t health; //0x0178
	int32_t maxHealth; //0x017C
	int32_t armor; //0x0180
	int32_t armorType; //0x0184
	int32_t quadDamage; //0x0188
	int32_t currentWeapon; //0x018C
	int32_t damageType; //0x0190
	int32_t fistAmmo; //0x0194
	int32_t shotgunAmmo; //0x0198
	int32_t chaingunAmmo; //0x019C
	int32_t launcherAmmo; //0x01A0
	int32_t rifleAmmo; //0x01A4
	int32_t grenadeAmmo; //0x01A8
	int32_t pistolAmmo; //0x01AC
	char pad_01B0[76]; //0x01B0
	bool N00000150; //0x01FC
	char pad_01FD[59]; //0x01FD
	int32_t killCount; //0x0238
	char pad_023C[56]; //0x023C
	char name[16]; //0x0274
	char pad_0284[244]; //0x0284
	char team[4]; //0x0378
}; //Size: 0x037C