#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <iostream>
#include <string>
#include "Widget_Systems/widgets_mandatory.h"
#include "public/steam/steam_api.h"

namespace steamworks {

class c_overlay;

class c_game_client {
 public:
  // c_game_client(ISteamUser* steam_user, ISteamFriends* steam_friends, ISteamUtils* steam_utils);
  c_game_client();
  ~c_game_client();

  void init();

  c_overlay* get_overlay();

  CSteamID get_c_steam_id_local_user();
  unsigned get_steam_app_id();

  std::string get_steam_persona_name();

  std::string get_current_game_language();
  std::string get_available_game_languages();

  static std::string get_steam_user_persona_name(CSteamID c_steam_id);
  static bool is_user_logged_on();
  static bool is_subscribed();

 private:
  c_overlay* overlay;

  CSteamID c_steam_id_local_user_;
  unsigned steam_app_id_;

  std::string steam_persona_name_;

  std::string current_game_language_;
  std::string available_game_languages_;

  // ISteamUser* steam_user_;
  // ISteamFriends* steam_friends_;
  // ISteamUtils* steam_utils_;
};
}  // namespace steamworks

#endif  // GAMECLIENT_H
