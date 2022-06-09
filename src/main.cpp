#include <doltlib.h>
#include <memory>
#include <string>

int runDolt(int argCount, std::string args[]) {
	auto goStringArgs = std::make_unique<GoString[]>(argCount+1);
	goStringArgs[0] = {"dolt", 4};
	for(int i = 0; i < argCount; i++) {
		goStringArgs[i+1].n = (ptrdiff_t)args[i].size();
		goStringArgs[i+1].p = args[i].data();
	}
	GoSlice goSliceArgs = {goStringArgs.get(), (GoInt)argCount+1, (GoInt)argCount+1};
	return (int)RunDolt(goSliceArgs);
}

int main(int argc, char *argv[]) {
	auto args = std::make_unique<std::string[]>(argc-1);
	for(int i = 1; i < argc; i++) {
		args[i-1] = argv[i];
	}
	return runDolt(argc-1, args.get());
}
