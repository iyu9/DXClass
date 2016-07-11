class Resource {

private:
	int id;
	char* file;
	int type;

public:
	Resource() {
		id = 0;
	}

	Resource(int id_) {
		id = id_;
	}

	Resource(int id_, char* file_) {
		id = id_;
		file = file_;
	}
};