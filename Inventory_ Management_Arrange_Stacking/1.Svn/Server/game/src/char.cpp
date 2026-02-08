///Add in void CHARACTER::Initialize()

#if defined(KD_MANAGE_INV)
	m_iManageInventoryPulse = 0;
#endif

///Add new func

#if defined(KD_MANAGE_INV)
static bool SortItems(const LPITEM& s1, const LPITEM& s2)
{
	return strcmp(s1->GetName(), s2->GetName()) < 0;
}

void CHARACTER::ManageInventory(EPacketCGInventoryManagementSubHeader bActionType)
{
	// Note: By default, items will always be stacked.

	if (IsDead())
		return;

	if (quest::CQuestManager::instance().GetPCForce(GetPlayerID())->IsRunning()) 
		return;

	if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen())
		return;

	if (GetManageInventoryPulse() > get_global_time()) 
	{
		ChatPacket(CHAT_TYPE_INFO, "You need to wait %d s", GetManageInventoryPulse() - get_global_time());
		return;
	}

	// Items that should not be managed (stacked/Arrange) by inventory
	// Note: you could check item->GetSocket() here in future expansions if needed
	auto IsInventoryProcessable = [&](LPITEM item) -> bool
	{
		if (!item) 
			return false;

		static const std::unordered_set<DWORD> s_nonManageableItems = {
			ITEM_MARRIAGE_RING, ITEM_AUTO_HP_RECOVERY_S, ITEM_AUTO_HP_RECOVERY_M, ITEM_AUTO_HP_RECOVERY_L, ITEM_AUTO_HP_RECOVERY_X,
			ITEM_AUTO_SP_RECOVERY_S, ITEM_AUTO_SP_RECOVERY_M, ITEM_AUTO_SP_RECOVERY_L, ITEM_AUTO_SP_RECOVERY_X,
		};

		if (s_nonManageableItems.find(item->GetVnum()) != s_nonManageableItems.end())
			return false;

		if (item->GetType() == ITEM_BLEND) 
			return false;

		return true;
	};

	// Stack
	for (int i = 0; i < INVENTORY_MAX_NUM; ++i) 
	{
		LPITEM baseItem = GetInventoryItem(i);
		if (!baseItem || !IsInventoryProcessable(baseItem) || !baseItem->IsStackable())
			continue;

		for (int j = i + 1; j < INVENTORY_MAX_NUM; ++j) 
		{
			LPITEM item = GetInventoryItem(j);
			if (!item || item == baseItem || item->GetVnum() != baseItem->GetVnum())
				continue;

			const int canAdd = ITEM_MAX_COUNT - baseItem->GetCount();
			if (canAdd <= 0) 
				break;

			const int moveCount = MIN(canAdd, item->GetCount());

			baseItem->SetCount(baseItem->GetCount() + moveCount);
			const int rest = item->GetCount() - moveCount;

			if (rest <= 0) 
			{
				item->RemoveFromCharacter(); 
				M2_DESTROY_ITEM(item);
			}
			else 
			{
				item->SetCount(rest);
			}
		}
	}

	//  Arrange
	if (bActionType == EPacketCGInventoryManagementSubHeader::INVENTORY_SUBHEADER_CG_ARRANGE)
	{
		std::vector<LPITEM> vec_pkItems;
		for (int i = 0; i < INVENTORY_MAX_NUM; ++i)
		{
			LPITEM pkItem = GetInventoryItem(i);
			if (pkItem)
			{
				vec_pkItems.emplace_back(pkItem);
				pkItem->RemoveFromCharacter();
				SyncQuickslot(QUICKSLOT_TYPE_ITEM, i, 255);
			}
		}

		if (!vec_pkItems.empty())
		{
			std::sort(vec_pkItems.begin(), vec_pkItems.end(), SortItems);
			for (const auto& item : vec_pkItems)
				AutoGiveItem(item);
		}
		ChatPacket(CHAT_TYPE_INFO, "Inventory has been sorted.");
	}
	else
	{
		ChatPacket(CHAT_TYPE_INFO, "All items have been stacked.");
	}
	// Waiting time 15Sce
	SetManageInventoryPulse(get_global_time() + 15); 
}

#endif
