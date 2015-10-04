#pragma once

#define APP_VERSION_W		_T("2.1.2")
#define APP_VERSION_A		"2.1.2"

// Total Size: 24 bytes
struct StringNode
{
	int32	field0000;
	int32	field0004;
	int32	field0008;
	int32	field0010;
	int32	field0014;
	LPSTR	ValuePtr;
};

// Total Size: 12 bytes
struct StringPool
{
	int32			field0000;
	int32			field0004;
	StringNode**	Nodes;
};

// Total Size: 40 bytes
struct Variable
{
	int32	field0000;
	int32	field0004;
	int32	field0008;
	int32	field000C;
	int32	field0010;
	int32	field0014;
	int32	field0018;
	int32	field001C;
	int32	field0020;
	int32	field0024;
};

// Total Size: 12 bytes
struct SymbolTable
{
	int32		FirstOperation;
	int32		ProgramLength;
	StringPool* StringPool;
};

// Total Size: 10420 bytes
struct VirtualMachine
{
	int32			field0000;
	int32			field0004;
	int32			field0008;
	int32			field000C;
	int32			field0010;
	int32			field0014;
	int32			field0018;
	int32			field001C;
	int32			CurrentOpcode;
	int32			field0024;
	int32			field0028;
	int32			field002C;
	int32			field0030;
	int32			field0034;
	int32			field0038;
	int32			field003C;
	int32			field0040;
	int32			MaxOperations;
	int32			field0048;
	Variable		Variables[256];
	int32			field284C;
	int32			field2850;
	int32			field2854;
	SymbolTable*	SymbolTable;
	LPVOID			GlobalTable;
	int32			field2860;
	int32			field2864;
	int32			LocalScope;
	int32			field286C;
	LPVOID			JumpTable;
	LPVOID			StringTable;
	int32			field2878;
	int32			field287C;
	int32			field2880;
	LPVOID			FunctionTable;
	int32			field2888;
	int32			field288C;
	int32			field2890;
	int32			field2894;
	int32			field2898;
	int32			field289C;
	int32			DecrementHandleFunction;
	LPVOID			HandleTable;
	int32			table28A8;
	int32			table28AC;
	int32			table28B0;
};

// Total Size: 668 bytes
struct Jass
{
	int32				VTable;
	int32				field0004;
	int32				field0008;
	VirtualMachine**	VirtualMachine;
	int32				field0010;
	int32				field0014;
	int32				field0018;
	int32				field001C;
	int32				field0020;
	int32				field0024;
	int32				field0028;
	int32				field002C;
	int32				field0030;
	int32				field0034;
	int32				field0038;
	int32				field003C;
	int32				field0040;
	int32				field0044;
	int32				field0048;
	int32				field004C;
	int32				field0050;
	int32				field0054;
	int32				field0058;
	int32				field005C;
	int32				field0060;
	int32				field0064;
	int32				field0068;
	int32				field006C;
	int32				field0070;
	int32				field0074;
	int32				field0078;
	int32				field007C;
	int32				field0080;
	int32				field0084;
	int32				field0088;
	int32				field008C;
	int32				field0090;
	int32				field0094;
	int32				field0098;
	int32				field009C;
	int32				field00A0;
	int32				field00A4;
	int32				field00A8;
	int32				field00AC;
	int32				field00B0;
	int32				field00B4;
	int32				field00B8;
	int32				field00BC;
	int32				field00C0;
	int32				field00C4;
	int32				field00C8;
	int32				field00CC;
	int32				field00D0;
	int32				field00D4;
	int32				field00D8;
	int32				field00DC;
	int32				field00E0;
	int32				field00E4;
	int32				field00E8;
	int32				field00EC;
	int32				field00F0;
	int32				field00F4;
	int32				field00F8;
	int32				field00FC;
	int32				field0100;
	int32				field0104;
	int32				field0108;
	int32				field010C;
	int32				field0110;
	int32				field0114;
	int32				field0118;
	int32				field011C;
	int32				field0120;
	int32				field0124;
	int32				field0128;
	int32				field012C;
	int32				field0130;
	int32				field0134;
	int32				field0138;
	int32				field013C;
	int32				field0140;
	int32				field0144;
	int32				field0148;
	int32				field014C;
	int32				field0150;
	int32				field0154;
	int32				field0158;
	int32				field015C;
	int32				field0160;
	int32				field0164;
	int32				field0168;
	int32				field016C;
	int32				field0170;
	int32				field0174;
	int32				field0178;
	int32				field017C;
	int32				field0180;
	int32				field0184;
	int32				field0188;
	int32				field018C;
	int32				field0190;
	int32				field0194;
	int32				field0198;
	int32				field019C;
	int32				field01A0;
	int32				field01A4;
	int32				field01A8;
	int32				field01AC;
	int32				field01B0;
	int32				field01B4;
	int32				field01B8;
	int32				field01BC;
	int32				field01C0;
	int32				field01C4;
	int32				field01C8;
	int32				field01CC;
	int32				field01D0;
	int32				field01D4;
	int32				field01D8;
	int32				field01DC;
	int32				field01E0;
	int32				field01E4;
	int32				field01E8;
	int32				field01EC;
	int32				field01F0;
	int32				field01F4;
	int32				field01F8;
	int32				field01FC;
	int32				field0200;
	int32				field0204;
	int32				field0208;
	int32				field020C;
	int32				field0210;
	int32				field0214;
	int32				field0218;
	int32				field021C;
	int32				field0220;
	int32				field0224;
	int32				field0228;
	int32				field022C;
	int32				field0230;
	int32				field0234;
	int32				field0238;
	int32				field023C;
	int32				field0240;
	int32				field0244;
	int32				field0248;
	int32				field024C;
	int32				field0250;
	int32				field0254;
	int32				field0258;
	int32				field025C;
	int32				field0260;
	int32				field0264;
	int32				field0268;
	int32				field026C;
	int32				field0270;
	int32				field0274;
	int32				field0278;
	int32				field027C;
	int32				field0280;
	int32				field0284;
	int32				field0288;
	int32				field028C;
	int32				field0290;
	int32				field0294;
	int32				field0298;
};

// Total Size: 784 bytes
struct Unit
{
	LPVOID	Virtual;
	int32	field0004;
	int32	field0008;
	int32	field000C;

	int32	field0010;
	int32	field0014;
	int32	field0018;
	int32	field001C;

	int32	field0020;
	int32	field0024;
	int32	field0028;
	int32	field002C;

	int32	field0030;
	int32	field0034;
	int32	field0038;
	int32	field003C;

	int32	field0040;
	int32	field0044;
	int32	field0048;
	int32	field004C;

	int32	field0050;
	int32	field0054;
	int32	field0058;
	int32	field005C;

	int32	field0060;
	int32	field0064;
	int32	field0068;
	int32	field006C;

	int32	field0070;
	int32	field0074;
	int32	field0078;
	int32	field007C;

	int32	field0080;
	int32	field0084;
	int32	field0088;
	int32	field008C;

	int32	field0090;
	int32	field0094;
	int32	field0098;
	int32	field009C;

	int32	field00A0;
	int32	field00A4;
	int32	field00A8;
	int32	field00AC;

	int32	field00B0;
	int32	field00B4;
	int32	field00B8;
	int32	field00BC;

	int32	field00C0;
	int32	field00C4;
	int32	field00C8;
	int32	field00CC;

	int32	field00D0;
	int32	field00D4;
	int32	field00D8;
	int32	field00DC;

	int32	field00E0;
	int32	field00E4;
	int32	field00E8;
	int32	field00EC;

	int32	field00F0;
	int32	field00F4;
	int32	field00F8;
	int32	field00FC;

	int32	field0100;
	int32	field0104;
	int32	field0108;
	int32	field010C;

	int32	field0110;
	int32	field0114;
	int32	field0118;
	int32	field011C;

	int32	field0120;
	int32	field0124;
	int32	field0128;
	int32	field012C;

	int32	field0130;
	int32	field0134;
	int32	field0138;
	int32	field013C;

	int32	field0140;
	int32	field0144;
	int32	field0148;
	int32	field014C;

	int32	field0150;
	int32	field0154;
	int32	field0158;
	int32	field015C;

	int32	field0160;
	int32	field0164;
	int32	field0168;
	int32	field016C;

	int32	field0170;
	int32	field0174;
	int32	field0178;
	int32	field017C;

	int32	field0180;
	int32	field0184;
	int32	field0188;
	int32	field018C;

	int32	field0190;
	int32	field0194;
	int32	field0198;
	int32	field019C;

	int32	field01A0;
	int32	field01A4;
	int32	field01A8;
	int32	field01AC;

	int32	field01B0;
	int32	field01B4;
	int32	field01B8;
	int32	field01BC;

	int32	field01C0;
	int32	field01C4;
	int32	field01C8;
	int32	field01CC;

	int32	field01D0;
	int32	field01D4;
	int32	field01D8;
	int32	field01DC;	//	Used	to	fetch	additional	abilities.

	int32	field01E0;	//	Used	to	fetch	additional	abilities.
	int32	field01E4;
	LPVOID	AbilityAttack;
	LPVOID	AbilityMove;

	LPVOID	AbilityHero;
	LPVOID	AbilityBuild;
	LPVOID	AbilityInventory;
	int32	field01FC;

	int32	field0200;
	int32	field0204;
	int32	field0208;
	int32	field020C;

	int32	field0210;
	int32	field0214;
	int32	field0218;
	int32	field021C;

	int32	field0220;
	int32	field0224;
	int32	field0228;
	int32	field022C;

	int32	field0230;
	int32	field0234;
	int32	field0238;
	int32	field023C;

	int32	field0240;
	int32	field0244;
	int32	field0248;
	int32	field024C;

	int32	field0250;
	int32	field0254;
	int32	field0258;
	int32	field025C;

	int32	field0260;
	int32	field0264;
	int32	field0268;
	int32	field026C;

	int32	field0270;
	int32	field0274;
	int32	field0278;
	int32	field027C;

	int32	field0280;
	float	X;
	float	Y;
	float	Z;

	int32	field0290;
	int32	field0294;
	int32	field0298;
	int32	field029C;

	int32	field02A0;
	int32	field02A4;
	int32	field02A8;
	int32	field02AC;

	int32	field02B0;
	int32	field02B4;
	int32	field02B8;
	int32	field02BC;

	int32	field02C0;
	int32	field02C4;
	int32	field02C8;
	int32	field02CC;

	int32	field02D0;
	int32	field02D4;
	int32	field02D8;
	int32	field02DC;

	int32	field02E0;
	int32	field02E4;
	int32	field02E8;
	int32	field02EC;

	int32	field02F0;
	int32	field02F4;
	int32	field02F8;
	int32	field02FC;

	int32	field0300;
	int32	field0304;
	int32	field0308;
	int32	field030C;
};

// Total Size: 32 bytes
struct RCString
{
	int32	VTable;
	int32	refCount;
	int32	Field_0008;
	int32	Field_000C;
	int32	Field_0010;
	int32	Field_0014;
	int32	Field_0018;
	LPSTR	String;
};

// Total Size: 16 bytes
struct JassString
{
	int32		VTable;
	int32		Field_0004;
	RCString*	Value;
	int32		Field_000C;
};

// Total Size: 12 bytes
struct JassStringManager
{
	int32		Field_0000;
	int32		Field_0004;
	JassString*	Strings;
};

// Total Size: 744 bytes
struct ThreadLocalStorage
{
	int32	field0000;
	int32	field0004;
	int32	field0008;
	int32	field000C;

	int32	field0010;
	Jass	Jass;
	int32	field02AC;
	int32	field02B0;

	int32	field02B4;
	int32	field02B8;
	int32	field02BC;
	int32	field02C0;

	int32	field02C4;
	int32	field02C8;
	int32	NetProviderLOOP;
	int32	field02D0;

	int32	field02D4;
	int32	field02D8;
	int32	field02DC;
	int32	field02E0;
};

// Total Size: 4 bytes
struct CTriggerWar3VTable
{
	LPVOID Function;
};

// Total Size: 124 bytes
struct Trigger
{
	CTriggerWar3VTable*	Virtual;
	int32				field0004;
	int32				field0008;
	int32				field000C;
	int32				field0010;
	int32				field0014;
	int32				field0018;
	int32				field001C;
	int32				field0020;
	int32				field0024;
	int32				field0028;
	int32				field002C;
	int32				field0030;
	int32				field0034;
	int32				field0038;
	int32				field003C;
	int32				field0040;
	int32				field0044;
	int32				field0048;
	int32				field004C;
	int32				field0050;
	int32				field0054;
	int32				field0058;
	int32				field005C;
	int32				field0060;
	int32				field0064;
	int32				field0068;
	int32				field006C;
	int32				field0070;
	int32				field0074;
	int32				field0078;
};

// Total Size: 4 bytes
struct CSimpleMessageFrameVTable
{
	LPVOID Function;
};

// Total Size: 404 bytes
struct SimpleMessageFrame
{
	CSimpleMessageFrameVTable*				Virtual;
	int32									field0004;
	int32									field0008;
	int32									field000C;
	int32									field0010;
	int32									field0014;
	int32									field0018;
	int32									field001C;
	int32									field0020;
	int32									field0024;
	int32									field0028;
	int32									field002C;
	int32									field0030;
	int32									field0034;
	int32									field0038;
	int32									field003C;
	int32									field0040;
	int32									field0044;
	int32									field0048;
	int32									field004C;
	int32									field0050;
	int32									field0054;
	int32									field0058;
	int32									field005C;
	int32									field0060;
	int32									field0064;
	int32									field0068;
	int32									field006C;
	int32									field0070;
	int32									field0074;
	int32									field0078;
	int32									field007C;
	int32									field0080;
	int32									field0084;
	int32									field0088;
	int32									field008C;
	int32									field0090;
	int32									field0094;
	int32									field0098;
	int32									field009C;
	int32									field00A0;
	int32									field00A4;
	int32									field00A8;
	int32									field00AC;
	int32									field00B0;
	int32									field00B4;
	int32									field00B8;
	int32									field00BC;
	int32									field00C0;
	int32									field00C4;
	int32									field00C8;
	int32									field00CC;
	int32									field00D0;
	int32									field00D4;
	int32									field00D8;
	int32									field00DC;
	int32									field00E0;
	int32									field00E4;
	int32									field00E8;
	int32									field00EC;
	int32									field00F0;
	int32									field00F4;
	int32									field00F8;
	int32									field00FC;
	int32									field0100;
	int32									field0104;
	int32									field0108;
	int32									field010C;
	int32									field0110;
	int32									field0114;
	int32									field0118;
	int32									field011C;
	int32									field0120;
	int32									field0124;
	int32									field0128;
	int32									field012C;
	int32									field0130;
	int32									field0134;
	int32									field0138;
	int32									field013C;
	int32									field0140;
	int32									field0144;
	int32									field0148;
	int32									field014C;
	int32									field0150;
	int32									field0154;
	int32									field0158;
	int32									field015C;
	int32									field0160;
	int32									field0164;
	int32									field0168;
	int32									field016C;
	int32									field0170;
	int32									field0174;
	int32									field0178;
	int32									field017C;
	int32									field0180;
	int32									field0184;
	int32									field0188;
	int32									field018C;
	int32									field0190;
}; 

// Total Size: 136 bytes
struct OrderTarget
{
	int32	VTable;
	int32	field0004;
	int32	field0008;
	int32	field000C;

	int32	field0010;
	int32	field0014;
	int32	field0018;
	int32	field001C;

	int32	field0020;
	int32	Order;
	int32	field0028;
	int32	field002C;

	int32	field0030;
	int32	field0034;
	int32	field0038;
	int32	field003C;

	int32	field0040;
	int32	field0044;
	float	X;
	int32	field004C;

	float	Y;
	int32	field0054;
	int32	field0058;
	int32	field005C;

	int32	field0060;
	int32	field0064;
	int32	field0068;
	int32	field006C;

	int32	field0070;
	int32	field0074;
	int32	field0078;
	int32	field007C;

	int32	field0080;
	int32	field0084;
};

// Total Size: 20 bytes
struct ClassPrototype
{
	int32	ClassSize;
	int32	BatchSize;
	int32	ElementsCreatedCount;
	LPVOID	MemoryAreas;
	LPVOID	FirstFreeElement;
};

// Total Size: 4 bytes
struct CItemVTable
{
	LPVOID Function;
};

// Total Size: 248 bytes
struct Item
{
	CItemVTable*	Virtual;
	int32			field0004;
	int32			field0008;
	int32			field000C;
	int32			field0010;
	int32			field0014;
	int32			field0018;
	int32			field001C;
	int32			field0020;
	int32			field0024;
	int32			field0028;
	int32			field002C;
	int32			field0030;
	int32			field0034;
	int32			field0038;
	int32			field003C;
	int32			field0040;
	int32			field0044;
	int32			field0048;
	int32			field004C;
	int32			field0050;
	int32			field0054;
	int32			field0058;
	int32			field005C;
	int32			field0060;
	int32			field0064;
	int32			field0068;
	int32			field006C;
	int32			field0070;
	int32			field0074;
	int32			field0078;
	int32			field007C;
	int32			field0080;
	int32			field0084;
	int32			field0088;
	int32			field008C;
	int32			field0090;
	int32			field0094;
	int32			field0098;
	int32			field009C;
	int32			field00A0;
	int32			field00A4;
	int32			field00A8;
	int32			field00AC;
	int32			field00B0;
	int32			field00B4;
	int32			field00B8;
	int32			field00BC;
	int32			field00C0;
	int32			field00C4;
	int32			field00C8;
	int32			field00CC;
	int32			field00D0;
	int32			field00D4;
	int32			field00D8;
	int32			field00DC;
	int32			field00E0;
	int32			field00E4;
	int32			field00E8;
	int32			field00EC;
	int32			field00F0;
	int32			field00F4;
};

// Total Size: 4 bytes
struct CGameUIVTable
{
	LPVOID Function;
};

// Total Size: 1108 bytes
struct GameUI
{
	CGameUIVTable*			Virtual;
	int32					field0004;
	int32					field0008;
	int32					field000C;
	int32					field0010;
	int32					field0014;
	int32					field0018;
	int32					field001C;
	int32					field0020;
	int32					field0024;
	int32					field0028;
	int32					field002C;
	int32					field0030;
	int32					field0034;
	int32					field0038;
	int32					field003C;
	int32					field0040;
	int32					field0044;
	int32					field0048;
	int32					field004C;
	int32					field0050;
	int32					field0054;
	int32					field0058;
	int32					field005C;
	int32					field0060;
	int32					field0064;
	int32					field0068;
	int32					field006C;
	int32					field0070;
	int32					field0074;
	int32					field0078;
	int32					field007C;
	int32					field0080;
	int32					field0084;
	int32					field0088;
	int32					field008C;
	int32					field0090;
	int32					field0094;
	int32					field0098;
	int32					field009C;
	int32					field00A0;
	int32					field00A4;
	int32					field00A8;
	int32					field00AC;
	int32					field00B0;
	int32					field00B4;
	int32					field00B8;
	int32					field00BC;
	int32					field00C0;
	int32					field00C4;
	int32					field00C8;
	int32					field00CC;
	int32					field00D0;
	int32					field00D4;
	int32					field00D8;
	int32					field00DC;
	int32					field00E0;
	int32					field00E4;
	int32					field00E8;
	int32					field00EC;
	int32					field00F0;
	int32					field00F4;
	int32					field00F8;
	int32					field00FC;
	int32					field0100;
	int32					field0104;
	int32					field0108;
	int32					field010C;
	int32					field0110;
	int32					field0114;
	int32					field0118;
	int32					field011C;
	int32					field0120;
	int32					field0124;
	int32					field0128;
	int32					field012C;
	int32					field0130;
	int32					field0134;
	int32					field0138;
	int32					field013C;
	int32					field0140;
	int32					field0144;
	int32					field0148;
	int32					field014C;
	int32					field0150;
	int32					field0154;
	int32					field0158;
	int32					field015C;
	int32					field0160;
	int32					field0164;
	int32					field0168;
	int32					field016C;
	int32					field0170;
	int32					field0174;
	int32					field0178;
	int32					field017C;
	int32					field0180;
	int32					field0184;
	int32					field0188;
	int32					field018C;
	int32					field0190;
	int32					field0194;
	int32					field0198;
	int32					field019C;
	int32					field01A0;
	int32					field01A4;
	int32					field01A8;
	int32					field01AC;
	BOOL					IsUserInterfaceEnabled; //field01B0
	int32					field01B4;
	int32					field01B8;
	int32					field01BC;
	int32					field01C0;
	int32					field01C4;
	int32					field01C8;
	int32					field01CC;
	int32					field01D0;
	int32					field01D4;
	int32					field01D8;
	int32					field01DC;
	int32					field01E0;
	int32					field01E4;
	int32					field01E8;
	int32					field01EC;
	int32					field01F0;
	int32					field01F4;
	int32					field01F8;
	int32					field01FC;
	int32					field0200;
	int32					field0204;
	int32					field0208;
	int32					field020C;
	int32					field0210;
	int32					field0214;
	int32					field0218;
	int32					field021C;
	int32					field0220;
	int32					field0224;
	int32					field0228;
	int32					field022C;
	int32					field0230;
	int32					field0234;
	int32					field0238;
	int32					field023C;
	int32					field0240;
	int32					field0244;
	int32					field0248;
	int32					field024C;
	int32					field0250;
	int32					field0254;
	int32					field0258;
	int32					field025C;
	int32					field0260;
	int32					field0264;
	int32					field0268;
	int32					field026C;
	int32					field0270;
	int32					field0274;
	int32					field0278;
	int32					field027C;
	int32					field0280;
	int32					field0284;
	int32					field0288;
	int32					field028C;
	int32					field0290;
	int32					field0294;
	int32					field0298;
	int32					field029C;
	int32					field02A0;
	int32					field02A4;
	int32					field02A8;
	int32					field02AC;
	int32					field02B0;
	int32					field02B4;
	int32					field02B8;
	int32					field02BC;
	int32					field02C0;
	int32					field02C4;
	int32					field02C8;
	int32					field02CC;
	int32					field02D0;
	int32					field02D4;
	int32					field02D8;
	int32					field02DC;
	int32					field02E0;
	int32					field02E4;
	int32					field02E8;
	int32					field02EC;
	int32					field02F0;
	int32					field02F4;
	int32					field02F8;
	int32					field02FC;
	int32					field0300;
	int32					field0304;
	int32					field0308;
	int32					field030C;
	int32					field0310;
	int32					field0314;
	int32					field0318;
	int32					field031C;
	int32					field0320;
	int32					field0324;
	int32					field0328;
	int32					field032C;
	int32					field0330;
	int32					field0334;
	int32					field0338;
	int32					field033C;
	int32					field0340;
	int32					field0344;
	int32					field0348;
	int32					field034C;
	int32					field0350;
	int32					field0354;
	int32					field0358;
	int32					field035C;
	int32					field0360;
	int32					field0364;
	int32					field0368;
	int32					field036C;
	int32					field0370;
	int32					field0374;
	int32					field0378;
	int32					field037C;
	int32					field0380;
	int32					field0384;
	int32					field0388;
	int32					field038C;
	int32					field0390;
	int32					field0394;
	int32					field0398;
	int32					field039C;
	int32					field03A0;
	int32					field03A4;
	int32					field03A8;
	int32					field03AC;
	int32					field03B0;
	int32					field03B4;
	int32					field03B8;
	int32					field03BC;
	int32					field03C0;
	int32					field03C4;
	int32					field03C8;
	int32					field03CC;
	int32					field03D0;
	int32					field03D4;
	int32					field03D8;
	int32					field03DC;
	int32					field03E0;
	SimpleMessageFrame*		Message;     //field03E4
	SimpleMessageFrame*		UnitMessage; //field03E8
	SimpleMessageFrame*		ChatMessage; //field03EC
	SimpleMessageFrame*		TopMessage;  //field03F0
	int32					field03F4;
	int32					field03F8;
	int32					field03FC;
	int32					field0400;
	int32					field0404;
	int32					field0408;
	int32					field040C;
	int32					field0410;
	int32					field0414;
	int32					field0418;
	int32					field041C;
	int32					field0420;
	int32					field0424;
	int32					field0428;
	int32					field042C;
	int32					field0430;
	int32					field0434;
	int32					field0438;
	int32					field043C;
	int32					field0440;
	int32					field0444;
	int32					field0448;
	int32					field044C;
	int32					field0450;
};

// Total Size: 4 bytes
struct CDestructableVTable
{
	LPVOID Function;
};

// Total Size: 136 bytes
struct Destructable
{
	CDestructableVTable*	Virtual;
	int32					field0004;
	int32					field0008;
	int32					field000C;
	int32					field0010;
	int32					field0014;
	int32					field0018;
	int32					field001C;
	int32					field0020;
	int32					field0024;
	int32					field0028;
	int32					field002C;
	int32					field0030;
	int32					field0034;
	int32					field0038;
	int32					field003C;
	int32					field0040;
	int32					field0044;
	int32					field0048;
	int32					field004C;
	int32					field0050;
	int32					field0054;
	int32					field0058;
	int32					field005C;
	int32					field0060;
	int32					field0064;
	int32					field0068;
	int32					field006C;
	int32					field0070;
	int32					field0074;
	int32					field0078;
	int32					field007C;
	int32					field0080;
	int32					field0084;
};

// Total Size: 92 bytes
struct VTable
{
	LPVOID	Func01;
	LPVOID	Func02;
	LPVOID	Func03;
	LPVOID	Func04;
	LPVOID	Func05;
	LPVOID	Func06;
	LPVOID	Func07;
	LPVOID	CAgent__GetClassId;
	LPVOID	Func09;
	LPVOID	Func10;
	LPVOID	Func11;
	LPVOID	Func12;
	LPVOID	Func13;
	LPVOID	Func14;
	LPVOID	Func15;
	LPVOID	Func16;
	LPVOID	Func17;
	LPVOID	Func18;
	LPVOID	Func19;
	LPVOID	Func20;
	LPVOID	Func21;
	LPVOID	Func22;
	LPVOID	CAgent__GetClassName;
};

// Total Size: 4 bytes
struct IAgent
{
	VTable* Virtual;
};

// Total Size: 4 bytes
struct CAbilityVTable
{
	LPVOID Function;
};

// Total Size: 104 bytes
struct AbilityLevelData
{
	int32	field0000;
	float	CastingTime;
	float	DurationNormal;
	float	DurationHero;

	int32	ManaCost;
	float	Cooldown;
	float	AreaOfEffect;
	float	CastRange;

	int32	DataA;
	int32	DataB;
	int32	DataC;
	int32	DataD;

	int32	DataE;
	int32	DataF;
	int32	DataG;
	int32	DataH;

	int32	DataI;
	int32	field0044;
	int32	field0048;
	int32	field004C;

	int32	field0050;
	int32	BuffId;
	int32	field0058;
	int32	field005C;

	int32	field0060;
	int32	field0064;
};

// Total Size: 88 bytes
struct AbilDataCacheNode
{
	int32					field0000;
	int32					field0004;
	int32					field0008;
	int32					field000C;

	int32					field0010;
	int32					AbilityId_0;
	int32					AbilityId_1;
	int32					field001C;

	int32					field0020;
	int32					field0024;
	int32					field0028;
	int32					field002C;

	int32					BaseAbilityId;
	int32					AbilityId;
	int32					field0038;
	int32					field003C;

	int32					field0040;
	int32					field0044;
	int32					field0048;
	int32					field004C;

	int32					Levels;
	AbilityLevelData*		Level;
};

// Total Size: 96 bytes
struct Ability
{
	CAbilityVTable*		Virtual;
	int32				State;
	int32				field0008;
	int32				field000C;

	int32				field0010;
	int32				field0014;
	int32				field0018;
	int32				field001C;

	int32				field0020;
	int32				field0024;
	int32				field0028;
	int32				field002C;

	Unit*				Owner;		// - The unit that has the ability.
	int32				AbilityId;	// - The ability id.
	int32				field0038;
	int32				field003C;

	int32				field0040;
	int32				field0044;
	int32				field0048;
	int32				field004C;

	int32				field0050;
	AbilDataCacheNode*	Data;		// - The ability data cache.
	int32				field0058;
	int32				field005C;
};

// Total Size: 1040 bytes
struct AbilityAttack
{
	Ability	Base;

	int32		field0060;
	int32		field0064;
	int32		field0068;
	int32		field006C;

	int32		field0070;
	int32		field0074;
	int32		field0078;
	int32		field007C;

	int32		field0080;
	int32		field0084;
	int32		Dices1;
	int32		Dices2;

	int32		field0090;
	int32		Sides1;
	int32		Sides2;
	int32		field009C;

	int32		Base1;
	int32		Base2;
	int32		field00A8;
	int32		Bonus1;

	int32		Bonus2;
	int32		field00B4;
	int32		field00B8;
	int32		field00BC;

	int32		field00C0;
	int32		field00C4;
	int32		field00C8;
	int32		field00CC;

	int32		field00D0;
	int32		field00D4;
	int32		field00D8;
	int32		field00DC;

	int32		field00E0;
	int32		field00E4;
	int32		field00E8;
	int32		field00EC;

	int32		field00F0;
	int32		field00F4;
	int32		field00F8;
	int32		field00FC;

	int32		field0100;
	int32		field0104;
	int32		field0108;
	int32		field010C;

	int32		field0110;
	int32		field0114;
	int32		field0118;
	int32		field011C;

	int32		field0120;
	int32		field0124;
	int32		field0128;
	int32		field012C;

	int32		field0130;
	int32		field0134;
	int32		field0138;
	int32		field013C;

	int32		field0140;
	int32		field0144;
	int32		field0148;
	int32		field014C;

	int32		field0150;
	int32		field0154;
	float		Cooldown1;
	int32		field015C;

	float		Cooldown2;
	int32		field0164;
	int32		field0168;
	int32		field016C;

	int32		field0170;
	int32		field0174;
	int32		field0178;
	int32		field017C;

	int32		field0180;
	int32		field0184;
	int32		field0188;
	int32		field018C;

	int32		field0190;
	int32		field0194;
	int32		field0198;
	int32		field019C;

	int32		field01A0;
	int32		field01A4;
	int32		field01A8;
	int32		field01AC;

	int32		field01B0;
	int32		field01B4;
	int32		field01B8;
	int32		field01BC;

	int32		field01C0;
	int32		field01C4;
	int32		field01C8;
	int32		field01CC;

	int32		field01D0;
	int32		field01D4;
	int32		field01D8;
	int32		field01DC;

	int32		field01E0;
	int32		field01E4;
	int32		field01E8;
	int32		field01EC;

	int32		field01F0;
	int32		field01F4;
	int32		field01F8;
	int32		field01FC;

	int32		field0200;
	int32		field0204;
	int32		field0208;
	int32		field020C;

	int32		field0210;
	int32		field0214;
	int32		field0218;
	int32		field021C;

	int32		field0220;
	int32		field0224;
	int32		field0228;
	int32		field022C;

	int32		field0230;
	int32		field0234;
	int32		field0238;
	int32		field023C;

	int32		field0240;
	int32		field0244;
	int32		field0248;
	int32		field024C;

	int32		field0250;
	int32		field0254;
	float		Range1;
	int32		field025C;

	float		Range2;
	int32		field0264;
	int32		field0268;
	int32		field026C;
};

// ------------------------------
// |	 Custom Structures		|
// ------------------------------

struct JassNative
{
	LPSTR FuncName;
	LPSTR FuncSig;
	LPVOID FuncAddr;

	JassNative(LPSTR funcname, LPSTR funcsig, LPVOID funcaddr) :
		FuncName(funcname), FuncSig(funcsig), FuncAddr(funcaddr) {}
};

struct Player
{
	BYTE _1[0x30];			//0x00
	WORD Slot;				//0x30
	WORD _2;				//0x32
	DWORD PtrList;			//0x34, Necessary to get ahold of the current selected units!
	BYTE _3[0x228];			//0x38
	DWORD Race;				//0x260
	DWORD ColorIndex;		//0x264
	BYTE _4[0x10];			//0x268
	DWORD Team;				//0x278
};

struct PlayerData
{
	DWORD PtrList;			//0x00, PtrList means pointer to some unknown list of pointers
	DWORD _1[0x9];			//0x24, _1 _2 _3 ... means unknown skipped data
	WORD PlayerSlot;		//0x28 
	WORD _2;				//0x30
	DWORD _3[0x6];			//0x40 
	DWORD MaxPlayerCount;	//0x44 
	DWORD _4;				//0x48 
	DWORD PlayerCount;		//0x4C 
	DWORD _5[0x2];			//0x50 
	Player* PlayerList[15];	//0x58 
};

#pragma pack(push,1)
struct Packet
{
	DWORD PacketClassPtr;	//+00, some unknown, but needed, Class Pointer
	BYTE* PacketData;		//+04
	DWORD _1;				//+08, zero
	DWORD _2;				//+0C, ??
	DWORD Size;				//+10, size of PacketData
	DWORD _3;				//+14, 0xFFFFFFFF
};
#pragma pack(pop)

enum GameFrame : int32
{
	FRAME_MESSAGE,
	FRAME_UNIT,
	FRAME_CHAT,
	FRAME_TOP
};

enum GameState : int32
{
	GS_NOTHING,
	GS_LOBBY,
	GS_LOADING = 3,
	GS_INGAME,
	GS_PAUSED = 6
};

enum GameEvent : int32
{
	EVENT_GAME_FINISHED,
	EVENT_ENTER_LOBBY,
	EVENT_ENTER_LOADING,
	EVENT_GAME_STARTED,
	EVENT_GAME_RESUMED,
	EVENT_GAME_PAUSED,
	EVENT_GAME_TICK,
	EVENT_UNIT_CREATE,
	EVENT_SET_UNIT_X,
	EVENT_SET_UNIT_Y,
	EVENT_PLUGIN_UNLOAD,
	EVENT_MULTIBOARD_CREATE,
	EVENT_LEADERBOARD_CREATE,
	EVENT_ITEM_CREATE
};

enum AbilityState : int32
{
	ABILITY_STATE_COOLDOWN,
	ABILITY_STATE_READY,
	ABILITY_STATE_INVALID
};

static int32 VAR_FRAME_MESSAGE = FRAME_MESSAGE;
static int32 VAR_FRAME_UNIT = FRAME_UNIT;
static int32 VAR_FRAME_CHAT = FRAME_CHAT;
static int32 VAR_FRAME_TOP = FRAME_TOP;

static int32 VAR_EVENT_GAME_FINISHED = EVENT_GAME_FINISHED;
static int32 VAR_EVENT_ENTER_LOBBY = EVENT_ENTER_LOBBY;
static int32 VAR_EVENT_ENTER_LOADING = EVENT_ENTER_LOADING;
static int32 VAR_EVENT_GAME_STARTED = EVENT_GAME_STARTED;
static int32 VAR_EVENT_GAME_RESUMED = EVENT_GAME_RESUMED;
static int32 VAR_EVENT_GAME_PAUSED = EVENT_GAME_PAUSED;
static int32 VAR_EVENT_GAME_TICK = EVENT_GAME_TICK;
static int32 VAR_EVENT_UNIT_CREATE = EVENT_UNIT_CREATE;
static int32 VAR_EVENT_SET_UNIT_X = EVENT_SET_UNIT_X;
static int32 VAR_EVENT_SET_UNIT_Y = EVENT_SET_UNIT_Y;
static int32 VAR_EVENT_PLUGIN_UNLOAD = EVENT_PLUGIN_UNLOAD;
static int32 VAR_EVENT_MULTIBOARD_CREATE = EVENT_MULTIBOARD_CREATE;
static int32 VAR_EVENT_LEADERBOARD_CREATE = EVENT_LEADERBOARD_CREATE;
static int32 VAR_EVENT_ITEM_CREATE = EVENT_ITEM_CREATE;

static int32 VAR_ABILITY_STATE_COOLDOWN = ABILITY_STATE_COOLDOWN;
static int32 VAR_ABILITY_STATE_READY = ABILITY_STATE_READY;
static int32 VAR_ABILITY_STATE_INVALID = ABILITY_STATE_INVALID;

static DWORD CMD_MOVE = 0xD0003;
static DWORD CMD_ATTACK = 0xD000F;
static DWORD CMD_HOLD = 0xD0019;
static DWORD CMD_STOP = 0xD0004;