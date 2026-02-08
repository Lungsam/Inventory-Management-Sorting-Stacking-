///Find
void CInputMain::Refine(LPCHARACTER ch, const char* c_pData))
{
	...
}

///Add

#if defined(KD_MANAGE_INV)
int CInputMain::InventoryManagement(LPCHARACTER ch, const char* c_pData, size_t uiBytes)
{
	if (uiBytes < sizeof(TPacketCGInventoryManagement))
		return -1;
	
	const TPacketCGInventoryManagement* p = reinterpret_cast<const TPacketCGInventoryManagement*>(c_pData);

	const auto subheader = static_cast<EPacketCGInventoryManagementSubHeader>(p->subheader);

	switch (subheader)
	{
		case EPacketCGInventoryManagementSubHeader::INVENTORY_SUBHEADER_CG_ARRANGE:
			ch->ManageInventory(EPacketCGInventoryManagementSubHeader::INVENTORY_SUBHEADER_CG_ARRANGE);
			break;

		case EPacketCGInventoryManagementSubHeader::INVENTORY_SUBHEADER_CG_STACK:
			ch->ManageInventory(EPacketCGInventoryManagementSubHeader::INVENTORY_SUBHEADER_CG_STACK);
			break;

		default:
			sys_err("CInputMain::Unknown InventoryManagement Subheader %d sent by %s", p->subheader, ch->GetName());
			break;
	}
	
	 return sizeof(TPacketCGInventoryManagement);
}
#endif


///find

		case HEADER_CG_DRAGON_SOUL_REFINE:
			{
				{
				...
				}
			}
			

///add

#if defined(KD_MANAGE_INV)
		case HEADER_CG_INVENTORY_MANAGEMENT:
			InventoryManagement(ch, c_pData, m_iBufferLeft);
			break;
#endif