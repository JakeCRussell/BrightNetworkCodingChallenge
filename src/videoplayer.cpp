#include "videoplayer.h"
#include "video.h"
#include "videoplaylist.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::string nowPlaying = "";
bool paused = false;
std::vector<std::string> playlists;

void VideoPlayer::numberOfVideos() {
  std::cout << mVideoLibrary.getVideos().size() << " videos in the library"
            << std::endl;
}

// A custom sort function to sort video objects using title.
bool SortByTitle(Video v1, Video v2) {
    // if str1.compare(str2) < 0 => str1 comes before str2 lexicographically.
    return v1.getTitle().compare(v2.getTitle()) < 0;
}


void VideoPlayer::showAllVideos() {
    std::vector<Video> videos = mVideoLibrary.getVideos();
    std::sort(videos.begin(), videos.end(), SortByTitle);

    int vidSize = mVideoLibrary.getVideos().size();
    std::string tagString;
    
    for (unsigned i = 0; i < vidSize; i++) {
        tagString = "[";
        Video vid = videos[i];
        std::vector<std::string> tags = vid.getTags();
        int tagSize = tags.size();

        for (unsigned j = 0; j < tagSize; j++) {
            tagString = tagString + tags[j];
            if (j < tagSize - 1) {
                tagString = tagString + " ";
            }
        }
        tagString = tagString + "]";

        std::cout << vid.getTitle() << " (" << vid.getVideoId() << ") " << tagString << std::endl;
    }
}

void VideoPlayer::playVideo(const std::string& videoId) {

  const auto* video = mVideoLibrary.getVideo(videoId);

  if (video == nullptr) {
      std::cout << "Cannot play video: Video does not exist" << std::endl;
      return;
  }

  if (!nowPlaying.empty()) {
      stopVideo();
  }

  nowPlaying = video->getVideoId();
  paused = false;
  std::cout << "Playing video: " << video->getTitle() << std::endl;
}

void VideoPlayer::stopVideo() {
    if (!nowPlaying.empty()) {
        std::cout << "Stopping video: " << mVideoLibrary.getVideo(nowPlaying)->getTitle() << std::endl;
        nowPlaying = "";
        paused = false;
    }
    else {
        std::cout << "Cannot stop video: No video is currently playing" << std::endl;
    }
}

void VideoPlayer::playRandomVideo() {
    std::vector<Video> videos = mVideoLibrary.getVideos();
    const auto& index = rand() % videos.size();
    playVideo(videos[index].getVideoId());
}

void VideoPlayer::pauseVideo() {
    if (nowPlaying.empty()) {
        std::cout << "Cannot pause video: No video is currently playing" << std::endl;
    }
    else if (paused) {
        std::cout << "Video already paused: " << mVideoLibrary.getVideo(nowPlaying)->getTitle() << std::endl;
    }
    else {
        paused = true;
        std::cout << "Pausing video: " << mVideoLibrary.getVideo(nowPlaying)->getTitle() << std::endl;
    }
}

void VideoPlayer::continueVideo() {
    if (nowPlaying.empty()) {
        // no video playing
        std::cout << "Cannot continue video: No video is currently playing" << std::endl;
    }
    else if (!paused) {
        // video playing but not paused
        std::cout << "Cannot continue video: Video is not paused" << std::endl;
    }
    else {
        //continue playing
        paused = false;
        std::cout << "Continuing video: " << mVideoLibrary.getVideo(nowPlaying)->getTitle() << std::endl;
    }
}

void VideoPlayer::showPlaying() {
    if (nowPlaying.empty()) {
        // no video playing
        std::cout << "No video is currently playing" << std::endl;
    }
    else {
        std::cout << "Currently playing: " << mVideoLibrary.getVideo(nowPlaying)->getTitle() << " (" << nowPlaying << ") [";
        
        std::vector<std::string> tags = mVideoLibrary.getVideo(nowPlaying)->getTags();
        int tagSize = tags.size();
        std::string tagString = "";
        for (unsigned i = 0; i < tagSize; i++) {
            tagString = tagString + tags[i];
            if (i < tagSize - 1) {
                tagString = tagString + " ";
            }
        }
        std::cout << tagString << "]";
        if (paused) {
            std::cout << " - PAUSED";
        }
        std::cout << std::endl;
    }
}

void VideoPlayer::createPlaylist(const std::string& playlistName) {
    //std::string name = playlistName;
    //VideoPlaylist list = VideoPlaylist(name);
    //playlists.push_back(list);
    if (std::find(playlists.begin(), playlists.end(), playlistName) != playlists.end())
    {
        std::cout << "Cannot create playlist: A playlist with the same name already exists" << std::endl;
    }
    else {
        std::cout << "Successfully created new playlist: " << playlistName << std::endl;
        playlists.push_back(playlistName);
    }
    
}

void VideoPlayer::addVideoToPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
    if (std::find(playlists.begin(), playlists.end(), playlistName ) != playlists.end())
    {
        std::cout << "Cannot add video to " << playlistName << ": Video does not exist" << std::endl;
    }
    else {
        std::cout << "Cannot add video to " << playlistName << ": Playlist does not exist" << std::endl;
    }
  
}

void VideoPlayer::showAllPlaylists() {
    if (playlists.empty()) {
        std::cout << "No playlists exist yet" << std::endl;
    }
    else {
        std::cout << "Showing all playlists:" << std::endl;
        for (unsigned i = 0; i < playlists.size(); i++) {
            std::cout << playlists[i] << std::endl;
        }
    }
  
}

void VideoPlayer::showPlaylist(const std::string& playlistName) {
  std::cout << "Cannot show playlist " << playlistName << ": Playlist does not exist" << std::endl;
}

void VideoPlayer::removeFromPlaylist(const std::string& playlistName,
                                     const std::string& videoId) {
    const auto* video = mVideoLibrary.getVideo(videoId);

    if (video == nullptr) {
        std::cout << "Cannot remove video from " << playlistName << ": Video does not exist" << std::endl;
        return;
    }

  std::cout << "Cannot remove video from " << playlistName << ": Playlist does not exist" << std::endl;
}

void VideoPlayer::clearPlaylist(const std::string& playlistName) {
  std::cout << "clearPlaylist needs implementation" << std::endl;
}

void VideoPlayer::deletePlaylist(const std::string& playlistName) {       
        auto itr = std::find(playlists.begin(), playlists.end(), playlistName);
        if (itr != playlists.end()) {
            playlists.erase(itr);
            std::cout << "Deleted playlist: " << playlistName << std::endl;
        }
        else {
            std::cout << "Cannot delete playlist " << playlistName << ": Playlist does not exist" << std::endl;
        }
}

void VideoPlayer::searchVideos(const std::string& searchTerm) {
  std::cout << "searchVideos needs implementation" << std::endl;
}

void VideoPlayer::searchVideosWithTag(const std::string& videoTag) {
  std::cout << "searchVideosWithTag needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::flagVideo(const std::string& videoId, const std::string& reason) {
  std::cout << "flagVideo needs implementation" << std::endl;
}

void VideoPlayer::allowVideo(const std::string& videoId) {
  std::cout << "allowVideo needs implementation" << std::endl;
}
