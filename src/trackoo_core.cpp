#include "trackoo_core.h"

TrackooCore * TrackooCore::pinstance{ nullptr };
std::mutex TrackooCore::mutex;

TrackooCore * TrackooCore::getInstance() {

	if (pinstance == nullptr) {
		std::lock_guard<std::mutex> lock(mutex);
		if (pinstance == nullptr) {

			pinstance = new TrackooCore();
		}
	}

	return pinstance;
}