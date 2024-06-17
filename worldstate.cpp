#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <boost/exception/exception.hpp>
using json = nlohmann::json;

const std::string site = "https://content.warframe.com/dynamic/worldState.php";
struct worldState
{
    bool hasReactor = false;
    bool hasCatalyst = false;
    bool hasForma = false;
};
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static worldState askWorldState()
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    worldState actualState;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, site.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        try
        {
            json j_filtered = json::parse(readBuffer);
            actualState.hasCatalyst = j_filtered.contains("OrokinCatalyst");
            actualState.hasReactor = j_filtered.contains("OrokinReactor");
            actualState.hasForma = j_filtered.contains("Forma");
        }
        catch (const std::exception& e)
        {
            std::cout << e.what();
        }
    }

    return actualState;
    std::this_thread::sleep_for(std::chrono::minutes(5));
}