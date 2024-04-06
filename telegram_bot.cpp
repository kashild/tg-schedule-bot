#include <stdio.h>
#include <tgbot/tgbot.h>
#include <vector>
#include <curl/curl.h>
#include "json.hpp"

using namespace TgBot;
using namespace std;

vector<string>bot_commands = {"start", "schedule"};

static size_t Writer(char *buffer, size_t size, size_t nmemb, std::string *html){
    int result = 0; 

    if(buffer != NULL){ 
        html->append(buffer, size*nmemb); 
        result = size*nmemb; 
    } 
    return result;
}

std::string get_request(std::string link) {
        CURL *curl; 
        std::string data; 
        curl=curl_easy_init(); 
        curl_easy_setopt(curl,CURLOPT_URL, link.c_str()); 
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, Writer); 
        curl_easy_setopt(curl,CURLOPT_WRITEDATA, &data); 
        curl_easy_perform(curl); 
        curl_easy_cleanup(curl); 
        return data;
}

string get_schedule(string day, string clas, string number) {
    auto js_obj = nlohmann::json::parse(get_request("file:///home/mydusiyo/schedule.json"));

    return js_obj[day][clas][number].get<string>();
    
}

int main() {
    

    Bot bot("6758268410:AAEuQ-3DLPUWEVROYQjlfHpsBBUytA76U4o");

    InlineKeyboardMarkup::Ptr keyboard1(new InlineKeyboardMarkup); 
    vector<InlineKeyboardButton::Ptr> buttons1; 
    InlineKeyboardButton::Ptr monday_btn(new InlineKeyboardButton), tuesday_btn(new InlineKeyboardButton), wednesday_btn(new InlineKeyboardButton), thursday_btn(new InlineKeyboardButton), friday_btn(new InlineKeyboardButton); 
    monday_btn->text = "ПН";
    tuesday_btn->text = "ВТ";
    wednesday_btn->text = "СР";
    thursday_btn->text = "ЧТ";
    friday_btn->text = "ПТ";
    monday_btn->callbackData = "ПН";
    tuesday_btn->callbackData = "ВТ";
    wednesday_btn->callbackData = "СР";
    thursday_btn->callbackData = "ЧТ";
    friday_btn->callbackData = "ПТ";
    buttons1.push_back(monday_btn);
    buttons1.push_back(tuesday_btn);
    buttons1.push_back(wednesday_btn);
    buttons1.push_back(thursday_btn);
    buttons1.push_back(friday_btn);
    keyboard1->inlineKeyboard.push_back(buttons1);

    InlineKeyboardMarkup::Ptr keyboard2(new InlineKeyboardMarkup); 
    vector<InlineKeyboardButton::Ptr> buttons2; 
    InlineKeyboardButton::Ptr five_btn(new InlineKeyboardButton), six_btn(new InlineKeyboardButton), seven_btn(new InlineKeyboardButton), eight_btn(new InlineKeyboardButton), nine_btn(new InlineKeyboardButton), ten_btn(new InlineKeyboardButton), eleven_btn(new InlineKeyboardButton); 
    five_btn->text = "5";
    six_btn->text = "6";
    seven_btn->text = "7";
    eight_btn->text = "8";
    nine_btn->text = "9";
    ten_btn->text = "10";
    eleven_btn->text = "11";
    five_btn->callbackData = "5";
    six_btn->callbackData = "6";
    seven_btn->callbackData = "7";
    eight_btn->callbackData = "8";
    nine_btn->callbackData = "9";
    ten_btn->callbackData = "10";
    eleven_btn->callbackData = "11";
    buttons2.push_back(five_btn);
    buttons2.push_back(six_btn);
    buttons2.push_back(seven_btn);
    buttons2.push_back(eight_btn);
    buttons2.push_back(nine_btn);
    buttons2.push_back(ten_btn);
    buttons2.push_back(eleven_btn);
    keyboard2->inlineKeyboard.push_back(buttons2);

    InlineKeyboardMarkup::Ptr keyboard3(new InlineKeyboardMarkup); 
    vector<InlineKeyboardButton::Ptr> buttons3; 
    InlineKeyboardButton::Ptr a_btn(new InlineKeyboardButton), b_btn(new InlineKeyboardButton), v_btn(new InlineKeyboardButton), g_btn(new InlineKeyboardButton), d_btn(new InlineKeyboardButton); 
    a_btn->text = "А";
    b_btn->text = "Б";
    v_btn->text = "В";
    g_btn->text = "Г";
    d_btn->text = "Д";
    a_btn->callbackData = "А";
    b_btn->callbackData = "Б";
    v_btn->callbackData = "В";
    g_btn->callbackData = "Г";
    d_btn->callbackData = "Д";
    buttons3.push_back(a_btn);
    buttons3.push_back(b_btn);
    buttons3.push_back(v_btn);
    buttons3.push_back(g_btn);
    buttons3.push_back(d_btn);
    keyboard3->inlineKeyboard.push_back(buttons3);



    bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Привет, " + message->chat->firstName);
        bot.getApi().sendMessage(message->chat->id, "\n Что бы узнать расписание введи команду /schedule");
    });


    bot.getEvents().onCommand("schedule", [&bot, &keyboard1](Message::Ptr message) {

        bot.getApi().sendMessage(message->chat->id, "Расписание для какого дня вы хотите узнать?", false, 0, keyboard1);

    });

    bot.getEvents().onCallbackQuery([&bot, &keyboard1, &keyboard2, &keyboard3](CallbackQuery::Ptr query) { 
        if (query->data == "ПН" || query->data == "ВТ" || query->data == "СР" || query->data == "ЧТ" || query->data == "ПТ") {
            string day2 = query->data;

            bot.getApi().sendMessage(query->message->chat->id, "Расписание для какого класса вы хотите узнать?", false, 0, keyboard2);

            bot.getEvents().onCallbackQuery([&bot, &keyboard2, &keyboard3, day2](CallbackQuery::Ptr query) {
                if (query->data == "5" || query->data == "6" || query->data == "7" || query->data == "8" || query->data == "9" || query->data == "10" || query->data == "11") {
                    string clas2 = query->data;

                    bot.getApi().sendMessage(query->message->chat->id,"Номер какого класса вам нужен?", false, 0, keyboard3);

                    bot.getEvents().onCallbackQuery([&bot, &keyboard3, day2, clas2](CallbackQuery::Ptr query) {
                    if (query->data == "А" || query->data == "Б" || query->data == "В" || query->data == "Г" || query->data == "Д") {
                        string number2 = query->data;

                    bot.getApi().sendMessage(query->message->chat->id, get_schedule(day2, clas2, number2));
                }
            });
                }
            });
        }
    });



    bot.getEvents().onAnyMessage([&bot](Message::Ptr message) {

        for(const auto& command : bot_commands){ 
            if("/"+command==message->text){
                return;
            }
        }


        bot.getApi().sendMessage(message->chat->id, "Sorry, I don't know (");
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgException& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}