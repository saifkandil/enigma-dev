#include "game_client.h"

#include "c_overlay.h"
#include "c_stats_and_achievements.h"

namespace steamworks {

c_game_client* game_client_{NULL};
c_game_client* game_client() { return game_client_; }

// c_game_client::c_game_client(ISteamUser* steam_user, ISteamFriends* steam_friends, ISteamUtils* steam_utils)
//     : steam_user_(steam_user),
//       steam_friends_(steam_friends),
//       steam_utils_(steam_utils),
//       steam_id_local_user_(steam_user->GetSteamID()),
//       steam_app_id_(steam_utils->GetAppID()) {
//   init();
// }

c_game_client::c_game_client()
    : c_overlay_(NULL),
      c_stats_and_achievements_(NULL),
      c_steam_id_local_user_(SteamUser()->GetSteamID()),
      steam_app_id_(SteamUtils()->GetAppID()),
      current_game_language_(SteamApps()->GetCurrentGameLanguage()),
      available_game_languages_(SteamApps()->GetAvailableGameLanguages()) {
  init();
}

c_game_client::~c_game_client() {
  if (NULL != c_game_client::c_overlay_) delete c_game_client::c_overlay_;
  if (NULL != c_game_client::c_stats_and_achievements_) delete c_game_client::c_stats_and_achievements_;
}

void c_game_client::init() {
  game_client_ = this;

  c_game_client::c_overlay_ = new c_overlay();
  c_game_client::c_stats_and_achievements_ = new c_stats_and_achievements();
}

c_overlay* c_game_client::get_c_overlay() { return c_game_client::c_overlay_; }

c_stats_and_achievements* c_game_client::get_c_stats_and_achievements() {
  return c_game_client::c_stats_and_achievements_;
}

CSteamID c_game_client::get_c_steam_id_local_user() { return c_game_client::c_steam_id_local_user_; }

unsigned c_game_client::get_steam_app_id() { return c_game_client::steam_app_id_; }

std::string c_game_client::get_current_game_language() { return c_game_client::current_game_language_; }

std::string c_game_client::get_available_game_languages() { return c_game_client::available_game_languages_; }

bool c_game_client::is_user_logged_on() { return SteamUser()->BLoggedOn(); }

std::string c_game_client::get_steam_user_persona_name(CSteamID c_steam_id) {
  return SteamFriends()->GetFriendPersonaName(c_steam_id);
}

std::string c_game_client::get_steam_persona_name() { return SteamFriends()->GetPersonaName(); }

bool c_game_client::is_subscribed() { return SteamApps()->BIsSubscribed(); }

}  // namespace steamworks
