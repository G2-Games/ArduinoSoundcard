#!/bin/bash
ffmpeg -hide_banner -loglevel error -stats -i "$2" -filter:a "volume=${3:-1}" -f u8 -acodec pcm_u8 -ar 44100 -ac 1 pipe:1 > $1
