
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
    HI_CHAR aszIP[HI_VSCP_IP_STRSIZE + 1];              /*IP地址*/
    HI_CHAR aszMASK[HI_VSCP_IP_STRSIZE + 1];            /*子网掩码*/
    HI_CHAR aszMAC[HI_VSCP_MAC_STRSIZE + 1];            /*MAC地址*/
    HI_CHAR aszGTW[HI_VSCP_IP_STRSIZE + 1];             /*网关地址*/
    HI_S32    s32Dhcp;     /* DHCP, 1 为开启，0为关闭 */
    HI_S32    s32DnsFlag; /* DNS设置标志，1 为自动，0为手动*/
    HI_CHAR aszFdns[HI_VSCP_IP_STRSIZE + 1];    /*首选DNS */
    HI_CHAR aszSdns[HI_VSCP_IP_STRSIZE + 1];   /* 备用DNS */
} HI_S_VSCP_NETINFO;    

typedef struct {
    HI_CHAR aszDevID[HI_VSCP_DEVID_STRSIZE + 1];        /*设备ID，随机生成的32个字符*/    
    HI_CHAR aszDevMDL[HI_VSCP_DEVNAME_STRSIZE + 1];     /*设备型号*/
    HI_CHAR aszSwVersion[HI_VSCP_SWVER_STRSIZE + 1];    /*软件版本*/
    HI_CHAR aszDevName[HI_VSCP_DEVNAME_STRSIZE + 1];    /*设备名*/
    HI_CHAR aszHttpPort[HI_VSCP_IP_STRSIZE + 1];        /*HTTP 监听端口*/
    HI_S_VSCP_NETINFO struNetInfo;
	HI_CHAR aszUID[HI_VSCP_DEVNAME_STRSIZE + 1];     /*UID*/
} HI_S_VSCP_DEVINFO;

typedef struct{
    HI_CHAR* pszDevID;      /*设备标识，设备唯一标识*/
    HI_CHAR* pszUserName;
    HI_CHAR* pszPasswd;
} HI_S_VSCP_DEVSCLI_DevInfo;

/*处理搜索响应接口*/
typedef int (SEARCH_APICALL *PTR_VSCP_DEVS_Search_RPNProcFN)(
                       const HI_VOID* pvHandle,
                       HI_CHAR* pszRNPCode,
                       HI_S_VSCP_DEVINFO* pstruDevInfo,
                       HI_VOID* pvUserData);

typedef struct {
    HI_CHAR* pszCmd;
    HI_CHAR* pszResultInfo;
} HI_S_VSCP_DEVSCLI_Cmd_ResponsInfo;


/*处理设置响应接口*/
typedef int (SEARCH_APICALL *PTR_VSCP_DEVS_Cmd_RPNProcFN)(
                       const HI_VOID* pvHandle,
                       HI_CHAR* pszRNPCode,
                       HI_S_VSCP_DEVSCLI_Cmd_ResponsInfo* pstruResponseInfo,
                       HI_VOID* pvUserData);

/*初始化设备搜索*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_INIT(
    const HI_CHAR* pszListenIP,
    HI_U16 u16Port,
    HI_U32 u32TimeOut,
    HI_VOID** ppvHandle);

/*去初始化设备搜索*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_Deinit(HI_VOID* pvHandle);

                               
/*注册命令响应处理接口*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_RegistCmdProc(const HI_VOID* pvHandle,
                                PTR_VSCP_DEVS_Cmd_RPNProcFN pfunCmdRProc,
                                HI_VOID* pvUserData);

SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_Register_IP(HI_CHAR aaszIP[][HI_VSCP_IP_STRSIZE + 1], 
                                HI_U32 u32Num);
/*发送搜索命令*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_Search(HI_VOID* pvHandle);

/*发送设置命令*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_Cmd(
    HI_VOID* pvHandle,
    const HI_S_VSCP_DEVSCLI_DevInfo* pstruDEV,
    HI_S32 s32Cmd, 
    const HI_VOID* pData);

/*注册搜索响应处理接口*/
SEARCH_API HI_S32 SEARCH_APICALL HI_VSCP_DEVSCLI_RegistSearchProc(const HI_VOID* pvHandle, 
                                PTR_VSCP_DEVS_Search_RPNProcFN pfunSearchRProc,
                                HI_VOID* pvUserData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_VSCP_DEVS_CLI_H__ */
    
    
