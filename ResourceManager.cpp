class ResourceManager {

private:
	int id;
	char* name;

public:
	ResourceManager() {
		id = 0;
		name = "NO_NAME";
	}

	ResourceManager(int id_) {
		id = id_;
	}

	ResourceManager(int id_, char* name) {
		id = id_;
		name = name;
	}
};