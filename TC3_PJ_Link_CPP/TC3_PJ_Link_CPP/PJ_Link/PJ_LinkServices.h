///////////////////////////////////////////////////////////////////////////////
// PJ_LinkServices.h

#pragma once

#include "TcServices.h"

const ULONG DrvID_PJ_Link = 0x3F000000;
#define SRVNAME_PJ_LINK "PJ_Link"

///<AutoGeneratedContent id="ClassIDs">
const CTCID CID_PJ_LinkCPJ_Link_Client = {0x4763444e,0x52c1,0x4ef1,{0x97,0x88,0x4c,0x02,0x21,0x34,0x11,0xee}};
///</AutoGeneratedContent>

///<AutoGeneratedContent id="ParameterIDs">
const PTCID PID_PJ_Link_ClientTcpServerIpAddress = 0x00000001;
const PTCID PID_PJ_Link_ClientTcpServerPort = 0x00000003;
const PTCID PID_PJ_Link_ClientClass2 = 0x00000004;
const PTCID PID_PJ_Link_ClientAuthentication = 0x00000005;
const PTCID PID_PJ_Link_ClientPollingRate = 0x00000006;
const PTCID PID_PJ_Link_ClientRT_Ethernet_Adapter = 0x00000002;
///</AutoGeneratedContent>

///<AutoGeneratedContent id="DataTypes">
#if !defined(_TC_TYPE_7CECC506_F55F_4594_B611_972D650865D2_INCLUDED_)
#define _TC_TYPE_7CECC506_F55F_4594_B611_972D650865D2_INCLUDED_
enum TCPIP_EVENT : ULONG {
	TCPIP_EVENT_NONE = 0,
	TCPIP_EVENT_ERROR = 1,
	TCPIP_EVENT_RESET = 2,
	TCPIP_EVENT_TIMEOUT = 3,
	TCPIP_EVENT_CONN_ESTABLISHED = 4,
	TCPIP_EVENT_CONN_INCOMING = 5,
	TCPIP_EVENT_CONN_CLOSED = 6,
	TCPIP_EVENT_CONN_IDLE = 7,
	TCPIP_EVENT_DATA_RECEIVED = 8,
	TCPIP_EVENT_DATA_SENT = 9,
	TCPIP_EVENT_KEEP_ALIVE = 10,
	TCPIP_EVENT_LINKCONNECT = 11,
	TCPIP_EVENT_LINKDISCONNECT = 12
};
#endif // !defined(_TC_TYPE_7CECC506_F55F_4594_B611_972D650865D2_INCLUDED_)

#if !defined(_TC_TYPE_18071995_0000_0000_0000_00000000003E_INCLUDED_)
#define _TC_TYPE_18071995_0000_0000_0000_00000000003E_INCLUDED_
typedef BYTE IPADDR[4];
#endif // !defined(_TC_TYPE_18071995_0000_0000_0000_00000000003E_INCLUDED_)

#if !defined(_TC_TYPE_0B60055A_B22D_43A4_89E9_1A8A0B08E559_INCLUDED_)
#define _TC_TYPE_0B60055A_B22D_43A4_89E9_1A8A0B08E559_INCLUDED_
#pragma pack(push,1)
typedef struct _ST_Projector_Lamp_Query
{
	ULONG Time;
	bool On;
} ST_Projector_Lamp_Query, *PST_Projector_Lamp_Query;
#pragma pack(pop)
#endif // !defined(_TC_TYPE_0B60055A_B22D_43A4_89E9_1A8A0B08E559_INCLUDED_)

#if !defined(_TC_TYPE_DE917159_D599_417F_AE22_D6B5171E1146_INCLUDED_)
#define _TC_TYPE_DE917159_D599_417F_AE22_D6B5171E1146_INCLUDED_
#pragma pack(push,1)
typedef struct _ST_Projector_Error
{
	bool NoError;
	bool Warning;
	bool Error;
} ST_Projector_Error, *PST_Projector_Error;
#pragma pack(pop)
#endif // !defined(_TC_TYPE_DE917159_D599_417F_AE22_D6B5171E1146_INCLUDED_)

#if !defined(_TC_TYPE_18071995_0000_0000_0000_0001000000FF_INCLUDED_)
#define _TC_TYPE_18071995_0000_0000_0000_0001000000FF_INCLUDED_
typedef CHAR STRING255[256];
#endif // !defined(_TC_TYPE_18071995_0000_0000_0000_0001000000FF_INCLUDED_)

#pragma pack(push,1)
typedef struct _PJ_Link_ClientAuthentication
{
	bool Enable;
	STRING255 Password;
} PJ_Link_ClientAuthentication, *PPJ_Link_ClientAuthentication;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _PJ_Link_ClientInputs
{
	struct {
		bool On;
		bool Off;
	} Power;
	struct {
		bool Request;
		STRING255 Channel;
	} Input;
	struct {
		bool Request;
		USHORT Selection;
	} Mute;
	struct {
		bool On;
		bool Off;
	} Freeze;
	struct {
		bool Up;
		bool Down;
	} SpeakerVolume;
	struct {
		bool Up;
		bool Down;
	} MicrophoneVolume;
} PJ_Link_ClientInputs, *PPJ_Link_ClientInputs;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct _PJ_Link_ClientOutputs
{
	bool Connected;
	USHORT Power;
	ST_Projector_Lamp_Query Lamps[8];
	struct {
		STRING255 Available[50];
		STRING255 Selected;
	} Inputs;
	struct {
		STRING255 Name;
		STRING255 InfoData1;
		STRING255 InfoData2;
		STRING255 InfoData3;
		USHORT Class;
	} Vendor;
	USHORT Mute;
	struct {
		ST_Projector_Error Fan;
		ST_Projector_Error Lamp;
		ST_Projector_Error Temp;
		ST_Projector_Error CoverOpen;
		ST_Projector_Error Filter;
		ST_Projector_Error Other;
	} Errors;
	struct {
		STRING255 SerialNumber;
		STRING255 SoftwareVersion;
		STRING255 InputTerminal;
		STRING255 InputResolution;
		STRING255 RecommendResolution;
		STRING255 ReplacementLamp;
		STRING255 ReplacementFilter;
		ULONG FilterTime;
		bool Freeze;
	} Class2;
	bool AuthRequired;
	bool AuthStatus;
} PJ_Link_ClientOutputs, *PPJ_Link_ClientOutputs;
#pragma pack(pop)

///</AutoGeneratedContent>



///<AutoGeneratedContent id="DataAreaIDs">
#define ADI_PJ_Link_ClientInputs 0
#define ADI_PJ_Link_ClientOutputs 1
///</AutoGeneratedContent>

///<AutoGeneratedContent id="InterfaceIDs">
#if !defined(_TC_IID_03010098_0000_0000_E000_000000000064_INCLUDED_)
#define _TC_IID_03010098_0000_0000_E000_000000000064_INCLUDED_
TCOM_DECL_INTERFACE("03010098-0000-0000-e000-000000000064", ITcIoTcpProtocol)
#endif // !defined(_TC_IID_03010098_0000_0000_E000_000000000064_INCLUDED_)

#if !defined(_TC_IID_03010099_0000_0000_E000_000000000064_INCLUDED_)
#define _TC_IID_03010099_0000_0000_E000_000000000064_INCLUDED_
TCOM_DECL_INTERFACE("03010099-0000-0000-e000-000000000064", ITcIoTcpProtocolRecv)
#endif // !defined(_TC_IID_03010099_0000_0000_E000_000000000064_INCLUDED_)

///</AutoGeneratedContent>

///<AutoGeneratedContent id="EventClasses">
///</AutoGeneratedContent>