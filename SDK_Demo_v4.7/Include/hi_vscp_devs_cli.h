
#ifndef __HI_VSCP_DEVS_CLI_H__
#define __HI_VSCP_DEVS_CLI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_vscp_devs_public.h"

#define SEARCH_API      __declspec(dllexport)
#define SEARCH_APICALL  __stdcall

#define HI_VSCP_CMD_NET        0x01
#define HI_VSCP_CMD_PORT       0x02

#define STREAMNO_LEN (20)
#define CHNNO_LEN (20)


typedef struct {
    HI_CHAR aszIP[HI_VSCP_IP_STRSIZE + 1];              /*IP��ַ*/
    HI_CHAR aszMASK[HI_VSCP_IP_STRSIZE + 1];            /*��������*/
    HI_CHAR aszMAC[HI_VSCP_MAC_STRSIZE + 1];            /*MAC��ַ*/
    HI_CHAR aszGTW[HI_VSCP_IP_STRSIZE + 1];             /*���ص�ַ*/
    HI_S32    s32Dhcp;     /* DHCP, 1 Ϊ������0Ϊ�ر� */
    HI_S32    s32DnsFlag; /* DNS���ñ�־��1 Ϊ�Զ���0Ϊ�ֶ�*/
    HI_CHAR aszFdns[HI_VSCP_IP_STRSIZE + 1];    /*��ѡDNS */
    HI_CHAR aszSdns[HI_VSCP_IP_STRSIZE + 1];   /* ����DNS */
} HI_S_VSCP_NETINFO;    

typedef struct {
    HI_CHAR aszDevID[HI_VSCP_DEVID_STRSIZE + 1];        /*�豸ID��������ɵ�32���ַ�*/    
    HI_CHAR aszDevMDL[HI_VSCP_DEVNAME_STRSIZE + 1];     /*�豸�ͺ�*/
    HI_CHAR aszSwVersion[HI_VSCP_SWVER_STRSIZE + 1];    /*����汾*/
    HI_CHAR aszDevName[HI_VSCP_DEVNAME_STRSIZE + 1];    /*�豸��*/
    HI_CHAR aszHttpPort[HI_VSCP_IP_STRSIZE + 1];        /*HTTP �����˿�*/
    HI_S_VSCP_NETINFO struNetInfo;
	HI_CHAR aszUID[HI_VSCP_DEVNAME_STRSIZE + 1];     /*UID*/
} HI_S_VSCP_DEVINFO;

typedef struct{
    HI_CHAR* pszDevID;      /*�豸��ʶ���豸Ψһ��ʶ*/
    HI_CHAR* pszUserName;
    HI_CHAR* pszPasswd;
} HI_S_VSCP_DEVSCLI_DevInfo;

/*����������Ӧ�ӿ�*/
typedef int (SEARCH_APICALL *PTR_VSCP_DEVS_Search_RPNProcFN)(
                       const HI_VOID* pvHandle,
                       HI_CHAR* pszRNPCode,
                       HI_S_VSCP_DEVINFO* pstruDevInfo,
                       HI_VOID* pvUserData);

typedef struct {
    HI_CHAR* pszCmd;
    HI_CHAR* pszResultInfo;
} HI_S_VSCP_DEVSCLI_Cmd_ResponsInfo;


/*����������Ӧ�ӿ�*/
typedef int (SEARCH_APICALL *PTR_VSCP_DEVS_Cmd_RPNProcFN)(
                       const HI_VOID* pvHandle,
                       HI_CHAR* pszRNPCode,
                       HI_S_VSCP_DEVSCLI_Cmd_ResponsInfo* pstruResponseInfo,
                       HI_VOID* pvUserData);

/*��ʼ���豸����*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_INIT(
    const HI_CHAR* pszListenIP,
    HI_U16 u16Port,
    HI_U32 u32TimeOut,
    HI_VOID** ppvHandle);

/*ȥ��ʼ���豸����*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_Deinit(HI_VOID* pvHandle);

                               
/*ע��������Ӧ����ӿ�*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_RegistCmdProc(const HI_VOID* pvHandle,
                                PTR_VSCP_DEVS_Cmd_RPNProcFN pfunCmdRProc,
                                HI_VOID* pvUserData);

SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_Register_IP(HI_CHAR aaszIP[][HI_VSCP_IP_STRSIZE + 1], 
                                HI_U32 u32Num);
/*������������*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_Search(HI_VOID* pvHandle);

/*������������*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_Cmd(
    HI_VOID* pvHandle,
    const HI_S_VSCP_DEVSCLI_DevInfo* pstruDEV,
    HI_S32 s32Cmd, 
    const HI_VOID* pData);

/*ע��������Ӧ����ӿ�*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_RegistSearchProc(const HI_VOID* pvHandle, 
                                PTR_VSCP_DEVS_Search_RPNProcFN pfunSearchRProc,
                                HI_VOID* pvUserData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_VSCP_DEVS_CLI_H__ */
    
    
