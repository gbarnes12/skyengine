#include '/Shared/ScriptBehavior.as'

class TestBehavior : ScriptBehavior
{
	TestBehavior()
	{
		print("Hello World from TestBehavior.as");
	}
	
	void OnStart() override {
		print("OnStart !!!!");
	}
	void OnUpdate() override {}
	
	float OnExit(float a, int b) override 
	{
		return a*b;
	}
}