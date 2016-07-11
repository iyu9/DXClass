class Vector3 {
public:
	double x, y, z;

	Vector3() {
		x = y = z = 0;
	}
};

class Object {
private:
	int id;
	char name[12];
	int img_id;

public:
	Vector3 scale;
	Vector3 pos;
	Vector3 rot;

	Object() {}

	void set_id(int id_) {
		id = id_;
	}
};

class ObjectManager {
private:
	int count;
	Object* objectPool[100];

public:

	ObjectManager() {
		count = 0;
	}

	void add_object(Object &obj) {
		objectPool[count] = new Object();
		objectPool[count] = &obj;
		count++;
	}

};