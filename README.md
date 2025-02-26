# ggwave-quiet

For the original README, as well as further instructions, see [the original project](https://github.com/ggerganov/ggwave/). 

# Quieter GGWave
For the original README, see [the original project](https://github.com/ggerganov/ggwave/).

This fork adds `ggwave-quiet`, similar to `ggwave-cli`, but almost verboseless (except for errors): informational/debugging output messages have been suppressed to facilitate seamless piping to and from other programs via `stdout` and `stdin`.

The original `ggwave-cli` was kept. Everything else was removed. For the purposes of this fork, I don't need the ios bindings, the Python bindings, the GUI bin, etc.