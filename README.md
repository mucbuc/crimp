#crimp
nodejs build tool for C++ based on [gyp](https://chromium.googlesource.com/external/gyp/+/master/docs/UserDocumentation.md)


#install
`npm install -g crimp`

#usage
```
  Usage: crimp [files] [options]

  Options:

    -h, --help           output usage information
    -V, --version        output the version number
    -o, --output [path]  build output (default: build)
    -t, --test           test build (default)
    -d, --debug          target debug
    -r, --release        target release
    -c, --clean          clean build
    -g, --gcc            use gcc compiler
    -e, --execute        execute product
    -i, --ide            open project in ide
    -x, --xargs []       pass on arguments
```

###properties:
- sources: array containing paths to C++ source files
- import: array containing paths to defenition files
- opengl: boolean to determine opengl linking
- tests: array of definition files 

# example
### src/main.cpp:
```
int main()
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
crimp test.json
```

### references
http://www.rioki.org/2013/02/07/experimenting-with-gyp.html
https://github.com/springmeyer/hello-gyp




