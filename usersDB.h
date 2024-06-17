#include <vector>
#include <string>

enum class Event { trackreactor, trackcatalyst, trackforma, unsubscride, smthngWrong };

constexpr const char* EventToString(Event e) noexcept
{
    switch (e)
    {
    case Event::trackreactor: return "trackreactor";
    case Event::trackcatalyst: return "trackcatalyst";
    case Event::trackforma: return "trackforma";
    case Event::unsubscride: return "unsubscride";
    case Event::smthngWrong: return "smthngWrong";
    }
}

struct userData {
	int64_t id;
    std::string event;
};
std::vector<userData> getObservers();
bool saveObserver(int64_t id, std::string event);
bool deleteObserver(int64_t id);