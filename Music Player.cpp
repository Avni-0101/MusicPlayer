#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <random>
#include<bits/stdc++.h>

using namespace std;

class Song {                                                       // Song class representing a single song
public:
    string title;                            //title of the song
    string artist;                            //artist of the song

    Song(const string& _title, const string& _artist)        //Song constructor
        : title(_title), artist(_artist) {}
};

// Playlist class representing a collection of songs using linked list
class Playlist {
public:
    string name;                        //name of the playlist
    list<Song*> songs;                    //list of songs, STL List is used here which is a doubly linked list

    Playlist(const string& _name) : name(_name) {}            //Playlist constructor

    void addSong(Song* song) {                //an object which adds a new song to the playlist                 
        songs.push_back(song);
    }

    void removeSong(Song* song) {               //an object which removes an existing song from the playlist
        songs.remove(song);
    }

    void shuffleSongs() {                                           //this will shuffle the contents of the playlist 
        vector<Song*> songsVector(songs.begin(), songs.end());
        random_shuffle(songsVector.begin(), songsVector.end());
        songs.assign(songsVector.begin(), songsVector.end());
    }

    void sortSongsByTitle() {                                 //if the user wants to sort songs on the basis of title
        songs.sort([](const Song* a, const Song* b) {
            return a->title < b->title;                         //lambda function, compares the songs and provides a lexicographically sorted list
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
    list<Song*> likedSongsList;                                    //collection of fav songs in a list

    void addSong(const string& title, const string& artist) {        //adding a song in the songs map
        Song* song = new Song(title, artist);                        //with the given title and artist name
        songsMap[title] = song;                                      //title being the key to the song class
    }

    void removeSong(const string & title) {                 //a constant pointer to title of the song
        Song* song = songsMap[title];                       //"song" stores 'Song' taken from the songs map
        if (song) {                                         //check if present
            for (auto & pair : playlistsMap) {              //range based loop iterates over every playlist in playlistmap
                pair.second->removeSong(song);              //searches the 'song' and calls removeSong on it
            }
                                                            //the song is deleted from every playlist it was into

            songsMap.erase(title);                          //also erase the song from the songs map
            delete song;                                    //deleting the object to free memory
        }
    }

    void createPlaylist(const string& name) {               //creating a playlist, constant pointer brings the name from the user
        Playlist* playlist = new Playlist(name);            
        playlistsMap[name] = playlist;                      //storing the new playlist in the hash map
    }

    void addSongToPlaylist(const string& playlistName, const string& songTitle) {
        Playlist* playlist = playlistsMap[playlistName];            //storing the required PL in "playlist" 
        Song* song = songsMap[songTitle];                           //similarly the associated song is brought in "song"
        if (playlist && song) {                                 //if they both exist in the library maps
            playlist->addSong(song);                            //we call addSong functor for the "song" on the "playlist"
        }
    }

    void removeSongFromPlaylist(const string& playlistName, const string& songTitle) {
        Playlist* playlist = playlistsMap[playlistName];
        Song* song = songsMap[songTitle];
        if (playlist && song) {
            playlist->removeSong(song);                 //user can call removeSong in a similar way
        }
    }

    void shufflePlaylist(const string& playlistName) {
        Playlist* playlist = playlistsMap[playlistName];
        if (playlist) {
            playlist->shuffleSongs();                   //user can call shuffleSong in a similar way
        }
    }

    void sortPlaylistByTitle(const string& playlistName) {
        Playlist* playlist = playlistsMap[playlistName];
        if (playlist) {
            playlist->sortSongsByTitle();               //user can call sortSongsByTitle in a similar way
        }
    }

    void sortPlaylistByArtist(const string& playlistName) {
        Playlist* playlist = playlistsMap[playlistName];
        if (playlist) {
            playlist->sortSongsByArtist();              //user can call sortSongsByArtist in a similar way
        }
    }

    void searchSong(const string& title) {             //user can search for a specific song 
        Song* song = songsMap[title];
        if(song){
            cout << "Song found: " << song->title << " by " << song->artist << endl;
        }               
        else{
            cout<<"Song not found.";
        }          
    }

    void mergePlaylists(const string& playlistName1, const string& playlistName2, const string& mergedPlaylistName) {
        Playlist* playlist1 = playlistsMap[playlistName1];
        Playlist* playlist2 = playlistsMap[playlistName2];
        if (playlist1 && playlist2) {
            
            Playlist* mergedPlaylist = new Playlist(mergedPlaylistName);                // Create a new merged playlist

            for (Song* song : playlist1->songs) {
                mergedPlaylist->addSong(song);                        // Add songs from playlist1 to the merged playlist
            }

            for (Song* song : playlist2->songs) {
                mergedPlaylist->addSong(song);                       // Add songs from playlist2 to the merged playlist
            }

            playlistsMap[mergedPlaylistName] = mergedPlaylist;          // Add the merged playlist to the library
        }
    }

    void markSongAsFavorite(const string& songTitle) {          // user can mark a song as favorite
        Song* song = songsMap[songTitle];                                
        if (song) {                                             //check if the song exists in the song map
            likedSongsList.push_back(song);                      //pushing it to fav list
        }
    }


    void printFavorites() {                                     //user can print fav songs
        if (likedSongsList.empty()) {
            cout << "No favorite songs found." << endl;         //empty fav list output
            return;
        }

        cout << "Favorite Songs:" << endl;
        for (const Song* song : likedSongsList) {                        //iterating over the fav list
            cout << " # " << song->title << " --> " << song->artist << endl;      //to get title and artist of the respective song
        }
    }

    void printAllPlaylists(){
        if(playlistsMap.empty())
        {
            cout<<"NO playlists found."<< endl;
            return;
        }

        for(auto &AplayList : playlistsMap)                     //to interate over all the playlists present
        {
            cout << AplayList.first <<": \n";
            for(auto &Asong : AplayList.second->songs)              //to access the songs list under Aplaylist's playlist
            {
                cout << " # " << Asong->title << " --> " << Asong->artist << endl;      //to get title and artist of the respective song
            }
        }
    }
};

int main() {

    cout<<endl;
    cout<< "\n# WELCOME TO THE MUSIC LIBRARY #\n";
    cout<<endl;

////////////////////     all the operations that can be performed a listed first    //////////////////

    START:

    cout<<endl;
    cout<<"What's up for today?"<<endl;

    cout<<endl;
    cout<<"1. Search a song."<<endl;
    cout<<"2. Create a new playlist."<<endl;
    cout<<"3. Add song to Liked Songs."<<endl;
    cout<<"4. Add song to a playlist."<<endl;
    cout<<"5. Delete a song from everywhere."<<endl;
    cout<<"6. Delete a song from a playlist."<<endl;
    cout<<"7. Shuffle a playlist."<<endl;
    cout<<"8. Sort a playlist by title."<<endl;
    cout<<"9. Sort a playlist by artist."<<endl;
    cout<<"10. Merge two playlists."<<endl;
    cout<<"11. View my Liked Songs."<<endl;
    cout<<"12. View my collection."<<endl;
    cout<<endl;

    cout<<endl;
    cout<<"Enter a valid number you want to perform:  ";

///////////////////////   declaring of strings, objects starts   ///////////////////////

    MusicLibrary musicLibrary;

    int oper;       
    cin>>oper;
    cin.ignore();           //clears the newline character from the input buffer

    string inputSong;
    string inputArtist;
    string inputPlaylist;
    string inputPlaylist1;
    string inputPlaylist2;

    switch(oper)
    {
    case 1:
        //search a song
        cout<<"Enter the song name you want to search: \n";
        getline(cin,inputSong);
        musicLibrary.searchSong(inputSong);

        break;
    
    case 2:
        //new playlist
        cout<<"Enter name of the playlist you want to create: \n";
        getline(cin,inputPlaylist);
        musicLibrary.createPlaylist(inputPlaylist);

        break;

    case 3:
        //add song to liked songs list
        cout<<"Enter the song name you want to add: \n";
        getline(cin,inputSong);

        musicLibrary.markSongAsFavorite(inputSong);

        break;
    
    case 4:
        //add song to liked songs list
        cout<<"Enter the song name you want to add: \n";
        getline(cin,inputSong);
        cout<<"Who's voice is this? \n";
        getline(cin,inputArtist);
        cout<<"Which playlist you wanna add the above song into? \n";
        getline(cin,inputPlaylist);

        musicLibrary.addSong(inputSong,inputArtist);
        musicLibrary.addSongToPlaylist(inputSong,inputPlaylist);
        
        break;
    
    case 5:
        // Delete a song
        cout<<"Enter the song name you want to remove: \n";
        getline(cin,inputSong);

        musicLibrary.removeSong(inputSong);        

        break;
    
    case 6:
        //delete song from a playlist
        cout<<"Enter the song name you want to remove: \n";
        getline(cin,inputSong);
        cout<<"Enter the playlist you want to remove from: \n";
        getline(cin,inputPlaylist);

        musicLibrary.removeSongFromPlaylist(inputSong,inputPlaylist);

        break;
    
    case 7:
        //shuffle the songs list
        cout<<"Enter the playlist you want to shuffle: \n";
        getline(cin,inputPlaylist);

        musicLibrary.shufflePlaylist(inputPlaylist);

        break;
    
    case 8:
        //Sort a playlist by title of the song
        cout<<"Enter the playlist you want to sort by title: \n";
        getline(cin,inputPlaylist);

        musicLibrary.sortPlaylistByTitle(inputPlaylist);

        break;
    
    case 9:
        //Sort a playlist by artist
        cout<<"Enter the playlist you want to sort by artist: \n";
        getline(cin,inputPlaylist);

        musicLibrary.sortPlaylistByArtist(inputPlaylist);

        break;
    
    case 10:
        //merge playlists
        cout<<"Enter the 1st playlist: \n";
        getline(cin,inputPlaylist1);
        cout<<"Enter the 2nd playlist: \n";
        getline(cin,inputPlaylist2);

        cout<<"What will be the final playlist called? \n";
        getline(cin,inputPlaylist2);

        musicLibrary.mergePlaylists(inputPlaylist1,inputPlaylist2,inputPlaylist);

        break;
    
    case 11:
        //View my liked collection
        cout<<endl;
        musicLibrary.printFavorites();

        break;
    
    case 12:
        //View my collection
        cout<<endl;
        musicLibrary.printAllPlaylists();

        break;
    
    default:
    cout<<"Wrong Number :( \n";

        break;
    }

//////////////////////////    end of all the functions in switch case     //////////////////////////

    END:

    string exit;
    cout<<"\n\n:) To stay in the World of Music TYPE 'stay'  \n:( Enough for today, wanna exit? TYPE 'exit' \n\n";
    cin>>exit;

    if(exit == "stay")
    {
        goto START;
    }
    else if(exit == "exit")
    {
        cout<<"\nTHANK YOU for coming! SEE YOU SOON BBYE! \n";
    }
    else
    {
        goto END;
    }

    return 0;
}
