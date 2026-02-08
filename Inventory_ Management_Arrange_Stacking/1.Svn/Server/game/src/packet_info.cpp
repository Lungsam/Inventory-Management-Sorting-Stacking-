///Find
	Set(HEADER_CG_GUILD, sizeof(TPacketCGGuild), "Guild", true);

///Add
#if defined(KD_MANAGE_INV)
	Set(HEADER_CG_INVENTORY_MANAGEMENT, sizeof(TPacketCGInventoryManagement), "InventoryManagement", true);
#endif