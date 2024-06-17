#include <iostream>
#include <tgbot/tgbot.h>
#include "messageWrapper.h"
#include "worldstate.cpp"
#include <thread>
#include <future>

int main() {
    std::string token(getenv("TOKEN"));
    TgBot::Bot bot(token);
    worldState actualState;
    MessageWrapper myMessage;
    std::vector<userData> observers = getObservers();
    const std::initializer_list<std::string> commands{ EventToString(Event::trackreactor),
                                                       EventToString(Event::trackcatalyst),
                                                       EventToString(Event::trackforma), 
                                                       EventToString(Event::unsubscride) };
    bot.getEvents().onCommand(commands, [&bot, &myMessage](TgBot::Message::Ptr message) {
        std::string response = myMessage.onEvent(message->text, message->chat->id);
        bot.getApi().sendMessage(message->chat->id, response);
        });
    try {
        while (true) {
            //std::promise<worldState> actual_state_promise;
            //std::future<worldState> actual_state_future = actual_state_promise.get_future();
            //std::thread actual_state_thread(askWorldState, std::move(actual_state_promise));
            //worldState actual_state = actual_state_future.get();
            //actual_state_thread.join();
            worldState actual_state = askWorldState();
            for each (userData user in observers)
            {

                if (user.event == EventToString(Event::trackreactor) && actual_state.hasReactor)
                {
                    bot.getApi().sendMessage(user.id, "Reactor is here!");
                }
                if (user.event == EventToString(Event::trackcatalyst) && actual_state.hasCatalyst)
                {
                    bot.getApi().sendMessage(user.id, "Catalyst is here!");
                }
                if (user.event == EventToString(Event::trackforma) && actual_state.hasForma)
                {
                    bot.getApi().sendMessage(user.id, "Forma is here!");
                }
                
            }
        }
    }
    catch (TgBot::TgException& e) {
        std::cout << "error: %s\n" << e.what();
    }
    return 0;
}