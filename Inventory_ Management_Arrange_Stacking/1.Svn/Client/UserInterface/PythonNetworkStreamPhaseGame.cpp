///Add to end
#if defined(KD_MANAGE_INV)
bool CPythonNetworkStream::SendInventoryManagement(BYTE bSubHeader)
{
	TPacketCGInventoryManagement packet{};
	packet.header = HEADER_CG_INVENTORY_MANAGEMENT;
	packet.subheader = bSubHeader;

	if (!Send(sizeof(packet), &packet))
		return false;

	return true;
}
#endif
