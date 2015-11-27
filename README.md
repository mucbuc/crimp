#crimp
nodejs build tool for C++ based on [gyp](https://chromium.googlesource.com/external/gyp/+/master/docs/UserDocumentation.md)


#install
`npm install -g crimp`

#usage
```
  Usage: crimp [options]

  Options:

    -h, --help           output usage information
    -V, --version        output the version number
    -o, --output [path]  build output (default: build)
    -p, --path [path]    test path (default .)
    -s, --suite [path]   suite json
    -t, --test           test build (default)
    -d, --debug          target debug
    -r, --release        target release
    -c, --clean          clean build
    -g, --gcc            use gcc compiler
    -e, --execute        execute product
    -i, --ide            open project in ide
```

# example
### src/main.cpp:
```
#include "test.h"

int main(int argc, const char * argv[])
{
	std::cout << "hello" << std::endl;
	return 0; 
}
```
### test.json:
```
{
	'sources': [ 
		'src/main.cpp' 
	],
}
```
### build and test
```
crimp -p test.json
```