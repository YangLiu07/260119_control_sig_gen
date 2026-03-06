#pragma once

#ifdef BODEBRIDGE_EXPORTS
#define BODE_API extern "C" __declspec(dllexport)
#else
#define BODE_API extern "C" __declspec(dllimport)
#endif

BODE_API int bode_connect();

BODE_API int bode_setup_sweep(
    double startFreq,
    double stopFreq,
    int points,
    int sweepType
);

BODE_API int bode_start();

BODE_API int bode_get_data(
    double* freq,
    double* mag,
    double* phase,
    int maxPoints
);

BODE_API void bode_disconnect();
