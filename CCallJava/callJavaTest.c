#include <jni.h>
#include <stdio.h>
#include <string.h>
#define NUM_SIZE 1000
JNIEnv* create_vm(JavaVM **jvm){
	JNIEnv* env;
	JavaVMInitArgs args;
	JavaVMOption options;
	int ret;

	args.version = JNI_VERSION_1_6;// see jni.h
	args.nOptions = 1;
	options.optionString = "-Djava.class.path=.:./calc.jar";
	args.options = &options;
	args.ignoreUnrecognized = 0;
	
	ret = JNI_CreateJavaVM(jvm,(void**)&env,&args);
	if (ret<0 || !env){
		printf("Unable to Launch JVM %d\n",ret);
	}else{
		printf(":aunched JVM! :)\n");
	}
	return env;
}
void invoke_class_add_method(JNIEnv* env,char* a,char* b,char* ret){
	jclass calc_class;
	jmethodID add_method;
	jstring jstr_a;
	jstring jstr_b;
	jstring jstr_ret;
	const char* ret_str;
	calc_class = (*env)->FindClass(env,"Calc");
	add_method = (*env)->GetStaticMethodID(env,calc_class,
			"add","(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
	jstr_a = (*env)->NewStringUTF(env,a); 
	jstr_b = (*env)->NewStringUTF(env,b);
	jstr_ret = (jstring)((*env)->CallStaticObjectMethod(env, calc_class, add_method, jstr_a,jstr_b));
	if (jstr_ret == NULL){
		strcpy(ret,"NULL");
		return ;
	}
	ret_str = (const char*)((*env)->GetStringUTFChars(env, jstr_ret, NULL));
	strncpy(ret, ret_str,sizeof(ret));//strcpy可能溢出,此处暂不更加详细地处理	
	(*env)->ReleaseStringUTFChars(env, jstr_ret, ret_str);
}
int main(int argc, char*argv[]) {  
	char ret[NUM_SIZE];
	if (argc!=3){
		printf("params error.please input two number!!!\n");
		return 1;	
	}
    	JavaVM *jvm;
    	JNIEnv *env;
    	env = create_vm(&jvm);
    	if(env == NULL){
		printf("create jvm failed");	
	}
	invoke_class_add_method(env,argv[1],argv[2],ret);
	printf("%s\n+\n%s\n=\n%s\n",argv[1],argv[2],ret);
    	return 0;
}  

