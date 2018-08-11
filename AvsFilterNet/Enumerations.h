//Enumerations from avisynth.h
namespace AvsFilterNet {
	public enum class PlanarChromaAlignmentMode {
		PlanarChromaAlignmentOff,
		PlanarChromaAlignmentOn,
		PlanarChromaAlignmentTest
	};

	public enum class AudioSampleType {
		SAMPLE_INT8 = 1 << 0,
		SAMPLE_INT16 = 1 << 1,
		SAMPLE_INT24 = 1 << 2,    // Int24 is a very stupid thing to code, but it's supported by some hardware.
		SAMPLE_INT32 = 1 << 3,
		SAMPLE_FLOAT = 1 << 4
	};

	public enum class YUVPlanes {
		PLANAR_Y = 1 << 0,
		PLANAR_U = 1 << 1,
		PLANAR_V = 1 << 2,
		PLANAR_ALIGNED = 1 << 3,
		PLANAR_Y_ALIGNED = PLANAR_Y | PLANAR_ALIGNED,
		PLANAR_U_ALIGNED = PLANAR_U | PLANAR_ALIGNED,
		PLANAR_V_ALIGNED = PLANAR_V | PLANAR_ALIGNED,
		PLANAR_A = 1 << 4,
		PLANAR_R = 1 << 5,
		PLANAR_G = 1 << 6,
		PLANAR_B = 1 << 7,
		PLANAR_A_ALIGNED = PLANAR_A | PLANAR_ALIGNED,
		PLANAR_R_ALIGNED = PLANAR_R | PLANAR_ALIGNED,
		PLANAR_G_ALIGNED = PLANAR_G | PLANAR_ALIGNED,
		PLANAR_B_ALIGNED = PLANAR_B | PLANAR_ALIGNED,
	};

	// Colorspace properties.
	public enum class ColorSpaces {
		CS_YUVA = 1 << 27,
		CS_BGR = 1 << 28,
		CS_YUV = 1 << 29,
		CS_INTERLEAVED = 1 << 30,
		CS_PLANAR = 1 << 31,

		CS_Shift_Sub_Width = 0,
		CS_Shift_Sub_Height = 8,
		CS_Shift_Sample_Bits = 16,

		CS_Sub_Width_Mask = 7 << CS_Shift_Sub_Width,
		CS_Sub_Width_1 = 3 << CS_Shift_Sub_Width, // YV24
		CS_Sub_Width_2 = 0 << CS_Shift_Sub_Width, // YV12, I420, YV16
		CS_Sub_Width_4 = 1 << CS_Shift_Sub_Width, // YUV9, YV411

		CS_VPlaneFirst = 1 << 3, // YV12, YV16, YV24, YV411, YUV9
		CS_UPlaneFirst = 1 << 4, // I420

		CS_Sub_Height_Mask = 7 << CS_Shift_Sub_Height,
		CS_Sub_Height_1 = 3 << CS_Shift_Sub_Height, // YV16, YV24, YV411
		CS_Sub_Height_2 = 0 << CS_Shift_Sub_Height, // YV12, I420
		CS_Sub_Height_4 = 1 << CS_Shift_Sub_Height, // YUV9

		CS_Sample_Bits_Mask = 0b111 << CS_Shift_Sample_Bits,
		CS_Sample_Bits_8 = 0 << CS_Shift_Sample_Bits,
		CS_Sample_Bits_10 = 0b101 << CS_Shift_Sample_Bits,
		CS_Sample_Bits_12 = 0b110 << CS_Shift_Sample_Bits,
		CS_Sample_Bits_14 = 0b111 << CS_Shift_Sample_Bits,
		CS_Sample_Bits_16 = 0b001 << CS_Shift_Sample_Bits,
		CS_Sample_Bits_32 = 0b010 << CS_Shift_Sample_Bits,

		CS_PLANAR_MASK = CS_PLANAR | CS_INTERLEAVED | CS_YUV | CS_BGR | CS_YUVA | CS_Sample_Bits_Mask
		| CS_Sub_Height_Mask | CS_Sub_Width_Mask,
		CS_PLANAR_FILTER = ~(CS_VPlaneFirst | CS_UPlaneFirst),

		CS_RGB_TYPE = 1 << 0,
		CS_RGBA_TYPE = 1 << 1,

		// Specific colorformats
		CS_UNKNOWN = 0,

		CS_BGR24 = CS_RGB_TYPE | CS_BGR | CS_INTERLEAVED,
		CS_BGR32 = CS_RGBA_TYPE | CS_BGR | CS_INTERLEAVED,
		CS_YUY2 = 1 << 2 | CS_YUV | CS_INTERLEAVED,
		//  CS_YV12  = 1<<3  Reserved
		//  CS_I420  = 1<<4  Reserved
		CS_RAW32 = 1 << 5 | CS_INTERLEAVED,

		//  YV12 must be 0xA000008 2.5 Baked API will see all new planar as YV12
		//  I420 must be 0xA000010

		CS_GENERIC_YUV420 = CS_PLANAR | CS_YUV | CS_VPlaneFirst | CS_Sub_Height_2 | CS_Sub_Width_2,  // 4:2:0 planar
		CS_GENERIC_YUV422 = CS_PLANAR | CS_YUV | CS_VPlaneFirst | CS_Sub_Height_1 | CS_Sub_Width_2,  // 4:2:2 planar
		CS_GENERIC_YUV444 = CS_PLANAR | CS_YUV | CS_VPlaneFirst | CS_Sub_Height_1 | CS_Sub_Width_1,  // 4:4:4 planar
		CS_GENERIC_Y = CS_PLANAR | CS_INTERLEAVED | CS_YUV,                                     // Y only (4:0:0)
		CS_GENERIC_RGBP = CS_PLANAR | CS_BGR | CS_RGB_TYPE,                                        // planar RGB. Though name is RGB but plane order G,B,R
		CS_GENERIC_RGBAP = CS_PLANAR | CS_BGR | CS_RGBA_TYPE,                                       // planar RGBA
		CS_GENERIC_YUVA420 = CS_PLANAR | CS_YUVA | CS_VPlaneFirst | CS_Sub_Height_2 | CS_Sub_Width_2, // 4:2:0:A planar
		CS_GENERIC_YUVA422 = CS_PLANAR | CS_YUVA | CS_VPlaneFirst | CS_Sub_Height_1 | CS_Sub_Width_2, // 4:2:2:A planar
		CS_GENERIC_YUVA444 = CS_PLANAR | CS_YUVA | CS_VPlaneFirst | CS_Sub_Height_1 | CS_Sub_Width_1, // 4:4:4:A planar

		CS_YV24 = CS_GENERIC_YUV444 | CS_Sample_Bits_8,  // YVU 4:4:4 planar
		CS_YV16 = CS_GENERIC_YUV422 | CS_Sample_Bits_8,  // YVU 4:2:2 planar
		CS_YV12 = CS_GENERIC_YUV420 | CS_Sample_Bits_8,  // YVU 4:2:0 planar
		CS_I420 = CS_PLANAR | CS_YUV | CS_Sample_Bits_8 | CS_UPlaneFirst | CS_Sub_Height_2 | CS_Sub_Width_2,  // YUV 4:2:0 planar
		CS_IYUV = CS_I420,
		CS_YUV9 = CS_PLANAR | CS_YUV | CS_Sample_Bits_8 | CS_VPlaneFirst | CS_Sub_Height_4 | CS_Sub_Width_4,  // YUV 4:1:0 planar
		CS_YV411 = CS_PLANAR | CS_YUV | CS_Sample_Bits_8 | CS_VPlaneFirst | CS_Sub_Height_1 | CS_Sub_Width_4,  // YUV 4:1:1 planar

		CS_Y8 = CS_GENERIC_Y | CS_Sample_Bits_8,    // Y   4:0:0 planar

		//-------------------------
		// AVS16: new planar constants go live! Experimental PF 160613
		// 10-12-14 bit + planar RGB + BRG48/64 160725

		CS_YUV444P10 = CS_GENERIC_YUV444 | CS_Sample_Bits_10, // YUV 4:4:4 10bit samples
		CS_YUV422P10 = CS_GENERIC_YUV422 | CS_Sample_Bits_10, // YUV 4:2:2 10bit samples
		CS_YUV420P10 = CS_GENERIC_YUV420 | CS_Sample_Bits_10, // YUV 4:2:0 10bit samples
		CS_Y10 = CS_GENERIC_Y | CS_Sample_Bits_10,            // Y   4:0:0 10bit samples

		CS_YUV444P12 = CS_GENERIC_YUV444 | CS_Sample_Bits_12, // YUV 4:4:4 12bit samples
		CS_YUV422P12 = CS_GENERIC_YUV422 | CS_Sample_Bits_12, // YUV 4:2:2 12bit samples
		CS_YUV420P12 = CS_GENERIC_YUV420 | CS_Sample_Bits_12, // YUV 4:2:0 12bit samples
		CS_Y12 = CS_GENERIC_Y | CS_Sample_Bits_12,            // Y   4:0:0 12bit samples

		CS_YUV444P14 = CS_GENERIC_YUV444 | CS_Sample_Bits_14, // YUV 4:4:4 14bit samples
		CS_YUV422P14 = CS_GENERIC_YUV422 | CS_Sample_Bits_14, // YUV 4:2:2 14bit samples
		CS_YUV420P14 = CS_GENERIC_YUV420 | CS_Sample_Bits_14, // YUV 4:2:0 14bit samples
		CS_Y14 = CS_GENERIC_Y | CS_Sample_Bits_14,            // Y   4:0:0 14bit samples

		CS_YUV444P16 = CS_GENERIC_YUV444 | CS_Sample_Bits_16, // YUV 4:4:4 16bit samples
		CS_YUV422P16 = CS_GENERIC_YUV422 | CS_Sample_Bits_16, // YUV 4:2:2 16bit samples
		CS_YUV420P16 = CS_GENERIC_YUV420 | CS_Sample_Bits_16, // YUV 4:2:0 16bit samples
		CS_Y16 = CS_GENERIC_Y | CS_Sample_Bits_16,            // Y   4:0:0 16bit samples

															  // 32 bit samples (float)
		CS_YUV444PS = CS_GENERIC_YUV444 | CS_Sample_Bits_32,  // YUV 4:4:4 32bit samples
		CS_YUV422PS = CS_GENERIC_YUV422 | CS_Sample_Bits_32,  // YUV 4:2:2 32bit samples
		CS_YUV420PS = CS_GENERIC_YUV420 | CS_Sample_Bits_32,  // YUV 4:2:0 32bit samples
		CS_Y32 = CS_GENERIC_Y | CS_Sample_Bits_32,            // Y   4:0:0 32bit samples

		// RGB packed
		CS_BGR48 = CS_RGB_TYPE | CS_BGR | CS_INTERLEAVED | CS_Sample_Bits_16, // BGR 3x16 bit
		CS_BGR64 = CS_RGBA_TYPE | CS_BGR | CS_INTERLEAVED | CS_Sample_Bits_16, // BGR 4x16 bit
																			   // no packed 32 bit (float) support for these legacy types

		// RGB planar
		CS_RGBP = CS_GENERIC_RGBP | CS_Sample_Bits_8,  // Planar RGB 8 bit samples
		CS_RGBP10 = CS_GENERIC_RGBP | CS_Sample_Bits_10, // Planar RGB 10bit samples
		CS_RGBP12 = CS_GENERIC_RGBP | CS_Sample_Bits_12, // Planar RGB 12bit samples
		CS_RGBP14 = CS_GENERIC_RGBP | CS_Sample_Bits_14, // Planar RGB 14bit samples
		CS_RGBP16 = CS_GENERIC_RGBP | CS_Sample_Bits_16, // Planar RGB 16bit samples
		CS_RGBPS = CS_GENERIC_RGBP | CS_Sample_Bits_32, // Planar RGB 32bit samples

		// RGBA planar
		CS_RGBAP = CS_GENERIC_RGBAP | CS_Sample_Bits_8,  // Planar RGBA 8 bit samples
		CS_RGBAP10 = CS_GENERIC_RGBAP | CS_Sample_Bits_10, // Planar RGBA 10bit samples
		CS_RGBAP12 = CS_GENERIC_RGBAP | CS_Sample_Bits_12, // Planar RGBA 12bit samples
		CS_RGBAP14 = CS_GENERIC_RGBAP | CS_Sample_Bits_14, // Planar RGBA 14bit samples
		CS_RGBAP16 = CS_GENERIC_RGBAP | CS_Sample_Bits_16, // Planar RGBA 16bit samples
		CS_RGBAPS = CS_GENERIC_RGBAP | CS_Sample_Bits_32, // Planar RGBA 32bit samples

		// Planar YUVA
		CS_YUVA444 = CS_GENERIC_YUVA444 | CS_Sample_Bits_8,  // YUVA 4:4:4 8bit samples
		CS_YUVA422 = CS_GENERIC_YUVA422 | CS_Sample_Bits_8,  // YUVA 4:2:2 8bit samples
		CS_YUVA420 = CS_GENERIC_YUVA420 | CS_Sample_Bits_8,  // YUVA 4:2:0 8bit samples

		CS_YUVA444P10 = CS_GENERIC_YUVA444 | CS_Sample_Bits_10, // YUVA 4:4:4 10bit samples
		CS_YUVA422P10 = CS_GENERIC_YUVA422 | CS_Sample_Bits_10, // YUVA 4:2:2 10bit samples
		CS_YUVA420P10 = CS_GENERIC_YUVA420 | CS_Sample_Bits_10, // YUVA 4:2:0 10bit samples

		CS_YUVA444P12 = CS_GENERIC_YUVA444 | CS_Sample_Bits_12, // YUVA 4:4:4 12bit samples
		CS_YUVA422P12 = CS_GENERIC_YUVA422 | CS_Sample_Bits_12, // YUVA 4:2:2 12bit samples
		CS_YUVA420P12 = CS_GENERIC_YUVA420 | CS_Sample_Bits_12, // YUVA 4:2:0 12bit samples

		CS_YUVA444P14 = CS_GENERIC_YUVA444 | CS_Sample_Bits_14, // YUVA 4:4:4 14bit samples
		CS_YUVA422P14 = CS_GENERIC_YUVA422 | CS_Sample_Bits_14, // YUVA 4:2:2 14bit samples
		CS_YUVA420P14 = CS_GENERIC_YUVA420 | CS_Sample_Bits_14, // YUVA 4:2:0 14bit samples

		CS_YUVA444P16 = CS_GENERIC_YUVA444 | CS_Sample_Bits_16, // YUVA 4:4:4 16bit samples
		CS_YUVA422P16 = CS_GENERIC_YUVA422 | CS_Sample_Bits_16, // YUVA 4:2:2 16bit samples
		CS_YUVA420P16 = CS_GENERIC_YUVA420 | CS_Sample_Bits_16, // YUVA 4:2:0 16bit samples

		CS_YUVA444PS = CS_GENERIC_YUVA444 | CS_Sample_Bits_32,  // YUVA 4:4:4 32bit samples
		CS_YUVA422PS = CS_GENERIC_YUVA422 | CS_Sample_Bits_32,  // YUVA 4:2:2 32bit samples
		CS_YUVA420PS = CS_GENERIC_YUVA420 | CS_Sample_Bits_32,  // YUVA 4:2:0 32bit samples
	};

	public enum class FrameType {
		IT_BFF = 1 << 0,
		IT_TFF = 1 << 1,
		IT_FIELDBASED = 1 << 2
	};

	public enum class CacheType {
		// Old 2.5 poorly defined cache hints.
		// Reserve values used by 2.5 API
		// Do not use in new filters
		CACHE_25_NOTHING = 0,
		CACHE_25_RANGE = 1,
		CACHE_25_ALL = 2,
		CACHE_25_AUDIO = 3,
		CACHE_25_AUDIO_NONE = 4,
		CACHE_25_AUDIO_AUTO = 5,

		// New 2.6 explicitly defined cache hints.
		CACHE_NOTHING = 10, // Do not cache video.
		CACHE_WINDOW = 11, // Hard protect upto X frames within a range of X from the current frame N.
		CACHE_GENERIC = 12, // LRU cache upto X frames.
		CACHE_FORCE_GENERIC = 13, // LRU cache upto X frames, override any previous CACHE_WINDOW.

		CACHE_GET_POLICY = 30, // Get the current policy.
		CACHE_GET_WINDOW = 31, // Get the current window h_span.
		CACHE_GET_RANGE = 32, // Get the current generic frame range.

		CACHE_AUDIO = 50, // Explicitly cache audio, X byte cache.
		CACHE_AUDIO_NOTHING = 51, // Explicitly do not cache audio.
		CACHE_AUDIO_NONE = 52, // Audio cache off (auto mode), X byte intial cache.
		CACHE_AUDIO_AUTO = 53, // Audio cache on (auto mode), X byte intial cache.

		CACHE_GET_AUDIO_POLICY = 70, // Get the current audio policy.
		CACHE_GET_AUDIO_SIZE = 71, // Get the current audio cache size.

		CACHE_PREFETCH_FRAME = 100, // Queue request to prefetch frame N.
		CACHE_PREFETCH_GO = 101, // Action video prefetches.

		CACHE_PREFETCH_AUDIO_BEGIN = 120, // Begin queue request transaction to prefetch audio (take critical section).
		CACHE_PREFETCH_AUDIO_STARTLO = 121, // Set low 32 bits of start.
		CACHE_PREFETCH_AUDIO_STARTHI = 122, // Set high 32 bits of start.
		CACHE_PREFETCH_AUDIO_COUNT = 123, // Set low 32 bits of length.
		CACHE_PREFETCH_AUDIO_COMMIT = 124, // Enqueue request transaction to prefetch audio (release critical section).
		CACHE_PREFETCH_AUDIO_GO = 125, // Action audio prefetches.

		CACHE_GETCHILD_CACHE_MODE = 200, // Cache ask Child for desired video cache mode.
		CACHE_GETCHILD_CACHE_SIZE = 201, // Cache ask Child for desired video cache size.
		CACHE_GETCHILD_AUDIO_MODE = 202, // Cache ask Child for desired audio cache mode.
		CACHE_GETCHILD_AUDIO_SIZE = 203, // Cache ask Child for desired audio cache size.

		CACHE_GETCHILD_COST = 220, // Cache ask Child for estimated processing cost.
		CACHE_COST_ZERO = 221, // Child response of zero cost (ptr arithmetic only).
		CACHE_COST_UNIT = 222, // Child response of unit cost (less than or equal 1 full frame blit).
		CACHE_COST_LOW = 223, // Child response of light cost. (Fast)
		CACHE_COST_MED = 224, // Child response of medium cost. (Real time)
		CACHE_COST_HI = 225, // Child response of heavy cost. (Slow)

		CACHE_GETCHILD_THREAD_MODE = 240, // Cache ask Child for thread safetyness.
		CACHE_THREAD_UNSAFE = 241, // Only 1 thread allowed for all instances. 2.5 filters default!
		CACHE_THREAD_CLASS = 242, // Only 1 thread allowed for each instance. 2.6 filters default!
		CACHE_THREAD_SAFE = 243, //  Allow all threads in any instance.
		CACHE_THREAD_OWN = 244, // Safe but limit to 1 thread, internally threaded.

		CACHE_GETCHILD_ACCESS_COST = 260, // Cache ask Child for preferred access pattern.
		CACHE_ACCESS_RAND = 261, // Filter is access order agnostic.
		CACHE_ACCESS_SEQ0 = 262, // Filter prefers sequential access (low cost)
		CACHE_ACCESS_SEQ1 = 263, // Filter needs sequential access (high cost)

		CACHE_AVSPLUS_CONSTANTS = 500,    // Smaller values are reserved for classic Avisynth

		CACHE_DONT_CACHE_ME,              // Filters that don't need caching (eg. trim, cache etc.) should return 1 to this request
		CACHE_SET_MIN_CAPACITY,
		CACHE_SET_MAX_CAPACITY,
		CACHE_GET_MIN_CAPACITY,
		CACHE_GET_MAX_CAPACITY,
		CACHE_GET_SIZE,
		CACHE_GET_REQUESTED_CAP,
		CACHE_GET_CAPACITY,
		CACHE_GET_MTMODE,

		CACHE_IS_CACHE_REQ,
		CACHE_IS_CACHE_ANS,
		CACHE_IS_MTGUARD_REQ,
		CACHE_IS_MTGUARD_ANS,

		CACHE_USER_CONSTANTS = 1000       // Smaller values are reserved for the core
	};

	[System::Flags]
	public enum class CPUFlags {
		/* slowest CPU to support extension */
		CPUF_FORCE = 0x01,   //  N/A
		CPUF_FPU = 0x02,   //  386/486DX
		CPUF_MMX = 0x04,   //  P55C, K6, PII
		CPUF_INTEGER_SSE = 0x08,   //  PIII, Athlon
		CPUF_SSE = 0x10,   //  PIII, Athlon XP/MP
		CPUF_SSE2 = 0x20,   //  PIV, Hammer
		CPUF_3DNOW = 0x40,   //  K6-2
		CPUF_3DNOW_EXT = 0x80,   //  Athlon
		CPUF_X86_64 = 0xA0,   //  Hammer (note: equiv. to 3DNow + SSE2, which
		//          only Hammer will have anyway)
		CPUF_SSE3 = 0x100,   //  PIV+, Hammer
	};

	/// <summary>The multi-threading mode for AviSynth+.</summary>
	public enum class MtMode {
		/// <summary>MT mode won't be configured.</summary>
		UNKNOWN = 0,
		/// <summary>A single instance of the filter will be created and GetFrame will be called in parallel from various threads.</summary>
		NICE_FILTER = 1,
		/// <summary>An instance of the filter will be created for each thread and each instance will receive a single GetFrame request at once.</summary>
		MULTI_INSTANCE = 2,
		/// <summary>A single instance of the filter will be created and it will receive a single GetFrame request at once. Useful for source filters.</summary>
		SERIALIZED = 3,
	};

	public enum class AvisynthProperty {
		PHYSICAL_CPUS = 1,
		LOGICAL_CPUS = 2,
		THREADPOOL_THREADS = 3,
		FILTERCHAIN_THREADS = 4,
		THREAD_ID = 5,
		VERSION = 6
	};
}