#Add
if app.KD_MANAGE_INV:
	import uiInventoryManagement


#Find in class InventoryWindow(ui.ScriptWindow): def __LoadWindow(self):

			self.wndBelt = None
			
#add
			if app.KD_MANAGE_INV:
				xPos = 135 if localeInfo.IsARABIC() else 150
				self.wndManageInv = uiInventoryManagement.InventoryManagementWindow()
				self.wndManageInv.SetParent(self.GetChild("board"))
				self.wndManageInv.SetPosition(self.GetChild("TitleBar").GetWidth() - xPos, 6)
				self.wndManageInv.Show()