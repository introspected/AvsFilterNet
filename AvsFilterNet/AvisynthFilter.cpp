#include "stdafx.h"

namespace AvsFilterNet {
	AvisynthFilter::AvisynthFilter() {
		_stub = new AvisynthFilterNativeStub(this);
		_mtMode = GetMtMode(GetType());
		_initialized = false;
	}

	AvisynthFilter::~AvisynthFilter() {
		if (_stub) {
			_stub = nullptr;
			delete _child;
			_child = nullptr;
		}
	}

	void AvisynthFilter::Initialize(AVSValue^ args, ScriptEnvironment^ env) {
	}

	AVSValue^ AvisynthFilter::ExecuteBefore(AVSValue^ args, bool% cancelLoad, ScriptEnvironment^ env) {
		//return gcnew AVSValue(args[0]->AsClip());
		return args[0];
	}

	AVSValue^ AvisynthFilter::ExecuteAfter(AVSValue^ clip, ScriptEnvironment^ env) {
		return clip;
		//return gcnew AVSValue(clip->AsClip());
	}

	VideoFrame^ AvisynthFilter::GetFrame(int n, ScriptEnvironment^ env) {
		return _child->GetFrame(n, env);
	}

	Clip^ AvisynthFilter::Child::get() {
		return _child;
	}

	void AvisynthFilter::GetAudio(IntPtr buf, __int64 start, __int64 count, ScriptEnvironment^ env) {
		if (_child)
			_child->GetAudio(buf, start, count, env);
	}

	bool AvisynthFilter::GetParity(int n) {
		return _child ? _child->GetParity(n) : false;
	}

	int AvisynthFilter::SetCacheHints(CacheType cachehints, int frame_range) {
		if (CacheType::CACHE_GET_MTMODE == cachehints)
		{
			return (NativeMtMode)_mtMode;
		}
		return _child ? _child->SetCacheHints(cachehints, frame_range) : 0;
	}

	VideoInfo AvisynthFilter::GetVideoInfo() {
		return _vi;
	}

	void AvisynthFilter::SetVideoInfo(VideoInfo% vi) {
		if (_initialized) throw gcnew InvalidOperationException("You can only set VideoInfo during initialization.");
		_vi = vi;
		pin_ptr<VideoInfo> pvi = &vi;
		_stub->SetVideoInfo(*(NativeVideoInfo*)(void*)pvi);
	}

	void AvisynthFilter::SetChild(Clip^ child) {
		if (_initialized) throw gcnew InvalidOperationException("You can only set child during initialization.");
		if (_child == child) return;
		if (_child) delete _child;
		_child = child;
		if (child) {
			_vi = child->GetVideoInfo();
			_stub->SetChild(child->GetNative());
		}
		else {
			_stub = new AvisynthFilterNativeStub(this);
		}
	}

	VideoFrame^ AvisynthFilter::NewVideoFrame(ScriptEnvironment^ env) {
		return NewVideoFrame(FRAME_ALIGN, env);
	}

	VideoFrame^ AvisynthFilter::NewVideoFrame(ScriptEnvironment^ env, VideoFrame^ propSrc) {
		return env->NewVideoFrameP(_vi, propSrc, FRAME_ALIGN);
	}

	VideoFrame^ AvisynthFilter::NewVideoFrame(int align, ScriptEnvironment^ env) {
		return env->NewVideoFrame(_vi, align);
	}

	PVideoFrame AvisynthFilter::GetFrame(int n, IScriptEnvironment* env) {
		VideoFrameCollector Collector; // This will release all VideoFrame created within GetFrame.
		VideoFrame^ ret = GetFrame(n, gcnew ScriptEnvironment(env));
		return ret ? ret->GetNative() : NULL;
	}

	void AvisynthFilter::GetAudio(void* buf, __int64 start, __int64 count, IScriptEnvironment* env) {
		GetAudio(IntPtr(buf), start, count, gcnew AvsFilterNet::ScriptEnvironment(env));
	}

	AvisynthFilterNativeStub* AvisynthFilter::GetNativeStub() {
		return _stub;
	}

	MtMode AvisynthFilter::GetMtMode(Type^ filterType)
	{
		return _mtModeMap->ContainsKey(filterType) ? _mtModeMap[filterType] : MtMode::UNKNOWN;
	}

	void AvisynthFilter::SetMtMode(Type^ filterType, MtMode mtMode)
	{
		_mtModeMap[filterType] = mtMode;
	}

	void AvisynthFilter::InitComplete() {
		_initialized = true;
	}
}