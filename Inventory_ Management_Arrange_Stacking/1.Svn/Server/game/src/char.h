///Find

};

ESex GET_SEX(LPCHARACTER ch);

///Before }; add


#if defined(KD_MANAGE_INV)
	public:
		void ManageInventory(EPacketCGInventoryManagementSubHeader bActionType);
		void SetManageInventoryPulse(int pulse) noexcept { m_iManageInventoryPulse = pulse; }
		int GetManageInventoryPulse() const noexcept { return m_iManageInventoryPulse; }
	protected:
		int m_iManageInventoryPulse;
#endif