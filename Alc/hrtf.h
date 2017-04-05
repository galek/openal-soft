#ifndef ALC_HRTF_H
#define ALC_HRTF_H

#include "AL/al.h"
#include "AL/alc.h"

#include "alMain.h"
#include "alstring.h"


#define HRTFDELAY_BITS    (20)
#define HRTFDELAY_FRACONE (1<<HRTFDELAY_BITS)
#define HRTFDELAY_MASK    (HRTFDELAY_FRACONE-1)

/* The maximum number of virtual speakers used to generate HRTF coefficients
 * for decoding B-Format.
 */
#define HRTF_AMBI_MAX_CHANNELS 16


struct HrtfEntry;

struct Hrtf {
    ALuint sampleRate;
    ALsizei irSize;
    ALubyte evCount;

    const ALubyte *azCount;
    const ALushort *evOffset;
    const ALfloat *coeffs;
    const ALubyte *delays;
};


void FreeHrtfs(void);

vector_EnumeratedHrtf EnumerateHrtf(const_al_string devname);
void FreeHrtfList(vector_EnumeratedHrtf *list);
struct Hrtf *GetLoadedHrtf(struct HrtfEntry *entry);

void GetHrtfCoeffs(const struct Hrtf *Hrtf, ALfloat elevation, ALfloat azimuth, ALfloat spread, ALfloat (*coeffs)[2], ALsizei *delays);

/**
 * Produces HRTF filter coefficients for decoding B-Format, given a set of
 * virtual speaker positions and HF/LF matrices for decoding to them. The
 * returned coefficients are ordered and scaled according to the matrices.
 * Returns the maximum impulse-response length of the generated coefficients.
 */
ALsizei BuildBFormatHrtf(const struct Hrtf *Hrtf, DirectHrtfState *state, ALsizei NumChannels, const ALfloat (*restrict AmbiPoints)[2], const ALfloat (*restrict AmbiMatrix)[2][MAX_AMBI_COEFFS], ALsizei AmbiCount);

#endif /* ALC_HRTF_H */
