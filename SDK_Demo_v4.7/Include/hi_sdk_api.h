#ifndef _HI_SDK_API_H_
#define _HI_SDK_API_H_

#include "hi_dataType.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#ifdef HISDK_EXPORTS
#define HISDK_API      __declspec( dllexport )
#define HISDK_APICALL  __stdcall

#elif defined(HISDK_LIB)
#define HISDK_API
#define HISDK_APICALL

#else
#define HISDK_API      __declspec( dllimport)
#define HISDK_APICALL  __stdcall
#endif

	typedef LONG (HISDK_APICALL* OnUpdateCallBack)(
		HI_U32 u32Chn, 
		HI_S32 s32Persent,
		HI_VOID *pUserData);
	
	
	typedef struct hiUPDATE_INFO_S
	{
		HI_CHAR sHost[32];
		HI_U32  u32Port;
		HI_CHAR sUser[16];
		HI_CHAR sPass[16];
		HI_CHAR sPath[256];
		HI_U32  u32Chn;
		HI_VOID *pUserData;
		OnUpdateCallBack callBack;
	}UPDATE_INFO_S;

	typedef LONG (HISDK_APICALL* OnRealDataCallBack)(
		HI_U32 u32Chn, MEDIA_TYPE_E eStreamType,
		HI_VOID* pStreamData, 
		HI_S32 s32DataNum, 
		HI_U32 s32Pts,
		HI_S32 s32KeyFrame,
		HI_VOID* pUserData);
	
	typedef LONG (HISDK_APICALL* OnEventCallBack)(
		HI_U32 u32Chn, 
		EVENT_TYPE_E eEventType,
		HI_VOID* pEventData, 
		HI_S32 s32DataNum, 
		HI_VOID* pUserData);
	
	typedef LONG (HISDK_APICALL* OnMessageCallBack)(
		HI_U32 u32Chn,
		MD_TYPE_E eDataType,
		HI_U8*  pu8Buffer,
		HI_U32 u32Length,
		HI_VOID* pUserData);
	
	typedef LONG (HISDK_APICALL* OnDrawCallBack)(
		HI_U32 u32Chn, 
		RECT rcDrawRect,
		HI_CHAR* pszName, 
		HI_VOID* pUserData);
	
	typedef LONG (HISDK_APICALL* OnVoiceDataCallBack)(
		HI_U32 u32Chn,
		HI_U8* pBuf, 
		HI_S32 s32Size,
		HI_U32 u32TimeStamp,
		HI_VOID *pUserData);
	
	typedef HRESULT(HISDK_APICALL *OnDecCallBack)(
		HI_U32 u32Chn,
		const FRAME_INFO_S *pFrameInfo,
		HI_VOID *pUserData);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_Init();
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_Cleanup();

	HISDK_API HI_HANDLE HISDK_APICALL HI_SDK_Login(const HI_CHAR* psHost, const HI_CHAR* psUsername, const HI_CHAR* psPassword, HI_U16 u16Port, HI_S32 *ps32Err=0);
	HISDK_API HI_HANDLE HISDK_APICALL HI_SDK_LoginExt(const HI_CHAR* psHost, 
													const HI_CHAR* psUsername, 
													const HI_CHAR* psPassword, 
													HI_U16 u16Port, 
													HI_U32 u32TimeOut=10000, 
													HI_S32 *ps32Err=0);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_Logout(HI_HANDLE lHandle);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetConnectTime(HI_HANDLE lHandle, HI_U32 u32Timeout);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetReconnect(HI_HANDLE lHandle, HI_U32 u32Interval);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_RealPlay(HI_HANDLE lHandle, HI_VOID *pWnd, HI_S_STREAM_INFO*  pstruStreamInfo);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_RealPlayExt(HI_HANDLE lHandle, HI_VOID *pWnd, HI_S_STREAM_INFO_EXT*  pstruStreamInfo);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_StopRealPlay(HI_HANDLE lHandle);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetDrawWnd(HI_HANDLE lHandle, HI_VOID* pWnd);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetRealDataCallBack(HI_HANDLE lHandle, HI_U32 u32Chn, OnRealDataCallBack streamCallBack, HI_VOID *pUserData);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetEventCallBack(HI_HANDLE lHandle, HI_U32 u32Chn, OnEventCallBack eventCallBack, HI_VOID *pUserData);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetDecCallBack(HI_HANDLE lHandle, HI_U32 u32Chn, OnDecCallBack CallBack, HI_VOID *pUserData);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetMessageCallBack(HI_HANDLE lHandle, HI_U32 u32Chn, OnMessageCallBack CallBack, HI_VOID *pUserData);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetDrawCallBack(HI_HANDLE lHandle, HI_U32 u32Chn, OnDrawCallBack callBack, HI_VOID* pUserData);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_PTZControl(HI_HANDLE lHandle, HI_U32 u32Command, HI_U32 u32Speed=0);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_PTZControlEx(HI_HANDLE lHandle, HI_U32 u32Command);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_PTZPreset(HI_HANDLE lHandle, HI_U32 u32Command, HI_U32 u32Preset);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_TransPTZ(HI_HANDLE lHandle, HI_CHAR* psBuf, HI_U32 u32BufLen);
	
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetVolume( HI_HANDLE lHandle, AUDIO_DIRECT_E eDir, HI_S32 s32Volume);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetVolume( HI_HANDLE lHandle, AUDIO_DIRECT_E eDir, HI_S32* pVolume);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetMute( HI_HANDLE lHandle, AUDIO_DIRECT_E eDir, AUDIO_MUTE_E eMute);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetMute( HI_HANDLE lHandle, AUDIO_DIRECT_E eDir, AUDIO_MUTE_E* pMute);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetState(HI_HANDLE lHandle, STATE_ID_E eStateID, HI_S32 *pState);

	HISDK_API HI_HANDLE HISDK_APICALL HI_SDK_Playback(HI_CHAR *psFilePath, HI_VOID *pWnd);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_StopPlayback(HI_HANDLE lPlayHandle);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_PlayBackControl(HI_HANDLE lPlayHandle, PBCTRL_TYPE_E s32Command, HI_S32 s32Value, HI_S32 *s32OutValue);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_StartRecord(HI_HANDLE lHandle, HI_CHAR *pFilePath, FILE_FORMAT_E eFileFormat, MEDIA_TYPE_E eFlag, HI_S32 s32FileTime=0);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_StopRecord(HI_HANDLE lHandle);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_CapturePicture(HI_HANDLE lHandle, HI_CHAR* pszFilePath);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_CaptureJPEGPicture(HI_HANDLE lHandle, HI_CHAR* sFilePath);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SnapJpeg(HI_HANDLE lHandle, HI_U8 *pu8Data, HI_S32 s32BufLen, HI_S32 *pSize);


	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetPlayerBufNumber(HI_HANDLE lHandle, HI_S32 s32BufNum);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetAutoAdjust(HI_HANDLE lHandle);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetAutoAdjust(HI_HANDLE lHandle);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_StartVoiceCom(HI_HANDLE lHandle, HI_U32 u32Chn=0, OnVoiceDataCallBack callback=NULL, HI_VOID *pUserData=NULL);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_StopVoiceCom(HI_HANDLE lHandle);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_VoiceComSendData(HI_HANDLE lHandle, HI_U8* pBuf, HI_S32 s32Len, HI_U32 u32Ts);


	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetSDKVersion(HI_CHAR* pVersion);


	HISDK_API HI_S32 HISDK_APICALL HI_SDK_InputDrawData(HI_HANDLE lHandle, DRAW_INFO_S* pstrDrawData, HI_S32 s32StrSize, HI_S32 s32DrawState);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_ClearDrawData(HI_HANDLE lHandle, HI_CHAR* pDrawData, HI_S32 s32DrawState);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SelectPic(HI_HANDLE lHandle, CPoint point);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_MouseMove(HI_HANDLE lHandle, UINT nFlags, CPoint point, CRect rcRect);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_EnablePic(HI_HANDLE lHandle, HI_CHAR* pszName, HI_S32 s32EnableValue, HI_S32 s32DrawState);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetPicInfo(HI_HANDLE lHandle, HI_S32* pHeight, HI_S32* pWidth);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetConfig(HI_HANDLE lHandle, HI_U32 u32Command, HI_VOID* pBuf, HI_U32 u32BufLen);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetConfig(HI_HANDLE lHandle, HI_U32 u32Command, HI_VOID* pBuf, HI_U32 u32BufLen);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetPlayRate(HI_HANDLE lHandle, HI_S32 *pFrameRate, HI_S32 *pBitRate);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetPlayerHandle(HI_HANDLE lHandle, void** ppPlayerHandle);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_Upgrade(HI_VOID *pParameter);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetSupportAttr(HI_HANDLE lHandle, HI_S_SUPPORT *pSupport);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_PauseDecode(HI_HANDLE lHandle);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_ResumeDecode(HI_HANDLE lHandle);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetMediaAttr(HI_HANDLE lHandle, STREAM_ATTR_S *pStreamInfo);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetPlayerAttr(HI_HANDLE lHandle, MEDIAATTR_TYPE_E eAttrType, HI_VOID *pAttr);
    HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetPlayerAttr(HI_HANDLE lHandle, MEDIAATTR_TYPE_E eAttrType, HI_VOID *pAttr);
	
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_DisplayAll(HI_HANDLE lHandle,
													HI_S32 s32Left = 0, 
													HI_S32 s32Top = 0, 
													HI_S32 s32Right = 0, 
													HI_S32 s32Bottom = 0, 
													HI_BOOL bDisplayAll = HI_TRUE);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetChannel(HI_HANDLE lHandle, HI_U32 u32Channel);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetChannel(HI_HANDLE lHandle);

	HISDK_API HI_S32 HISDK_APICALL HI_SDK_MakeKeyFrame(HI_HANDLE lHandle, HI_U32 u32Channel);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetDisplayMode(HI_HANDLE lHandle, PLAYER_DISPLAYMODE_E eDisplayMode);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_GetDisplayMode(HI_HANDLE lHandle, PLAYER_DISPLAYMODE_E *pDisplayMode);
	HISDK_API HI_S32 HISDK_APICALL HI_SDK_SetDisplayCallback(HI_HANDLE lHandle, HI_BOOL bDisplayCallback);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*_OPESDK_API_H_*/