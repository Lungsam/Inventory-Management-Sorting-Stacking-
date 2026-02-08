//Find
		void 		Refine(LPCHARACTER ch, const char* c_pData);
		
///Add

#if defined(KD_MANAGE_INV)
		int			InventoryManagement(LPCHARACTER ch, const char* c_pData, size_t uiBytes);
#endif