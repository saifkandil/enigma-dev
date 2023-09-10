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

#include "gc_leaderboards_score_uploaded_cookies.h"

#include "../../leaderboards.h"
#include "../gc_leaderboards.h"

namespace steamworks_gc {

////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////

GCLeaderboardsScoreUploadedCookies::GCLeaderboardsScoreUploadedCookies(int id, GCLeaderboards* gc_leaderboards,
                                                                       SteamAPICall_t steam_api_call)
    : id_(id), gc_leaderboards_(gc_leaderboards), is_done_(false) {
  GCLeaderboardsScoreUploadedCookies::set_call_result(steam_api_call);
}

////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////

bool GCLeaderboardsScoreUploadedCookies::is_done() const { return GCLeaderboardsScoreUploadedCookies::is_done_; }

void GCLeaderboardsScoreUploadedCookies::set_call_result(SteamAPICall_t steam_api_call) {
#ifndef ENIGMA_STEAMWORKS_API_MOCK
  GCLeaderboardsScoreUploadedCookies::m_SteamCallResultUploadScore.Set(
      steam_api_call, this, &GCLeaderboardsScoreUploadedCookies::on_upload_score);
#else
  LeaderboardScoreUploaded_t pScoreUploadedResult;
  pScoreUploadedResult.m_bSuccess = true;
  pScoreUploadedResult.m_hSteamLeaderboard = INVALID_LEADERBOARD;
  pScoreUploadedResult.m_nScore = 0;
  pScoreUploadedResult.m_bScoreChanged = true;
  pScoreUploadedResult.m_nGlobalRankNew = 0;
  pScoreUploadedResult.m_nGlobalRankPrevious = 0;

  GCLeaderboardsScoreUploadedCookies::on_upload_score(&pScoreUploadedResult, false);
#endif  // ENIGMA_STEAMWORKS_API_MOCK
}

void GCLeaderboardsScoreUploadedCookies::on_upload_score(LeaderboardScoreUploaded_t* pScoreUploadedResult,
                                                         bool bIOFailure) {
  if (!pScoreUploadedResult->m_bSuccess || bIOFailure) {
    if (enigma::number_of_successful_upload_requests % 10 == 0 && enigma::number_of_successful_upload_requests != 0) {
      DEBUG_MESSAGE(
          "Did you create 10 upload requests in less than 10 minutes? Well, the upload rate is limited to "
          "10 upload requests per 10 minutes so you may want to wait before another request.",
          M_WARNING);
      enigma::upload_rate_limit_exceeded = true;
    } else
      DEBUG_MESSAGE("Failed to upload score to leaderboard.", M_ERROR);
    // gc_leaderboards_score_uploaded_cookies::gc_leaderboards_->set_loading(false);
    GCLeaderboardsScoreUploadedCookies::is_done_ = true;
    return;
  }

  // TODO: Build failure when uncommenting this line.
  // TODO: Create a struct for this.
  // Success? Let's save it.
  // LGM and SOGs are failing because of this line.
  // enigma::scores_array.get(gc_leaderboards_score_uploaded_cookies::id_) = true;

  // Done? We are ready to accept new requests.
  // gc_leaderboards_score_uploaded_cookies::gc_leaderboards_->set_loading(false);

  GCLeaderboardScoreUploadedResult leaderboard_score_uploaded_result;
  leaderboard_score_uploaded_result.success = pScoreUploadedResult->m_bSuccess;
  leaderboard_score_uploaded_result.leaderboard = pScoreUploadedResult->m_hSteamLeaderboard;
  leaderboard_score_uploaded_result.score = pScoreUploadedResult->m_nScore;
  leaderboard_score_uploaded_result.score_changed = pScoreUploadedResult->m_bScoreChanged;
  leaderboard_score_uploaded_result.global_rank_new = pScoreUploadedResult->m_nGlobalRankNew;
  leaderboard_score_uploaded_result.global_rank_previous = pScoreUploadedResult->m_nGlobalRankPrevious;

  enigma::push_leaderboard_upload_steam_async_event(GCLeaderboardsScoreUploadedCookies::id_,
                                                    leaderboard_score_uploaded_result);

  GCLeaderboardsScoreUploadedCookies::is_done_ = true;
}

}  // namespace steamworks_gc
