#under construction
C++ build tool based on [gyp](https://chromium.googlesource.com/external/gyp/+/master/docs/UserDocumentation.md)

# example
### main.cpp:
```
#include "test.h"

int main(int argc, const char * argv[])
{
  std::cout << "hello" << std::endl;
	return 0; 
}
```
### test.gyp:
```
{
	'target_defaults': {
		'sources': [ 
			'src/main.cpp' 
		],
	}
}
```


plank
https://github.com/mucbuc/plank/wiki/quick-guide
