/*
*  An example of an asynchronous C++ node addon.
* Provided by paulhauner https://github.com/paulhauner
* License MIT
* Tested in node.js v4.4.2 LTS in Ubuntu Linux
* Tested in node.js v6.0.1     in Windows 7 32-bit
*/
#include <node.h>
#include <uv.h>
#include <iostream>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
namespace asyncAddon{
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Persistent;
struct Work{
uv_work_t request;
Persistent<Function> callback;
string result;
};

static void WorkAsync(uv_work_t *req){
Work *work=static_cast<Work*>(req->data);
#ifdef WIN32
    Sleep(3000);
#else
	sleep(3);
#endif
work->result="Async task processed.";
}
static void WorkAsyncComplete(uv_work_t *req,int status){
Isolate *isolate=Isolate::GetCurrent();
v8::HandleScope handleScope(isolate);
Work *work=static_cast<Work*>(req->data);
const char *result = work->result.c_str();
Local<Value> argv[1]={String::NewFromUtf8(isolate,result)};
Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(),1,argv);
work->callback.Reset();
delete work;
}
void DoTaskAsync(const FunctionCallbackInfo<Value>& args){
Isolate *isolate=args.GetIsolate();
Work *work=new Work();
work->request.data=work;
Local<Function> callback=Local<Function>::Cast(args[0]);
work->callback.Reset(isolate,callback);
uv_queue_work(uv_default_loop(),&work->request,WorkAsync,WorkAsyncComplete);
args.GetReturnValue().Set(Undefined(isolate));
}
void init(Local<Object> exports){
NODE_SET_METHOD(exports,"doTask",DoTaskAsync);
}
NODE_MODULE(asyncAddon,init);
}