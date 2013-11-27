// ==================================================================================================================================
//	   ______                             __     ___   ____     ___    ____  ____
//	  / ____/___  _________  ____  __  __/ /_   |__ \ / __ \   /   |  / __ \/  _/
//	 / /   / __ \/ ___/ __ \/ __ \/ / / / __/   __/ // / / /  / /| | / /_/ // /  
//	/ /___/ /_/ / /__/ /_/ / / / / /_/ / /_    / __// /_/ /  / ___ |/ ____// /   
//	\____/\____/\___/\____/_/ /_/\__,_/\__/   /____/_____/  /_/  |_/_/   /___/   
//	                                                                             
// ==================================================================================================================================

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>

class WebGLRenderingContext;

#define Number          float
#define Boolean         bool
#define String          std::string
#define Function        void*
#define Object          void*
#define Array<T>        std::vector<T*>
#define Stack<T>        std::stack<T*>
#define Dictionary<T>   std::map<String, T*>
#define Index<T>		std::map<Number, T*>

typedef void (*FPAction)(WebGLRenderingContext*, Number, Number, CocoScene*, CocoClip*);
typedef std::vector<float> Float32Array;