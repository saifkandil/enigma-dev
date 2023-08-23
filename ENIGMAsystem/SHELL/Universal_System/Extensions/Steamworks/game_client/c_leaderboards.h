/** Copyright (C) 2023-2024 Saif Kandil
***
*** This file is a part of the ENIGMA Development Environment.
***
*** ENIGMA is free software: you can redistribute it and/or modify it under the
*** terms of the GNU General Public License as published by the Free Software
*** Foundation, version 3 of the license or any later version.
***
*** This application and its source code is distributed AS-IS, WITHOUT ANY
*** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
*** FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
*** details.
***
*** You should have received a copy of the GNU General Public License along
*** with this code. If not, see <http://www.gnu.org/licenses/>
**/

/*
  Steam supports persistent leaderboards with automatically ordered entries. These leaderboards can 
  be used to display global and friend leaderboards in your game and on your community webpage. Each 
  Steamworks title can create up to 10,000 leaderboards, and each leaderboard can be retrieved immediately 
  after a player's score has been inserted.
  Check https://partner.steamgames.com/doc/features/leaderboards for more information.
*/

#ifndef GAMECLIENT_LEADERBOARDS_H
#define GAMECLIENT_LEADERBOARDS_H

// TODO: This documentation need to be improved when uploading a game to Steam Store.

#include "game_client.h"

namespace steamworks {

class c_leaderboards_find_result_cookies;
class c_leaderboards_score_uploaded_cookies;
class c_leaderboards_score_downloaded_cookies;

class c_game_client;

class c_leaderboards {
 public:
  c_leaderboards();
  ~c_leaderboards();

  void find_leaderboard(const int id, const std::string& leaderboard_name,
                        const ELeaderboardSortMethod leaderboard_sort_method = k_ELeaderboardSortMethodNone,
                        const ELeaderboardDisplayType leaderboard_display_type = k_ELeaderboardDisplayTypeNone);
  
  /*
    Uploads a user score to a specified leaderboard. Uploading scores to Steam is rate limited to 10 uploads 
    per 10 minutes and you may only have one outstanding call to this function at a time. Calls UploadLeaderboardScore.
    Check https://partner.steamgames.com/doc/api/ISteamUserStats#UploadLeaderboardScore for more information.
  */
  bool upload_score(
      const int id, const int score,
      const ELeaderboardUploadScoreMethod leaderboard_upload_score_method = k_ELeaderboardUploadScoreMethodNone);

  bool download_scores(const int id, const ELeaderboardDataRequest leaderboard_data_request, const int range_start = -1,
                       const int range_end = -1);

  static std::string get_leaderboard_name(const SteamLeaderboard_t leaderboard);

  void set_current_leaderboard(const SteamLeaderboard_t leaderboard);
  void set_loading(const bool loading);

 private:
  SteamLeaderboard_t* current_leaderboard_;
  bool loading_;
  unsigned number_of_leaderboard_entries_;

  /*
    These vectors can't have a race condition because they are only accessed from the main thread as
    ENIGMA single-threaded.
  */
  /*
    This vector is used to track all instances of c_leaderboards_find_result_cookies so that we can
    destroy them when they are done.
*/
  std::vector<c_leaderboards_find_result_cookies*> c_leaderboards_find_result_cookies_;

  /*
    This vector is used to track all instances of c_leaderboards_score_uploaded_cookies so that we can
    destroy them when they are done.
*/
  std::vector<c_leaderboards_score_uploaded_cookies*> c_leaderboards_score_uploaded_cookies_;

  /*
    This vector is used to track all instances of c_leaderboards_score_downloaded_cookies so that we can
    destroy them when they are done.
*/
  std::vector<c_leaderboards_score_downloaded_cookies*> c_leaderboards_score_downloaded_cookies_;

  void deallocate_all_c_leaderboards_find_result_cookies();
  void deallocate_all_c_leaderboards_score_uploaded_cookies();
  void deallocate_all_c_leaderboards_score_downloaded_cookies();

  void deallocate_c_leaderboards_find_result_cookies_if_done();
  void deallocate_c_leaderboards_score_uploaded_cookies_if_done();
  void deallocate_c_leaderboards_score_downloaded_cookies_if_done();
};
}  // namespace steamworks

#endif  // GAMECLIENT_LEADERBOARDS_H
