// Epvolume.cpp -- WinMain and dialog box functions

#include "Epvolume.h"
#include "com_guwei_volume_VolumeControl.h"
GUID g_guidMyContext = GUID_NULL;

static IAudioEndpointVolume *g_pEndptVol = NULL;

IMMDeviceEnumerator *pEnumerator = NULL;
IMMDevice *pDevice = NULL;

JNIEXPORT void JNICALL Java_com_guwei_volume_VolumeControl_init(JNIEnv *env,
	jobject obj)
{
	jclass cls;
	cls = env->FindClass("com/guwei/volume/OperationFailedException");
	if (cls == NULL){
		return;
	}

	HRESULT hr = S_OK;
	CoInitialize(NULL);
	//CAudioEndpointVolumeCallback EPVolEvents;

	//�õ�g_guidMyContext hrֻ�ǽ��
	hr = CoCreateGuid(&g_guidMyContext);
	if (FAILED(hr)) {
		env->ThrowNew(cls, "CoCreateGuid error");
	}

	// Get enumerator for audio endpoint devices. pEnumerator��
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
		NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator),
		(void**)&pEnumerator);
	if (FAILED(hr)) {
		env->ThrowNew(cls, "CoCreateInstance error");
	}

	// Get default audio-rendering device. pDevice��
	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
	if (FAILED(hr)) {
		env->ThrowNew(cls, "pEnumerator->GetDefaultAudioEndpoint error");
	}

	hr = pDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_ALL, NULL, (void**)&g_pEndptVol);

	if (FAILED(hr)) {
		env->ThrowNew(cls, "pDevice->Activate error");
	}
}
JNIEXPORT void JNICALL Java_com_guwei_volume_VolumeControl_setMasterVolume(JNIEnv *env,
	jobject obj,
	jint nVolume)
{
	jclass cls;
	cls = env->FindClass("com/guwei/volume/OperationFailedException");
	if (cls == NULL){
		return;
	}

	float fVolume = (float)nVolume / MAX_VOL;//��������
	HRESULT hr = g_pEndptVol->SetMasterVolumeLevelScalar(fVolume, &g_guidMyContext);
	if (FAILED(hr)) {
		env->ThrowNew(cls, "setMasterVolume error");
	}	
}
JNIEXPORT jint JNICALL Java_com_guwei_volume_VolumeControl_getMasterVolume(JNIEnv *env,
	jobject obj)
{
	jclass cls;
	cls = env->FindClass("com/guwei/volume/OperationFailedException");
	if (cls == NULL){
		return -1;
	}

	int ret;
	float fVolume;
	HRESULT hr = g_pEndptVol->GetMasterVolumeLevelScalar(&fVolume);//�õ��������Ĵ�С��������0.0~1.0��    
	if (FAILED(hr)) {
		env->ThrowNew(cls, "getMasterVolume error");
	}
	ret = (int)(MAX_VOL*fVolume + 0.5);//������ת��Ϊ������0��100�� MAX_VOLΪ100
	return ret;
}
JNIEXPORT void JNICALL Java_com_guwei_volume_VolumeControl_setMute(JNIEnv *env,
	jobject obj,
	jboolean bMute)
{
	jclass cls;
	cls = env->FindClass("com/guwei/volume/OperationFailedException");
	if (cls == NULL){
		return;
	}	
	HRESULT hr = g_pEndptVol->SetMute(bMute, &g_guidMyContext);//���þ���
	if (FAILED(hr)) {
		env->ThrowNew(cls, "setMute error");
	}
}

JNIEXPORT jboolean JNICALL Java_com_guwei_volume_VolumeControl_getMute(JNIEnv *env,
	jobject obj)
{
	jclass cls;
	cls = env->FindClass("com/guwei/volume/OperationFailedException");
	if (cls == NULL){
		return false;
	}	

	BOOL bMute;//�Ƿ���
	HRESULT hr = g_pEndptVol->GetMute(&bMute);//�õ�����״̬
	if (FAILED(hr)) {
		env->ThrowNew(cls, "getMute error");
	}
	return bMute;
}
JNIEXPORT void JNICALL Java_com_guwei_volume_VolumeControl_finished(JNIEnv *env,
	jobject obj)
{
	//�ͷ�ָ��
	SAFE_RELEASE(pEnumerator)
	SAFE_RELEASE(pDevice)
	SAFE_RELEASE(g_pEndptVol)		
}