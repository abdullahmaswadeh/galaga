#pragma once
#ifndef _STAGES_H_
#define _STAGES_H_

typedef void(*stageFuncs)();

class stages {

public:
	static void init();
	static void loadStage(int index);
	static void stage1();
	static void stage2();
	static void stage3();
	static void stage4();
	static stageFuncs stagesArr[4];

};

#endif // !_STAGES_H_
