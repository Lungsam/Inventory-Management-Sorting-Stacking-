//Find
		bool SendGuildWithdrawMoneyPacket(DWORD dwMoney);

///Add
#if defined(KD_MANAGE_INV)
		bool SendInventoryManagement(BYTE bSubHeader);
#endif