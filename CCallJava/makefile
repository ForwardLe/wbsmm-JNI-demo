a.out: callJavaTest.c 
# for ubuntu
#	gcc callJavaTest.c -o a.out -L $(JAVA_HOME)/jre/lib/amd64/server/ -I $(JAVA_HOME)/include/ -I $(JAVA_HOME)/include/linux/ -ljvm
# for OSX
	gcc callJavaTest.c -o a.out -L $(JAVA_HOME)/jre/lib/server/ -rpath  $(JAVA_HOME)/jre/lib/server/ -I $(JAVA_HOME)/include/ -I $(JAVA_HOME)/include/darwin/ -ljvm

# -rpath 用于运行时不用指明LD_LIBRARY_PATH这个环境变量 OSX 和 ubuntu都不会自动载入这个环境变量

