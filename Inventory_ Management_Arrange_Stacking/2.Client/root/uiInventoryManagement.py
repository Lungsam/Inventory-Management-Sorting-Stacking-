# * Author: Khaled
# * Date: 2026.02.08

import ui
import net
import snd
import localeInfo
import uiCommon

class InventoryManagementWindow(ui.Window):
    INVENTORY_ARRANGE = 0
    INVENTORY_STACK = 1

    def __init__(self):
        ui.Window.__init__(self)
        self.isLoad = False
        self.questionDialog = None
        self.actionType = -1
        self.__LoadWindow()

    def __del__(self):
        ui.Window.__del__(self)

    def __LoadWindow(self):
        self.SetSize(32, 32)

        self.board = ui.ImageBox()
        self.board.SetParent(self)
        self.board.LoadImage("d:/ymir work/ui/game/inventory/typeslot.tga")
        self.board.SetPosition(10, 0)
        self.board.Hide()

        self.btnMain = ui.Button()
        self.btnMain.SetParent(self)
        self.btnMain.SetPosition(0, 0)
        self.btnMain.SetUpVisual("d:/ymir work/ui/game/inventory/wheel-1.tga")
        self.btnMain.SetOverVisual("d:/ymir work/ui/game/inventory/wheel-2.tga")
        self.btnMain.SetDownVisual("d:/ymir work/ui/game/inventory/wheel-3.tga")
        self.btnMain.SetToolTipText(localeInfo.INVENTORY_MANAGEMENT_TITLE)
        self.btnMain.SetEvent(ui.__mem_func__(self.__ToggleMenu))
        self.btnMain.Show()

        self.btnSort = self.__CreateButton(84, 0, localeInfo.INVENTORY_MANAGEMENT_SORT, lambda: self.__OnInventoryManagement(self.INVENTORY_ARRANGE), "d:/ymir work/ui/game/inventory/btn-sort-1.tga", "d:/ymir work/ui/game/inventory/btn-sort-2.tga", "d:/ymir work/ui/game/inventory/btn-sort-3.tga")
        self.btnStack = self.__CreateButton(64, 0, localeInfo.INVENTORY_MANAGEMENT_STACK, lambda: self.__OnInventoryManagement(self.INVENTORY_STACK), "d:/ymir work/ui/game/inventory/btn-stack-1.tga", "d:/ymir work/ui/game/inventory/btn-stack-2.tga", "d:/ymir work/ui/game/inventory/btn-stack-3.tga")

    def __CreateButton(self, x, y, tooltip, event, up, over, down):
        btn = ui.Button()
        btn.SetParent(self.board)
        btn.SetPosition(x, y)
        btn.SetUpVisual(up)
        btn.SetOverVisual(over)
        btn.SetDownVisual(down)
        btn.SetToolTipText(tooltip)
        btn.SetEvent(event)
        btn.Show()
        return btn

    def __OnInventoryManagement(self, actionType):
        messages = {self.INVENTORY_ARRANGE: localeInfo.INVENTORY_MANAGEMENT_SORT_QUESTION,self.INVENTORY_STACK: localeInfo.INVENTORY_MANAGEMENT_STACK_QUESTION}

        self.actionType = actionType
        self.questionDialog = uiCommon.QuestionDialog()
        self.questionDialog.SetText(messages.get(actionType, ""))
        self.questionDialog.SetAcceptEvent(ui.__mem_func__(self.AcceptInventoryManagement))
        self.questionDialog.SetCancelEvent(ui.__mem_func__(self.CancelInventoryManagement))
        self.questionDialog.Open()

    def CancelInventoryManagement(self):
        self.OnCloseQuestionDialog()

    def AcceptInventoryManagement(self):
        if self.questionDialog:
            net.SendInventoryManagement(self.actionType)
            snd.PlaySound("sound/ui/pick.wav")
            self.OnCloseQuestionDialog()

    def OnCloseQuestionDialog(self):
        if self.questionDialog:
            self.questionDialog.Close()
        self.questionDialog = None
        self.actionType = -1

    def __ToggleMenu(self):
        if self.isLoad:
            self.board.Hide()
            self.isLoad = False
        else:
            self.board.Show()
            self.isLoad = True

        width = 150 if self.isLoad else 32
        self.SetSize(width, 32)

    def OnPressEscapeKey(self):
        if self.isLoad:
            self.__ToggleMenu()
            return True
        return False

