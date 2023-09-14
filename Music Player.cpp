#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <random>
#include<bits/stdc++.h>

using namespace std;

// Song class representing a single song
class Song {                                                       
public:
    string title;                            //title of the song
    string artist;                            //artist of the song

    Song(const string& _title, const string& _artist)        //Song constructor taking title and artist as its parameters
        : title(_title), artist(_artist) {}
};

// Playlist class representing a collection of songs using linked list
class Playlist {
public:
    string name;                        //name of the playlist
    list<Song*> songs;                    //list of songs, STL List is used here which is a doubly linked list

    Playlist(const string& _name) : name(_name) {}            //Playlist constructor

    void addSong(Song* song) {                                //an object which adds a new song to the playlist 
        songs.push_back(song);
    }

    void removeSong(Song* song) {                            //an object which removes an existing song from the playlist
        songs.remove(song);
    }

void shuffleSongs() {                                              //this will shuffle the contents of the playlist                      
    vector<Song*> songsVector(songs.begin(), songs.end());
    random_shuffle(songsVector.begin(), songsVector.end());
    songs.assign(songsVector.begin(), songsVector.end());
}

    void sortSongsByTitle() {                                   //if the user wants to sort songs on the basis of title
        songs.sort([](const Song* a, const Song* b) {           
            return a->title < b->title;                            //lambda function, compares the songs and provides a lexicographically sorted list
        });
    }

    void sortSongsByArtist() {                                //if the user wants to sort songs on the basis of artist's name
        songs.sort([](const Song* a, const Song* b) {            //which in this case is given by a and b and the comparision criteria
            return a->artist < b->artist;                    //STL sort can be given a comparator
        });                                                    
    }
};

// MusicLibrary class representing the entire music collection
class MusicLibrary {
public:
    unordered_map<string, Song*> songsMap;                            // representing all songs in a hash map through stl container
    unordered_map<string, Playlist*> playlistsMap;                    // representing all playlists in a hash map through stl container
    list<Song*> favoritesList;                                    //collection of fav songs in a list

    void addSong(const string& title, const string& artist) {        //adding a song in the songs map
        Song* song = new Song(title, artist);                        //with the given title and artist name
        songsMap[title] = song;                                      //title being the key to the song class
    }

    void removeSong(const string & title) {                    
        Song* song = songsMap[title];
        if (song) {
            for (auto& pair : playlistsMap) {
                pair.second->removeSong(song);
            }
            songsMap.erase(title);
            delete song;
        }
    }

    void createPlaylist(const string& name) {
        Playlist* playlist = new Playlist(name);
        playlistsMap[name] = playlist;
    }

    void addSongToPlaylist(const string& playlistName, const string& songTitle) {
        Playlist* playlist = playlistsMap[playlistName];
        Song* song = songsMap[songTitle];
        if (playlist && song) {
            playlist->addSong(song);
        }
    }

    void removeSongFromPlaylist(const string& playlistName, const string& songTitle) {
        Playlist* playlist = playlistsMap[playlistName];
        Song* song = songsMap[songTitle];
        if (playlist && song) {
            playlist->removeSong(song);
        }
    }

    void shufflePlaylist(const string& playlistName) {
        Playlist* playlist = playlistsMap[playlistName];
        if (playlist) {
            playlist->shuffleSongs();
        }
    }

    void sortPlaylistByTitle(const string& playlistName) {
        Playlist* playlist = playlistsMap[playlistName];
        if (playlist) {
            playlist->sortSongsByTitle();
        }
    }

    void sortPlaylistByArtist(const string& playlistName) {
        Playlist* playlist = playlistsMap[playlistName];
        if (playlist) {
            playlist->sortSongsByArtist();
        }
    }

    Song* searchSong(const string& title) {
        return songsMap[title];
    }

    void mergePlaylists(const string& playlistName1, const string& playlistName2, const string& mergedPlaylistName) {
        Playlist* playlist1 = playlistsMap[playlistName1];
        Playlist* playlist2 = playlistsMap[playlistName2];
        if (playlist1 && playlist2) {
            // Create a new merged playlist
            Playlist* mergedPlaylist = new Playlist(mergedPlaylistName);

            // Add songs from playlist1 to the merged playlist
            for (Song* song : playlist1->songs) {
                mergedPlaylist->addSong(song);
            }

            // Add songs from playlist2 to the merged playlist
            for (Song* song : playlist2->songs) {
                mergedPlaylist->addSong(song);
            }

            // Add the merged playlist to the library
            playlistsMap[mergedPlaylistName] = mergedPlaylist;
        }
    }

    void markSongAsFavorite(const string& songTitle) {
        Song* song = songsMap[songTitle];
        if (song) {
            favoritesList.push_back(song);
        }
    }

    void printFavorites() {
        if (favoritesList.empty()) {
            cout << "No favorite songs found." << endl;
            return;
        }

        cout << "Favorite Songs:" << endl;
        for (const Song* song : favoritesList) {
            cout << song->title << " by " << song->artist << endl;
        }
    }
};

int main() {
    MusicLibrary musicLibrary;

    // Adding songs to the library
    musicLibrary.addSong("Song A", "Artist A");
    musicLibrary.addSong("Song B", "Artist B");
    musicLibrary.addSong("Song C", "Artist C");

    // Creating playlists and adding songs to them
    musicLibrary.createPlaylist("Playlist 1");
    musicLibrary.addSongToPlaylist("Playlist 1", "Song A");
    musicLibrary.addSongToPlaylist("Playlist 1", "Song B");

    musicLibrary.createPlaylist("Playlist 2");
    musicLibrary.addSongToPlaylist("Playlist 2", "Song C");

    // Shuffling and sorting playlists
    musicLibrary.shufflePlaylist("Playlist 1");
    musicLibrary.sortPlaylistByTitle("Playlist 2");

    // Search for a song
    Song* foundSong = musicLibrary.searchSong("Song A");
    if (foundSong) {
        cout << "Found song: " << foundSong->title << " by " << foundSong->artist << endl;
    } else {
        cout << "Song not found." << endl;
    }

    // Merge playlists
    musicLibrary.mergePlaylists("Playlist 1", "Playlist 2", "Merged Playlist");

    // Mark songs as favorites
    musicLibrary.markSongAsFavorite("Song A");
    musicLibrary.markSongAsFavorite("Song C");

    // Print favorites
    musicLibrary.printFavorites();

    return 0;
}
