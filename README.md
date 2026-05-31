# MinimalSawSynth

Minimal VST3 software synth using the Steinberg VST3 SDK in `../VST_SDK/Download/vst3sdk`.

It is intentionally small: one monophonic saw/ramp oscillator, MIDI note-on/off handling, stereo output, no envelope, no filter, and no parameters. VST3 audio buffers are floating point, so the oscillator is quantized to 16-bit integer values and converted back to float for the host.

Build:

```sh
cmake -S MinimalSawSynth -B MinimalSawSynth/build
cmake --build MinimalSawSynth/build
```

The built `.vst3` bundle will be under the CMake build output directory.
