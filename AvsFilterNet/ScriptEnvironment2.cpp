#include "stdafx.h"

using namespace System;

namespace AvsFilterNet {
	ScriptEnvironment2::ScriptEnvironment2(IScriptEnvironment2 *env) {
		_env = env;
	};

	IScriptEnvironment2* ScriptEnvironment2::GetNative() {
		return _env;
	}

	bool ScriptEnvironment2::LoadPlugin(String^ filePath, bool throwOnError, AVSValue^ result) {
		NativeString^ nfilePath = gcnew NativeString(filePath);
		bool Result = false;
		try {
			Result = _env->LoadPlugin(nfilePath->GetPointer(), throwOnError, &result->GetNative());
		}
		catch (IScriptEnvironment2::NotFound) {
			throw gcnew FilterNotFoundException(filePath);
		}
		finally {
			delete nfilePath;
		}
		return Result;
	}

	void ScriptEnvironment2::ClearAutoloadDirs() {
		_env->ClearAutoloadDirs();
	}

	void ScriptEnvironment2::AddAutoloadDir(String ^ dirPath, bool toFront) {
		NativeString^ ndirPath = gcnew NativeString(dirPath);
		_env->AddAutoloadDir(ndirPath->GetPointer(), toFront);
		delete ndirPath;
	}

	void ScriptEnvironment2::AutoloadPlugins() {
		_env->AutoloadPlugins();
	}

	bool ScriptEnvironment2::InternalFunctionExists(String ^ name) {
		NativeString^ nname = gcnew NativeString(name);
		bool Result = _env->InternalFunctionExists(nname->GetPointer());
		delete nname;
		return Result;
	}

	void ScriptEnvironment2::SetFilterMTMode(String^ filter, MtMode mode, bool force) {
		NativeString^ nfilter = gcnew NativeString(filter);
		_env->SetFilterMTMode(nfilter->GetPointer(), (NativeMtMode)mode, force);
		delete nfilter;
	}
}
