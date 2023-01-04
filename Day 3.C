
//      $$$$$$\   $$$$$$\  $$$$$$$\      $$$$$$$\                                               $$$$$$\       $$$$$$\                  $$\
//     $$ ___$$\ $$  __$$\ $$  ____|     $$  __$$\                                             $$  __$$\     $$  __$$\                 $$ |
//     \_/   $$ |$$ /  \__|$$ |          $$ |  $$ | $$$$$$\  $$\   $$\  $$$$$$$\      $$$$$$\  $$ /  \__|    $$ /  \__| $$$$$$\   $$$$$$$ | $$$$$$\
//        $$$$$ / $$$$$$$\  $$$$$$$\     $$ |  $$ | \____$$\ $$ |  $$ |$$  _____|    $$  __$$\ $$$$\         $$ |      $$  __$$\ $$  __$$ |$$  __$$\
//       \___$$\ $$  __$$\ \_____$$\     $$ |  $$ | $$$$$$$ |$$ |  $$ |\$$$$$$\      $$ /  $$ |$$  _|        $$ |      $$ /  $$ |$$ /  $$ |$$$$$$$$ |
//     $$\   $$ |$$ /  $$ |$$\   $$      $$ |  $$ |$$  __$$ |$$ |  $$ | \____$$\     $$ |  $$ |$$ |          $$ |  $$\ $$ |  $$ |$$ |  $$ |$$   ____|
//     \$$$$$$  | $$$$$$  |\$$$$$$  |    $$$$$$$  |\$$$$$$$ |\$$$$$$$ |$$$$$$$  |    \$$$$$$  |$$ |          \$$$$$$  |\$$$$$$  |\$$$$$$$ |\$$$$$$$\
//      \______/  \______/  \______/     \_______/  \_______| \____$$ |\_______/      \______/ \__|           \______/  \______/  \_______| \_______|
//                                                             $$\   $$ |
//                                                             \$$$$$$  |
//                                                              \______/
// Author : Saihaj Law
// Date : January 3rd
// Project : Simple Audio Player
#include <stdio.h>
#include <VLC/vlc.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <audio_file>\n", argv[0]);
        return 1;
    }

    char* audio_file = argv[1];

    libvlc_instance_t* vlc;
    libvlc_media_player_t* mp;
    libvlc_media_t* media;

    // Initialize libvlc
    vlc = libvlc_new(0, NULL);
    if (vlc == NULL) {
        fprintf(stderr, "Error initializing libvlc.\n");
        return 1;
    }

    // Load the audio file
    media = libvlc_media_new_path(vlc, audio_file);
    if (media == NULL) {
        fprintf(stderr, "Error loading media file.\n");
        return 1;
    }

    // Create a media player
    mp = libvlc_media_player_new_from_media(media);
    if (mp == NULL) {
        fprintf(stderr, "Error creating media player.\n");
        return 1;
    }

    // Play the audio file
    libvlc_media_player_play(mp);

    // Wait for the audio to finish playing
    while (libvlc_media_player_is_playing(mp)) {
        // Do nothing
    }

    // Clean up
    libvlc_media_player_release(mp);
    libvlc_media_release(media);
    libvlc_release(vlc);

    return 0;
}
