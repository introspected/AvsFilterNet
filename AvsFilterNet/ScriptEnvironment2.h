#ifndef SCRIPTENVIRONMENT2_H
#define SCRIPTENVIRONMENT2_H

#include <stdlib.h>
using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::Collections::Generic;

namespace AvsFilterNet {
	ref class AVSValueCollector;
	//Wrapper of IScriptEnvironment
	public ref class ScriptEnvironment2 sealed {

	private:
		IScriptEnvironment2 * _env;

	internal:
		ScriptEnvironment2(IScriptEnvironment2 *env);
		IScriptEnvironment2 * GetNative();

	public:

		// Plugin functions
		bool LoadPlugin(String^ filePath, bool throwOnError, AVSValue^ result);
		void AddAutoloadDir(String^ dirPath, bool toFront);
		void ClearAutoloadDirs();
		void AutoloadPlugins();
		//void AddFunction(String^ name, String^ params, ApplyFunc apply, void* user_data, String^ exportVar);
		bool InternalFunctionExists(String^ name);

		// Threading
		void SetFilterMTMode(String^ filter, MtMode mode, bool force); // If filter is "", sets the default MT mode
		//IJobCompletion* NewCompletion(size_t capacity);
		//void ParallelJob(ThreadWorkerFuncPtr jobFunc, void* jobData, IJobCompletion* completion);

	};
}

#endif
