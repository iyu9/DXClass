#include "scene.cpp"

class SceneManager {

private:
	Scene* scene;

public:
	SceneManager() {
		scene = new Scene();
		scene->Update();
	}

	void ChangeScene(Scene* next) {
		scene = next;
	}
};