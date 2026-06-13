#ifndef H_ASSETS
#define H_ASSETS

#include <vector>
#include <fstream>
#include <string>

#include "entities.h"
#include "encounters.h"

class Assets {
private:
  static Assets* assets_instance_;
  Assets() {}

public:
	Assets(const Assets&) = delete;
	Assets& operator=(const Assets&) = delete;
	Assets(Assets&&) = delete;
	Assets& operator=(Assets&&) = delete;

	static Assets* GetInstance() {
		if (assets_instance_ == nullptr) {
			assets_instance_ = new Assets();
		}
		return assets_instance_;
	}

	std::vector<Entities> assets_entities_;
	std::vector<Encounters> assets_encounters_;
	std::vector<Encounters> assets_extras_;
	std::vector<int> merges_;

	void ReadEntities();
	void ReadEncounters();
	void ReadExtras();
	void ReadMerges();

	static void Destroy() {
		delete assets_instance_;
		assets_instance_ = nullptr;
	}
	
};

#endif