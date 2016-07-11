class Scene {

private:
	int id;
	char* name;
	double time;

public:

	Scene() {
		time = 0;
	}

	void KeyEvent(int key) {
		
	}

	void Update() {
		time++;
	}
};