#include "ggwave/ggwave.h"

#include "ggwave-common.h"
#include "ggwave-common-sdl2.h"

#include <SDL.h>

#include <cstdio>
#include <string>

#include <mutex>
#include <thread>
#include <iostream>

int main(int argc, char** argv) {
    // Expects to be minimal: just send and receive, being quiet (so stdout and stdin can be piped to/from other programs).
    const auto argm          = parseCmdArguments(argc, argv);
    const int  captureId     = argm.count("c") == 0 ?  0 : std::stoi(argm.at("c"));
    const int  playbackId    = argm.count("p") == 0 ?  0 : std::stoi(argm.at("p"));
    const int  txProtocolId  = argm.count("t") == 0 ?  1 : std::stoi(argm.at("t"));
    const int  payloadLength = argm.count("l") == 0 ? -1 : std::stoi(argm.at("l"));
    const bool useDSS        = argm.count("d") >  0;
    const bool showHelp      = argm.count("h") >  0;

    if (showHelp){
        printf("Usage: %s [-h] [-cN] [-pN] [-tN] [-lN]\n", argv[0]);
        printf("    -cN - select capture device N\n");
        printf("    -pN - select playback device N\n");
        printf("    -tN - transmission protocol\n");
        printf("    -lN - fixed payload length of size N, N in [1, %d]\n", GGWave::kMaxLengthFixed);
        printf("    -d  - use Direct Sequence Spread (DSS)\n");
        printf("    -h  - show this help\n");
        printf("\n");
        return 0;
    }

    if (GGWave_init(playbackId, captureId, payloadLength, 0.0f, useDSS, true) == false) {
        fprintf(stderr, "Failed to initialize GGWave\n");
        return -1;
    }

    auto ggWave = GGWave_instance();

    std::mutex mutex;
    std::thread inputThread([&]() {
        while (true) {
            std::string input;
            fflush(stdout);
            getline(std::cin, input);
            if (!input.empty()) {
                std::lock_guard<std::mutex> lock(mutex);
                ggWave->init(input.size(), input.data(), GGWave::TxProtocolId(txProtocolId), 10);
            }
        }
    });

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        {
            std::lock_guard<std::mutex> lock(mutex);
            GGWave_mainLoop();
        }
    }

    inputThread.join();

    GGWave_deinit();

    SDL_CloseAudio();
    SDL_Quit();

    return 0;


}