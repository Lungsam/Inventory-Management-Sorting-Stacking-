///Find

	HEADER_CG_STATE_CHECKER					= 206,

///Add
#if defined(KD_MANAGE_INV)
	HEADER_CG_INVENTORY_MANAGEMENT			= 220,
#endif

//Find
typedef struct command_position command_shop
{
   ...
} TPacketCGPosition;

///add

#if defined(KD_MANAGE_INV)
enum class EPacketCGInventoryManagementSubHeader : BYTE
{
	INVENTORY_SUBHEADER_CG_ARRANGE,
	INVENTORY_SUBHEADER_CG_STACK,
};

typedef struct packet_inventory_Management
{
	BYTE header;
	BYTE subheader;
} TPacketCGInventoryManagement;
#endif